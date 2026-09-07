#!/usr/bin/env python3
"""Optimistic worker models from a cold DOOF_TIMINGS=1 emit.

Uses measured serial jobs; excludes contention, publication, and worker setup.
Full-module estimates also assume shared preparation caches remain as effective.
"""
import argparse
import json
import re
from pathlib import Path


def model(text):
    phases = {}
    for name, ms in re.findall(r'^\[timings\] (.+) ms=([\d.eE+-]+) count=\d+$', text, re.M):
        phases[name] = phases.get(name, 0.0) + float(ms)
    total = phases.get('command.total', 0)
    if total <= 0:
        raise ValueError('Missing positive command.total timing')
    if any(name.startswith('module.reuse:') for name in phases):
        raise ValueError('Use a cold emission: reused modules cannot model full jobs')
    prepare = {name[len('module.prepare:'):]: ms for name, ms in phases.items() if name.startswith('module.prepare:')}
    render = {name[len('module.render:'):]: ms for name, ms in phases.items() if name.startswith('module.render:')}
    if not render or prepare.keys() != render.keys():
        raise ValueError('Missing or unmatched per-module preparation/render timings')
    results = {'total_ms': total, 'modules': len(render), 'models': {}}
    for name, costs in [('render', render), ('prepare_and_render', {p: render[p] + prepare[p] for p in render})]:
        jobs = sorted(costs.values(), reverse=True)
        work = sum(jobs)
        residual = total - work
        if residual < -0.01:
            raise ValueError('Module times exceed command.total; use a serial emission')
        estimates = []
        for workers in (2, 4, 8):
            loads = [0.0] * workers
            for cost in jobs:
                index = min(range(workers), key=loads.__getitem__)
                loads[index] += cost
            predicted = residual + max(loads)
            estimates.append({'workers': workers, 'ideal_ms': residual + max(jobs[0], work / workers),
                              'scheduled_ms': predicted, 'saving_ms': total - predicted,
                              'overhead_budget_for_10_percent_ms': 0.9 * total - predicted})
        results['models'][name] = {'work_ms': work, 'serial_residual_ms': residual,
                                 'largest_job_ms': jobs[0], 'estimates': estimates}
    return results


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('logs', nargs='+', type=Path)
    args = parser.parse_args()
    print(json.dumps({str(path): model(path.read_text()) for path in args.logs}, indent=2))

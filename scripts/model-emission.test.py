#!/usr/bin/env python3
import importlib.util
from pathlib import Path
import unittest
import sys
sys.dont_write_bytecode = True

spec = importlib.util.spec_from_file_location('model_emission', Path(__file__).with_name('model-emission.py'))
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)


def log(total=100):
    return '\n'.join(f'[timings] {name} ms={value} count=1' for name, value in [
        ('command.total', total), ('compiler.emission', 80),
        ('module.prepare:/a with spaces.do', 10), ('module.prepare:/b.do', 10),
        ('module.render:/a with spaces.do', 40), ('module.render:/b.do', 20)])


class ModelTests(unittest.TestCase):
    def test_nested_phases_are_not_double_counted_and_largest_job_limits_speedup(self):
        result = module.model(log())['models']['prepare_and_render']
        self.assertEqual(result['work_ms'], 80)
        self.assertEqual(result['serial_residual_ms'], 20)
        self.assertEqual(result['estimates'][0]['scheduled_ms'], 70)
        self.assertEqual(result['estimates'][2]['scheduled_ms'], 70)
        self.assertEqual(result['estimates'][0]['overhead_budget_for_10_percent_ms'], 20)

    def test_rejects_missing_reused_and_inconsistent_measurements(self):
        for text in ['', log(10), log() + '\n[timings] module.reuse:/c ms=1 count=1',
                     log().replace('module.prepare:/b.do', 'other')]:
            with self.assertRaises(ValueError):
                module.model(text)


if __name__ == '__main__':
    unittest.main()

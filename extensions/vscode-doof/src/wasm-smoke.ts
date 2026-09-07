import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { Worker, isMainThread, parentPort, workerData } from 'node:worker_threads';
import { loadService } from './wasm-runtime.ts';
if (isMainThread) {
    const path = process.argv[2];
    if (!path)
        throw new Error('Usage: node src/wasm-smoke.ts /absolute/path/to/service.wasm');
    const worker = new Worker(new URL(import.meta.url), { workerData: path });
    worker.on('message', message => console.log(JSON.stringify(message)));
    worker.on('error', error => { console.error(error); process.exitCode = 1; });
    worker.on('exit', code => { if (code)
        process.exitCode = code; });
}
else {
    const started = performance.now();
    const service = await loadService(workerData);
    const startupMs = performance.now() - started;
    const sources = [
        { path: '/main.do', source: 'import { answer } from "./answer"\nfunction main(): int => answer()', physicalPath: '' },
        { path: '/answer.do', source: 'export function answer(): int => 42', physicalPath: '' },
    ];
    assert.deepEqual(service.call('diagnostics', { sources, entry: '/main.do' }), []);
    const mathSource = await readFile(new URL('../../../../doof-stdlib/math/index.do', import.meta.url), 'utf8');
    assert.deepEqual(service.call('diagnostics', {
        sources: [
            { path: '/main.do', source: 'import { clamp } from "std/math"\nfunction main(): int => clamp(42, 0, 100)', physicalPath: '' },
            { path: '/std/math/index.do', source: mathSource, physicalPath: '' },
        ], entry: '/main.do',
    }), []);
    const warmBytes = service.memoryBytes();
    const editsStarted = performance.now();
    for (let index = 0; index < 100; index++) {
        sources[1].source = index % 2 ? 'export function answer(): int => 42' : 'export function answer(): int => "wrong"';
        const diagnostics = service.call('diagnostics', { sources, entry: '/main.do' }) as unknown[];
        assert.equal(diagnostics.length > 0, index % 2 === 0);
    }
    parentPort!.postMessage({ startupMs, editMeanMs: (performance.now() - editsStarted) / 100, warmBytes, finalBytes: service.memoryBytes(), imports: service.imports });
}

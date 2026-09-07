import { parentPort, workerData } from 'node:worker_threads';
import { loadService } from './wasm-runtime.ts';
const service = await loadService(workerData);
parentPort!.on('message', ({ id, operation, parameters }) => {
    try {
        parentPort!.postMessage({ id, result: service.call(operation, parameters), memoryBytes: service.memoryBytes() });
    }
    catch (error) {
        if (error instanceof WebAssembly.RuntimeError)
            throw error;
        parentPort!.postMessage({ id, error: String(error) });
    }
});

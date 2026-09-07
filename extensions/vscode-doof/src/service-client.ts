import { Worker } from 'node:worker_threads';
export class ServiceClient {
    private worker: Worker;
    private sequence = 0;
    memoryBytes = 0;
    private pending = new Map<number, {
        resolve(value: any): void;
        reject(error: Error): void;
    }>();
    constructor(workerPath: string, wasmPath: string, private failed: (error: Error) => void) {
        this.worker = new Worker(workerPath, { workerData: wasmPath });
        this.worker.on('message', ({ id, result, error, memoryBytes }) => {
            this.memoryBytes = memoryBytes ?? this.memoryBytes;
            const callback = this.pending.get(id);
            this.pending.delete(id);
            if (error)
                callback?.reject(new Error(error));
            else
                callback?.resolve(result);
        });
        this.worker.on('error', error => this.fail(error));
        this.worker.on('exit', code => { if (code !== 0)
            this.fail(new Error(`Doof worker exited with code ${code}`)); });
    }
    private fail(error: Error) {
        for (const request of this.pending.values())
            request.reject(error);
        this.pending.clear();
        this.failed(error);
    }
    call<T = any>(operation: string, parameters: unknown): Promise<T> {
        return new Promise((resolve, reject) => {
            const id = ++this.sequence;
            this.pending.set(id, { resolve, reject });
            this.worker.postMessage({ id, operation, parameters });
        });
    }
    async dispose() {
        for (const request of this.pending.values())
            request.reject(new Error('Doof worker stopped'));
        this.pending.clear();
        this.worker.removeAllListeners();
        await this.worker.terminate();
    }
}

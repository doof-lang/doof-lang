import { readFile } from 'node:fs/promises';
import { WASI } from 'node:wasi';
/** Hosts the compiler's existing JSON reactor ABI; no language rules live here. */
export async function loadService(path: string) {
    const module = await WebAssembly.compile(await readFile(path));
    const imports = WebAssembly.Module.imports(module);
    const wasi = new WASI({ version: 'preview1', args: [], env: {}, preopens: {}, returnOnExit: true });
    const instance = await WebAssembly.instantiate(module, { wasi_snapshot_preview1: wasi.wasiImport, env: { emscripten_notify_memory_growth() { } } });
    wasi.initialize(instance);
    const exports = instance.exports as unknown as {
        memory: WebAssembly.Memory;
        malloc(size: number): number;
        free(pointer: number): void;
        doof_free(pointer: number): void;
        doof_initialize(): number;
        [key: string]: unknown;
    };
    function consume(pointer: number): unknown {
        if (!pointer)
            throw new Error('Doof Wasm returned a null response');
        try {
            const memory = new Uint8Array(exports.memory.buffer);
            const end = memory.indexOf(0, pointer);
            if (end < pointer)
                throw new Error('Doof Wasm returned unterminated JSON');
            const response = JSON.parse(new TextDecoder().decode(memory.subarray(pointer, end)));
            if (!response.ok)
                throw new Error(JSON.stringify(response.error));
            return response.value;
        }
        finally {
            exports.doof_free(pointer);
        }
    }
    consume(exports.doof_initialize());
    return {
        imports,
        memoryBytes: () => exports.memory.buffer.byteLength,
        call(name: string, parameters: unknown): unknown {
            const fn = exports[`doof_export_${name}`];
            if (typeof fn !== 'function')
                throw new Error(`Unknown Doof service operation: ${name}`);
            const bytes = new TextEncoder().encode(JSON.stringify(parameters));
            const pointer = exports.malloc(bytes.length + 1);
            if (!pointer)
                throw new Error('Doof Wasm allocation failed');
            try {
                const memory = new Uint8Array(exports.memory.buffer);
                memory.set(bytes, pointer);
                memory[pointer + bytes.length] = 0;
                return consume(fn(pointer));
            }
            finally {
                exports.free(pointer);
            }
        },
    };
}

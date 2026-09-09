// Native debug build boundary; no VS Code dependency so failures are testable.
import { spawn, type ChildProcess } from 'node:child_process';
import { mkdtemp, readFile, rm, access } from 'node:fs/promises';
import { tmpdir } from 'node:os';
import { join, isAbsolute } from 'node:path';
import { debugBuildProgress } from './debug-progress.ts';

export interface DebugLaunch {
    version: 1;
    executable: string;
    source: string;
    directory: string;
    symbols: string;
    arguments: string[];
}
export function parseDebugLaunch(text: string): DebugLaunch {
    const value = JSON.parse(text);
    if (!value || value.version !== 1)
        throw new Error('Unsupported Doof debug launch version. Select a current compiler with doof.compilerPath.');
    for (const key of ['executable', 'source', 'directory', 'symbols'])
        if (typeof value[key] !== 'string' || !isAbsolute(value[key]))
            throw new Error(`Invalid Doof debug launch ${key}: expected an absolute path.`);
    if (!Array.isArray(value.arguments) || !value.arguments.every((arg: unknown) => typeof arg === 'string'))
        throw new Error('Invalid Doof debug launch arguments: expected an array of strings.');
    return value;
}
export function stopDebugBuild(child: ChildProcess) {
    if (child.pid) {
        try { process.kill(-child.pid, 'SIGKILL'); } catch { /* Already exited. */ }
    }
}
export async function buildDebugLaunch(options: {
    compiler: string; entry: string; cwd: string; args: string[];
    signal: AbortSignal; output: (text: string) => void;
    children: Set<ChildProcess>;
    progress?: (message: string) => void;
}): Promise<DebugLaunch> {
    const temporary = await mkdtemp(join(tmpdir(), 'doof-vscode-debug-'));
    try {
        const descriptor = join(temporary, 'launch.json');
        let tail = '';
        const progress = debugBuildProgress(options.progress ?? (() => {}));
        const record = (data: Buffer | string) => {
            const text = data.toString();
            tail = (tail + text).slice(-16384);
            options.output(text);
        };
        const exit = await new Promise<number>((resolve, reject) => {
            if (options.signal.aborted) { reject(new Error('Doof debug build cancelled.')); return; }
            const child = spawn(options.compiler, ['debug', options.entry, '--launch-json', descriptor, '--', ...options.args],
                { cwd: options.cwd, detached: true, stdio: ['ignore', 'pipe', 'pipe'] });
            options.children.add(child);
            const cancel = () => stopDebugBuild(child);
            options.signal.addEventListener('abort', cancel, { once: true });
            child.stdout.setEncoding('utf8');
            child.stdout.on('data', (text: string) => { record(text); progress.write(text); });
            child.stderr.on('data', record);
            child.once('error', error => record(String(error)));
            child.once('close', code => {
                progress.end();
                options.children.delete(child);
                options.signal.removeEventListener('abort', cancel);
                resolve(code ?? -1);
            });
        });
        if (options.signal.aborted) throw new Error('Doof debug build cancelled.');
        if (exit !== 0)
            throw new Error(`Doof debug build failed (${exit}). ${tail.trim()}\nUse a compiler supporting debug --launch-json; configure doof.compilerPath.`);
        let launch: DebugLaunch;
        try { launch = parseDebugLaunch(await readFile(descriptor, 'utf8')); }
        catch (error) { throw new Error(`Could not read the Doof debug launch descriptor: ${String(error)}`); }
        await Promise.all([launch.executable, launch.source, launch.directory, launch.symbols].map(path => access(path)));
        return launch;
    } finally { await rm(temporary, { recursive: true, force: true }); }
}

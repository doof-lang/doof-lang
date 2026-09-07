import assert from 'node:assert/strict';
import { fork } from 'node:child_process';
import { readFile, writeFile, mkdir } from 'node:fs/promises';
import { resolve, join } from 'node:path';
import { IPCMessageReader, IPCMessageWriter, createMessageConnection } from 'vscode-jsonrpc/node.js';
import { URI } from 'vscode-uri';
const root = resolve(import.meta.dirname, '../../..');
const directory = join(root, 'build/editor-lsp-fixture');
await mkdir(directory, { recursive: true });
await writeFile(join(directory, 'doof.json'), JSON.stringify({ name: 'editor-test', build: { entry: 'main.do' } }));
const original = 'import { value } from "./dep"\nfunction main(): int => value()';
await writeFile(join(directory, 'main.do'), original);
await writeFile(join(directory, 'dep.do'), 'export function value(): int => 42');
const child = fork(join(root, 'extensions/vscode-doof/out/server.cjs'), ['--node-ipc'], { silent: true });
child.stderr?.on('data', data => process.stderr.write(data));
const connection = createMessageConnection(new IPCMessageReader(child), new IPCMessageWriter(child));
const diagnostics = new Map<string, any[]>();
connection.onNotification('textDocument/publishDiagnostics', params => diagnostics.set(params.uri, params.diagnostics));
connection.onNotification('window/logMessage', params => { if (params.type === 1)
    console.error(params.message); });
connection.onRequest('workspace/semanticTokens/refresh', () => null);
connection.onRequest('workspace/configuration', () => [{ indentSize: 2 }]);
connection.listen();
async function eventually<T>(operation: () => Promise<T>, accept: (value: T) => boolean) { const deadline = Date.now() + 30000; while (true) {
    const result = await operation();
    if (accept(result))
        return result;
    if (Date.now() > deadline)
        throw new Error('LSP timeout');
    await new Promise(resolve => setTimeout(resolve, 50));
} }
const uri = URI.file(join(directory, 'main.do')).toString();
const dep = URI.file(join(directory, 'dep.do')).toString();
try {
    await connection.sendRequest('initialize', { processId: process.pid, capabilities: { workspace: { workspaceFolders: true, configuration: true, semanticTokens: { refreshSupport: true } } }, workspaceFolders: [{ uri: URI.file(directory).toString(), name: 'fixture' }] });
    await connection.sendNotification('initialized', {});
    await connection.sendNotification('textDocument/didOpen', { textDocument: { uri, languageId: 'doof', version: 1, text: original } });
    const hover = await eventually(() => connection.sendRequest<any>('textDocument/hover', { textDocument: { uri }, position: { line: 1, character: 25 } }), value => !!value);
    assert.match(hover.contents.value, /int/);
    await connection.sendNotification('textDocument/didOpen', { textDocument: { uri: dep, languageId: 'doof', version: 1, text: 'export function value(): string => "wrong"' } });
    await eventually(async () => diagnostics.get(uri), value => !!value?.length);
    await connection.sendNotification('textDocument/didChange', { textDocument: { uri: dep, version: 2 }, contentChanges: [{ text: 'export function value(): int => 42' }] });
    await eventually(async () => diagnostics.get(uri), value => !!value && value.length === 0);
    // Several rapid updates must publish the final version and clear obsolete errors.
    for (let version = 3; version <= 12; version++)
        await connection.sendNotification('textDocument/didChange', { textDocument: { uri: dep, version }, contentChanges: [{ text: version === 12 ? 'export function value(): int => 42' : 'export function value(): int => "wrong"' }] });
    await eventually(() => connection.sendRequest<any[]>('doof/serviceStatus'), value => value.length === 1 && value[0].publishedVersion === value[0].version);
    assert.deepEqual(diagnostics.get(uri), []);
    const rename = await connection.sendRequest<any>('textDocument/rename', { textDocument: { uri }, position: { line: 1, character: 25 }, newName: 'answer' });
    assert.ok(rename.documentChanges.some((change: any) => change.textDocument.uri === dep && change.textDocument.version === 12));
    const tests = await connection.sendRequest<any>('doof/discoverTests', { source: 'export function testOne(): none {}', module: join(directory, 'sample.test.do'), root: directory });
    assert.equal(tests.tests[0].id, 'sample.test.do::testOne');
    const unfinished = 'function main(): int => cla';
    await connection.sendNotification('textDocument/didChange',{textDocument:{uri,version:2},contentChanges:[{text:unfinished}]});
    const completions = await eventually(()=>connection.sendRequest<any>('textDocument/completion',{textDocument:{uri},position:{line:0,character:unfinished.length}}),value=>value?.items.some((item:any)=>item.label==='clamp'&&item.data?.target==='/std/math/index.do'));
    const clamp = completions.items.find((item:any)=>item.label==='clamp'&&item.data?.target==='/std/math/index.do');
    const resolved = await connection.sendRequest<any>('completionItem/resolve',clamp);
    assert.equal(resolved.additionalTextEdits[0].newText,'import { clamp } from "std/math"\n');
    await connection.sendNotification('textDocument/didChange',{textDocument:{uri,version:3},contentChanges:[{text:resolved.additionalTextEdits[0].newText+'function main(): int => clamp(42, 0, 100)'}]});
    await eventually(async()=>diagnostics.get(uri),value=>!!value&&value.length===0);
    console.log('LSP: selecting a stdlib auto-import produces a clean checked program.');
    if (process.argv.includes('--benchmark')) {
        const compilerUri = URI.file(join(root, 'src/frontend.do')).toString();
        const compilerSource = await readFile(join(root, 'src/frontend.do'), 'utf8');
        const prefix = compilerSource.slice(0, compilerSource.indexOf('analyzer.serialParsing'));
        const position = { line: prefix.split('\n').length - 1, character: prefix.length - prefix.lastIndexOf('\n') - 1 };
        await connection.sendNotification('textDocument/didOpen', { textDocument: { uri: compilerUri, languageId: 'doof', version: 1, text: compilerSource } });
        await eventually(() => connection.sendRequest<any[]>('doof/serviceStatus'), states => states.some(state => state.root === root && !state.running && state.publishedVersion === state.version));
        await connection.sendNotification('textDocument/didChange', { textDocument: { uri: compilerUri, version: 2 }, contentChanges: [{ text: compilerSource + '\n// interactive benchmark\n' }] });
        await eventually(() => connection.sendRequest<any[]>('doof/serviceStatus'), states => states.some(state => state.root === root && state.running));
        const times: number[] = [];
        for (let i = 0; i < 20; i++) {
            const start = performance.now();
            const value = await connection.sendRequest<any>('textDocument/hover', { textDocument: { uri: compilerUri }, position });
            assert.ok(value);
            times.push(performance.now() - start);
        }
        times.sort((a, b) => a - b);
        console.log(JSON.stringify({ compilerGraphConcurrentHoverP50: times[10], compilerGraphConcurrentHoverP95: times[19] }));
        assert.ok(times[19] < 300, 'A background compiler check must not block warm hover requests');
        await eventually(() => connection.sendRequest<any[]>('doof/serviceStatus'), states => states.some(state => state.root === root && !state.running && state.publishedVersion === state.version));
        let maximumBytes = 0;
        for (let version = 3; version <= 8; version++) {
            await connection.sendNotification('textDocument/didChange', { textDocument: { uri: compilerUri, version }, contentChanges: [{ text: compilerSource + '\n// memory probe ' + version + '\n' }] });
            await new Promise(resolve => setTimeout(resolve, 210));
            const states = await eventually(() => connection.sendRequest<any[]>('doof/serviceStatus'), states => states.some(state => state.root === root && !state.running && state.publishedVersion === state.version));
            maximumBytes = Math.max(maximumBytes, states.find(state => state.root === root).memoryBytes);
        }
        console.log(JSON.stringify({ repeatedCompilerEditMaximumWorkerBytes: maximumBytes }));
        assert.ok(maximumBytes < 768 * 1024 * 1024, 'Worker recycling must bound repeated compiler edits');
    }
    console.log('LSP: unsaved cross-file types, coalescing, obsolete diagnostics, versioned rename, and bundled test discovery passed.');
}
finally {
    await connection.sendRequest('shutdown');
    await connection.sendNotification('exit');
    connection.dispose();
    child.kill();
}

import assert from 'node:assert/strict';
import { readFile, writeFile, mkdir } from 'node:fs/promises';
import { execFileSync } from 'node:child_process';
import { resolve, join } from 'node:path';
import { loadService } from '../src/wasm-runtime.ts';
const root = resolve(import.meta.dirname, '../../..');
const directory = join(root, 'build/editor-parity');
await mkdir(directory, { recursive: true });
execFileSync(join(root, 'dist/doof'), ['build', join(root, 'tools/editor-parity.do'), '-o', directory], { cwd: root, stdio: 'inherit' });
const service = await loadService(join(root, 'extensions/vscode-doof/artifacts/service.wasm'));
const stdlib = JSON.parse(await readFile(join(root, 'extensions/vscode-doof/artifacts/stdlib.json'), 'utf8'));
const fixtures = [
    { source: 'function main(): int {\r\n  title := "😀"\r\n  answer := 42\r\n  return answer\r\n}', operation: 'rename', needle: 'return answer', adjust: 8, text: 'value' },
    { source: 'import { clamp } from "std/math"\nfunction main(): int => clamp(42, 0, 100)', operation: 'hover', needle: 'clamp(42', adjust: 1, text: '' },
    { source: 'import { value as local } from "./dep"\nfunction main(): int => local()', operation: 'rename', needle: 'local()', adjust: 1, text: 'renamed' },
    { source: 'function main(): none {\n  title := "Doof"\n  title.\n}', operation: 'completion', needle: 'title.', adjust: 6, text: '' },
    { source: 'function main(): int => "wrong"', operation: 'symbols', needle: '', adjust: 0, text: '' },
];
for (const [index, fixture] of fixtures.entries()) {
    const sources = [{ path: '/main.do', source: fixture.source, physicalPath: '' }, { path: '/dep.do', source: 'export function value(): int => 42', physicalPath: '' }, ...stdlib];
    const offset = Buffer.byteLength(fixture.source.slice(0, fixture.source.indexOf(fixture.needle) + fixture.adjust));
    const input = { sources, entry: '/main.do', module: '/main.do', operation: fixture.operation, offset, text: fixture.text };
    const path = join(directory, 'fixture.json');
    await writeFile(path, JSON.stringify(input));
    const native = JSON.parse(execFileSync(join(directory, process.platform === 'win32' ? 'doof.exe' : 'doof'), [path], { encoding: 'utf8' }));
    const diagnostics = service.call('analyze', input), response = service.call('query', input), strict = service.call('diagnostics', input);
    assert.deepEqual({ diagnostics, response, strict }, native, `Native/Wasm parity fixture ${index}`);
}
console.log(`Native/Wasm diagnostics and query parity: ${fixtures.length} fixtures passed.`);

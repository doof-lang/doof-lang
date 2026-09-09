import test from 'node:test';
import assert from 'node:assert/strict';
import { mkdtemp, writeFile, chmod, rm, access } from 'node:fs/promises';
import { tmpdir } from 'node:os';
import { join } from 'node:path';
import { buildDebugLaunch, parseDebugLaunch } from './native-debug.ts';

const launch = { version: 1, executable: '/tmp/工具 app', source: '/tmp/main.do', directory: '/tmp', symbols: '/tmp/app.dSYM', arguments: ['a b', '工具', '--flag'] };
test('launch descriptor preserves absolute paths and argument boundaries', () => {
    assert.deepEqual(parseDebugLaunch(JSON.stringify(launch)), launch);
});
test('launch descriptor diagnoses incompatible and malformed compiler output', () => {
    assert.throws(() => parseDebugLaunch('{'), SyntaxError);
    for (const value of [null, {}, { ...launch, version: 2 }]) assert.throws(() => parseDebugLaunch(JSON.stringify(value)), /version/);
    for (const key of ['executable', 'source', 'directory', 'symbols']) {
        assert.throws(() => parseDebugLaunch(JSON.stringify({ ...launch, [key]: 'relative' })), /absolute/);
        assert.throws(() => parseDebugLaunch(JSON.stringify({ ...launch, [key]: null })), /absolute/);
    }
    for (const args of ['one', [1], null]) assert.throws(() => parseDebugLaunch(JSON.stringify({ ...launch, arguments: args })), /arguments/);
});
const quote = (value: string) => "'" + value.replaceAll("'", "'\\''") + "'";
test('native build uses the compiler contract, drains output and cleans its descriptor', { skip: process.platform === 'win32' }, async () => {
    const root = await mkdtemp(join(tmpdir(), 'doof debug 工具 '));
    try {
        const compiler = join(root, 'compiler');
        const fixture = { ...launch, executable: root, source: root, directory: root, symbols: root };
        await writeFile(join(root, 'fixture.json'), JSON.stringify(fixture));
        const captured = join(root, 'descriptor-path');
        await writeFile(compiler, `#!/bin/sh\nset -eu\n[ "$1" = debug ]\n[ "$2" = 'entry space' ]\n[ "$3" = --launch-json ]\nprintf '%s' "$4" > ${quote(captured)}\ncp ${quote(join(root, 'fixture.json'))} "$4"\n[ "$5" = -- ]\n[ "$6" = 'a b' ]\n[ "$7" = 工具 ]\nprintf 'build output\\n'\nprintf 'compiler warning\\n' >&2\n`);
        await chmod(compiler, 0o755);
        const children = new Set<import('node:child_process').ChildProcess>();
        let output = '';
        const result = await buildDebugLaunch({ compiler, entry: 'entry space', cwd: root, args: ['a b', '工具'], signal: new AbortController().signal, children, output: text => output += text });
        assert.deepEqual(result, fixture);
        assert.match(output, /build output/); assert.match(output, /compiler warning/);
        assert.equal(children.size, 0);
        const { readFile } = await import('node:fs/promises');
        await assert.rejects(access(await readFile(captured, 'utf8')));
    } finally { await rm(root, { recursive: true, force: true }); }
});
test('native build reports compiler failure and missing launch output', { skip: process.platform === 'win32' }, async () => {
    const options = { entry: '.', cwd: tmpdir(), args: [], signal: new AbortController().signal, children: new Set<import('node:child_process').ChildProcess>(), output: () => {} };
    await assert.rejects(buildDebugLaunch({ ...options, compiler: '/usr/bin/false' }), /doof.compilerPath/);
    await assert.rejects(buildDebugLaunch({ ...options, compiler: '/usr/bin/true' }), /launch descriptor/);
    await assert.rejects(buildDebugLaunch({ ...options, compiler: '/does-not-exist/doof' }), /ENOENT/);
    assert.equal(options.children.size, 0);
});
test('cancelled native build kills its process group and removes child ownership', { skip: process.platform === 'win32' }, async () => {
    const root = await mkdtemp(join(tmpdir(), 'doof-debug-cancel-'));
    try {
        const compiler = join(root, 'compiler');
        await writeFile(compiler, '#!/bin/sh\nsleep 60 &\nprintf "ready\\n"\nwait\n');
        await chmod(compiler, 0o755);
        const abort = new AbortController();
        const children = new Set<import('node:child_process').ChildProcess>();
        await assert.rejects(buildDebugLaunch({ compiler, entry: '.', cwd: root, args: [], signal: abort.signal, children,
            output: text => { if (text.includes('ready')) abort.abort(); } }), /cancelled/);
        assert.equal(children.size, 0);
        await assert.rejects(buildDebugLaunch({ compiler, entry: '.', cwd: root, args: [], signal: abort.signal, children, output: () => {} }), /cancelled/);
    } finally { await rm(root, { recursive: true, force: true }); }
});

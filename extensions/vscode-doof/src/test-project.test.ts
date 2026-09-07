import { test } from 'node:test';
import assert from 'node:assert/strict';
import { mkdtemp, mkdir, writeFile, rm } from 'node:fs/promises';
import { tmpdir } from 'node:os';
import { join } from 'node:path';
import { testProjectRoot, testCommandFailure } from './test-project.ts';
test('nested project roots match native traversal boundaries', async () => {
    const root = await mkdtemp(join(tmpdir(), 'doof-project-test-'));
    try {
        await mkdir(join(root, 'tools/nested/src'), { recursive: true });
        await writeFile(join(root, 'tools/nested/doof.json'), '{}');
        const cache = new Map<string, string>();
        assert.equal(await testProjectRoot(join(root, 'tools/nested/src/a.test.do'), root, cache), join(root, 'tools/nested'));
        assert.equal(await testProjectRoot(join(root, 'tools/nested/b.test.do'), root, cache), join(root, 'tools/nested'));
        assert.equal(await testProjectRoot(join(root, 'tools/c.test.do'), root, cache), root);
        assert.equal(await testProjectRoot(join(root, 'a.test.do'), root, cache), root);
    } finally { await rm(root, { recursive: true, force: true }); }
});
test('early compiler failure retains the actionable diagnostic', () => {
    assert.match(testCommandFailure(1, 'error: Selected test no longer exists: nested::testA\n'), /Selected test no longer exists/);
    assert.match(testCommandFailure(1, ''), /no test report or diagnostic/);
});

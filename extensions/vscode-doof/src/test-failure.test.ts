import { test } from 'node:test';
import assert from 'node:assert/strict';
import { mkdtemp, writeFile, rm } from 'node:fs/promises';
import { tmpdir } from 'node:os';
import { join } from 'node:path';
import { presentTestFailure } from './test-failure.ts';
test('assertion failures navigate to verified source and retain a short summary', async () => {
    const root = await mkdtemp(join(tmpdir(), 'doof-failure-'));
    try {
        await writeFile(join(root, 'é sample.test.do'), 'function example() {\r\n  Assert.isFalse(true)\r\n}\r\n');
        const result = await presentTestFailure('log before failure\r\npanic: Assertion failed: expected value to be false at é sample.test:2\r\n', 1, root);
        assert.deepEqual(result, { summary: 'Assertion failed: expected value to be false', path: join(root, 'é sample.test.do'), line: 1, column: 2 });
        assert.equal((await presentTestFailure('panic: failure at é sample.test.do:2:3', 1, root)).column, 2);
        assert.equal((await presentTestFailure('panic: failure at missing.test:2', 1, root)).summary, 'failure at missing.test:2');
        assert.equal((await presentTestFailure('panic: failure at é sample.test:99', 1, root)).path, undefined);
    } finally { await rm(root, { recursive: true, force: true }); }
});
test('plain panics and empty output remain readable without fabricated locations', async () => {
    assert.deepEqual(await presentTestFailure('panic: custom failure\n', 1, '/tmp'), { summary: 'custom failure' });
    assert.deepEqual(await presentTestFailure('', 7, '/tmp'), { summary: 'Test exited with code 7' });
});

import { test } from 'node:test';
import assert from 'node:assert/strict';
import { byteOffset, positionAt } from './positions.ts';
test('UTF-16 positions round trip through UTF-8 with CRLF and astral characters', () => {
    const text = 'a😀é\r\n  name';
    for (const position of [{ line: 0, character: 1 }, { line: 0, character: 3 }, { line: 1, character: 2 }, { line: 1, character: 6 }]) {
        assert.deepEqual(positionAt(text, byteOffset(text, position)), position);
    }
});

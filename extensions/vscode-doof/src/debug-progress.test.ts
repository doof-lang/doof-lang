import test from 'node:test';
import assert from 'node:assert/strict';
import { debugBuildProgress } from './debug-progress.ts';

test('debug progress handles split chunks, terminal updates and final unterminated output', () => {
    const messages: string[] = [];
    const progress = debugBuildProgress(message => messages.push(message));
    for (const chunk of ['Compil', 'ing 2 files\n[--] 0/', '2\r[#-] 1/2\r[##] 2/2']) progress.write(chunk);
    progress.end();
    assert.deepEqual(messages, ['Compiling 2 source files…', 'Compiling source files: 0 of 2…',
        'Compiling source files: 1 of 2…', 'Finishing build and preparing debug symbols…']);
});

test('debug progress ignores diagnostics, invalid counts and duplicate updates', () => {
    const messages: string[] = [];
    const progress = debugBuildProgress(message => messages.push(message));
    progress.write('warning: example\n[--] 4/2\n[--] 0/0\nCompiling 1 file\r\nCompiling 1 file\n');
    progress.end();
    assert.deepEqual(messages, ['Compiling 1 source file…']);
});

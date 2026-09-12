import test from 'node:test';
import assert from 'node:assert/strict';
import { debuggerPreRunCommands } from './debug-configuration.ts';

test('debugger runs without stopping at entry and stops only on unhandled panics by default', () => {
    assert.deepEqual(debuggerPreRunCommands([], undefined, undefined, undefined), [
        'breakpoint set --name doof::unhandled_panic',
    ]);
    assert.deepEqual(debuggerPreRunCommands(['settings set target.x true'], false, false, false), [
        'settings set target.x true',
    ]);
});

test('debugger can still stop at entry when explicitly requested', () => {
    assert.deepEqual(debuggerPreRunCommands([], true, true, false), [
        'breakpoint set --name doof_main --one-shot true',
        'breakpoint set --name doof::unhandled_panic',
    ]);
});

test('debugger can stop on every panic when explicitly requested', () => {
    assert.deepEqual(debuggerPreRunCommands([], false, true, true), [
        'breakpoint set --name doof::panic',
    ]);
});

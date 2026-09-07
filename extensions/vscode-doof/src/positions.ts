import type { Position, Range } from 'vscode-languageserver/node.js';
/** Compiler offsets count UTF-8 bytes; VS Code positions count UTF-16 units. */
export function byteOffset(text: string, position: Position): number {
    let offset = 0;
    for (let line = 0; line < position.line; line++) {
        const next = text.indexOf('\n', offset);
        if (next < 0)
            return Buffer.byteLength(text);
        offset = next + 1;
    }
    const end = text.indexOf('\n', offset);
    return Buffer.byteLength(text.slice(0, Math.min(offset + position.character, end < 0 ? text.length : end)));
}
export function positionAt(text: string, byte: number): Position {
    const prefix = Buffer.from(text).subarray(0, Math.max(0, byte)).toString('utf8');
    const lines = prefix.split('\n');
    return { line: lines.length - 1, character: lines.at(-1)!.length };
}
export function rangeAt(text: string, start: number, end: number): Range {
    return { start: positionAt(text, start), end: positionAt(text, Math.max(start, end)) };
}

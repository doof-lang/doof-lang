import { readFile } from 'node:fs/promises';
import { resolve, isAbsolute } from 'node:path';

export interface FailurePresentation {
    summary: string;
    path?: string;
    line?: number;
    column?: number;
}

// Status always comes from the structured report. This only presents the
// optional source location carried in today's assertion diagnostic text.
export async function presentTestFailure(output: string, exitCode: number, root: string): Promise<FailurePresentation> {
    const lines = output.replace(/\u001b\[[0-9;]*m/g, '').split(/\r?\n/).filter(line => line.trim());
    const diagnostic = lines.find(line => line.startsWith('panic: ')) ?? lines[0] ?? `Test exited with code ${exitCode}`;
    const text = diagnostic.replace(/^panic:\s*/, '');
    const match = /^(.*) at (.+?):([1-9][0-9]*)(?::([1-9][0-9]*))?$/.exec(text);
    if (!match) return { summary: text };
    const path = isAbsolute(match[2]) ? match[2] : resolve(root, match[2]);
    for (const candidate of path.endsWith('.do') ? [path] : [path + '.do', path]) {
        try {
            const source = await readFile(candidate, 'utf8');
            const sourceLines = source.split(/\r?\n/);
            const line = Number(match[3]) - 1;
            if (line >= sourceLines.length) continue;
            const column = match[4] ? Number(match[4]) - 1 : sourceLines[line].search(/\S|$/);
            if (column > sourceLines[line].length) continue;
            return { summary: match[1], path: candidate, line, column };
        } catch { /* Keep the original diagnostic when source cannot be located. */ }
    }
    return { summary: text };
}

import { stat } from 'node:fs/promises';
import { dirname, join } from 'node:path';

// The native runner stops traversal at nested doof.json boundaries. Use the
// nearest boundary inside the workspace as both discovery root and run target.
export async function testProjectRoot(file: string, workspace: string, cache = new Map<string, string>()): Promise<string> {
    const directory = dirname(file);
    const known = cache.get(directory);
    if (known) return known;
    if (directory === workspace || dirname(directory) === directory) return workspace;
    let root: string;
    try { await stat(join(directory, 'doof.json')); root = directory; }
    catch (error) {
        if ((error as NodeJS.ErrnoException).code !== 'ENOENT') throw error;
        root = await testProjectRoot(directory, workspace, cache);
    }
    cache.set(directory, root);
    return root;
}

export function testCommandFailure(exit: number, output: string): string {
    const diagnostic = output.trim();
    return `Doof could not complete the test run (exit ${exit}).\n` +
        (diagnostic || 'The compiler produced no test report or diagnostic output. See the Doof output channel.');
}

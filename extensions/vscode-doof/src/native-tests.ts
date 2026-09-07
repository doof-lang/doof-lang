import { writeFile } from 'node:fs/promises';
import { execFile } from 'node:child_process';
import { promisify } from 'node:util';
const execute = promisify(execFile);

// Probe an empty directory with --list: validate the complete protocol without
// compiling or executing workspace code, and without parsing human test output.
export async function verifyTestCompiler(compiler: string, cwd: string, emptyDirectory: string) {
    try {
        await writeFile(`${emptyDirectory}/probe-selection.json`, '[]');
        const { stdout } = await execute(compiler, ['test', emptyDirectory, '--list', '--json',
            '--selection-json', `${emptyDirectory}/probe-selection.json`, '--report-json', `${emptyDirectory}/probe.json`],
            { cwd, timeout: 5000, maxBuffer: 1024 * 1024 });
        const discovery: unknown = JSON.parse(stdout);
        if (!Array.isArray(discovery) || discovery.length !== 0)
            throw new Error('Unexpected response to the structured test protocol probe.');
    } catch (error) {
        const code = (error as NodeJS.ErrnoException).code;
        const reason = code === 'ENOENT' ? 'was not found' : 'does not support the required structured test protocol, or could not start';
        throw new Error(`Native Doof compiler ${JSON.stringify(compiler)} ${reason}. ` +
            'Set doof.compilerPath to a current compiler using “Doof: Select Native Compiler”, then rerun the tests. ' +
            'Test Explorer requires --selection-json, --json, and --report-json. Editor intelligence remains available.');
    }
}

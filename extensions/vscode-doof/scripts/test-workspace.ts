import { runTests } from '@vscode/test-electron';
import { resolve, join } from 'node:path';
import { build } from 'esbuild';
const extension = resolve(import.meta.dirname, '..');
const root = resolve(extension, '../..');
const workspace = process.env.DOOF_TEST_WORKSPACE;
if (!workspace) throw new Error('Set DOOF_TEST_WORKSPACE to a trusted saved project whose tests may be executed.');
await build({ entryPoints: [join(extension, 'src/workspace-tests.ts')], outfile: join(extension, 'out/workspace-tests.cjs'), bundle: true, platform: 'node', format: 'cjs', external: ['vscode'] });
await runTests({ vscodeExecutablePath: process.env.VSCODE_EXECUTABLE,
    extensionDevelopmentPath: join(root, 'build/vscode-packaged-smoke/extension'),
    extensionTestsPath: join(extension, 'out/workspace-tests.cjs'),
    launchArgs: [workspace, '--user-data-dir=' + join(root, 'build/vscode-workspace-test/profile'), '--extensions-dir=' + join(root, 'build/vscode-workspace-test/extensions'), '--disable-extensions', '--disable-workspace-trust', '--skip-welcome', '--skip-release-notes'], reuseMachineInstall: false });

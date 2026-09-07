import * as vscode from 'vscode';
import { LanguageClient, TransportKind } from 'vscode-languageclient/node.js';
import { spawn, execFile, type ChildProcess } from 'node:child_process';
import { readFile, writeFile, mkdtemp, rm } from 'node:fs/promises';
import { tmpdir } from 'node:os';
import { join, dirname, basename, relative } from 'node:path';
import { promisify } from 'node:util';
import { rangeAt } from './positions.ts';
import { presentTestFailure } from './test-failure.ts';
import { testProjectRoot, testCommandFailure } from './test-project.ts';
import { verifyTestCompiler } from './native-tests.ts';
let client: LanguageClient | undefined;
const execute = promisify(execFile);
export async function activate(context: vscode.ExtensionContext) {
    const children = new Set<ChildProcess>();
    function terminate(child: ChildProcess) {
        if (!child.pid)
            return;
        if (process.platform === 'win32')
            spawn('taskkill', ['/PID', String(child.pid), '/T', '/F'], { windowsHide: true });
        else {
            try {
                process.kill(-child.pid, 'SIGKILL');
            }
            catch { /* Already exited. */ }
        }
    }
    context.subscriptions.push({ dispose: () => { for (const child of children)
            terminate(child); } });
    const output = vscode.window.createOutputChannel('Doof');
    context.subscriptions.push(output);
    const server = context.asAbsolutePath('out/server.cjs');
    client = new LanguageClient('doof', 'Doof', { run: { module: server, transport: TransportKind.ipc }, debug: { module: server, transport: TransportKind.ipc } }, { documentSelector: [{ scheme: 'file', language: 'doof' }], outputChannel: output, synchronize: { fileEvents: [vscode.workspace.createFileSystemWatcher('**/*.do'), vscode.workspace.createFileSystemWatcher('**/doof.json')] } });
    await client.start();
    context.subscriptions.push({ dispose: () => void client?.stop() });
    context.subscriptions.push(vscode.commands.registerCommand('doof.restart', async () => { await client?.stop(); await client?.start(); }));
    const compiler = (uri?: vscode.Uri) => vscode.workspace.getConfiguration('doof', uri).get<string>('compilerPath', 'doof');
    context.subscriptions.push(vscode.commands.registerCommand('doof.selectCompiler', async () => {
        const chosen = await vscode.window.showOpenDialog({ canSelectMany: false, canSelectFolders: false, openLabel: 'Use Doof compiler' });
        if (!chosen?.[0]) return;
        await vscode.workspace.getConfiguration('doof', vscode.window.activeTextEditor?.document.uri)
            .update('compilerPath', chosen[0].fsPath, vscode.ConfigurationTarget.Workspace);
        void vscode.window.showInformationMessage('Native Doof compiler selected. Rerun your tests to use it.');
    }));
    async function savedAndTrusted() {
        if (!vscode.workspace.isTrusted) {
            void vscode.window.showInformationMessage('Trust this workspace to build, run, or test Doof code.');
            return false;
        }
        if (vscode.workspace.textDocuments.some(document => (document.languageId === 'doof' || basename(document.fileName) === 'doof.json') && document.isDirty)) {
            const answer = await vscode.window.showInformationMessage('Save Doof files before running the native compiler?', 'Save and continue');
            if (answer !== 'Save and continue')
                return false;
            for (const document of vscode.workspace.textDocuments)
                if ((document.languageId === 'doof' || basename(document.fileName) === 'doof.json') && document.isDirty && !await document.save())
                    return false;
        }
        return true;
    }
    for (const command of ['build', 'run'])
        context.subscriptions.push(vscode.commands.registerCommand(`doof.${command}`, async () => {
            if (!await savedAndTrusted())
                return;
            const file = vscode.window.activeTextEditor?.document.uri;
            const folder = file ? vscode.workspace.getWorkspaceFolder(file) : vscode.workspace.workspaceFolders?.[0];
            const target = folder?.uri.fsPath ?? file?.fsPath;
            if (!target)
                return;
            const task = new vscode.Task({ type: 'doof', command }, folder ?? vscode.TaskScope.Workspace, `Doof ${command}`, 'Doof', new vscode.ProcessExecution(compiler(file), [command, target], { cwd: folder?.uri.fsPath ?? dirname(target) }));
            await vscode.tasks.executeTask(task);
        }));
    const bundled = JSON.parse(await readFile(context.asAbsolutePath('artifacts/service-version.json'), 'utf8'));
    const status = vscode.window.createStatusBarItem(vscode.StatusBarAlignment.Right, 20);
    status.text = `Doof ${bundled.version}`;
    status.tooltip = 'Bundled compiler language service. Click to compare native and bundled toolchain versions.';
    status.command = 'doof.versions';
    const showStatus = () => vscode.window.activeTextEditor?.document.languageId === 'doof' ? status.show() : status.hide();
    context.subscriptions.push(status, vscode.window.onDidChangeActiveTextEditor(showStatus));
    showStatus();
    context.subscriptions.push(vscode.commands.registerCommand('doof.versions', async () => {
        let native = vscode.workspace.isTrusted ? 'not available' : 'workspace trust required to query the native compiler';
        try {
            if (vscode.workspace.isTrusted) {
                const { stdout, stderr } = await execute(compiler(vscode.window.activeTextEditor?.document.uri), ['--version'], { timeout: 5000 });
                native = (stdout || stderr).trim();
            }
        }
        catch {
            native = `${compiler()} (version unavailable; select a current Doof compiler in settings)`;
        }
        output.appendLine(`Bundled service: ${bundled.version}, ${bundled.revision}, SHA-256 ${bundled.wasmSha256 ?? 'unavailable'}`);
        output.appendLine(`Native compiler: ${native}`);
        const nativeVersion = native.match(/\b\d+\.\d+\.\d+\b/)?.[0];
        const mismatch = nativeVersion && nativeVersion !== bundled.version;
        status.text = `Doof ${bundled.version}${mismatch ? ' $(warning)' : ''}`;
        status.tooltip = `Bundled: ${bundled.version}; native: ${native}`;
        if (mismatch) output.appendLine('Version mismatch: native workflows and editor intelligence use different compiler versions.');
        output.show();
    }));
    const controller = vscode.tests.createTestController('doof', 'Doof tests');
    context.subscriptions.push(controller);
    const testTargets = new WeakMap<vscode.TestItem, { root: string; id: string }>();
    let discovering: Promise<void> | undefined;
    function discover(): Promise<void> {
        return discovering ??= discoverNow().finally(() => { discovering = undefined; });
    }
    async function discoverNow() {
        controller.items.replace([]);
        const roots = new Map<string, string>();
        const projects = new Map<string, vscode.TestItem>();
        for (const folder of vscode.workspace.workspaceFolders ?? []) {
            const files = await vscode.workspace.findFiles(new vscode.RelativePattern(folder, '**/*.test.do'), '**/{node_modules,build,dist,bootstrap}/**');
            for (const uri of files) {
                try {
                    const root = await testProjectRoot(uri.fsPath, folder.uri.fsPath, roots);
                    const source = await readFile(uri.fsPath, 'utf8');
                    const discovery = await client!.sendRequest<{
                        tests: {
                            id: string;
                            name: string;
                            modulePath: string;
                            startOffset: number;
                            endOffset: number;
                        }[];
                        errors: string[];
                    }>('doof/discoverTests', { source, module: uri.fsPath, root });
                    for (const error of discovery.errors)
                        output.appendLine(`${uri.fsPath}: ${error}`);
                    for (const test of discovery.tests) {
                        const item = controller.createTestItem(vscode.Uri.file(root).toString() + '#' + test.id, test.name, uri);
                        testTargets.set(item, { root, id: test.id });
                        const range = rangeAt(source, test.startOffset, test.endOffset);
                        item.range = new vscode.Range(range.start.line, range.start.character, range.end.line, range.end.character);
                        let project = projects.get(root);
                        if (!project) {
                            project = controller.createTestItem(vscode.Uri.file(root).toString() + '#project', basename(root), vscode.Uri.file(root));
                            project.description = relative(folder.uri.fsPath, root) || 'Workspace project';
                            projects.set(root, project);
                            controller.items.add(project);
                        }
                        const fileId = uri.toString() + '#file';
                        let file = project.children.get(fileId);
                        if (!file) {
                            file = controller.createTestItem(fileId, relative(root, uri.fsPath), uri);
                            project.children.add(file);
                        }
                        file.children.add(item);
                    }
                }
                catch (error) {
                    output.appendLine(`Test discovery: ${String(error)}`);
                }
            }
        }
    }
    controller.resolveHandler = async () => discover();
    controller.refreshHandler = async () => discover();
    let running = Promise.resolve();
    const profile = controller.createRunProfile('Run', vscode.TestRunProfileKind.Run, (request, cancellationToken) => {
        running = running.then(async () => {
            if (cancellationToken.isCancellationRequested || !await savedAndTrusted())
                return;
            const run = controller.createTestRun(request);
            const selected: vscode.TestItem[] = [];
            const visited = new Set<string>();
            const collect = (item: vscode.TestItem) => {
                for (let ancestor: vscode.TestItem | undefined = item; ancestor; ancestor = ancestor.parent)
                    if (request.exclude?.includes(ancestor)) return;
                if (visited.has(item.id)) return;
                visited.add(item.id);
                if (testTargets.has(item)) selected.push(item);
                else item.children.forEach(collect);
            };
            if (request.include) request.include.forEach(collect);
            else controller.items.forEach(collect);
            const temporary = await mkdtemp(join(tmpdir(), 'doof-vscode-'));
            const groups = new Map<string, { root: string; executable: string; items: vscode.TestItem[] }>();
            for (const item of selected) {
                if (request.exclude?.includes(item)) continue;
                const folder = item.uri ? vscode.workspace.getWorkspaceFolder(item.uri) : undefined;
                if (!folder) { run.errored(item, new vscode.TestMessage('The test is outside an open workspace.')); continue; }
                const target = testTargets.get(item);
                if (!target) { run.errored(item, new vscode.TestMessage('Refresh test discovery before running this test.')); continue; }
                const executable = compiler(item.uri);
                const key = JSON.stringify([executable, target.root]);
                if (!groups.has(key)) groups.set(key, { root: target.root, executable, items: [] });
                groups.get(key)!.items.push(item);
                run.enqueued(item);
            }
            try {
                for (const { root, executable, items } of groups.values()) {
                    if (run.token.isCancellationRequested || cancellationToken.isCancellationRequested) {
                        for (const item of items) run.skipped(item);
                        continue;
                    }
                    try { await verifyTestCompiler(executable, root, temporary); }
                    catch (error) {
                        const message = error instanceof Error ? error.message : String(error);
                        for (const item of items) run.errored(item, new vscode.TestMessage(message));
                        output.appendLine(message);
                        void vscode.window.showErrorMessage(message, 'Select compiler').then(action => {
                            if (action) void vscode.commands.executeCommand('doof.selectCompiler');
                        });
                        continue;
                    }
                    const idOf = (item: vscode.TestItem) => testTargets.get(item)!.id;
                    const selection = join(temporary, 'selected.json');
                    const report = join(temporary, 'result.json');
                    await writeFile(selection, JSON.stringify(items.map(idOf)));
                    await rm(report, { force: true });
                    for (const item of items) run.started(item);
                    let commandOutput = '';
                    const recordOutput = (data: Buffer | string) => {
                        const text = data.toString();
                        commandOutput = (commandOutput + text).slice(-65536);
                        run.appendOutput(text.replace(/\r?\n/g, '\r\n'));
                        output.append(text);
                    };
                    const exit = await new Promise<number>((resolve) => {
                        if (run.token.isCancellationRequested || cancellationToken.isCancellationRequested) { resolve(-1); return; }
                        run.appendOutput(`Doof: ${executable} — ${items.length} selected tests (${root})\r\n`);
                        const child = spawn(executable, ['test', root, '--selection-json', selection, '--report-json', report], { cwd: root, detached: process.platform !== 'win32', stdio: ['ignore', 'pipe', 'pipe'] });
                        child.stdout.on('data', recordOutput);
                        child.stderr.on('data', recordOutput);
                        children.add(child);
                        const cancellation = run.token.onCancellationRequested(() => terminate(child));
                        const queuedCancellation = cancellationToken.onCancellationRequested(() => terminate(child));
                        child.once('close', () => { children.delete(child); queuedCancellation.dispose(); cancellation.dispose(); });
                        child.on('error', error => { recordOutput(String(error) + '\n'); resolve(-1); });
                        child.on('close', code => resolve(code ?? -1));
                    });
                    if (run.token.isCancellationRequested || cancellationToken.isCancellationRequested) {
                        for (const item of items) run.skipped(item);
                        continue;
                    }
                    try {
                        const reports = JSON.parse(await readFile(report, 'utf8')) as { id: string; exitCode: number; output: string }[];
                        const byId = new Map(reports.map(result => [result.id, result]));
                        for (const item of items) {
                            const result = byId.get(idOf(item));
                            if (!result) run.errored(item, new vscode.TestMessage(testCommandFailure(exit, commandOutput)));
                            else if (result.exitCode === 0) run.passed(item);
                            else {
                                const failure = await presentTestFailure(result.output, result.exitCode, root);
                                const details = new vscode.MarkdownString();
                                details.appendText(failure.summary);
                                const message = new vscode.TestMessage(details);
                                if (failure.path !== undefined && failure.line !== undefined) {
                                    const uri = vscode.Uri.file(failure.path);
                                    const position = new vscode.Position(failure.line, failure.column ?? 0);
                                    message.location = new vscode.Location(uri, position);
                                    message.stackTrace = [new vscode.TestMessageStackFrame(item.label, uri, position)];
                                }
                                if (result.output) run.appendOutput(result.output.replace(/\r?\n/g, '\r\n') + '\r\n', message.location, item);
                                run.failed(item, message);
                            }
                        }
                    } catch (error) {
                        for (const item of items) run.errored(item, new vscode.TestMessage(testCommandFailure(exit, commandOutput)));
                    }
                }
            }
            finally {
                await rm(temporary, { recursive: true, force: true });
                run.end();
            }
        }).catch(error => output.appendLine(String(error)));
        return running;
    }, true);
    context.subscriptions.push(vscode.workspace.onDidSaveTextDocument(document => { if (document.fileName.endsWith('.test.do'))
        void discover(); }));
    if (context.extensionMode === vscode.ExtensionMode.Test) return { controller, profile };
}
export async function deactivate() { await client?.stop(); }

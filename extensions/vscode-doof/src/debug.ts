import * as vscode from 'vscode';
import { execFile, type ChildProcess } from 'node:child_process';
import { promisify } from 'node:util';
import { dirname, resolve } from 'node:path';
import { buildDebugLaunch, stopDebugBuild } from './native-debug.ts';
import { debuggerPreRunCommands } from './debug-configuration.ts';
const execute = promisify(execFile);

export function registerDebugger(context: vscode.ExtensionContext, output: vscode.OutputChannel,
    compiler: (uri?: vscode.Uri) => string, savedAndTrusted: () => Promise<boolean>) {
    const children = new Set<ChildProcess>();
    context.subscriptions.push({ dispose: () => { for (const child of children) stopDebugBuild(child); } });
    const initial = (entry = '${workspaceFolder}') => ({
        type: 'doof', request: 'launch', name: 'Debug Doof', entry, args: [], stopOnEntry: false,
        stopOnUnhandledPanic: true, stopOnPanic: false,
    });
    const provider: vscode.DebugConfigurationProvider = {
        provideDebugConfigurations: () => [initial()],
        resolveDebugConfiguration(_folder, configuration) {
            if (!configuration.type && !configuration.request && !configuration.name)
                return initial(_folder ? '${workspaceFolder}' : '${file}');
            return configuration;
        },
        async resolveDebugConfigurationWithSubstitutedVariables(folder, configuration, token) {
            if (!await savedAndTrusted()) return undefined;
            try {
                if (process.platform !== 'darwin') throw new Error('Doof debugging currently requires macOS and Xcode LLDB-DAP.');
                if (configuration.request !== 'launch') throw new Error('Doof debugging currently supports launch requests only.');
                const file = vscode.window.activeTextEditor?.document.uri;
                const base = folder?.uri.fsPath ?? (file?.scheme === 'file' ? dirname(file.fsPath) : undefined);
                if (!base) throw new Error('Open a Doof project or a local .do file before debugging.');
                if (configuration.entry !== undefined && (typeof configuration.entry !== 'string' || !configuration.entry))
                    throw new Error('Doof debug entry must be a nonempty file or package path.');
                if (configuration.cwd !== undefined && typeof configuration.cwd !== 'string') throw new Error('Doof debug cwd must be a path.');
                const entry = resolve(base, configuration.entry ?? base);
                const args = configuration.args ?? [];
                if (!Array.isArray(args) || !args.every(arg => typeof arg === 'string')) throw new Error('Doof debug args must be an array of strings.');
                for (const key of ['stopOnEntry', 'stopOnUnhandledPanic', 'stopOnPanic'])
                    if (configuration[key] !== undefined && typeof configuration[key] !== 'boolean') throw new Error(`Doof debug ${key} must be a boolean.`);
                const commands = configuration.preRunCommands ?? [];
                if (!Array.isArray(commands) || !commands.every(command => typeof command === 'string')) throw new Error('preRunCommands must be an array of LLDB commands.');
                if (configuration.env !== undefined && (!configuration.env || typeof configuration.env !== 'object' || Array.isArray(configuration.env) || !Object.values(configuration.env).every(value => typeof value === 'string')))
                    throw new Error('Doof debug env must map environment names to strings.');
                // Detect missing Xcode tools before starting an expensive native build.
                const { stdout } = await execute('/usr/bin/xcrun', ['--find', 'lldb-dap'], { timeout: 5000 });
                if (!stdout.trim()) throw new Error('Xcode did not provide lldb-dap.');
                const launch = await vscode.window.withProgress({ location: vscode.ProgressLocation.Notification, title: 'Preparing Doof debug session', cancellable: true }, async (progress, cancellation) => {
                    progress.report({ message: 'Checking sources and build cache…' });
                    const abort = new AbortController();
                    const subscriptions = [token?.onCancellationRequested(() => abort.abort()), cancellation.onCancellationRequested(() => abort.abort())];
                    if (token?.isCancellationRequested || cancellation.isCancellationRequested) abort.abort();
                    try {
                        return await buildDebugLaunch({ compiler: compiler(vscode.Uri.file(entry)), entry, cwd: base, args,
                            signal: abort.signal, output: text => output.append(text), children,
                            progress: message => progress.report({ message }) });
                    } finally { subscriptions.forEach(subscription => subscription?.dispose()); }
                });
                if (token?.isCancellationRequested) return undefined;
                return {
                    ...configuration, program: launch.executable, cwd: configuration.cwd ? resolve(base, configuration.cwd) : launch.directory,
                    args: launch.arguments, stopOnEntry: false, disableASLR: false,
                    // LLDB-DAP applies source breakpoints before configurationDone releases the target.
                    preRunCommands: debuggerPreRunCommands(commands, configuration.stopOnEntry,
                        configuration.stopOnUnhandledPanic, configuration.stopOnPanic),
                };
            } catch (error) {
                output.appendLine(String(error)); output.show(true);
                void vscode.window.showErrorMessage(`Cannot debug Doof: ${error instanceof Error ? error.message : String(error)}`);
                return undefined;
            }
        },
    };
    context.subscriptions.push(vscode.debug.registerDebugConfigurationProvider('doof', provider));
    context.subscriptions.push(vscode.debug.registerDebugAdapterDescriptorFactory('doof', {
        async createDebugAdapterDescriptor() {
            if (!vscode.workspace.isTrusted) throw new Error('Trust the workspace before debugging Doof code.');
            return new vscode.DebugAdapterExecutable('/usr/bin/xcrun', ['lldb-dap']);
        },
    }));
    context.subscriptions.push(vscode.commands.registerCommand('doof.debug', async () => {
        const file = vscode.window.activeTextEditor?.document.uri;
        const folder = file ? vscode.workspace.getWorkspaceFolder(file) : vscode.workspace.workspaceFolders?.[0];
        if (!folder && file?.scheme !== 'file') { void vscode.window.showErrorMessage('Open a local Doof project or file before debugging.'); return; }
        await vscode.debug.startDebugging(folder, initial(folder?.uri.fsPath ?? file!.fsPath));
    }));
}

import * as vscode from 'vscode';
import assert from 'node:assert/strict';

async function until(predicate: () => boolean, message: string) {
    const deadline = Date.now() + 30000;
    while (!predicate()) {
        if (Date.now() > deadline) throw new Error(message);
        await new Promise(resolve => setTimeout(resolve, 25));
    }
}
export async function testDebugger(root: vscode.Uri) {
    if (process.platform !== 'darwin' || !process.env.DOOF_TEST_COMPILER) return;
    const uri = vscode.Uri.joinPath(root, 'debug-smoke.do');
    await vscode.workspace.fs.writeFile(uri, Buffer.from('import { env } from "std/os"\nfunction main(arguments: string[]): none {\n  let count = 41\n  count += 1\n  println(count)\n  for argument of arguments { println(argument) }\n  println(try! env("DOOF_VSCODE_DEBUG_SMOKE"))\n}\n'));
    const breakpoints = [new vscode.SourceBreakpoint(new vscode.Location(uri, new vscode.Position(3, 0)))];
    const stops: { threadId: number }[] = [];
    let output = '';
    let breakpointReplies = 0;
    let terminated = false;
    let targetPid: number | undefined;
    const tracker = vscode.debug.registerDebugAdapterTrackerFactory('doof', {
        createDebugAdapterTracker: () => ({
            onDidSendMessage: message => {
                if (message.type === 'response' && message.command === 'setBreakpoints' && message.success) breakpointReplies++;
                if (message.type !== 'event') return;
                if (message.event === 'stopped') stops.push(message.body);
                if (message.event === 'process') targetPid = message.body.systemProcessId;
                if (message.event === 'output') output += message.body.output;
                if (message.event === 'terminated') terminated = true;
            },
        }),
    });
    const folder = vscode.workspace.getWorkspaceFolder(root)!;
    let session: vscode.DebugSession | undefined;
    try {
        vscode.debug.addBreakpoints(breakpoints);
        assert.equal(await vscode.debug.startDebugging(folder, {
            type: 'doof', request: 'launch', name: 'Doof debugger smoke', entry: uri.fsPath,
            args: ['argument space', '工具'], env: { DOOF_VSCODE_DEBUG_SMOKE: 'vscode-environment' },
        }), true);
        session = vscode.debug.activeDebugSession;
        assert.ok(session);
        await until(() => breakpointReplies > 0, 'Source breakpoint was not installed before launch');
        await until(() => stops.length === 1, 'Source breakpoint was not the first stop');
        const frames = await session.customRequest('stackTrace', { threadId: stops[0].threadId });
        const frame = frames.stackFrames.find((item: any) => item.source?.path === uri.fsPath);
        assert.ok(frame); assert.equal(frame.line, 4);
        const scopes = await session.customRequest('scopes', { frameId: frame.id });
        let variables: any[] = [];
        for (const scope of scopes.scopes.filter((scope: any) => scope.name === 'Locals')) {
            const response = await session.customRequest('variables', { variablesReference: scope.variablesReference });
            variables.push(...response.variables);
        }
        assert.ok(variables.some(variable => variable.name === 'count' && variable.value === '41'), 'Doof local count should be inspectable');
        await session.customRequest('next', { threadId: stops[0].threadId });
        await until(() => stops.length === 2, 'Step over did not stop');
        await session.customRequest('continue', { threadId: stops[1].threadId });
        await until(() => terminated, 'Debug target did not exit');
        assert.match(output, /42/); assert.match(output, /argument space/); assert.match(output, /工具/); assert.match(output, /vscode-environment/);
        await until(() => vscode.debug.activeDebugSession === undefined, 'VS Code did not finish the debug session');
        stops.length = 0; terminated = false; targetPid = undefined;
        const panicUri = vscode.Uri.joinPath(root, 'debug-panic.do');
        await vscode.workspace.fs.writeFile(panicUri, Buffer.from('function main(): none { panic("vscode panic") }\n'));
        assert.equal(await vscode.debug.startDebugging(folder, {
            type: 'doof', request: 'launch', name: 'Doof panic smoke', entry: panicUri.fsPath, stopOnEntry: false,
        }), true);
        session = vscode.debug.activeDebugSession;
        assert.ok(session);
        await until(() => stops.length === 1, 'Doof panic did not stop');
        const panicStack = await session.customRequest('stackTrace', { threadId: stops[0].threadId });
        assert.match(panicStack.stackFrames[0].name, /doof::panic/);
        await vscode.debug.stopDebugging(session);
        await until(() => vscode.debug.activeDebugSession !== session, 'Stopping did not end the panic session');
        assert.ok(targetPid, 'LLDB must report its launched process');
        await until(() => { try { process.kill(targetPid!, 0); return false; } catch { return true; } }, 'Stopping left the target process alive');
    } finally {
        if (session && vscode.debug.activeDebugSession === session) await vscode.debug.stopDebugging(session);
        vscode.debug.removeBreakpoints(breakpoints);
        tracker.dispose();
    }
    console.log('Doof VS Code debugger: startup/source breakpoints, locals, stepping, args/environment/output, panic and stop passed.');
}

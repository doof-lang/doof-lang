import * as vscode from 'vscode';
import assert from 'node:assert/strict';
async function eventually<T>(operation: () => PromiseLike<T>, accept: (value: T) => boolean): Promise<T> {
    const until = Date.now() + 20000;
    while (true) {
        const value = await operation();
        if (accept(value))
            return value;
        if (Date.now() > until)
            throw new Error('Timed out waiting for the Doof language service');
        await new Promise(resolve => setTimeout(resolve, 100));
    }
}
export async function run() {
    const extension = vscode.extensions.getExtension('doof-lang.doof-language');
    assert.ok(extension);
    const api = await extension.activate() as { controller: vscode.TestController; profile: vscode.TestRunProfile };
    const root = vscode.workspace.workspaceFolders![0].uri;
    const uri = vscode.Uri.joinPath(root, 'main.do');
    const document = await vscode.workspace.openTextDocument(uri);
    await vscode.window.showTextDocument(document);
    const position = new vscode.Position(2, 4);
    const hovers = await eventually(() => vscode.commands.executeCommand<vscode.Hover[]>('vscode.executeHoverProvider', uri, position), value => !!value?.length);
    assert.match(hovers.flatMap(hover => hover.contents.map(content => typeof content === 'string' ? content : content.value)).join('\n'), /string/);
    const definitions = await vscode.commands.executeCommand<(vscode.Location | vscode.LocationLink)[]>('vscode.executeDefinitionProvider', uri, position);
    assert.ok(definitions.length);
    const completionStarted = Date.now();
    const completions = await vscode.commands.executeCommand<vscode.CompletionList>('vscode.executeCompletionItemProvider', uri, new vscode.Position(2, 7), '.');
    assert.ok(completions.items.some(item => (typeof item.label === 'string' ? item.label : item.label.label) === 'substring'));
    assert.ok(Date.now() - completionStarted < 1000, 'Warm completion should not stall for a full graph check');
    const rename = await vscode.commands.executeCommand<vscode.WorkspaceEdit>('vscode.executeDocumentRenameProvider', uri, position, 'title');
    assert.ok(rename.size > 0);
    const formatting = await vscode.commands.executeCommand<vscode.TextEdit[]>('vscode.executeFormatDocumentProvider', uri, { tabSize: 2, insertSpaces: true });
    assert.ok(Array.isArray(formatting));
    const edit = new vscode.WorkspaceEdit();
    edit.replace(uri, new vscode.Range(3, 9, 3, 11), '"wrong"');
    await vscode.workspace.applyEdit(edit);
    await eventually(async () => vscode.languages.getDiagnostics(uri), value => value.some(diagnostic => diagnostic.severity === vscode.DiagnosticSeverity.Error));
    await vscode.commands.executeCommand('doof.restart');
    await eventually(async () => vscode.languages.getDiagnostics(uri), value => value.some(diagnostic => diagnostic.severity === vscode.DiagnosticSeverity.Error));
    const autoUri = vscode.Uri.joinPath(root, 'auto-import.do');
    const unfinished = 'function example(): int => cla';
    await vscode.workspace.fs.writeFile(autoUri, Buffer.from(unfinished));
    const autoDocument = await vscode.workspace.openTextDocument(autoUri);
    await vscode.window.showTextDocument(autoDocument);
    const autoCompletion = await eventually(() => vscode.commands.executeCommand<vscode.CompletionList>('vscode.executeCompletionItemProvider', autoUri, new vscode.Position(0, unfinished.length), undefined, 100), value => !!value?.items.some(item => (typeof item.label === 'string' ? item.label : item.label.label) === 'clamp' && !!item.additionalTextEdits?.some(edit => edit.newText.includes('\"std/math\"'))));
    const clamp = autoCompletion.items.find(item => (typeof item.label === 'string' ? item.label : item.label.label) === 'clamp' && !!item.additionalTextEdits?.some(edit => edit.newText.includes('\"std/math\"')))!;
    assert.match(clamp.additionalTextEdits![0].newText, /std\/math/);
    const autoEdit = new vscode.WorkspaceEdit();
    for (const additional of clamp.additionalTextEdits!) autoEdit.replace(autoUri, additional.range, additional.newText);
    autoEdit.replace(autoUri, new vscode.Range(0, unfinished.length - 3, 0, unfinished.length), 'clamp(42, 0, 100)');
    await vscode.workspace.applyEdit(autoEdit);
    await eventually(async () => vscode.languages.getDiagnostics(autoUri), value => value.length === 0);
    await autoDocument.save();
    // Native tasks run saved fixture source through the configured executable.
    const restore = new vscode.WorkspaceEdit();
    restore.replace(uri, new vscode.Range(3, 9, 3, 16), '42');
    await vscode.workspace.applyEdit(restore);
    await document.save();
    await vscode.workspace.getConfiguration('doof').update('compilerPath', process.env.DOOF_TEST_COMPILER, vscode.ConfigurationTarget.Workspace);
    if (process.env.DOOF_TEST_COMPILER) {
        // Invoke the registered Test Explorer profile, preserving real VS Code
        // TestRun objects while observing the reported terminal states.
        await api.controller.resolveHandler!(undefined);
        const items: vscode.TestItem[] = [];
        const collectTests = (item: vscode.TestItem) => { if (item.children.size) item.children.forEach(collectTests); else items.push(item); };
        api.controller.items.forEach(collectTests);
        const selected = items.find(item => item.label === 'testSelected');
        const failing = items.find(item => item.label === 'testSelectedOther');
        const nested = items.find(item => item.label === 'testNested');
        assert.ok(nested);
        assert.equal(nested.parent!.parent!.label, 'nested');
        assert.ok(selected); assert.ok(failing);
        let invocations = 0;
        const outcomes: { id: string; state: string; message?: string; location?: vscode.Location }[] = [];
        const createRun = api.controller.createTestRun.bind(api.controller);
        api.controller.createTestRun = (...args) => {
            const run = createRun(...args);
            const appendOutput = run.appendOutput.bind(run);
            run.appendOutput = (...args) => { if (args[0].startsWith('Doof: ')) invocations++; appendOutput(...args); };
            for (const state of ['passed', 'failed', 'errored'] as const) {
                const original = run[state].bind(run) as (...args: any[]) => void;
                (run as any)[state] = (item: vscode.TestItem, ...rest: any[]) => {
                    outcomes.push({ id: item.id, state, message: rest[0]?.message, location: rest[0]?.location });
                    original(item, ...rest);
                };
            }
            return run;
        };
        const cancellation = new vscode.CancellationTokenSource();
        const runItem = async (item: vscode.TestItem) => {
            outcomes.length = 0;
            await api.profile.runHandler(new vscode.TestRunRequest([item], undefined, api.profile), cancellation.token);
            assert.equal(outcomes.length, 1, 'Exact selection must report only the requested test');
            assert.equal(outcomes[0].id, item.id);
            return outcomes[0];
        };
        try {
            if (process.env.DOOF_TEST_OLD_COMPILER) {
                await vscode.workspace.getConfiguration('doof').update('compilerPath', process.env.DOOF_TEST_OLD_COMPILER, vscode.ConfigurationTarget.Workspace);
                const incompatible = await runItem(selected);
                assert.equal(incompatible.state, 'errored');
                assert.match(incompatible.message!, /doof.compilerPath/);
                assert.match(incompatible.message!, /structured test protocol/);
            }
            await vscode.workspace.getConfiguration('doof').update('compilerPath', process.env.DOOF_TEST_COMPILER, vscode.ConfigurationTarget.Workspace);
            assert.equal((await runItem(selected)).state, 'passed');
            assert.ok(failing.range?.contains(new vscode.Position(3, 3)), 'Test range must include its body');
            const testEditor = await vscode.window.showTextDocument(await vscode.workspace.openTextDocument(failing.uri!));
            testEditor.selection = new vscode.Selection(3, 3, 3, 3);
            outcomes.length = 0; invocations = 0;
            await vscode.commands.executeCommand('testing.runAtCursor');
            await eventually(async () => outcomes, values => values.length === 1);
            assert.equal(outcomes[0].id, failing.id, 'VS Code cursor command must select the containing test');
            assert.equal(invocations, 1);
            const failure = await runItem(failing);
            assert.equal(failure.state, 'failed');
            assert.equal(failure.location?.uri.fsPath, failing.uri!.fsPath);
            assert.equal(failure.location?.range.start.line, 3);
            assert.equal(failure.location?.range.start.character, 2);
            outcomes.length = 0; invocations = 0;
            await api.profile.runHandler(new vscode.TestRunRequest([selected, failing], undefined, api.profile), cancellation.token);
            assert.equal(invocations, 1, 'A selection must use one compound runner invocation');
            assert.deepEqual(outcomes.map(result => result.state).sort(), ['failed', 'passed']);
            outcomes.length = 0; invocations = 0;
            await api.profile.runHandler(new vscode.TestRunRequest(undefined, [failing, nested.parent!.parent!], api.profile), cancellation.token);
            assert.equal(invocations, 1);
            assert.deepEqual(outcomes.map(result => result.id), [selected.id]);
            outcomes.length = 0; invocations = 0;
            await api.profile.runHandler(new vscode.TestRunRequest([selected.parent!, nested.parent!.parent!], [failing], api.profile), cancellation.token);
            assert.equal(invocations, 2, 'Nested projects must have independent runner invocations');
            assert.deepEqual(outcomes.map(result => result.state), ['passed', 'passed']);
            const testUri = selected.uri!;
            const originalSource = await vscode.workspace.fs.readFile(testUri);
            try {
                await vscode.workspace.fs.writeFile(testUri, Buffer.from('export function testSelected(): int => "wrong"'));
                const broken = await runItem(selected);
                assert.equal(broken.state, 'errored');
                assert.match(broken.message!, /error:/);
                assert.doesNotMatch(broken.message!, /ENOENT|result.json/);
            } finally { await vscode.workspace.fs.writeFile(testUri, originalSource); }

        } finally { api.controller.createTestRun = createRun; cancellation.dispose(); }

        for (const command of ['build', 'run']) {
            const completed = new Promise<number | undefined>((resolve, reject) => {
                const timeout = setTimeout(() => { subscription.dispose(); reject(new Error('Native task timed out')); }, 60000);
                const subscription = vscode.tasks.onDidEndTaskProcess(event => {
                    if (event.execution.task.name !== `Doof ${command}`) return;
                    clearTimeout(timeout); subscription.dispose(); resolve(event.exitCode);
                });
            });
            await vscode.commands.executeCommand(`doof.${command}`);
            assert.equal(await completed, command === 'build' ? 0 : 42);
        }
    }
    console.log('Doof packaged extension: hover, definition, completion, rename, formatting, unsaved diagnostics, stdlib auto-import, Test Explorer exact pass/fail and incompatible compiler handling, and configured native tasks passed.');
}

import * as vscode from 'vscode';
import assert from 'node:assert/strict';
export async function run() {
    const extension = vscode.extensions.getExtension('doof-lang.doof-language')!;
    const api = await extension.activate() as { controller: vscode.TestController; profile: vscode.TestRunProfile };
    await api.controller.resolveHandler!(undefined);
    let discovered = 0;
    const count = (item: vscode.TestItem) => { if (item.children.size) item.children.forEach(count); else discovered++; };
    api.controller.items.forEach(count);
    assert.ok(discovered > 0);
    const problems: string[] = [];
    let passed = 0, invocations = 0;
    const create = api.controller.createTestRun.bind(api.controller);
    api.controller.createTestRun = (...args) => {
        const run = create(...args);
        const pass = run.passed.bind(run), fail = run.failed.bind(run), error = run.errored.bind(run), append = run.appendOutput.bind(run);
        run.passed = (...args) => { passed++; pass(...args); };
        run.failed = (...args) => { problems.push(`${args[0].id}: ${JSON.stringify(args[1])}`); fail(...args); };
        run.errored = (...args) => { problems.push(`${args[0].id}: ${JSON.stringify(args[1])}`); error(...args); };
        run.appendOutput = (...args) => { if (args[0].startsWith('Doof: ')) invocations++; append(...args); };
        return run;
    };
    const token = new vscode.CancellationTokenSource();
    try {
        const started = Date.now();
        await api.profile.runHandler(new vscode.TestRunRequest(undefined, undefined, api.profile), token.token);
        console.log(JSON.stringify({ discovered, passed, projects: api.controller.items.size, invocations, seconds: (Date.now() - started) / 1000, problems: problems.slice(0, 5) }));
        assert.deepEqual(problems, []);
        assert.equal(passed, discovered);
        assert.equal(invocations, api.controller.items.size);
    } finally { api.controller.createTestRun = create; token.dispose(); }
}

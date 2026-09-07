import { createConnection, ProposedFeatures, TextDocuments, TextDocumentSyncKind, CompletionItemKind, SymbolKind, DiagnosticSeverity, SemanticTokensBuilder, CodeActionKind, TextEdit, ResponseError, ErrorCodes } from 'vscode-languageserver/node.js';
import { TextDocument } from 'vscode-languageserver-textdocument';
import { URI } from 'vscode-uri';
import { join } from 'node:path';
import { readFileSync } from 'node:fs';
import { ServiceClient } from './service-client.ts';
import { loadSnapshot, projectRoot, type Snapshot } from './workspace.ts';
import { byteOffset, rangeAt } from './positions.ts';
import type { Source, Diagnostic, Response, Item } from './protocol.ts';
const connection = createConnection(ProposedFeatures.all);
const documents = new TextDocuments(TextDocument);
const artifactRoot = join(__dirname, '../artifacts');
const stdlib: Source[] = JSON.parse(readFileSync(join(artifactRoot, 'stdlib.json'), 'utf8'));
for (const source of stdlib)
    source.physicalPath = join(artifactRoot, 'stdlib', source.path.slice('/std/'.length));
let roots: string[] = [];
const contexts = new Map<string, Context>();
const failures = new Map<string, number>();
const tokenTypes = ['variable', 'function', 'method', 'property', 'class', 'interface', 'enum', 'type', 'parameter'];
function kind(item: Item): string {
    if (item.kind === 'immutable-binding' || item.kind === 'let' || item.kind === 'readonly' || item.kind === 'const' || item.kind === 'import' || item.kind === 'module-let')
        return 'variable';
    return tokenTypes.includes(item.kind) ? item.kind : 'variable';
}
function client(onFailure: (error: Error) => void) { return new ServiceClient(join(__dirname, 'worker.mjs'), join(artifactRoot, 'service.wasm'), onFailure); }
class Context {
    queryWorker = client(error => this.recover(error));
    analysisWorker = client(error => this.recover(error));
    snapshot?: Snapshot;
    version = 0;
    publishedVersion = -1;
    running = false;
    timer?: NodeJS.Timeout;
    disposed = false;
    diagnostics = new Map<string, Diagnostic[]>();
    constructor(readonly root: string, readonly uri: string) { }
    schedule() {
        this.version++;
        clearTimeout(this.timer);
        this.timer = setTimeout(() => void this.update(), 200);
    }
    async recover(error: Error) {
        if (this.disposed)
            return;
        connection.console.error(String(error));
        const attempts = (failures.get(this.uri) ?? 0) + 1;
        failures.set(this.uri, attempts);
        this.disposed = true;
        await Promise.all([this.queryWorker.dispose(), this.analysisWorker.dispose()]);
        const members = [...contexts.entries()].filter(([, value]) => value === this).map(([uri]) => uri);
        for (const uri of members)
            contexts.delete(uri);
        if (members.some(uri => documents.get(uri)) && attempts <= 3) {
            setTimeout(async () => { for (const uri of members)
                if (documents.get(uri) && !contexts.has(uri))
                    (await contextFor(uri)).schedule(); }, attempts * 1000);
        }
        else
            connection.console.error("Language service stopped after repeated worker failures. Use Doof: Restart Language Service to retry.");
    }
    async update() {
        if (this.running || this.disposed)
            return;
        this.running = true;
        try {
            do {
                const version = this.version;
                // Reclaim compiler reference cycles by recycling the spare worker; the
                // published query snapshot remains available throughout replay.
                if (this.analysisWorker.memoryBytes > 192 * 1024 * 1024) {
                    await this.analysisWorker.dispose();
                    this.analysisWorker = client(error => this.recover(error));
                }
                const overlays = new Map(documents.all().map(document => [document.uri, document.getText()]));
                const activeUri = [...contexts.entries()].find(([uri, value]) => value === this && documents.get(uri))?.[0] ?? this.uri;
                const snapshot = await loadSnapshot(this.root, activeUri, overlays, stdlib, this.analysisWorker);
                const diagnostics = await this.analysisWorker.call<Diagnostic[]>('analyze', { sources: snapshot.sources, entry: snapshot.entry, additionalEntries: snapshot.additionalEntries });
                if (version !== this.version)
                    continue;
                [this.queryWorker, this.analysisWorker] = [this.analysisWorker, this.queryWorker];
                this.snapshot = snapshot;
                this.publishedVersion = version;
                this.diagnostics.clear();
                for (const diagnostic of diagnostics) {
                    const source = snapshot.byModule.get(diagnostic.module);
                    if (!source)
                        continue;
                    const uri = URI.file(source.physicalPath).toString();
                    const group = this.diagnostics.get(uri) ?? [];
                    group.push(diagnostic);
                    this.diagnostics.set(uri, group);
                }
                connection.sendDiagnostics({ uri: URI.file(join(this.root, 'doof.json')).toString(), diagnostics: [] });
                publishDiagnostics();
                connection.languages.semanticTokens.refresh();
                break;
            } while (!this.disposed);
        }
        catch (error) {
            if (!this.disposed) {
                this.diagnostics.clear();
                publishDiagnostics();
                connection.sendDiagnostics({ uri: URI.file(join(this.root, 'doof.json')).toString(), diagnostics: [{ range: { start: { line: 0, character: 0 }, end: { line: 0, character: 0 } }, message: String(error), source: 'Doof', severity: DiagnosticSeverity.Error }] });
            }
            connection.console.error(String(error));
        }
        finally {
            this.running = false;
        }
    }
}
let utilityWorker: ServiceClient | undefined;
connection.onRequest('doof/discoverTests', async (params: {
    source: string;
    module: string;
    root: string;
}) => {
    utilityWorker ??= client(error => { connection.console.error(String(error)); void utilityWorker?.dispose(); utilityWorker = undefined; });
    return utilityWorker.call('tests', params);
});
connection.onRequest('doof/serviceStatus', () => [...new Set(contexts.values())].map(context => ({ root: context.root, version: context.version, publishedVersion: context.publishedVersion, running: context.running, memoryBytes: context.queryWorker.memoryBytes + context.analysisWorker.memoryBytes })));
const published = new Set<string>();
function publishDiagnostics() {
    const byUri = new Map<string, any[]>();
    for (const context of new Set(contexts.values()))
        for (const [uri, diagnostics] of (context.publishedVersion === context.version ? context.diagnostics : new Map<string, Diagnostic[]>())) {
            const result = byUri.get(uri) ?? [];
            for (const diagnostic of diagnostics) {
                const source = context.snapshot?.byModule.get(diagnostic.module);
                if (!source)
                    continue;
                const value = { range: rangeAt(source.source, diagnostic.span.start.offset, diagnostic.span.end.offset), message: diagnostic.message, severity: diagnostic.severity === 'warning' ? DiagnosticSeverity.Warning : DiagnosticSeverity.Error, source: 'Doof', data: { replacement: diagnostic.replacement, version: documents.get(uri)?.version } };
                if (!result.some(item => JSON.stringify(item) === JSON.stringify(value)))
                    result.push(value);
            }
            byUri.set(uri, result);
        }
    for (const uri of new Set([...published, ...byUri.keys()]))
        connection.sendDiagnostics({ uri, diagnostics: byUri.get(uri) ?? [] });
    published.clear();
    for (const uri of byUri.keys())
        published.add(uri);
}
async function contextFor(uri: string) {
    let context = contexts.get(uri);
    if (!context) {
        const root = await projectRoot(URI.parse(uri).fsPath, roots);
        context = [...contexts.values()].find(value => value.root === root && !uri.endsWith('.test.do') && !value.uri.endsWith('.test.do'));
        context ??= new Context(root, uri);
        contexts.set(uri, context);
    }
    return context;
}
// Map positions through one pending edit region. Navigation within changed text
// is suppressed; completion may still use its enclosing last-checked scope.
function mappedOffset(old: string, current: string, offset: number, completion: boolean): number | undefined {
    const before = Buffer.from(old), after = Buffer.from(current);
    let prefix = 0;
    while (prefix < before.length && prefix < after.length && before[prefix] === after[prefix])
        prefix++;
    let suffix = 0;
    while (suffix < before.length - prefix && suffix < after.length - prefix && before[before.length - 1 - suffix] === after[after.length - 1 - suffix])
        suffix++;
    if (offset <= prefix)
        return offset;
    if (offset >= after.length - suffix)
        return offset + before.length - after.length;
    return completion ? prefix : undefined;
}
async function query(params: any, operation: string, text = ''): Promise<{
    response: Response;
    context: Context;
} | undefined> {
    const uri = params.textDocument.uri;
    const context = await contextFor(uri);
    if (!context.snapshot) {
        if (!context.running)
            await context.update();
        else
            return;
    }
    const snapshot = context.snapshot;
    if (!snapshot)
        return;
    const module = snapshot.byUri.get(uri);
    if (!module)
        return;
    const source = snapshot.byModule.get(module)!;
    const document = documents.get(uri);
    const offset = params.position ? mappedOffset(source.source, document?.getText() ?? source.source, byteOffset(document?.getText() ?? source.source, params.position), operation === 'completion' || operation === 'signature') : 0;
    if (offset === undefined)
        return;
    if ((operation === 'completion' || operation === 'signature') && params.position && document)
        text = Buffer.from(document.getText()).subarray(0, byteOffset(document.getText(), params.position)).toString('utf8');
    const version = document?.version;
    const response = await context.queryWorker.call<Response>('query', { operation, module, offset, text });
    if (context.snapshot !== snapshot || documents.get(uri)?.version !== version)
        return;
    return { context, response };
}
function location(context: Context, module: string, start: number, end: number) {
    const source = context.snapshot?.byModule.get(module);
    if (!source)
        return;
    const uri = URI.file(source.physicalPath).toString();
    const current = documents.get(uri)?.getText() ?? source.source;
    const currentStart = mappedOffset(current, source.source, start, false);
    const currentEnd = mappedOffset(current, source.source, end, false);
    if (currentStart === undefined || currentEnd === undefined)
        return;
    return { uri, range: rangeAt(current, currentStart, currentEnd) };
}
connection.onInitialize(params => {
    roots = (params.workspaceFolders ?? []).map(folder => URI.parse(folder.uri).fsPath);
    return { capabilities: { textDocumentSync: TextDocumentSyncKind.Incremental, completionProvider: { resolveProvider: true, triggerCharacters: ['.', '{', '"'] }, hoverProvider: true, definitionProvider: true, typeDefinitionProvider: true, referencesProvider: true, renameProvider: { prepareProvider: true }, documentSymbolProvider: true, workspaceSymbolProvider: true, signatureHelpProvider: { triggerCharacters: ['(', ',', '{'] }, documentFormattingProvider: true, codeActionProvider: { codeActionKinds: [CodeActionKind.QuickFix] }, semanticTokensProvider: { legend: { tokenTypes, tokenModifiers: ['declaration'] }, full: true }, workspace: { workspaceFolders: { supported: true, changeNotifications: true } } } };
});
documents.onDidOpen(async ({ document }) => (await contextFor(document.uri)).schedule());
documents.onDidChangeContent(({ document }) => { for (const context of new Set(contexts.values()))
    if (document.uri === context.uri || context.snapshot?.byUri.has(document.uri))
        context.schedule(); });
documents.onDidClose(async ({ document }) => { const context = contexts.get(document.uri); contexts.delete(document.uri); if (context && ![...contexts.values()].includes(context)) {
    context.disposed = true;
    clearTimeout(context.timer);
    await Promise.all([context.queryWorker.dispose(), context.analysisWorker.dispose()]);
} publishDiagnostics(); });
connection.onDidChangeWatchedFiles(() => { for (const context of new Set(contexts.values()))
    context.schedule(); });
connection.onInitialized(() => connection.workspace.onDidChangeWorkspaceFolders(event => { roots = roots.filter(root => !event.removed.some(folder => URI.parse(folder.uri).fsPath === root)); roots.push(...event.added.map(folder => URI.parse(folder.uri).fsPath)); for (const context of new Set(contexts.values()))
    context.schedule(); }));
connection.onCompletion(async params => {
    const result = await query(params, 'completion');
    const document = documents.get(params.textDocument.uri);
    return {isIncomplete: true, items: (result?.response.items ?? []).map(item => ({
        label: item.label,
        labelDetails: item.importModule ? {description:item.detail.replace('Auto import from ','')} : undefined,
        detail: item.detail, documentation: item.documentation, insertText:item.insertText || undefined,
        sortText: (item.importModule ? '1' : '0') + item.label,
        data: item.importModule && result && document ? {uri:document.uri, version:document.version, generation:result.context.version, target:item.importModule} : undefined,
        textEdit:item.kind === 'module' && document ? {range:rangeAt(document.getText(),item.start,item.end),newText:item.label} : undefined,
        kind:kind(item)==='function'||kind(item)==='method'?CompletionItemKind.Function:kind(item)==='class'?CompletionItemKind.Class:kind(item)==='interface'?CompletionItemKind.Interface:kind(item)==='property'?CompletionItemKind.Property:CompletionItemKind.Variable
    }))};
});
connection.onCompletionResolve(async item => {
    if (!item.data) return item;
    const {uri,version,generation,target} = item.data;
    const document = documents.get(uri), context = contexts.get(uri);
    if (!document || !context?.snapshot || document.version !== version || context.version !== generation) return item;
    const snapshot = context.snapshot, module = snapshot.byUri.get(uri);
    if (!module) return item;
    const response = await context.queryWorker.call<Response>('autoImport',{module,target,name:item.label,source:document.getText()});
    if (version !== documents.get(uri)?.version || contexts.get(uri) !== context || context.version !== generation || context.snapshot !== snapshot) return item;
    if (!response.error) item.additionalTextEdits = response.edits.map(edit=>({range:rangeAt(document.getText(),edit.start,edit.end),newText:edit.text}));
    return item;
});
connection.onHover(async (params) => { const result = await query(params, 'hover'); const item = result?.response.items[0]; return item ? { contents: { kind: 'markdown' as const, value: '```doof\n' + item.label + ': ' + item.detail + '\n```' + (item.documentation ? '\n\n' + item.documentation : '') } } : null; });
connection.onDefinition(async (params) => { const result = await query(params, 'definition'); const item = result?.response.items[0]; return item && result ? location(result.context, item.definitionModule, item.definitionStart, item.definitionEnd) : null; });
connection.onTypeDefinition(async (params) => { const result = await query(params, 'typeDefinition'); const item = result?.response.items[0]; return item && result ? location(result.context, item.definitionModule, item.definitionStart, item.definitionEnd) : null; });
connection.onReferences(async (params) => { const result = await query(params, 'references'); return result?.response.items.filter(item => params.context.includeDeclaration || !item.declaration).map(item => location(result.context, item.module, item.start, item.end)).filter(Boolean) as any ?? []; });
connection.onDocumentSymbol(async params => {
    const result = await query(params, 'symbols');
    return (result?.response.items ?? []).flatMap(item => {
        const target = location(result!.context, item.module, item.start, item.end);
        return target ? [{name:item.label,detail:item.detail,kind:kind(item)==='function'?SymbolKind.Function:SymbolKind.Variable,range:target.range,selectionRange:target.range}] : [];
    });
});
connection.onWorkspaceSymbol(async (params) => { const items: any[] = []; for (const context of new Set(contexts.values())) {
    if (!context.snapshot)
        continue;
    const snapshot = context.snapshot;
    const response = await context.queryWorker.call<Response>('query', { operation: 'workspaceSymbols', module: '', offset: 0, text: params.query });
    if (context.snapshot !== snapshot) continue;
    for (const item of response.items) {
        const target = location(context, item.module, item.start, item.end);
        if (target && !items.some(value => value.name === item.label && JSON.stringify(value.location) === JSON.stringify(target)))
            items.push({ name: item.label, kind: SymbolKind.Variable, location: target });
    }
} return items; });
connection.onSignatureHelp(async (params) => { const result = await query(params, 'signature'); return result?.response.items.length ? { signatures: result.response.items.map(item => ({ label: item.label, parameters: item.parameters.map(label => ({ label })) })), activeSignature: 0, activeParameter: result.response.activeParameter } : null; });
connection.onPrepareRename(async (params) => { const result = await query(params, 'prepareRename'); const item = result?.response.items[0]; return item && result ? location(result.context, item.module, item.start, item.end)?.range : null; });
connection.onRenameRequest(async (params) => { const result = await query(params, 'rename', params.newName); if (!result)
    return null; if (result.context.publishedVersion !== result.context.version)
    throw new ResponseError(ErrorCodes.InvalidRequest, 'Wait for current analysis before renaming.'); if (result.response.error)
    throw new ResponseError(ErrorCodes.InvalidRequest, result.response.error); const changes: Record<string, TextEdit[]> = {}; for (const edit of result.response.edits) {
    const target = location(result.context, edit.module, edit.start, edit.end);
    if (target)
        (changes[target.uri] ??= []).push({ range: target.range, newText: edit.text });
} return { documentChanges: Object.entries(changes).map(([uri, edits]) => ({ textDocument: { uri, version: documents.get(uri)?.version ?? null }, edits })) }; });
connection.onDocumentFormatting(async (params) => {
    const document = documents.get(params.textDocument.uri);
    if (!document)
        return [];
    const source = document.getText(), version = document.version;
    const context = await contextFor(document.uri);
    const settings = await connection.workspace.getConfiguration({ scopeUri: document.uri, section: 'doof' });
    const response = await context.queryWorker.call<Response>('format', { source, module: document.uri, indentation: settings?.indentSize ?? 2 });
    if (documents.get(document.uri)?.version !== version)
        return [];
    return response.edits.map(edit => ({ range: rangeAt(source, edit.start, edit.end), newText: edit.text }));
});
connection.onCodeAction(async (params) => {
    const document = documents.get(params.textDocument.uri);
    if (!document)
        return [];
    const version = document.version;
    const actions: any[] = [];
    for (const diagnostic of params.context.diagnostics) {
        if ((diagnostic.data as any)?.version !== version)
            continue;
        const replacement = (diagnostic.data as any)?.replacement;
        let edits: TextEdit[] = [];
        if (replacement)
            edits = [{ range: diagnostic.range, newText: replacement }];
        else {
            const result = await query({ ...params, position: diagnostic.range.start }, 'codeAction', diagnostic.message);
            if (!result || result.context.version !== result.context.publishedVersion)
                continue;
            edits = result.response.edits.map(edit => ({ range: rangeAt(document.getText(), edit.start, edit.end), newText: edit.text }));
        }
        if (edits.length && documents.get(document.uri)?.version === version)
            actions.push({ title: replacement ? 'Apply Doof suggested replacement' : 'Import missing declaration', kind: CodeActionKind.QuickFix, diagnostics: [diagnostic], edit: { documentChanges: [{ textDocument: { uri: document.uri, version }, edits }] } });
    }
    return actions;
});
connection.languages.semanticTokens.on(async (params) => { const result = await query(params, 'semanticTokens'); const builder = new SemanticTokensBuilder(); let previous = -1; for (const item of (result?.response.items ?? []).sort((a, b) => a.start - b.start)) {
    if (item.start === previous || item.end <= item.start)
        continue;
    const target = location(result!.context, item.module, item.start, item.end);
    if (!target || target.range.start.line !== target.range.end.line)
        continue;
    builder.push(target.range.start.line, target.range.start.character, target.range.end.character - target.range.start.character, tokenTypes.indexOf(kind(item)), item.declaration ? 1 : 0);
    previous = item.start;
} return builder.build(); });
connection.onShutdown(async () => { await utilityWorker?.dispose(); for (const context of new Set(contexts.values())) {
    context.disposed = true;
    clearTimeout(context.timer);
    await Promise.all([context.queryWorker.dispose(), context.analysisWorker.dispose()]);
} });
documents.listen(connection);
connection.listen();

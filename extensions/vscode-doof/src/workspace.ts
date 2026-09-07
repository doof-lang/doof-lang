import { readdir, readFile, stat } from 'node:fs/promises';
import { dirname, join, relative, resolve, isAbsolute } from 'node:path';
import { URI } from 'vscode-uri';
import type { Source } from './protocol.ts';
import type { ServiceClient } from './service-client.ts';
export interface Snapshot {
    sources: Source[];
    entry: string;
    additionalEntries: string[];
    byModule: Map<string, Source>;
    byUri: Map<string, string>;
}
function within(root: string, path: string) { const child = relative(root, path); return child === '' || (!child.startsWith('..') && !isAbsolute(child)); }
const excluded = new Set(['.git', '.doof', 'node_modules', 'build', 'dist', 'bootstrap', 'artifacts', '.venv']);
export async function projectRoot(path: string, workspaceRoots: string[]): Promise<string> {
    let directory = dirname(path);
    const boundary = workspaceRoots.filter(root => within(root, path)).sort((a, b) => b.length - a.length)[0];
    while (true) {
        try {
            if ((await stat(join(directory, 'doof.json'))).isFile())
                return directory;
        }
        catch { /* No manifest at this level. */ }
        if (directory === boundary || dirname(directory) === directory)
            break;
        directory = dirname(directory);
    }
    return boundary ?? dirname(path);
}
export async function loadSnapshot(root: string, entryUri: string, overlays: Map<string, string>, stdlib: Source[], service: ServiceClient): Promise<Snapshot> {
    const sources: Source[] = [...stdlib];
    const visited = new Set<string>();
    const physical = new Set<string>();
    let configuredEntry: string | undefined;
    async function files(directory: string, prefix: string) {
        for (const file of await readdir(directory, { withFileTypes: true })) {
            if (file.name.startsWith('.') || excluded.has(file.name))
                continue;
            const path = join(directory, file.name);
            const logical = `${prefix}/${file.name}`;
            if (file.isDirectory())
                await files(path, logical);
            else if (file.isFile() && file.name.endsWith('.do')) {
                const uri = URI.file(path).toString();
                sources.push({ path: logical, physicalPath: path, source: overlays.get(uri) ?? await readFile(path, 'utf8') });
                physical.add(uri);
            }
        }
    }
    async function packageSources(directory: string, prefix: string) {
        const identity = `${directory}\0${prefix}`;
        if (visited.has(identity))
            return;
        visited.add(identity);
        await files(directory, prefix);
        const manifest = join(directory, 'doof.json');
        let source: string;
        try {
            source = overlays.get(URI.file(manifest).toString()) ?? await readFile(manifest, 'utf8');
        }
        catch (error: any) {
            if (error.code === 'ENOENT')
                return;
            throw error;
        }
        const settings = await service.call<{
            entry: string;
            dependencies: {
                name: string;
                path: string;
            }[];
        }>('project', { source, manifest, root: directory });
        if (directory === root)
            configuredEntry = '/' + settings.entry.replace(/\\/g, '/').replace(/^\.\//, '');
        for (const dependency of settings.dependencies)
            await packageSources(resolve(dependency.path), `/${dependency.name}`);
    }
    await packageSources(root, '');
    for (const [uri, source] of overlays) {
        const path = URI.parse(uri).fsPath;
        if (!path.endsWith('.do') || physical.has(uri) || !(within(root, path)))
            continue;
        sources.push({ path: '/' + relative(root, path).split('\\').join('/'), source, physicalPath: path });
    }
    const byModule = new Map(sources.map(source => [source.path, source]));
    const byUri = new Map(sources.map(source => [URI.file(source.physicalPath).toString(), source.path]));
    const entry = byUri.get(entryUri);
    if (!entry)
        throw new Error(`Cannot load ${entryUri}`);
    const primary = configuredEntry && byModule.has(configuredEntry) && !entry.endsWith(".test.do") ? configuredEntry : entry;
    return { sources, entry: primary, additionalEntries: entry.endsWith('.test.do') ? [] : [...new Set([entry, ...[...overlays.keys()].filter(uri => !uri.endsWith('.test.do')).map(uri => byUri.get(uri)).filter((path): path is string => !!path)])].filter(path => path !== primary), byModule, byUri };
}

import { readdir, readFile } from 'node:fs/promises';
import { resolve, join } from 'node:path';
import { loadService } from './wasm-runtime.ts';
const repository = resolve(import.meta.dirname, '../../..');
const sources: {
    path: string;
    source: string;
    physicalPath: string;
}[] = [];
async function collect(directory: string, logical: string) {
    for (const item of await readdir(directory, { withFileTypes: true })) {
        if (item.name.startsWith('.') || ['node_modules', 'build', 'dist', 'tests', 'examples'].includes(item.name))
            continue;
        const physicalPath = join(directory, item.name);
        if (item.isDirectory())
            await collect(physicalPath, `${logical}/${item.name}`);
        else if (item.name.endsWith('.do') && !item.name.endsWith('.test.do')) {
            sources.push({ path: `${logical}/${item.name}`, source: await readFile(physicalPath, 'utf8'), physicalPath });
        }
    }
}
const application = process.argv[3] ? resolve(process.argv[3]) : undefined;
if (application) await collect(application, '');
else await collect(join(repository, 'src'), '/src');
const bundled = JSON.parse(await readFile(resolve(import.meta.dirname,'../artifacts/stdlib.json'),'utf8'));
sources.push(...bundled);
const entry = application ? '/src/main.do' : '/src/frontend.do';
const service = await loadService(resolve(process.argv[2]));
const started = performance.now();
const diagnostics = service.call('analyze', { sources, entry });
console.log(JSON.stringify({ milliseconds: performance.now() - started, memoryBytes: service.memoryBytes(), diagnostics }));
const queryTimes: number[] = [];
const module = sources.find(source => source.path === entry)!;
for (let i = 0; i < 100; i++) {
    const start = performance.now();
    service.call('query', { operation: application ? 'hover' : 'completion', module: module.path, offset: application ? module.source.indexOf('runViewerApp())') + 1 : module.source.indexOf('analyzer.serialParsing'), text: '' });
    queryTimes.push(performance.now() - start);
}
queryTimes.sort((a, b) => a - b);
const editStart = performance.now();
module.source += '\n// editor latency probe\n';
const edited = service.call('analyze', { sources, entry });
console.log(JSON.stringify({ warmQueryP50: queryTimes[50], warmQueryP95: queryTimes[95], editMilliseconds: performance.now() - editStart, memoryBytes: service.memoryBytes(), diagnostics: edited }));

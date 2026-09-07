import { cp, mkdir, readFile, writeFile, readdir, rm } from 'node:fs/promises';
import { resolve, join } from 'node:path';
import { createHash } from 'node:crypto';
import { execFileSync } from 'node:child_process';
const root = resolve(import.meta.dirname, '../../..');
const staging = join(root, 'build/vscode-service-package');
const output = join(root, 'extensions/vscode-doof/artifacts');
await rm(join(staging, "src"), { recursive: true, force: true });
await mkdir(staging, { recursive: true });
await mkdir(output, { recursive: true });
await cp(join(root, 'src'), join(staging, 'src'), { recursive: true, filter: path => !path.endsWith('.test.do') });
await writeFile(join(staging, 'doof.json'), JSON.stringify({
    name: 'doof-language-service',
    build: {
        entry: 'src/editor-wasm.do', target: 'wasm',
        native: { linkerFlags: ['-sALLOW_MEMORY_GROWTH=1', '-sMAXIMUM_MEMORY=1073741824', '-sSTACK_SIZE=1048576'] },
    },
}, null, 2));
const compilerEnvironment = {...process.env};
delete compilerEnvironment.DOOF_STDLIB_ROOT;
execFileSync(join(root, 'dist/doof'), ['build', staging, '-o', join(root, 'build/vscode-service')], {
    cwd: root, stdio: 'inherit', env: compilerEnvironment,
});
await cp(join(root, 'build/vscode-service/doof-language-service.wasm'), join(output, 'service.wasm'));
const sourceIdentity = createHash('sha256');
for (const name of (await readdir(join(staging, 'src'))).filter(name => name.endsWith('.do')).sort()) {
    sourceIdentity.update(name + '\0');
    sourceIdentity.update(await readFile(join(staging, 'src', name)));
}
const manifest = JSON.parse(await readFile(join(root, 'doof.json'), 'utf8'));
const wasmSha256 = createHash('sha256').update(await readFile(join(output, 'service.wasm'))).digest('hex');
await writeFile(join(output, 'service-version.json'), JSON.stringify({ version: manifest.version, compilerSourceSha256: sourceIdentity.digest('hex'), dirty: execFileSync('git', ['status', '--porcelain', '--', 'src'], { cwd: root, encoding: 'utf8' }).trim() !== '', wasmSha256, revision: execFileSync('git', ['rev-parse', 'HEAD'], { cwd: root, encoding: 'utf8' }).trim() }, null, 2));
// The compiler's curated bundle is authoritative. Nearby applications and
// examples must never be exposed as fictitious std/<directory> packages.
const archive = join(root, 'dist/doof-stdlib.tar');
const catalog = JSON.parse(execFileSync('tar', ['-xOf', archive, 'bundle-index.json'], {encoding:'utf8'}));
const bundled: {path:string;source:string;physicalPath:string}[] = [];
await rm(join(output,'stdlib'),{recursive:true,force:true});
for (const member of catalog.members) {
    if (member.kind !== 'module') continue;
    const relativeName = member.packageName.slice('std/'.length) + '/' + member.path;
    if (!member.packageName.startsWith('std/') || relativeName.split('/').some((part:string)=>part==='..'||part==='') || !relativeName.endsWith('.do')) throw new Error('Invalid stdlib module path');
    const compressed = execFileSync('tar',['-xOf',archive,member.member],{maxBuffer:32*1024*1024});
    if (createHash('sha256').update(compressed).digest('hex') !== member.sha256) throw new Error('Stdlib artifact digest mismatch');
    const source = execFileSync('tar',['-xOf','-',member.path],{input:compressed,maxBuffer:32*1024*1024}).toString('utf8');
    bundled.push({path:'/std/'+relativeName,source,physicalPath:''});
    const target = join(output,'stdlib',relativeName);
    await mkdir(resolve(target,'..'),{recursive:true});await writeFile(target,source);
}
bundled.sort((a, b) => a.path.localeCompare(b.path));
await writeFile(join(output, 'stdlib.json'), JSON.stringify(bundled));
const versionPath = join(output, 'service-version.json');
const version = JSON.parse(await readFile(versionPath, 'utf8'));
version.stdlibBundleDigest = catalog.bundleDigest;
version.stdlibSha256 = createHash('sha256').update(JSON.stringify(bundled)).digest('hex');
await writeFile(versionPath, JSON.stringify(version, null, 2));

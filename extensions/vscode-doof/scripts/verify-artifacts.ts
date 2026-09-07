import assert from 'node:assert/strict';
import {createHash} from 'node:crypto';
import {readFile,readdir} from 'node:fs/promises';
import {resolve,join} from 'node:path';
const root=resolve(import.meta.dirname,'../../..');
const artifacts=join(root,'extensions/vscode-doof/artifacts');
const version=JSON.parse(await readFile(join(artifacts,'service-version.json'),'utf8'));
const hash=(bytes:Uint8Array|string)=>createHash('sha256').update(bytes).digest('hex');
assert.equal(hash(await readFile(join(artifacts,'service.wasm'))),version.wasmSha256,'Wasm identity mismatch; rebuild the service');
const stdlib=await readFile(join(artifacts,'stdlib.json'),'utf8');
assert.equal(hash(stdlib),version.stdlibSha256,'Standard-library identity mismatch');
for(const source of JSON.parse(stdlib))assert.equal(await readFile(join(artifacts,'stdlib',source.path.slice('/std/'.length)),'utf8'),source.source);
const identity=createHash('sha256');
for(const name of (await readdir(join(root,'src'))).filter(name=>name.endsWith('.do')&&!name.endsWith('.test.do')).sort()){
 identity.update(name+'\0');identity.update(await readFile(join(root,'src',name)));
}
assert.equal(identity.digest('hex'),version.compilerSourceSha256,'Compiler sources changed; run npm run build:service before packaging');
assert.equal(JSON.parse(await readFile(join(root,'doof.json'),'utf8')).version,version.version);
console.log('Wasm, compiler sources, and bundled standard-library identities verified.');

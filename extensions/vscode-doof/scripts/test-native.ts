import assert from 'node:assert/strict';
import {execFileSync} from 'node:child_process';
import {mkdtemp,writeFile,readFile,rm} from 'node:fs/promises';
import {resolve,join} from 'node:path';
const root=resolve(import.meta.dirname,'../../..');
const compiler=process.env.DOOF_TEST_COMPILER ?? join(root,'dist/doof');
const directory=await mkdtemp(join(root,'build/editor-native-'));
try {
 await writeFile(join(directory,'doof.json'),JSON.stringify({name:'native-editor-fixture',build:{entry:'main.do'}}));
 await writeFile(join(directory,'main.do'),'function main(): int => 0');
 await writeFile(join(directory,'workflow.test.do'),'export function testSelected(): none {}\nexport function testSelectedOther(): none { panic("Unselected test must not execute") }');
 const tests=JSON.parse(execFileSync(compiler,['test',directory,'--list','--json'],{encoding:'utf8'}));
 assert.equal(tests.length,2);
 const id='workflow.test.do::testSelected', report=join(directory,'results.json');
 execFileSync(compiler,['test',directory,'--exact-filter',id,'--report-json',report],{stdio:'inherit'});
 const results=JSON.parse(await readFile(report,'utf8'));
 assert.equal(results.length,1);assert.equal(results[0].id,id);assert.equal(results[0].exitCode,0);
 const selection=join(directory,'selected.json');
 await writeFile(selection,JSON.stringify([id,'workflow.test.do::testSelectedOther']));
 let batchOutput='';
 try {execFileSync(compiler,['test',directory,'--selection-json',selection,'--report-json',report],{encoding:'utf8'});}
 catch(error) {batchOutput=String((error as {stdout:unknown}).stdout);}
 assert.match(batchOutput,/REUSE frontend shared/);
 const batch=JSON.parse(await readFile(report,'utf8'));
 assert.equal(batch.length,2); assert.equal(batch[0].exitCode,0); assert.notEqual(batch[1].exitCode,0);
 // A source edit must invalidate the whole-graph hit, while selection changes must not.
 await writeFile(join(directory,'workflow.test.do'),'export function testSelected(): none {}\nexport function testSelectedOther(): none {}');
 const changed=execFileSync(compiler,['test',directory,'--selection-json',selection,'--report-json',report],{encoding:'utf8'});
 assert.doesNotMatch(changed,/REUSE frontend/);
 assert.ok(JSON.parse(await readFile(report,'utf8')).every((result:{exitCode:number})=>result.exitCode===0));
 console.log('Native workflow: JSON discovery, exact selection, and structured results passed.');
} finally {await rm(directory,{recursive:true,force:true});}

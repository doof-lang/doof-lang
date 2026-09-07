import { build } from 'esbuild';
import { resolve } from 'node:path';
const root = resolve(import.meta.dirname, '..');
for (const name of ['extension', 'server', 'worker'])
    await build({ entryPoints: [`${root}/src/${name}.ts`], outfile: `${root}/out/${name}.${name === 'worker' ? 'mjs' : 'cjs'}`, bundle: true, platform: 'node', format: name === 'worker' ? 'esm' : 'cjs', target: 'node22', external: ['vscode'], sourcemap: true });

// Reuse exact projected declarations only within one checked module graph.
// Namespace mappings, source paths, surfaces and instantiations are fixed for
// the lifetime of this cache. Never retain it across compilations.
import { Program } from "./ast"
import { HeaderPlan } from "./emitter-header"
import { StringBuilder } from "./string-builder"

export class HeaderPlanCache {
  private plans: Map<string, HeaderPlan> = {}

  get(key: string): HeaderPlan | none {
    plan := plans.get(key) else { return none }
    return plan
  }

  store(key: string, plan: HeaderPlan): none {
    plans.set(key, plan)
  }
}

/** Source spans identify the original, checked statements in this one graph. */
export function projectedHeaderKey(path: string, program: Program, interfaceKeys: string[]): string {
  key := StringBuilder()
  key.append(string(path.length) + ":" + path + "|")
  for statement of program.statements {
    key.append(string(statement.span.start.offset) + ":" + string(statement.span.end.offset) + ";")
  }
  key.append("|")
  for interfaceKey of interfaceKeys { key.append(string(interfaceKey.length) + ":" + interfaceKey) }
  return key.drainToString()
}


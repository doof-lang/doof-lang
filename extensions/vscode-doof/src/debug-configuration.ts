export function debuggerPreRunCommands(commands: string[], stopOnEntry: boolean | undefined,
    stopOnUnhandledPanic: boolean | undefined, stopOnPanic: boolean | undefined): string[] {
    return [...commands,
        ...(stopOnEntry === true ? ['breakpoint set --name doof_main --one-shot true'] : []),
        ...(stopOnPanic === true ? ['breakpoint set --name doof::panic'] :
            stopOnUnhandledPanic !== false ? ['breakpoint set --name doof::unhandled_panic'] : [])];
}

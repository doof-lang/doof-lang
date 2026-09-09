// Interpret the compiler's line/terminal progress without exposing diagnostics in the popup.
export function debugBuildProgress(report: (message: string) => void) {
    let pending = '';
    let previous = '';
    const line = (text: string) => {
        let message = '';
        const heading = /^Compiling (\d+) files?$/.exec(text.trim());
        const count = /^\[[-#]+\] (\d+)\/(\d+)$/.exec(text.trim());
        if (heading) message = `Compiling ${heading[1]} source file${heading[1] === '1' ? '' : 's'}…`;
        if (count) {
            const completed = Number(count[1]), total = Number(count[2]);
            if (total > 0 && completed <= total) message = completed === total
                ? 'Finishing build and preparing debug symbols…'
                : `Compiling source files: ${completed} of ${total}…`;
        }
        if (message && message !== previous) { previous = message; report(message); }
    };
    return {
        write(text: string) {
            const lines = (pending + text).split(/[\r\n]/);
            pending = lines.pop()!.slice(-4096);
            for (const value of lines) line(value);
        },
        end() { line(pending); pending = ''; },
    };
}

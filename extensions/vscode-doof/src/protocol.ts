export interface Source {
    path: string;
    source: string;
    physicalPath: string;
}
export interface Item {
    importModule: string;
    parameters: string[];
    label: string;
    detail: string;
    insertText: string;
    documentation: string;
    kind: string;
    module: string;
    start: number;
    end: number;
    identity: string;
    definitionModule: string;
    definitionStart: number;
    definitionEnd: number;
    declaration: boolean;
    shorthand: boolean;
}
export interface Edit {
    module: string;
    start: number;
    end: number;
    text: string;
}
export interface Response {
    activeParameter: number;
    items: Item[];
    edits: Edit[];
    error: string;
}
export interface Diagnostic {
    module: string;
    severity: string;
    message: string;
    replacement: string;
    span: {
        start: {
            offset: number;
        };
        end: {
            offset: number;
        };
    };
}

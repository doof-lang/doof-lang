#include "src_test_runner.hpp"

namespace app_src_test_runner_ {
using namespace ::app_src_ast_;
using namespace ::app_src_emitter_module_;





std::shared_ptr<TestDiscovery> discoverModuleTests(const std::shared_ptr<::app_src_ast_::Program>& program, const std::string& modulePath, const std::string& rootDirectory) {
    const auto result = std::make_shared<TestDiscovery>(std::make_shared<std::vector<std::shared_ptr<DiscoveredTest>>>(std::vector<std::shared_ptr<DiscoveredTest>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    auto usesMocks = false;
    const auto& _iterable_2 = program->statements;
    for (const auto& statement : *_iterable_2) {
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MockImportDirective>>(_case_subject)) {
                (usesMocks = true);
        }
        else {
        }
        }
    }
    const auto& _iterable_4 = program->statements;
    for (const auto& statement : *_iterable_4) {
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
                const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
                if (fn->exported && doof::string_startsWith(fn->name, std::string("test"))) {
                    addDiscoveredTest(result, fn, fn->name, modulePath, rootDirectory, usesMocks);
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportList>>(_case_subject)) {
                const auto& list = std::get<std::shared_ptr<::app_src_ast_::ExportList>>(_case_subject);
                if (!doof::is_null(list->source)) {
                    continue;
                }
                const auto& _iterable_6 = list->specifiers;
                for (const auto& specifier : *_iterable_6) {
                    const auto exportedName = (doof::is_null(specifier->alias) ? specifier->name : doof::unwrap_optional(specifier->alias));
                    if (!doof::string_startsWith(exportedName, std::string("test"))) {
                        continue;
                    }
                    const auto declaration = findFunction(program->statements, specifier->name);
                    if (!doof::is_null(declaration)) {
                        addDiscoveredTest(result, doof::unwrap_optional(declaration), exportedName, modulePath, rootDirectory, usesMocks);
                    }
                }
        }
        else {
        }
        }
    }
    return result;
}
std::shared_ptr<std::vector<std::shared_ptr<TestCompilationGroup>>> groupTestsForCompilation(const std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>>& tests) {
    const auto shared = std::make_shared<TestCompilationGroup>(std::string("shared"), std::make_shared<std::vector<std::shared_ptr<DiscoveredTest>>>(std::vector<std::shared_ptr<DiscoveredTest>>{}));
    std::shared_ptr<std::vector<std::shared_ptr<TestCompilationGroup>>> mocked = std::make_shared<std::vector<std::shared_ptr<TestCompilationGroup>>>(std::vector<std::shared_ptr<TestCompilationGroup>>{});
    const auto& _iterable_8 = tests;
    for (const auto& test : *_iterable_8) {
        if (!test->usesMocks) {
            shared->tests->push_back(test);
            continue;
        }
        std::shared_ptr<TestCompilationGroup> group = nullptr;
        const auto& _iterable_10 = mocked;
        for (const auto& existing : *_iterable_10) {
            if ((static_cast<int32_t>((existing->tests)->size()) > 0) && (doof::array_at(existing->tests, 0, "src/test-runner", 97)->modulePath == test->modulePath)) {
                (group = existing);
                break;
            }
        }
        if (doof::is_null(group)) {
            (group = std::make_shared<TestCompilationGroup>((std::string("mock-") + safeGroupName(test->moduleDisplayPath)), std::make_shared<std::vector<std::shared_ptr<DiscoveredTest>>>(std::vector<std::shared_ptr<DiscoveredTest>>{})));
            mocked->push_back(doof::unwrap_optional(group));
        }
        group->tests->push_back(test);
    }
    std::shared_ptr<std::vector<std::shared_ptr<TestCompilationGroup>>> result = std::make_shared<std::vector<std::shared_ptr<TestCompilationGroup>>>(std::vector<std::shared_ptr<TestCompilationGroup>>{});
    if (static_cast<int32_t>((shared->tests)->size()) > 0) {
        result->push_back(shared);
    }
    const auto& _iterable_12 = mocked;
    for (const auto& group : *_iterable_12) {
        result->push_back(group);
    }
    return result;
}
std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> filterDiscoveredTests(const std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>>& tests, const std::string& filter) {
    if (filter == std::string("")) {
        return copyTests(tests);
    }
    const auto needle = doof::string_toLowerCase(filter);
    std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> selected = std::make_shared<std::vector<std::shared_ptr<DiscoveredTest>>>(std::vector<std::shared_ptr<DiscoveredTest>>{});
    const auto& _iterable_14 = tests;
    for (const auto& test : *_iterable_14) {
        if (doof::string_contains(doof::string_toLowerCase(test->id), needle)) {
            selected->push_back(test);
        }
    }
    return selected;
}
std::string generateTestHarness(const std::string& harnessPath, const std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>>& tests) {
    auto source = std::string("");
    for (int32_t index = 0; index < static_cast<int32_t>((tests)->size()); ++index) {
        const auto test = doof::array_at(tests, index, "src/test-runner", 126);
        (source = (((((((source + std::string("import { ")) + test->name) + std::string(" as __doof_test_")) + doof::to_string(index)) + std::string(" } from \"")) + relativeImportSpecifier(harnessPath, test->modulePath)) + std::string("\"\n")));
    }
    (source = (source + std::string("\nfunction main(args: string[]): int {\n")));
    (source = (source + std::string("    if args.length < 1 {\n")));
    (source = (source + std::string("        println(\"missing test id\")\n")));
    (source = (source + std::string("        return 2\n")));
    (source = (source + std::string("    }\n\n")));
    (source = (source + std::string("    testId := args[0]\n")));
    for (int32_t index = 0; index < static_cast<int32_t>((tests)->size()); ++index) {
        const auto id = escapeDoofString(doof::array_at(tests, index, "src/test-runner", 136)->id);
        (source = (((source + std::string("    if testId == \"")) + id) + std::string("\" {\n")));
        (source = (((source + std::string("        __doof_test_")) + doof::to_string(index)) + std::string("()\n")));
        (source = (source + std::string("        return 0\n")));
        (source = (source + std::string("    }\n")));
    }
    (source = (source + std::string("\n")));
    (source = ((source + std::string("    println(\"unknown test id: $")) + std::string("{testId}\")\n")));
    (source = (source + std::string("    return 2\n")));
    (source = (source + std::string("}\n")));
    return source;
}
std::string safeGroupName(const std::string& value) {
    return doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(value, std::string("/"), std::string("_")), std::string("\\"), std::string("_")), std::string("."), std::string("_")), std::string("-"), std::string("_"));
}
std::string testDisplayPath(const std::string& rootDirectory, const std::string& modulePath) {
    const auto root = trimTrailingSlashes(doof::string_replaceAll(rootDirectory, std::string("\\"), std::string("/")));
    const auto module = doof::string_replaceAll(modulePath, std::string("\\"), std::string("/"));
    const auto prefix = (root + std::string("/"));
    if (doof::string_startsWith(module, prefix)) {
        return doof::string_substring(module, static_cast<int32_t>(prefix.size()), static_cast<int32_t>(module.size()));
    }
    return module;
}
std::string formatParseFailure(const std::string& modulePath, const std::string& source, int32_t line, int32_t column, const std::string& message) {
    const auto header = ((((((modulePath + std::string(":")) + doof::to_string(line)) + std::string(":")) + doof::to_string(column)) + std::string(": error: ")) + message);
    const auto lines = doof::string_split(source, std::string("\n"));
    if ((line < 1) || (line > static_cast<int32_t>((lines)->size()))) {
        return header;
    }
    const auto caretColumn = ((column < 1) ? 1 : column);
    return (((((header + std::string("\n")) + doof::array_at(lines, (line - 1), "src/test-runner", 174)) + std::string("\n")) + doof::string_repeat(std::string(" "), (caretColumn - 1))) + std::string("^"));
}
void mergeCoverageOutput(const std::string& output, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>>& modules, const std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>>& hitsByModule) {
    const auto& _iterable_18 = doof::string_split(output, std::string("\n"));
    for (const auto& line : *_iterable_18) {
        const auto trimmed = doof::string_trim(line);
        if (!doof::string_startsWith(trimmed, std::string("__COV__ "))) {
            continue;
        }
        const auto parts = doof::string_split(trimmed, std::string(" "));
        if (static_cast<int32_t>((parts)->size()) != 3) {
            continue;
        }
        const auto moduleId = parseCoverageInteger(doof::array_at(parts, 1, "src/test-runner", 188));
        const auto sourceLine = parseCoverageInteger(doof::array_at(parts, 2, "src/test-runner", 189));
        if ((moduleId < 0) || (sourceLine < 1)) {
            continue;
        }
        for (int32_t index = 0; index < static_cast<int32_t>((modules)->size()); ++index) {
            if (doof::array_at(modules, index, "src/test-runner", 192)->moduleId == moduleId) {
                while (static_cast<int32_t>((hitsByModule)->size()) <= index) {
                    hitsByModule->push_back(std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}));
                }
                appendUniqueLine(doof::array_at(hitsByModule, index, "src/test-runner", 194), sourceLine);
            }
        }
    }
}
std::string stripCoverageLines(const std::string& output) {
    auto result = std::string("");
    const auto& _iterable_21 = doof::string_split(output, std::string("\n"));
    for (const auto& line : *_iterable_21) {
        if (doof::string_startsWith(doof::string_trim(line), std::string("__COV__ "))) {
            continue;
        }
        if (result != std::string("")) {
            (result = (result + std::string("\n")));
        }
        (result = (result + line));
    }
    return doof::string_trim(result);
}
std::shared_ptr<CoverageReport> buildCoverageReport(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>>& modules, const std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>>& hitsByModule, const std::string& rootDirectory) {
    const auto report = std::make_shared<CoverageReport>(0, 0, 1000, std::make_shared<std::vector<std::shared_ptr<CoverageFileReport>>>(std::vector<std::shared_ptr<CoverageFileReport>>{}));
    for (int32_t index = 0; index < static_cast<int32_t>((modules)->size()); ++index) {
        const auto module = doof::array_at(modules, index, "src/test-runner", 219);
        if (static_cast<int32_t>((module->instrumentedLines)->size()) == 0) {
            continue;
        }
        std::shared_ptr<std::vector<int32_t>> hits = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
        if (index < static_cast<int32_t>((hitsByModule)->size())) {
            (hits = doof::array_at(hitsByModule, index, "src/test-runner", 222));
        }
        const auto file = std::make_shared<CoverageFileReport>(testDisplayPath(rootDirectory, module->modulePath), 0, static_cast<int32_t>((module->instrumentedLines)->size()), 0, std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}), std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}));
        const auto& _iterable_24 = module->instrumentedLines;
        for (const auto& line : *_iterable_24) {
            if (containsLine(hits, line)) {
                file->hitLines->push_back(line);
                (file->covered += 1);
            } else {
                file->missedLines->push_back(line);
            }
        }
        (file->percentTenths = coveragePercentTenths(file->covered, file->total));
        report->files->push_back(file);
        (report->totalCovered += file->covered);
        (report->totalLines += file->total);
    }
    (report->totalPercentTenths = coveragePercentTenths(report->totalCovered, report->totalLines));
    return report;
}
std::string renderCoverageJson(const std::shared_ptr<CoverageReport>& report) {
    auto output = (std::string("{\n  \"timestamp\": \"\",\n  \"totals\": { \"covered\": ") + doof::to_string(report->totalCovered));
    (output = (((((output + std::string(", \"total\": ")) + doof::to_string(report->totalLines)) + std::string(", \"percent\": ")) + coveragePercentText(report->totalPercentTenths)) + std::string(" },\n")));
    (output = (output + std::string("  \"files\": [")));
    for (int32_t index = 0; index < static_cast<int32_t>((report->files)->size()); ++index) {
        const auto file = doof::array_at(report->files, index, "src/test-runner", 248);
        (output = (output + ((index == 0) ? std::string("\n") : std::string(",\n"))));
        (output = (((output + std::string("    {\n      \"path\": \"")) + escapeJson(file->path)) + std::string("\",\n")));
        (output = (((output + std::string("      \"covered\": ")) + doof::to_string(file->covered)) + std::string(",\n")));
        (output = (((output + std::string("      \"total\": ")) + doof::to_string(file->total)) + std::string(",\n")));
        (output = (((output + std::string("      \"percent\": ")) + coveragePercentText(file->percentTenths)) + std::string(",\n")));
        (output = (((output + std::string("      \"hitLines\": ")) + renderLineArray(file->hitLines)) + std::string(",\n")));
        (output = (((output + std::string("      \"missedLines\": ")) + renderLineArray(file->missedLines)) + std::string("\n    }")));
    }
    return (output + ((static_cast<int32_t>((report->files)->size()) == 0) ? std::string("]\n}\n") : std::string("\n  ]\n}\n")));
}
std::string renderCoverageHtml(const std::shared_ptr<CoverageReport>& report, const std::string& fileDirectoryName) {
    auto rows = std::string("");
    const auto& _iterable_27 = report->files;
    for (const auto& file : *_iterable_27) {
        const auto href = escapeHtml(((fileDirectoryName + std::string("/")) + coverageFileRelativePath(file->path)));
        (rows = (((((rows + std::string("<tr><td><a href=\"")) + href) + std::string("\">")) + escapeHtml(file->path)) + std::string("</a></td>")));
        (rows = (((((rows + std::string("<td>")) + doof::to_string(file->covered)) + std::string("/")) + doof::to_string(file->total)) + std::string("</td>")));
        (rows = (((rows + std::string("<td>")) + coveragePercentText(file->percentTenths)) + std::string("%</td></tr>\n")));
    }
    const auto overall = coveragePercentText(report->totalPercentTenths);
    return (((((((((std::string("<!doctype html>\n<html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width\"><title>Doof Coverage Report</title><style>body{font:16px system-ui;max-width:960px;margin:2rem auto;padding:0 1rem;color:#1f2933}table{width:100%;border-collapse:collapse}th,td{text-align:left;padding:.65rem;border-bottom:1px solid #ddd}a{color:#9a3412}.summary{font-size:1.3rem}</style></head><body><h1>Doof Coverage</h1><p class=\"summary\">Overall: ") + doof::to_string(report->totalCovered)) + std::string("/")) + doof::to_string(report->totalLines)) + std::string(" lines (")) + overall) + std::string("%)</p>")) + std::string("<table><thead><tr><th>File</th><th>Lines</th><th>Coverage</th></tr></thead><tbody>")) + rows) + std::string("</tbody></table></body></html>\n"));
}
std::string renderCoverageFileHtml(const std::shared_ptr<CoverageFileReport>& file, const std::string& source, const std::string& indexHref) {
    auto lines = std::string("");
    const auto sourceLines = doof::string_split(source, std::string("\n"));
    for (int32_t index = 0; index < static_cast<int32_t>((sourceLines)->size()); ++index) {
        const auto line = (index + 1);
        const auto className = (containsLine(file->hitLines, line) ? std::string("covered") : (containsLine(file->missedLines, line) ? std::string("missed") : std::string("neutral")));
        (lines = (((((((lines + std::string("<div class=\"line ")) + className) + std::string("\"><span>")) + doof::to_string(line)) + std::string("</span><code>")) + escapeHtml(doof::array_at(sourceLines, index, "src/test-runner", 286))) + std::string("</code></div>\n")));
    }
    return (((((((((((std::string("<!doctype html>\n<html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width\"><title>") + escapeHtml(file->path)) + std::string(" — Doof Coverage</title><style>body{font:15px system-ui;margin:2rem;color:#1f2933}")) + std::string(".line{display:grid;grid-template-columns:4rem 1fr;font-family:monospace;white-space:pre}.line span{text-align:right;padding-right:1rem;color:#6b7280}")) + std::string(".covered{background:#dcfce7}.missed{background:#fee2e2}.neutral{background:#f8fafc}a{color:#9a3412}</style></head><body>")) + std::string("<a href=\"")) + escapeHtml(indexHref)) + std::string("\">Back to coverage summary</a><h1>")) + escapeHtml(file->path)) + std::string("</h1>")) + lines) + std::string("</body></html>\n"));
}
std::string coverageFileRelativePath(const std::string& path) {
    return (doof::string_replaceAll(doof::string_replaceAll(path, std::string("\\"), std::string("/")), std::string("../"), std::string("_external/")) + std::string(".html"));
}
int32_t parseCoverageInteger(const std::string& value) {
    if (value == std::string("")) {
        return -1;
    }
    auto result = 0;
    for (int32_t index = 0; index < static_cast<int32_t>(value.size()); ++index) {
        const auto char_ = doof::string_at(value, index, "src/test-runner", 305);
        auto digit = -1;
        if (char_ == U'\u0030') {
            (digit = 0);
        } else if (char_ == U'\u0031') {
            (digit = 1);
        } else if (char_ == U'\u0032') {
            (digit = 2);
        } else if (char_ == U'\u0033') {
            (digit = 3);
        } else if (char_ == U'\u0034') {
            (digit = 4);
        } else if (char_ == U'\u0035') {
            (digit = 5);
        } else if (char_ == U'\u0036') {
            (digit = 6);
        } else if (char_ == U'\u0037') {
            (digit = 7);
        } else if (char_ == U'\u0038') {
            (digit = 8);
        } else if (char_ == U'\u0039') {
            (digit = 9);
        }
        if (digit < 0) {
            return -1;
        }
        (result = ((result * 10) + digit));
    }
    return result;
}
void appendUniqueLine(const std::shared_ptr<std::vector<int32_t>>& lines, int32_t line) {
    if (!containsLine(lines, line)) {
        lines->push_back(line);
    }
}
bool containsLine(const std::shared_ptr<std::vector<int32_t>>& lines, int32_t line) {
    const auto& _iterable_31 = lines;
    for (const auto& existing : *_iterable_31) {
        if (existing == line) {
            return true;
        }
    }
    return false;
}
int32_t coveragePercentTenths(int32_t covered, int32_t total) {
    if (total == 0) {
        return 1000;
    }
    return (((covered * 1000) + (total / 2)) / total);
}
std::string coveragePercentText(int32_t tenths) {
    return ((doof::to_string((tenths / 10)) + std::string(".")) + doof::to_string((tenths % 10)));
}
std::string renderLineArray(const std::shared_ptr<std::vector<int32_t>>& lines) {
    auto result = std::string("[");
    for (int32_t index = 0; index < static_cast<int32_t>((lines)->size()); ++index) {
        if (index > 0) {
            (result = (result + std::string(", ")));
        }
        (result = (result + doof::to_string(doof::array_at(lines, index, "src/test-runner", 345))));
    }
    return (result + std::string("]"));
}
std::string escapeJson(const std::string& value) {
    return doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(value, std::string("\\"), std::string("\\\\")), std::string("\""), std::string("\\\"")), std::string("\n"), std::string("\\n"));
}
std::string escapeHtml(const std::string& value) {
    return doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(value, std::string("&"), std::string("&amp;")), std::string("<"), std::string("&lt;")), std::string(">"), std::string("&gt;")), std::string("\""), std::string("&quot;")), std::string("'"), std::string("&#39;"));
}
void addDiscoveredTest(const std::shared_ptr<TestDiscovery>& result, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& declaration, const std::string& exportedName, const std::string& modulePath, const std::string& rootDirectory, bool usesMocks) {
    const auto location = ((((modulePath + std::string(":")) + doof::to_string(declaration->span.start.line)) + std::string(":")) + doof::to_string(declaration->span.start.column));
    if (static_cast<int32_t>((declaration->params)->size()) > 0) {
        result->errors->push_back((((location + std::string(": error: test \"")) + exportedName) + std::string("\" must not declare parameters")));
        return;
    }
    if (static_cast<int32_t>((declaration->typeParams)->size()) > 0) {
        result->errors->push_back((((location + std::string(": error: test \"")) + exportedName) + std::string("\" must not declare type parameters")));
        return;
    }
    if (!returnsNone(declaration)) {
        result->errors->push_back((((location + std::string(": error: test \"")) + exportedName) + std::string("\" must return none")));
        return;
    }
    const auto displayPath = testDisplayPath(rootDirectory, modulePath);
    result->tests->push_back(std::make_shared<DiscoveredTest>(((displayPath + std::string("::")) + exportedName), exportedName, modulePath, displayPath, usesMocks));
}
bool returnsNone(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& declaration) {
    if (doof::is_null(declaration->returnType)) {
        {
            auto _case_subject = declaration->body;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                return true;
        }
        else {
                return false;
        }
        }
        doof::unreachable();
    }
    {
        auto _case_subject = doof::unwrap_optional(declaration->returnType);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
            return ((named->name == std::string("none")) || (named->name == std::string("void")));
    }
    else {
            return false;
    }
    }
    doof::unreachable();
}
std::shared_ptr<::app_src_ast_::FunctionDeclaration> findFunction(const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>>& statements, const std::string& name) {
    const auto& _iterable_34 = statements;
    for (const auto& statement : *_iterable_34) {
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
                const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
                if (fn->name == name) {
                    return fn;
                }
        }
        else {
        }
        }
    }
    return nullptr;
}
std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> copyTests(const std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>>& tests) {
    std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> result = std::make_shared<std::vector<std::shared_ptr<DiscoveredTest>>>(std::vector<std::shared_ptr<DiscoveredTest>>{});
    const auto& _iterable_36 = tests;
    for (const auto& test : *_iterable_36) {
        result->push_back(test);
    }
    return result;
}
std::string relativeImportSpecifier(const std::string& harnessPath, const std::string& modulePath) {
    const auto sourceComponents = parentComponents(doof::string_replaceAll(harnessPath, std::string("\\"), std::string("/")));
    const auto to = doof::string_split(withoutExtension(doof::string_replaceAll(modulePath, std::string("\\"), std::string("/"))), std::string("/"));
    auto common = 0;
    while (((common < static_cast<int32_t>((sourceComponents)->size())) && (common < static_cast<int32_t>((to)->size()))) && (doof::array_at(sourceComponents, common, "src/test-runner", 422) == doof::array_at(to, common, "src/test-runner", 422))) {
        (common = (common + 1));
    }
    auto result = std::string("");
    for (int32_t ignored = common; ignored < static_cast<int32_t>((sourceComponents)->size()); ++ignored) {
        (result = (result + std::string("../")));
    }
    for (int32_t index = common; index < static_cast<int32_t>((to)->size()); ++index) {
        if ((result != std::string("")) && !doof::string_endsWith(result, std::string("/"))) {
            (result = (result + std::string("/")));
        }
        (result = (result + doof::array_at(to, index, "src/test-runner", 429)));
    }
    if (!doof::string_startsWith(result, std::string("."))) {
        return (std::string("./") + result);
    }
    return result;
}
std::shared_ptr<std::vector<std::string>> parentComponents(const std::string& path) {
    const auto components = doof::array_cloneMutable(doof::string_split(path, std::string("/")), "", 0);
    if (static_cast<int32_t>((components)->size()) > 0) {
        auto ignored = [&]() -> std::string { auto _try_value = doof::array_pop(components); if (doof::is_failure(_try_value)) doof::panic_at("src/test-runner", 437, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
    }
    return components;
}
std::string withoutExtension(const std::string& path) {
    if (doof::string_endsWith(path, std::string(".do"))) {
        return doof::string_substring(path, 0, (static_cast<int32_t>(path.size()) - 3));
    }
    return path;
}
std::string trimTrailingSlashes(const std::string& path) {
    auto end = static_cast<int32_t>(path.size());
    while ((end > 1) && (doof::string_at(path, (end - 1), "src/test-runner", 448) == U'\u002F')) {
        (end = (end - 1));
    }
    return doof::string_substring(path, 0, end);
}
std::string escapeDoofString(const std::string& value) {
    return doof::string_replaceAll(doof::string_replaceAll(value, std::string("\\"), std::string("\\\\")), std::string("\""), std::string("\\\""));
}
}

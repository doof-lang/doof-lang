#include "src_test_runner.hpp"

namespace app_src_test_runner_ {
using namespace ::app_src_ast_;
using namespace ::app_src_emitter_module_;





#line 49 "/src/test-runner.do"
std::shared_ptr<TestDiscovery> discoverModuleTests(const std::shared_ptr<::app_src_ast_::Program>& program, const std::string& modulePath, const std::string& rootDirectory) {
#line 54 "/src/test-runner.do"
    const auto result = std::make_shared<TestDiscovery>(std::make_shared<std::vector<std::shared_ptr<DiscoveredTest>>>(std::vector<std::shared_ptr<DiscoveredTest>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 55 "/src/test-runner.do"
    auto usesMocks = false;
#line 56 "/src/test-runner.do"
    const auto& _iterable_2 = program->statements;
    for (const auto& statement : *_iterable_2) {
#line 57 "/src/test-runner.do"
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MockImportDirective>>(_case_subject)) {
#line 58 "/src/test-runner.do"
                (usesMocks = true);
        }
        else {
        }
        }
    }
#line 62 "/src/test-runner.do"
    const auto& _iterable_4 = program->statements;
    for (const auto& statement : *_iterable_4) {
#line 63 "/src/test-runner.do"
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
                const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
#line 65 "/src/test-runner.do"
                if (fn->exported && doof::string_startsWith(fn->name, std::string("test"))) {
#line 66 "/src/test-runner.do"
                    addDiscoveredTest(result, fn, fn->name, modulePath, rootDirectory, usesMocks);
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportList>>(_case_subject)) {
                const auto& list = std::get<std::shared_ptr<::app_src_ast_::ExportList>>(_case_subject);
#line 70 "/src/test-runner.do"
                if (!doof::is_null(list->source)) {
#line 70 "/src/test-runner.do"
                    continue;
                }
#line 71 "/src/test-runner.do"
                const auto& _iterable_6 = list->specifiers;
                for (const auto& specifier : *_iterable_6) {
#line 72 "/src/test-runner.do"
                    const auto exportedName = (doof::is_null(specifier->alias) ? specifier->name : doof::unwrap_optional(specifier->alias));
#line 73 "/src/test-runner.do"
                    if (!doof::string_startsWith(exportedName, std::string("test"))) {
#line 73 "/src/test-runner.do"
                        continue;
                    }
#line 74 "/src/test-runner.do"
                    const auto declaration = findFunction(program->statements, specifier->name);
#line 75 "/src/test-runner.do"
                    if (!doof::is_null(declaration)) {
#line 76 "/src/test-runner.do"
                        addDiscoveredTest(result, doof::unwrap_optional(declaration), exportedName, modulePath, rootDirectory, usesMocks);
                    }
                }
        }
        else {
        }
        }
    }
#line 83 "/src/test-runner.do"
    return result;
}
#line 87 "/src/test-runner.do"
std::shared_ptr<std::vector<std::shared_ptr<TestCompilationGroup>>> groupTestsForCompilation(const std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>>& tests) {
#line 88 "/src/test-runner.do"
    const auto shared = std::make_shared<TestCompilationGroup>(std::string("shared"), std::make_shared<std::vector<std::shared_ptr<DiscoveredTest>>>(std::vector<std::shared_ptr<DiscoveredTest>>{}));
#line 89 "/src/test-runner.do"
    std::shared_ptr<std::vector<std::shared_ptr<TestCompilationGroup>>> mocked = std::make_shared<std::vector<std::shared_ptr<TestCompilationGroup>>>(std::vector<std::shared_ptr<TestCompilationGroup>>{});
#line 90 "/src/test-runner.do"
    const auto& _iterable_8 = tests;
    for (const auto& test : *_iterable_8) {
#line 91 "/src/test-runner.do"
        if (!test->usesMocks) {
#line 92 "/src/test-runner.do"
            shared->tests->push_back(test);
#line 93 "/src/test-runner.do"
            continue;
        }
#line 95 "/src/test-runner.do"
        std::shared_ptr<TestCompilationGroup> group = nullptr;
#line 96 "/src/test-runner.do"
        const auto& _iterable_10 = mocked;
        for (const auto& existing : *_iterable_10) {
#line 97 "/src/test-runner.do"
            if ((static_cast<int32_t>((existing->tests)->size()) > 0) && (doof::array_at(existing->tests, 0, "src/test-runner", 97)->modulePath == test->modulePath)) {
#line 97 "/src/test-runner.do"
                (group = existing);
#line 97 "/src/test-runner.do"
                break;
            }
        }
#line 99 "/src/test-runner.do"
        if (doof::is_null(group)) {
#line 100 "/src/test-runner.do"
            (group = std::make_shared<TestCompilationGroup>((std::string("mock-") + safeGroupName(test->moduleDisplayPath)), std::make_shared<std::vector<std::shared_ptr<DiscoveredTest>>>(std::vector<std::shared_ptr<DiscoveredTest>>{})));
#line 101 "/src/test-runner.do"
            mocked->push_back(doof::unwrap_optional(group));
        }
#line 103 "/src/test-runner.do"
        group->tests->push_back(test);
    }
#line 105 "/src/test-runner.do"
    std::shared_ptr<std::vector<std::shared_ptr<TestCompilationGroup>>> result = std::make_shared<std::vector<std::shared_ptr<TestCompilationGroup>>>(std::vector<std::shared_ptr<TestCompilationGroup>>{});
#line 106 "/src/test-runner.do"
    if (static_cast<int32_t>((shared->tests)->size()) > 0) {
#line 106 "/src/test-runner.do"
        result->push_back(shared);
    }
#line 107 "/src/test-runner.do"
    const auto& _iterable_12 = mocked;
    for (const auto& group : *_iterable_12) {
#line 107 "/src/test-runner.do"
        result->push_back(group);
    }
#line 108 "/src/test-runner.do"
    return result;
}
#line 112 "/src/test-runner.do"
std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> filterDiscoveredTests(const std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>>& tests, const std::string& filter) {
#line 113 "/src/test-runner.do"
    if (filter == std::string("")) {
#line 113 "/src/test-runner.do"
        return copyTests(tests);
    }
#line 114 "/src/test-runner.do"
    const auto needle = doof::string_toLowerCase(filter);
#line 115 "/src/test-runner.do"
    std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> selected = std::make_shared<std::vector<std::shared_ptr<DiscoveredTest>>>(std::vector<std::shared_ptr<DiscoveredTest>>{});
#line 116 "/src/test-runner.do"
    const auto& _iterable_14 = tests;
    for (const auto& test : *_iterable_14) {
#line 117 "/src/test-runner.do"
        if (doof::string_contains(doof::string_toLowerCase(test->id), needle)) {
#line 117 "/src/test-runner.do"
            selected->push_back(test);
        }
    }
#line 119 "/src/test-runner.do"
    return selected;
}
#line 123 "/src/test-runner.do"
std::string generateTestHarness(const std::string& harnessPath, const std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>>& tests) {
#line 124 "/src/test-runner.do"
    auto source = std::string("");
#line 125 "/src/test-runner.do"
    for (int32_t index = 0; index < static_cast<int32_t>((tests)->size()); ++index) {
#line 126 "/src/test-runner.do"
        const auto test = doof::array_at(tests, index, "src/test-runner", 126);
#line 127 "/src/test-runner.do"
        (source = (((((((source + std::string("import { ")) + test->name) + std::string(" as __doof_test_")) + doof::to_string(index)) + std::string(" } from \"")) + relativeImportSpecifier(harnessPath, test->modulePath)) + std::string("\"\n")));
    }
#line 129 "/src/test-runner.do"
    (source = (source + std::string("\nfunction main(args: string[]): int {\n")));
#line 130 "/src/test-runner.do"
    (source = (source + std::string("    if args.length < 1 {\n")));
#line 131 "/src/test-runner.do"
    (source = (source + std::string("        println(\"missing test id\")\n")));
#line 132 "/src/test-runner.do"
    (source = (source + std::string("        return 2\n")));
#line 133 "/src/test-runner.do"
    (source = (source + std::string("    }\n\n")));
#line 134 "/src/test-runner.do"
    (source = (source + std::string("    testId := args[0]\n")));
#line 135 "/src/test-runner.do"
    for (int32_t index = 0; index < static_cast<int32_t>((tests)->size()); ++index) {
#line 136 "/src/test-runner.do"
        const auto id = escapeDoofString(doof::array_at(tests, index, "src/test-runner", 136)->id);
#line 137 "/src/test-runner.do"
        (source = (((source + std::string("    if testId == \"")) + id) + std::string("\" {\n")));
#line 138 "/src/test-runner.do"
        (source = (((source + std::string("        __doof_test_")) + doof::to_string(index)) + std::string("()\n")));
#line 139 "/src/test-runner.do"
        (source = (source + std::string("        return 0\n")));
#line 140 "/src/test-runner.do"
        (source = (source + std::string("    }\n")));
    }
#line 142 "/src/test-runner.do"
    (source = (source + std::string("\n")));
#line 143 "/src/test-runner.do"
    (source = ((source + std::string("    println(\"unknown test id: $")) + std::string("{testId}\")\n")));
#line 144 "/src/test-runner.do"
    (source = (source + std::string("    return 2\n")));
#line 145 "/src/test-runner.do"
    (source = (source + std::string("}\n")));
#line 146 "/src/test-runner.do"
    return source;
}
#line 149 "/src/test-runner.do"
std::string safeGroupName(const std::string& value) {
#line 150 "/src/test-runner.do"
    return doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(value, std::string("/"), std::string("_")), std::string("\\"), std::string("_")), std::string("."), std::string("_")), std::string("-"), std::string("_"));
}
#line 154 "/src/test-runner.do"
std::string testDisplayPath(const std::string& rootDirectory, const std::string& modulePath) {
#line 155 "/src/test-runner.do"
    const auto root = trimTrailingSlashes(doof::string_replaceAll(rootDirectory, std::string("\\"), std::string("/")));
#line 156 "/src/test-runner.do"
    const auto module = doof::string_replaceAll(modulePath, std::string("\\"), std::string("/"));
#line 157 "/src/test-runner.do"
    const auto prefix = (root + std::string("/"));
#line 158 "/src/test-runner.do"
    if (doof::string_startsWith(module, prefix)) {
#line 158 "/src/test-runner.do"
        return doof::string_substring(module, static_cast<int32_t>(prefix.size()), static_cast<int32_t>(module.size()));
    }
#line 159 "/src/test-runner.do"
    return module;
}
#line 163 "/src/test-runner.do"
std::string formatParseFailure(const std::string& modulePath, const std::string& source, int32_t line, int32_t column, const std::string& message) {
#line 170 "/src/test-runner.do"
    const auto header = ((((((modulePath + std::string(":")) + doof::to_string(line)) + std::string(":")) + doof::to_string(column)) + std::string(": error: ")) + message);
#line 171 "/src/test-runner.do"
    const auto lines = doof::string_split(source, std::string("\n"));
#line 172 "/src/test-runner.do"
    if ((line < 1) || (line > static_cast<int32_t>((lines)->size()))) {
#line 172 "/src/test-runner.do"
        return header;
    }
#line 173 "/src/test-runner.do"
    const auto caretColumn = ((column < 1) ? 1 : column);
#line 174 "/src/test-runner.do"
    return (((((header + std::string("\n")) + doof::array_at(lines, (line - 1), "src/test-runner", 174)) + std::string("\n")) + doof::string_repeat(std::string(" "), (caretColumn - 1))) + std::string("^"));
}
#line 178 "/src/test-runner.do"
void mergeCoverageOutput(const std::string& output, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>>& modules, const std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>>& hitsByModule) {
#line 183 "/src/test-runner.do"
    const auto& _iterable_18 = doof::string_split(output, std::string("\n"));
    for (const auto& line : *_iterable_18) {
#line 184 "/src/test-runner.do"
        const auto trimmed = doof::string_trim(line);
#line 185 "/src/test-runner.do"
        if (!doof::string_startsWith(trimmed, std::string("__COV__ "))) {
#line 185 "/src/test-runner.do"
            continue;
        }
#line 186 "/src/test-runner.do"
        const auto parts = doof::string_split(trimmed, std::string(" "));
#line 187 "/src/test-runner.do"
        if (static_cast<int32_t>((parts)->size()) != 3) {
#line 187 "/src/test-runner.do"
            continue;
        }
#line 188 "/src/test-runner.do"
        const auto moduleId = parseCoverageInteger(doof::array_at(parts, 1, "src/test-runner", 188));
#line 189 "/src/test-runner.do"
        const auto sourceLine = parseCoverageInteger(doof::array_at(parts, 2, "src/test-runner", 189));
#line 190 "/src/test-runner.do"
        if ((moduleId < 0) || (sourceLine < 1)) {
#line 190 "/src/test-runner.do"
            continue;
        }
#line 191 "/src/test-runner.do"
        for (int32_t index = 0; index < static_cast<int32_t>((modules)->size()); ++index) {
#line 192 "/src/test-runner.do"
            if (doof::array_at(modules, index, "src/test-runner", 192)->moduleId == moduleId) {
#line 193 "/src/test-runner.do"
                while (static_cast<int32_t>((hitsByModule)->size()) <= index) {
#line 193 "/src/test-runner.do"
                    hitsByModule->push_back(std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}));
                }
#line 194 "/src/test-runner.do"
                appendUniqueLine(doof::array_at(hitsByModule, index, "src/test-runner", 194), sourceLine);
            }
        }
    }
}
#line 201 "/src/test-runner.do"
std::string stripCoverageLines(const std::string& output) {
#line 202 "/src/test-runner.do"
    auto result = std::string("");
#line 203 "/src/test-runner.do"
    const auto& _iterable_21 = doof::string_split(output, std::string("\n"));
    for (const auto& line : *_iterable_21) {
#line 204 "/src/test-runner.do"
        if (doof::string_startsWith(doof::string_trim(line), std::string("__COV__ "))) {
#line 204 "/src/test-runner.do"
            continue;
        }
#line 205 "/src/test-runner.do"
        if (result != std::string("")) {
#line 205 "/src/test-runner.do"
            (result = (result + std::string("\n")));
        }
#line 206 "/src/test-runner.do"
        (result = (result + line));
    }
#line 208 "/src/test-runner.do"
    return doof::string_trim(result);
}
#line 212 "/src/test-runner.do"
std::shared_ptr<CoverageReport> buildCoverageReport(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>>& modules, const std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>>& hitsByModule, const std::string& rootDirectory) {
#line 217 "/src/test-runner.do"
    const auto report = std::make_shared<CoverageReport>(0, 0, 1000, std::make_shared<std::vector<std::shared_ptr<CoverageFileReport>>>(std::vector<std::shared_ptr<CoverageFileReport>>{}));
#line 218 "/src/test-runner.do"
    for (int32_t index = 0; index < static_cast<int32_t>((modules)->size()); ++index) {
#line 219 "/src/test-runner.do"
        const auto module = doof::array_at(modules, index, "src/test-runner", 219);
#line 220 "/src/test-runner.do"
        if (static_cast<int32_t>((module->instrumentedLines)->size()) == 0) {
#line 220 "/src/test-runner.do"
            continue;
        }
#line 221 "/src/test-runner.do"
        std::shared_ptr<std::vector<int32_t>> hits = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
#line 222 "/src/test-runner.do"
        if (index < static_cast<int32_t>((hitsByModule)->size())) {
#line 222 "/src/test-runner.do"
            (hits = doof::array_at(hitsByModule, index, "src/test-runner", 222));
        }
#line 223 "/src/test-runner.do"
        const auto file = std::make_shared<CoverageFileReport>(testDisplayPath(rootDirectory, module->modulePath), 0, static_cast<int32_t>((module->instrumentedLines)->size()), 0, std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}), std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}));
#line 229 "/src/test-runner.do"
        const auto& _iterable_24 = module->instrumentedLines;
        for (const auto& line : *_iterable_24) {
#line 230 "/src/test-runner.do"
            if (containsLine(hits, line)) {
#line 230 "/src/test-runner.do"
                file->hitLines->push_back(line);
#line 230 "/src/test-runner.do"
                (file->covered += 1);
            } else {
#line 231 "/src/test-runner.do"
                file->missedLines->push_back(line);
            }
        }
#line 233 "/src/test-runner.do"
        (file->percentTenths = coveragePercentTenths(file->covered, file->total));
#line 234 "/src/test-runner.do"
        report->files->push_back(file);
#line 235 "/src/test-runner.do"
        (report->totalCovered += file->covered);
#line 236 "/src/test-runner.do"
        (report->totalLines += file->total);
    }
#line 238 "/src/test-runner.do"
    (report->totalPercentTenths = coveragePercentTenths(report->totalCovered, report->totalLines));
#line 239 "/src/test-runner.do"
    return report;
}
#line 243 "/src/test-runner.do"
std::string renderCoverageJson(const std::shared_ptr<CoverageReport>& report) {
#line 244 "/src/test-runner.do"
    auto output = (std::string("{\n  \"timestamp\": \"\",\n  \"totals\": { \"covered\": ") + doof::to_string(report->totalCovered));
#line 245 "/src/test-runner.do"
    (output = (((((output + std::string(", \"total\": ")) + doof::to_string(report->totalLines)) + std::string(", \"percent\": ")) + coveragePercentText(report->totalPercentTenths)) + std::string(" },\n")));
#line 246 "/src/test-runner.do"
    (output = (output + std::string("  \"files\": [")));
#line 247 "/src/test-runner.do"
    for (int32_t index = 0; index < static_cast<int32_t>((report->files)->size()); ++index) {
#line 248 "/src/test-runner.do"
        const auto file = doof::array_at(report->files, index, "src/test-runner", 248);
#line 249 "/src/test-runner.do"
        (output = (output + ((index == 0) ? std::string("\n") : std::string(",\n"))));
#line 250 "/src/test-runner.do"
        (output = (((output + std::string("    {\n      \"path\": \"")) + escapeJson(file->path)) + std::string("\",\n")));
#line 251 "/src/test-runner.do"
        (output = (((output + std::string("      \"covered\": ")) + doof::to_string(file->covered)) + std::string(",\n")));
#line 252 "/src/test-runner.do"
        (output = (((output + std::string("      \"total\": ")) + doof::to_string(file->total)) + std::string(",\n")));
#line 253 "/src/test-runner.do"
        (output = (((output + std::string("      \"percent\": ")) + coveragePercentText(file->percentTenths)) + std::string(",\n")));
#line 254 "/src/test-runner.do"
        (output = (((output + std::string("      \"hitLines\": ")) + renderLineArray(file->hitLines)) + std::string(",\n")));
#line 255 "/src/test-runner.do"
        (output = (((output + std::string("      \"missedLines\": ")) + renderLineArray(file->missedLines)) + std::string("\n    }")));
    }
#line 257 "/src/test-runner.do"
    return (output + ((static_cast<int32_t>((report->files)->size()) == 0) ? std::string("]\n}\n") : std::string("\n  ]\n}\n")));
}
#line 261 "/src/test-runner.do"
std::string renderCoverageHtml(const std::shared_ptr<CoverageReport>& report, const std::string& fileDirectoryName) {
#line 262 "/src/test-runner.do"
    auto rows = std::string("");
#line 263 "/src/test-runner.do"
    const auto& _iterable_27 = report->files;
    for (const auto& file : *_iterable_27) {
#line 264 "/src/test-runner.do"
        const auto href = escapeHtml(((fileDirectoryName + std::string("/")) + coverageFileRelativePath(file->path)));
#line 265 "/src/test-runner.do"
        (rows = (((((rows + std::string("<tr><td><a href=\"")) + href) + std::string("\">")) + escapeHtml(file->path)) + std::string("</a></td>")));
#line 266 "/src/test-runner.do"
        (rows = (((((rows + std::string("<td>")) + doof::to_string(file->covered)) + std::string("/")) + doof::to_string(file->total)) + std::string("</td>")));
#line 267 "/src/test-runner.do"
        (rows = (((rows + std::string("<td>")) + coveragePercentText(file->percentTenths)) + std::string("%</td></tr>\n")));
    }
#line 269 "/src/test-runner.do"
    const auto overall = coveragePercentText(report->totalPercentTenths);
#line 270 "/src/test-runner.do"
    return (((((((((std::string("<!doctype html>\n<html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width\"><title>Doof Coverage Report</title><style>body{font:16px system-ui;max-width:960px;margin:2rem auto;padding:0 1rem;color:#1f2933}table{width:100%;border-collapse:collapse}th,td{text-align:left;padding:.65rem;border-bottom:1px solid #ddd}a{color:#9a3412}.summary{font-size:1.3rem}</style></head><body><h1>Doof Coverage</h1><p class=\"summary\">Overall: ") + doof::to_string(report->totalCovered)) + std::string("/")) + doof::to_string(report->totalLines)) + std::string(" lines (")) + overall) + std::string("%)</p>")) + std::string("<table><thead><tr><th>File</th><th>Lines</th><th>Coverage</th></tr></thead><tbody>")) + rows) + std::string("</tbody></table></body></html>\n"));
}
#line 280 "/src/test-runner.do"
std::string renderCoverageFileHtml(const std::shared_ptr<CoverageFileReport>& file, const std::string& source, const std::string& indexHref) {
#line 281 "/src/test-runner.do"
    auto lines = std::string("");
#line 282 "/src/test-runner.do"
    const auto sourceLines = doof::string_split(source, std::string("\n"));
#line 283 "/src/test-runner.do"
    for (int32_t index = 0; index < static_cast<int32_t>((sourceLines)->size()); ++index) {
#line 284 "/src/test-runner.do"
        const auto line = (index + 1);
#line 285 "/src/test-runner.do"
        const auto className = (containsLine(file->hitLines, line) ? std::string("covered") : (containsLine(file->missedLines, line) ? std::string("missed") : std::string("neutral")));
#line 286 "/src/test-runner.do"
        (lines = (((((((lines + std::string("<div class=\"line ")) + className) + std::string("\"><span>")) + doof::to_string(line)) + std::string("</span><code>")) + escapeHtml(doof::array_at(sourceLines, index, "src/test-runner", 286))) + std::string("</code></div>\n")));
    }
#line 288 "/src/test-runner.do"
    return (((((((((((std::string("<!doctype html>\n<html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width\"><title>") + escapeHtml(file->path)) + std::string(" — Doof Coverage</title><style>body{font:15px system-ui;margin:2rem;color:#1f2933}")) + std::string(".line{display:grid;grid-template-columns:4rem 1fr;font-family:monospace;white-space:pre}.line span{text-align:right;padding-right:1rem;color:#6b7280}")) + std::string(".covered{background:#dcfce7}.missed{background:#fee2e2}.neutral{background:#f8fafc}a{color:#9a3412}</style></head><body>")) + std::string("<a href=\"")) + escapeHtml(indexHref)) + std::string("\">Back to coverage summary</a><h1>")) + escapeHtml(file->path)) + std::string("</h1>")) + lines) + std::string("</body></html>\n"));
}
#line 297 "/src/test-runner.do"
std::string coverageFileRelativePath(const std::string& path) {
#line 298 "/src/test-runner.do"
    return (doof::string_replaceAll(doof::string_replaceAll(path, std::string("\\"), std::string("/")), std::string("../"), std::string("_external/")) + std::string(".html"));
}
#line 301 "/src/test-runner.do"
int32_t parseCoverageInteger(const std::string& value) {
#line 302 "/src/test-runner.do"
    if (value == std::string("")) {
#line 302 "/src/test-runner.do"
        return -1;
    }
#line 303 "/src/test-runner.do"
    auto result = 0;
#line 304 "/src/test-runner.do"
    for (int32_t index = 0; index < static_cast<int32_t>(value.size()); ++index) {
#line 305 "/src/test-runner.do"
        const auto char_ = doof::string_at(value, index, "src/test-runner", 305);
#line 306 "/src/test-runner.do"
        auto digit = -1;
#line 307 "/src/test-runner.do"
        if (char_ == U'\u0030') {
#line 307 "/src/test-runner.do"
            (digit = 0);
        } else if (char_ == U'\u0031') {
#line 308 "/src/test-runner.do"
            (digit = 1);
        } else if (char_ == U'\u0032') {
#line 309 "/src/test-runner.do"
            (digit = 2);
        } else if (char_ == U'\u0033') {
#line 310 "/src/test-runner.do"
            (digit = 3);
        } else if (char_ == U'\u0034') {
#line 311 "/src/test-runner.do"
            (digit = 4);
        } else if (char_ == U'\u0035') {
#line 312 "/src/test-runner.do"
            (digit = 5);
        } else if (char_ == U'\u0036') {
#line 313 "/src/test-runner.do"
            (digit = 6);
        } else if (char_ == U'\u0037') {
#line 314 "/src/test-runner.do"
            (digit = 7);
        } else if (char_ == U'\u0038') {
#line 315 "/src/test-runner.do"
            (digit = 8);
        } else if (char_ == U'\u0039') {
#line 316 "/src/test-runner.do"
            (digit = 9);
        }
#line 317 "/src/test-runner.do"
        if (digit < 0) {
#line 317 "/src/test-runner.do"
            return -1;
        }
#line 318 "/src/test-runner.do"
        (result = ((result * 10) + digit));
    }
#line 320 "/src/test-runner.do"
    return result;
}
#line 323 "/src/test-runner.do"
void appendUniqueLine(const std::shared_ptr<std::vector<int32_t>>& lines, int32_t line) {
#line 324 "/src/test-runner.do"
    if (!containsLine(lines, line)) {
#line 324 "/src/test-runner.do"
        lines->push_back(line);
    }
}
#line 327 "/src/test-runner.do"
bool containsLine(const std::shared_ptr<std::vector<int32_t>>& lines, int32_t line) {
#line 328 "/src/test-runner.do"
    const auto& _iterable_31 = lines;
    for (const auto& existing : *_iterable_31) {
#line 328 "/src/test-runner.do"
        if (existing == line) {
#line 328 "/src/test-runner.do"
            return true;
        }
    }
#line 329 "/src/test-runner.do"
    return false;
}
#line 332 "/src/test-runner.do"
int32_t coveragePercentTenths(int32_t covered, int32_t total) {
#line 333 "/src/test-runner.do"
    if (total == 0) {
#line 333 "/src/test-runner.do"
        return 1000;
    }
#line 334 "/src/test-runner.do"
    return (((covered * 1000) + (total / 2)) / total);
}
#line 337 "/src/test-runner.do"
std::string coveragePercentText(int32_t tenths) {
#line 338 "/src/test-runner.do"
    return ((doof::to_string((tenths / 10)) + std::string(".")) + doof::to_string((tenths % 10)));
}
#line 341 "/src/test-runner.do"
std::string renderLineArray(const std::shared_ptr<std::vector<int32_t>>& lines) {
#line 342 "/src/test-runner.do"
    auto result = std::string("[");
#line 343 "/src/test-runner.do"
    for (int32_t index = 0; index < static_cast<int32_t>((lines)->size()); ++index) {
#line 344 "/src/test-runner.do"
        if (index > 0) {
#line 344 "/src/test-runner.do"
            (result = (result + std::string(", ")));
        }
#line 345 "/src/test-runner.do"
        (result = (result + doof::to_string(doof::array_at(lines, index, "src/test-runner", 345))));
    }
#line 347 "/src/test-runner.do"
    return (result + std::string("]"));
}
#line 350 "/src/test-runner.do"
std::string escapeJson(const std::string& value) {
#line 351 "/src/test-runner.do"
    return doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(value, std::string("\\"), std::string("\\\\")), std::string("\""), std::string("\\\"")), std::string("\n"), std::string("\\n"));
}
#line 354 "/src/test-runner.do"
std::string escapeHtml(const std::string& value) {
#line 355 "/src/test-runner.do"
    return doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(value, std::string("&"), std::string("&amp;")), std::string("<"), std::string("&lt;")), std::string(">"), std::string("&gt;")), std::string("\""), std::string("&quot;")), std::string("'"), std::string("&#39;"));
}
#line 358 "/src/test-runner.do"
void addDiscoveredTest(const std::shared_ptr<TestDiscovery>& result, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& declaration, const std::string& exportedName, const std::string& modulePath, const std::string& rootDirectory, bool usesMocks) {
#line 366 "/src/test-runner.do"
    const auto location = ((((modulePath + std::string(":")) + doof::to_string(declaration->span.start.line)) + std::string(":")) + doof::to_string(declaration->span.start.column));
#line 367 "/src/test-runner.do"
    if (static_cast<int32_t>((declaration->params)->size()) > 0) {
#line 368 "/src/test-runner.do"
        result->errors->push_back((((location + std::string(": error: test \"")) + exportedName) + std::string("\" must not declare parameters")));
#line 369 "/src/test-runner.do"
        return;
    }
#line 371 "/src/test-runner.do"
    if (static_cast<int32_t>((declaration->typeParams)->size()) > 0) {
#line 372 "/src/test-runner.do"
        result->errors->push_back((((location + std::string(": error: test \"")) + exportedName) + std::string("\" must not declare type parameters")));
#line 373 "/src/test-runner.do"
        return;
    }
#line 375 "/src/test-runner.do"
    if (!returnsNone(declaration)) {
#line 376 "/src/test-runner.do"
        result->errors->push_back((((location + std::string(": error: test \"")) + exportedName) + std::string("\" must return none")));
#line 377 "/src/test-runner.do"
        return;
    }
#line 379 "/src/test-runner.do"
    const auto displayPath = testDisplayPath(rootDirectory, modulePath);
#line 380 "/src/test-runner.do"
    result->tests->push_back(std::make_shared<DiscoveredTest>(((displayPath + std::string("::")) + exportedName), exportedName, modulePath, displayPath, usesMocks));
}
#line 389 "/src/test-runner.do"
bool returnsNone(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& declaration) {
#line 390 "/src/test-runner.do"
    if (doof::is_null(declaration->returnType)) {
#line 391 "/src/test-runner.do"
        {
            auto _case_subject = declaration->body;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
#line 392 "/src/test-runner.do"
                return true;
        }
        else {
#line 393 "/src/test-runner.do"
                return false;
        }
        }
        doof::unreachable();
    }
#line 396 "/src/test-runner.do"
    {
        auto _case_subject = doof::unwrap_optional(declaration->returnType);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 397 "/src/test-runner.do"
            return ((named->name == std::string("none")) || (named->name == std::string("void")));
    }
    else {
#line 398 "/src/test-runner.do"
            return false;
    }
    }
    doof::unreachable();
}
#line 402 "/src/test-runner.do"
std::shared_ptr<::app_src_ast_::FunctionDeclaration> findFunction(const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>>& statements, const std::string& name) {
#line 403 "/src/test-runner.do"
    const auto& _iterable_34 = statements;
    for (const auto& statement : *_iterable_34) {
#line 404 "/src/test-runner.do"
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
                const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
#line 405 "/src/test-runner.do"
                if (fn->name == name) {
#line 405 "/src/test-runner.do"
                    return fn;
                }
        }
        else {
        }
        }
    }
#line 409 "/src/test-runner.do"
    return nullptr;
}
#line 412 "/src/test-runner.do"
std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> copyTests(const std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>>& tests) {
#line 413 "/src/test-runner.do"
    std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> result = std::make_shared<std::vector<std::shared_ptr<DiscoveredTest>>>(std::vector<std::shared_ptr<DiscoveredTest>>{});
#line 414 "/src/test-runner.do"
    const auto& _iterable_36 = tests;
    for (const auto& test : *_iterable_36) {
#line 414 "/src/test-runner.do"
        result->push_back(test);
    }
#line 415 "/src/test-runner.do"
    return result;
}
#line 418 "/src/test-runner.do"
std::string relativeImportSpecifier(const std::string& harnessPath, const std::string& modulePath) {
#line 419 "/src/test-runner.do"
    const auto sourceComponents = parentComponents(doof::string_replaceAll(harnessPath, std::string("\\"), std::string("/")));
#line 420 "/src/test-runner.do"
    const auto to = doof::string_split(withoutExtension(doof::string_replaceAll(modulePath, std::string("\\"), std::string("/"))), std::string("/"));
#line 421 "/src/test-runner.do"
    auto common = 0;
#line 422 "/src/test-runner.do"
    while (((common < static_cast<int32_t>((sourceComponents)->size())) && (common < static_cast<int32_t>((to)->size()))) && (doof::array_at(sourceComponents, common, "src/test-runner", 422) == doof::array_at(to, common, "src/test-runner", 422))) {
#line 423 "/src/test-runner.do"
        (common = (common + 1));
    }
#line 425 "/src/test-runner.do"
    auto result = std::string("");
#line 426 "/src/test-runner.do"
    for (int32_t ignored = common; ignored < static_cast<int32_t>((sourceComponents)->size()); ++ignored) {
#line 426 "/src/test-runner.do"
        (result = (result + std::string("../")));
    }
#line 427 "/src/test-runner.do"
    for (int32_t index = common; index < static_cast<int32_t>((to)->size()); ++index) {
#line 428 "/src/test-runner.do"
        if ((result != std::string("")) && !doof::string_endsWith(result, std::string("/"))) {
#line 428 "/src/test-runner.do"
            (result = (result + std::string("/")));
        }
#line 429 "/src/test-runner.do"
        (result = (result + doof::array_at(to, index, "src/test-runner", 429)));
    }
#line 431 "/src/test-runner.do"
    if (!doof::string_startsWith(result, std::string("."))) {
#line 431 "/src/test-runner.do"
        return (std::string("./") + result);
    }
#line 432 "/src/test-runner.do"
    return result;
}
#line 435 "/src/test-runner.do"
std::shared_ptr<std::vector<std::string>> parentComponents(const std::string& path) {
#line 436 "/src/test-runner.do"
    const auto components = doof::array_cloneMutable(doof::string_split(path, std::string("/")), "", 0);
#line 437 "/src/test-runner.do"
    if (static_cast<int32_t>((components)->size()) > 0) {
#line 437 "/src/test-runner.do"
        auto ignored = [&]() -> std::string { auto _try_value = doof::array_pop(components); if (doof::is_failure(_try_value)) doof::panic_at("src/test-runner", 437, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
    }
#line 438 "/src/test-runner.do"
    return components;
}
#line 441 "/src/test-runner.do"
std::string withoutExtension(const std::string& path) {
#line 442 "/src/test-runner.do"
    if (doof::string_endsWith(path, std::string(".do"))) {
#line 442 "/src/test-runner.do"
        return doof::string_substring(path, 0, (static_cast<int32_t>(path.size()) - 3));
    }
#line 443 "/src/test-runner.do"
    return path;
}
#line 446 "/src/test-runner.do"
std::string trimTrailingSlashes(const std::string& path) {
#line 447 "/src/test-runner.do"
    auto end = static_cast<int32_t>(path.size());
#line 448 "/src/test-runner.do"
    while ((end > 1) && (doof::string_at(path, (end - 1), "src/test-runner", 448) == U'\u002F')) {
#line 448 "/src/test-runner.do"
        (end = (end - 1));
    }
#line 449 "/src/test-runner.do"
    return doof::string_substring(path, 0, end);
}
#line 452 "/src/test-runner.do"
std::string escapeDoofString(const std::string& value) {
#line 453 "/src/test-runner.do"
    return doof::string_replaceAll(doof::string_replaceAll(value, std::string("\\"), std::string("\\\\")), std::string("\""), std::string("\\\""));
}
#line 1 "<doof-generated>"
}

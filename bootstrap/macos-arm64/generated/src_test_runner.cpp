#include "src_test_runner.hpp"
#include <cmath>
#include "src_ast.hpp"
#include "src_emitter_module.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_test_runner_ {
using namespace ::app_src_ast_;
using namespace ::app_src_emitter_module_;

doof::JsonObject CoverageFileReport::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["path"] = doof::json_value(this->path);
    (*_json)["covered"] = doof::json_value(this->covered);
    (*_json)["total"] = doof::json_value(this->total);
    (*_json)["percentTenths"] = doof::json_value(this->percentTenths);
    (*_json)["hitLines"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->hitLines->size()); for (const auto& _element : *this->hitLines) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["missedLines"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->missedLines->size()); for (const auto& _element : *this->missedLines) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<CoverageFileReport>, std::string> CoverageFileReport::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_path = _object->find("path");
    if (_iterator_path == _object->end()) { return doof::Failure<std::string>{"Missing required field \"path\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_path->second) : doof::json_is_string(_iterator_path->second)))) { return doof::Failure<std::string>{"Field \"path\" expected string but got " + std::string(doof::json_type_name(_iterator_path->second))}; }
    auto _field_path = (_lenient ? doof::json_as_string_lenient(_iterator_path->second) : doof::json_as_string(_iterator_path->second));
    auto _iterator_covered = _object->find("covered");
    if (_iterator_covered == _object->end()) { return doof::Failure<std::string>{"Missing required field \"covered\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_covered->second) : doof::json_is_number(_iterator_covered->second)))) { return doof::Failure<std::string>{"Field \"covered\" expected number but got " + std::string(doof::json_type_name(_iterator_covered->second))}; }
    auto _field_covered = (_lenient ? doof::json_as_int_lenient(_iterator_covered->second) : doof::json_as_int(_iterator_covered->second));
    auto _iterator_total = _object->find("total");
    if (_iterator_total == _object->end()) { return doof::Failure<std::string>{"Missing required field \"total\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_total->second) : doof::json_is_number(_iterator_total->second)))) { return doof::Failure<std::string>{"Field \"total\" expected number but got " + std::string(doof::json_type_name(_iterator_total->second))}; }
    auto _field_total = (_lenient ? doof::json_as_int_lenient(_iterator_total->second) : doof::json_as_int(_iterator_total->second));
    auto _iterator_percentTenths = _object->find("percentTenths");
    if (_iterator_percentTenths == _object->end()) { return doof::Failure<std::string>{"Missing required field \"percentTenths\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_percentTenths->second) : doof::json_is_number(_iterator_percentTenths->second)))) { return doof::Failure<std::string>{"Field \"percentTenths\" expected number but got " + std::string(doof::json_type_name(_iterator_percentTenths->second))}; }
    auto _field_percentTenths = (_lenient ? doof::json_as_int_lenient(_iterator_percentTenths->second) : doof::json_as_int(_iterator_percentTenths->second));
    std::optional<std::shared_ptr<std::vector<int32_t>>> _field_hitLines;
    if (auto _iterator_hitLines = _object->find("hitLines"); _iterator_hitLines != _object->end()) {
        if (!(doof::json_is_array(_iterator_hitLines->second))) { return doof::Failure<std::string>{"Field \"hitLines\" expected array but got " + std::string(doof::json_type_name(_iterator_hitLines->second))}; }
        _field_hitLines = [&]() { const auto* _array = doof::json_as_array(_iterator_hitLines->second); auto _values = std::make_shared<std::vector<int32_t>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_int_lenient(_element) : doof::json_as_int(_element))); } return _values; }();
    } else {
        _field_hitLines = std::shared_ptr<std::vector<int32_t>>{std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{})};
    }
    std::optional<std::shared_ptr<std::vector<int32_t>>> _field_missedLines;
    if (auto _iterator_missedLines = _object->find("missedLines"); _iterator_missedLines != _object->end()) {
        if (!(doof::json_is_array(_iterator_missedLines->second))) { return doof::Failure<std::string>{"Field \"missedLines\" expected array but got " + std::string(doof::json_type_name(_iterator_missedLines->second))}; }
        _field_missedLines = [&]() { const auto* _array = doof::json_as_array(_iterator_missedLines->second); auto _values = std::make_shared<std::vector<int32_t>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_int_lenient(_element) : doof::json_as_int(_element))); } return _values; }();
    } else {
        _field_missedLines = std::shared_ptr<std::vector<int32_t>>{std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{})};
    }
    return doof::Success<std::shared_ptr<CoverageFileReport>>{std::make_shared<CoverageFileReport>(_field_path, _field_covered, _field_total, _field_percentTenths, _field_hitLines.value(), _field_missedLines.value())};
}

doof::JsonObject CoverageReport::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["totalCovered"] = doof::json_value(this->totalCovered);
    (*_json)["totalLines"] = doof::json_value(this->totalLines);
    (*_json)["totalPercentTenths"] = doof::json_value(this->totalPercentTenths);
    (*_json)["files"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->files->size()); for (const auto& _element : *this->files) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<CoverageReport>, std::string> CoverageReport::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<int32_t> _field_totalCovered;
    if (auto _iterator_totalCovered = _object->find("totalCovered"); _iterator_totalCovered != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_totalCovered->second) : doof::json_is_number(_iterator_totalCovered->second)))) { return doof::Failure<std::string>{"Field \"totalCovered\" expected number but got " + std::string(doof::json_type_name(_iterator_totalCovered->second))}; }
        _field_totalCovered = (_lenient ? doof::json_as_int_lenient(_iterator_totalCovered->second) : doof::json_as_int(_iterator_totalCovered->second));
    } else {
        _field_totalCovered = int32_t{0};
    }
    std::optional<int32_t> _field_totalLines;
    if (auto _iterator_totalLines = _object->find("totalLines"); _iterator_totalLines != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_totalLines->second) : doof::json_is_number(_iterator_totalLines->second)))) { return doof::Failure<std::string>{"Field \"totalLines\" expected number but got " + std::string(doof::json_type_name(_iterator_totalLines->second))}; }
        _field_totalLines = (_lenient ? doof::json_as_int_lenient(_iterator_totalLines->second) : doof::json_as_int(_iterator_totalLines->second));
    } else {
        _field_totalLines = int32_t{0};
    }
    std::optional<int32_t> _field_totalPercentTenths;
    if (auto _iterator_totalPercentTenths = _object->find("totalPercentTenths"); _iterator_totalPercentTenths != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_totalPercentTenths->second) : doof::json_is_number(_iterator_totalPercentTenths->second)))) { return doof::Failure<std::string>{"Field \"totalPercentTenths\" expected number but got " + std::string(doof::json_type_name(_iterator_totalPercentTenths->second))}; }
        _field_totalPercentTenths = (_lenient ? doof::json_as_int_lenient(_iterator_totalPercentTenths->second) : doof::json_as_int(_iterator_totalPercentTenths->second));
    } else {
        _field_totalPercentTenths = int32_t{1000};
    }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<CoverageFileReport>>>> _field_files;
    if (auto _iterator_files = _object->find("files"); _iterator_files != _object->end()) {
        if (!(doof::json_is_array(_iterator_files->second))) { return doof::Failure<std::string>{"Field \"files\" expected array but got " + std::string(doof::json_type_name(_iterator_files->second))}; }
        _field_files = [&]() { const auto* _array = doof::json_as_array(_iterator_files->second); auto _values = std::make_shared<std::vector<std::shared_ptr<CoverageFileReport>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(CoverageFileReport::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_files = std::shared_ptr<std::vector<std::shared_ptr<CoverageFileReport>>>{std::make_shared<std::vector<std::shared_ptr<CoverageFileReport>>>(std::vector<std::shared_ptr<CoverageFileReport>>{})};
    }
    return doof::Success<std::shared_ptr<CoverageReport>>{std::make_shared<CoverageReport>(_field_totalCovered.value(), _field_totalLines.value(), _field_totalPercentTenths.value(), _field_files.value())};
}

doof::JsonObject DiscoveredTest::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["id"] = doof::json_value(this->id);
    (*_json)["name"] = doof::json_value(this->name);
    (*_json)["modulePath"] = doof::json_value(this->modulePath);
    (*_json)["moduleDisplayPath"] = doof::json_value(this->moduleDisplayPath);
    return _json;
}
doof::Result<std::shared_ptr<DiscoveredTest>, std::string> DiscoveredTest::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_id = _object->find("id");
    if (_iterator_id == _object->end()) { return doof::Failure<std::string>{"Missing required field \"id\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_id->second) : doof::json_is_string(_iterator_id->second)))) { return doof::Failure<std::string>{"Field \"id\" expected string but got " + std::string(doof::json_type_name(_iterator_id->second))}; }
    auto _field_id = (_lenient ? doof::json_as_string_lenient(_iterator_id->second) : doof::json_as_string(_iterator_id->second));
    auto _iterator_name = _object->find("name");
    if (_iterator_name == _object->end()) { return doof::Failure<std::string>{"Missing required field \"name\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_name->second) : doof::json_is_string(_iterator_name->second)))) { return doof::Failure<std::string>{"Field \"name\" expected string but got " + std::string(doof::json_type_name(_iterator_name->second))}; }
    auto _field_name = (_lenient ? doof::json_as_string_lenient(_iterator_name->second) : doof::json_as_string(_iterator_name->second));
    auto _iterator_modulePath = _object->find("modulePath");
    if (_iterator_modulePath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"modulePath\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_modulePath->second) : doof::json_is_string(_iterator_modulePath->second)))) { return doof::Failure<std::string>{"Field \"modulePath\" expected string but got " + std::string(doof::json_type_name(_iterator_modulePath->second))}; }
    auto _field_modulePath = (_lenient ? doof::json_as_string_lenient(_iterator_modulePath->second) : doof::json_as_string(_iterator_modulePath->second));
    auto _iterator_moduleDisplayPath = _object->find("moduleDisplayPath");
    if (_iterator_moduleDisplayPath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"moduleDisplayPath\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_moduleDisplayPath->second) : doof::json_is_string(_iterator_moduleDisplayPath->second)))) { return doof::Failure<std::string>{"Field \"moduleDisplayPath\" expected string but got " + std::string(doof::json_type_name(_iterator_moduleDisplayPath->second))}; }
    auto _field_moduleDisplayPath = (_lenient ? doof::json_as_string_lenient(_iterator_moduleDisplayPath->second) : doof::json_as_string(_iterator_moduleDisplayPath->second));
    return doof::Success<std::shared_ptr<DiscoveredTest>>{std::make_shared<DiscoveredTest>(_field_id, _field_name, _field_modulePath, _field_moduleDisplayPath)};
}

doof::JsonObject TestDiscovery::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["tests"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->tests->size()); for (const auto& _element : *this->tests) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["errors"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->errors->size()); for (const auto& _element : *this->errors) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<TestDiscovery>, std::string> TestDiscovery::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>>> _field_tests;
    if (auto _iterator_tests = _object->find("tests"); _iterator_tests != _object->end()) {
        if (!(doof::json_is_array(_iterator_tests->second))) { return doof::Failure<std::string>{"Field \"tests\" expected array but got " + std::string(doof::json_type_name(_iterator_tests->second))}; }
        _field_tests = [&]() { const auto* _array = doof::json_as_array(_iterator_tests->second); auto _values = std::make_shared<std::vector<std::shared_ptr<DiscoveredTest>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(DiscoveredTest::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_tests = std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>>{std::make_shared<std::vector<std::shared_ptr<DiscoveredTest>>>(std::vector<std::shared_ptr<DiscoveredTest>>{})};
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_errors;
    if (auto _iterator_errors = _object->find("errors"); _iterator_errors != _object->end()) {
        if (!(doof::json_is_array(_iterator_errors->second))) { return doof::Failure<std::string>{"Field \"errors\" expected array but got " + std::string(doof::json_type_name(_iterator_errors->second))}; }
        _field_errors = [&]() { const auto* _array = doof::json_as_array(_iterator_errors->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_errors = std::shared_ptr<std::vector<std::string>>{std::make_shared<std::vector<std::string>>(std::vector<std::string>{})};
    }
    return doof::Success<std::shared_ptr<TestDiscovery>>{std::make_shared<TestDiscovery>(_field_tests.value(), _field_errors.value())};
}
std::shared_ptr<TestDiscovery> discoverModuleTests(std::shared_ptr<::app_src_ast_::Program> program, std::string modulePath, std::string rootDirectory) {
    const auto result = std::make_shared<TestDiscovery>(std::make_shared<std::vector<std::shared_ptr<DiscoveredTest>>>(std::vector<std::shared_ptr<DiscoveredTest>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    const auto& _iterable_1 = program->statements;
    for (const auto& statement : *_iterable_1) {
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
                const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
                if (fn->exported && doof::string_startsWith(fn->name, std::string("test"))) {
                    addDiscoveredTest(result, fn, fn->name, modulePath, rootDirectory);
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportList>>(_case_subject)) {
                const auto& list = std::get<std::shared_ptr<::app_src_ast_::ExportList>>(_case_subject);
                if (!doof::is_null(list->source)) {
                    continue;
                }
                const auto& _iterable_2 = list->specifiers;
                for (const auto& specifier : *_iterable_2) {
                    const auto exportedName = (doof::is_null(specifier->alias) ? specifier->name : doof::unwrap_optional(specifier->alias));
                    if (!doof::string_startsWith(exportedName, std::string("test"))) {
                        continue;
                    }
                    const auto declaration = findFunction(program->statements, specifier->name);
                    if (!doof::is_null(declaration)) {
                        addDiscoveredTest(result, doof::unwrap_optional(declaration), exportedName, modulePath, rootDirectory);
                    }
                }
        }
        else {
        }
        }
    }
    return result;
}
std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> filterDiscoveredTests(std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> tests, std::string filter) {
    if (filter == std::string("")) {
        return copyTests(tests);
    }
    const auto needle = doof::string_toLowerCase(filter);
    std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> selected = std::make_shared<std::vector<std::shared_ptr<DiscoveredTest>>>(std::vector<std::shared_ptr<DiscoveredTest>>{});
    const auto& _iterable_3 = tests;
    for (const auto& test : *_iterable_3) {
        if (doof::string_contains(doof::string_toLowerCase(test->id), needle)) {
            selected->push_back(test);
        }
    }
    return selected;
}
std::string generateTestHarness(std::string harnessPath, std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> tests) {
    auto source = std::string("");
    const auto& _iterable_4 = tests;
    for (const auto& test : *_iterable_4) {
        (source = (((((source + std::string("import { ")) + test->name) + std::string(" } from \"")) + relativeImportSpecifier(harnessPath, test->modulePath)) + std::string("\"\n")));
    }
    (source = (source + std::string("\nfunction main(args: string[]): int {\n")));
    (source = (source + std::string("    if args.length < 1 {\n")));
    (source = (source + std::string("        println(\"missing test id\")\n")));
    (source = (source + std::string("        return 2\n")));
    (source = (source + std::string("    }\n\n")));
    (source = (source + std::string("    testId := args[0]\n")));
    for (int32_t index = 0; index < static_cast<int32_t>((tests)->size()); ++index) {
        const auto keyword = ((index == 0) ? std::string("if") : std::string("} else if"));
        const auto id = escapeDoofString((*tests)[index]->id);
        (source = (((((source + std::string("    ")) + keyword) + std::string(" testId == \"")) + id) + std::string("\" {\n")));
        (source = (((source + std::string("        ")) + (*tests)[index]->name) + std::string("()\n")));
        (source = (source + std::string("        return 0\n")));
    }
    (source = (source + std::string("    } else {\n")));
    (source = ((source + std::string("        println(\"unknown test id: $")) + std::string("{testId}\")\n")));
    (source = (source + std::string("        return 2\n")));
    (source = (source + std::string("    }\n")));
    (source = (source + std::string("}\n")));
    return source;
}
std::string testDisplayPath(std::string rootDirectory, std::string modulePath) {
    const auto root = trimTrailingSlashes(doof::string_replaceAll(rootDirectory, std::string("\\"), std::string("/")));
    const auto module = doof::string_replaceAll(modulePath, std::string("\\"), std::string("/"));
    const auto prefix = (root + std::string("/"));
    if (doof::string_startsWith(module, prefix)) {
        return doof::string_substring(module, static_cast<int32_t>(prefix.size()), static_cast<int32_t>(module.size()));
    }
    return module;
}
std::string formatParseFailure(std::string modulePath, std::string source, int32_t line, int32_t column, std::string message) {
    const auto header = ((((((modulePath + std::string(":")) + doof::to_string(line)) + std::string(":")) + doof::to_string(column)) + std::string(": error: ")) + message);
    const auto lines = doof::string_split(source, std::string("\n"));
    if ((line < 1) || (line > static_cast<int32_t>((lines)->size()))) {
        return header;
    }
    const auto caretColumn = ((column < 1) ? 1 : column);
    return (((((header + std::string("\n")) + (*lines)[(line - 1)]) + std::string("\n")) + doof::string_repeat(std::string(" "), (caretColumn - 1))) + std::string("^"));
}
void mergeCoverageOutput(std::string output, std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>> modules, std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> hitsByModule) {
    const auto& _iterable_5 = doof::string_split(output, std::string("\n"));
    for (const auto& line : *_iterable_5) {
        const auto trimmed = doof::string_trim(line);
        if (!doof::string_startsWith(trimmed, std::string("__COV__ "))) {
            continue;
        }
        const auto parts = doof::string_split(trimmed, std::string(" "));
        if (static_cast<int32_t>((parts)->size()) != 3) {
            continue;
        }
        const auto moduleId = parseCoverageInteger((*parts)[1]);
        const auto sourceLine = parseCoverageInteger((*parts)[2]);
        if ((moduleId < 0) || (sourceLine < 1)) {
            continue;
        }
        for (int32_t index = 0; index < static_cast<int32_t>((modules)->size()); ++index) {
            if ((*modules)[index]->moduleId == moduleId) {
                while (static_cast<int32_t>((hitsByModule)->size()) <= index) {
                    hitsByModule->push_back(std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}));
                }
                appendUniqueLine((*hitsByModule)[index], sourceLine);
            }
        }
    }
}
std::string stripCoverageLines(std::string output) {
    auto result = std::string("");
    const auto& _iterable_6 = doof::string_split(output, std::string("\n"));
    for (const auto& line : *_iterable_6) {
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
std::shared_ptr<CoverageReport> buildCoverageReport(std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>> modules, std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> hitsByModule, std::string rootDirectory) {
    const auto report = std::make_shared<CoverageReport>(0, 0, 1000, std::make_shared<std::vector<std::shared_ptr<CoverageFileReport>>>(std::vector<std::shared_ptr<CoverageFileReport>>{}));
    for (int32_t index = 0; index < static_cast<int32_t>((modules)->size()); ++index) {
        const auto module = (*modules)[index];
        if (static_cast<int32_t>((module->instrumentedLines)->size()) == 0) {
            continue;
        }
        std::shared_ptr<std::vector<int32_t>> hits = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
        if (index < static_cast<int32_t>((hitsByModule)->size())) {
            (hits = (*hitsByModule)[index]);
        }
        const auto file = std::make_shared<CoverageFileReport>(testDisplayPath(rootDirectory, module->modulePath), 0, static_cast<int32_t>((module->instrumentedLines)->size()), 0, std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}), std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}));
        const auto& _iterable_7 = module->instrumentedLines;
        for (const auto& line : *_iterable_7) {
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
std::string renderCoverageJson(std::shared_ptr<CoverageReport> report) {
    auto output = (std::string("{\n  \"timestamp\": \"\",\n  \"totals\": { \"covered\": ") + doof::to_string(report->totalCovered));
    (output = (((((output + std::string(", \"total\": ")) + doof::to_string(report->totalLines)) + std::string(", \"percent\": ")) + coveragePercentText(report->totalPercentTenths)) + std::string(" },\n")));
    (output = (output + std::string("  \"files\": [")));
    for (int32_t index = 0; index < static_cast<int32_t>((report->files)->size()); ++index) {
        const auto file = (*report->files)[index];
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
std::string renderCoverageHtml(std::shared_ptr<CoverageReport> report, std::string fileDirectoryName) {
    auto rows = std::string("");
    const auto& _iterable_8 = report->files;
    for (const auto& file : *_iterable_8) {
        const auto href = escapeHtml(((fileDirectoryName + std::string("/")) + coverageFileRelativePath(file->path)));
        (rows = (((((rows + std::string("<tr><td><a href=\"")) + href) + std::string("\">")) + escapeHtml(file->path)) + std::string("</a></td>")));
        (rows = (((((rows + std::string("<td>")) + doof::to_string(file->covered)) + std::string("/")) + doof::to_string(file->total)) + std::string("</td>")));
        (rows = (((rows + std::string("<td>")) + coveragePercentText(file->percentTenths)) + std::string("%</td></tr>\n")));
    }
    const auto overall = coveragePercentText(report->totalPercentTenths);
    return (((((((((((((std::string("<!doctype html>\n<html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width\">") + std::string("<title>Doof Coverage Report</title><style>body{font:16px system-ui;max-width:960px;margin:2rem auto;padding:0 1rem;color:#1f2933}")) + std::string("table{width:100%;border-collapse:collapse}th,td{text-align:left;padding:.65rem;border-bottom:1px solid #ddd}")) + std::string("a{color:#9a3412}.summary{font-size:1.3rem}</style></head><body><h1>Doof Coverage</h1>")) + std::string("<p class=\"summary\">Overall: ")) + doof::to_string(report->totalCovered)) + std::string("/")) + doof::to_string(report->totalLines)) + std::string(" lines (")) + overall) + std::string("%)</p>")) + std::string("<table><thead><tr><th>File</th><th>Lines</th><th>Coverage</th></tr></thead><tbody>")) + rows) + std::string("</tbody></table></body></html>\n"));
}
std::string renderCoverageFileHtml(std::shared_ptr<CoverageFileReport> file, std::string source, std::string indexHref) {
    auto lines = std::string("");
    const auto sourceLines = doof::string_split(source, std::string("\n"));
    for (int32_t index = 0; index < static_cast<int32_t>((sourceLines)->size()); ++index) {
        const auto line = (index + 1);
        const auto className = (containsLine(file->hitLines, line) ? std::string("covered") : (containsLine(file->missedLines, line) ? std::string("missed") : std::string("neutral")));
        (lines = (((((((lines + std::string("<div class=\"line ")) + className) + std::string("\"><span>")) + doof::to_string(line)) + std::string("</span><code>")) + escapeHtml((*sourceLines)[index])) + std::string("</code></div>\n")));
    }
    return ((((((((((((std::string("<!doctype html>\n<html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width\">") + std::string("<title>")) + escapeHtml(file->path)) + std::string(" — Doof Coverage</title><style>body{font:15px system-ui;margin:2rem;color:#1f2933}")) + std::string(".line{display:grid;grid-template-columns:4rem 1fr;font-family:monospace;white-space:pre}.line span{text-align:right;padding-right:1rem;color:#6b7280}")) + std::string(".covered{background:#dcfce7}.missed{background:#fee2e2}.neutral{background:#f8fafc}a{color:#9a3412}</style></head><body>")) + std::string("<a href=\"")) + escapeHtml(indexHref)) + std::string("\">Back to coverage summary</a><h1>")) + escapeHtml(file->path)) + std::string("</h1>")) + lines) + std::string("</body></html>\n"));
}
std::string coverageFileRelativePath(std::string path) {
    return (doof::string_replaceAll(doof::string_replaceAll(path, std::string("\\"), std::string("/")), std::string("../"), std::string("_external/")) + std::string(".html"));
}
int32_t parseCoverageInteger(std::string value) {
    if (value == std::string("")) {
        return -1;
    }
    auto result = 0;
    for (int32_t index = 0; index < static_cast<int32_t>(value.size()); ++index) {
        const auto char_ = value[index];
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
void appendUniqueLine(std::shared_ptr<std::vector<int32_t>> lines, int32_t line) {
    if (!containsLine(lines, line)) {
        lines->push_back(line);
    }
}
bool containsLine(std::shared_ptr<std::vector<int32_t>> lines, int32_t line) {
    const auto& _iterable_9 = lines;
    for (const auto& existing : *_iterable_9) {
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
std::string renderLineArray(std::shared_ptr<std::vector<int32_t>> lines) {
    auto result = std::string("[");
    for (int32_t index = 0; index < static_cast<int32_t>((lines)->size()); ++index) {
        if (index > 0) {
            (result = (result + std::string(", ")));
        }
        (result = (result + doof::to_string((*lines)[index])));
    }
    return (result + std::string("]"));
}
std::string escapeJson(std::string value) {
    return doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(value, std::string("\\"), std::string("\\\\")), std::string("\""), std::string("\\\"")), std::string("\n"), std::string("\\n"));
}
std::string escapeHtml(std::string value) {
    return doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(value, std::string("&"), std::string("&amp;")), std::string("<"), std::string("&lt;")), std::string(">"), std::string("&gt;")), std::string("\""), std::string("&quot;")), std::string("'"), std::string("&#39;"));
}
void addDiscoveredTest(std::shared_ptr<TestDiscovery> result, std::shared_ptr<::app_src_ast_::FunctionDeclaration> declaration, std::string exportedName, std::string modulePath, std::string rootDirectory) {
    const auto location = ((((modulePath + std::string(":")) + doof::to_string(declaration->span.start.line)) + std::string(":")) + doof::to_string(declaration->span.start.column));
    if (static_cast<int32_t>((declaration->params)->size()) > 0) {
        result->errors->push_back((((location + std::string(": error: test \"")) + exportedName) + std::string("\" must not declare parameters")));
        return;
    }
    if (static_cast<int32_t>((declaration->typeParams)->size()) > 0) {
        result->errors->push_back((((location + std::string(": error: test \"")) + exportedName) + std::string("\" must not declare type parameters")));
        return;
    }
    if (!returnsVoid(declaration)) {
        result->errors->push_back((((location + std::string(": error: test \"")) + exportedName) + std::string("\" must return void")));
        return;
    }
    const auto displayPath = testDisplayPath(rootDirectory, modulePath);
    result->tests->push_back(std::make_shared<DiscoveredTest>(((displayPath + std::string("::")) + exportedName), exportedName, modulePath, displayPath));
}
bool returnsVoid(std::shared_ptr<::app_src_ast_::FunctionDeclaration> declaration) {
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
    }
    {
        auto _case_subject = doof::unwrap_optional(declaration->returnType);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
            return (named->name == std::string("void"));
    }
    else {
            return false;
    }
    }
}
std::shared_ptr<::app_src_ast_::FunctionDeclaration> findFunction(std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>> statements, std::string name) {
    const auto& _iterable_10 = statements;
    for (const auto& statement : *_iterable_10) {
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
std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> copyTests(std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> tests) {
    std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> result = std::make_shared<std::vector<std::shared_ptr<DiscoveredTest>>>(std::vector<std::shared_ptr<DiscoveredTest>>{});
    const auto& _iterable_11 = tests;
    for (const auto& test : *_iterable_11) {
        result->push_back(test);
    }
    return result;
}
std::string relativeImportSpecifier(std::string harnessPath, std::string modulePath) {
    const auto sourceComponents = parentComponents(doof::string_replaceAll(harnessPath, std::string("\\"), std::string("/")));
    const auto to = doof::string_split(withoutExtension(doof::string_replaceAll(modulePath, std::string("\\"), std::string("/"))), std::string("/"));
    auto common = 0;
    while (((common < static_cast<int32_t>((sourceComponents)->size())) && (common < static_cast<int32_t>((to)->size()))) && ((*sourceComponents)[common] == (*to)[common])) {
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
        (result = (result + (*to)[index]));
    }
    if (!doof::string_startsWith(result, std::string("."))) {
        return (std::string("./") + result);
    }
    return result;
}
std::shared_ptr<std::vector<std::string>> parentComponents(std::string path) {
    const auto components = doof::string_split(path, std::string("/"));
    if (static_cast<int32_t>((components)->size()) > 0) {
        auto ignored = [&]() -> std::string { auto _try_value = doof::array_pop(components); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
    }
    return components;
}
std::string withoutExtension(std::string path) {
    if (doof::string_endsWith(path, std::string(".do"))) {
        return doof::string_substring(path, 0, (static_cast<int32_t>(path.size()) - 3));
    }
    return path;
}
std::string trimTrailingSlashes(std::string path) {
    auto end = static_cast<int32_t>(path.size());
    while ((end > 1) && (path[(end - 1)] == U'\u002F')) {
        (end = (end - 1));
    }
    return doof::string_substring(path, 0, end);
}
std::string escapeDoofString(std::string value) {
    return doof::string_replaceAll(doof::string_replaceAll(value, std::string("\\"), std::string("\\\\")), std::string("\""), std::string("\\\""));
}
}

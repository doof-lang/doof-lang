#include "src_test_runner.hpp"

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
    try {
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
        _field_hitLines = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
    }
    std::optional<std::shared_ptr<std::vector<int32_t>>> _field_missedLines;
    if (auto _iterator_missedLines = _object->find("missedLines"); _iterator_missedLines != _object->end()) {
            if (!(doof::json_is_array(_iterator_missedLines->second))) { return doof::Failure<std::string>{"Field \"missedLines\" expected array but got " + std::string(doof::json_type_name(_iterator_missedLines->second))}; }
        _field_missedLines = [&]() { const auto* _array = doof::json_as_array(_iterator_missedLines->second); auto _values = std::make_shared<std::vector<int32_t>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_int_lenient(_element) : doof::json_as_int(_element))); } return _values; }();
    } else {
        _field_missedLines = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
    }
        return doof::Success<std::shared_ptr<CoverageFileReport>>{std::make_shared<CoverageFileReport>(_field_path, _field_covered, _field_total, _field_percentTenths, _field_hitLines.value(), _field_missedLines.value())};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
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
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<int32_t> _field_totalCovered;
    if (auto _iterator_totalCovered = _object->find("totalCovered"); _iterator_totalCovered != _object->end()) {
            if (!((_lenient ? doof::json_is_lenient_number(_iterator_totalCovered->second) : doof::json_is_number(_iterator_totalCovered->second)))) { return doof::Failure<std::string>{"Field \"totalCovered\" expected number but got " + std::string(doof::json_type_name(_iterator_totalCovered->second))}; }
        _field_totalCovered = (_lenient ? doof::json_as_int_lenient(_iterator_totalCovered->second) : doof::json_as_int(_iterator_totalCovered->second));
    } else {
        _field_totalCovered = 0;
    }
    std::optional<int32_t> _field_totalLines;
    if (auto _iterator_totalLines = _object->find("totalLines"); _iterator_totalLines != _object->end()) {
            if (!((_lenient ? doof::json_is_lenient_number(_iterator_totalLines->second) : doof::json_is_number(_iterator_totalLines->second)))) { return doof::Failure<std::string>{"Field \"totalLines\" expected number but got " + std::string(doof::json_type_name(_iterator_totalLines->second))}; }
        _field_totalLines = (_lenient ? doof::json_as_int_lenient(_iterator_totalLines->second) : doof::json_as_int(_iterator_totalLines->second));
    } else {
        _field_totalLines = 0;
    }
    std::optional<int32_t> _field_totalPercentTenths;
    if (auto _iterator_totalPercentTenths = _object->find("totalPercentTenths"); _iterator_totalPercentTenths != _object->end()) {
            if (!((_lenient ? doof::json_is_lenient_number(_iterator_totalPercentTenths->second) : doof::json_is_number(_iterator_totalPercentTenths->second)))) { return doof::Failure<std::string>{"Field \"totalPercentTenths\" expected number but got " + std::string(doof::json_type_name(_iterator_totalPercentTenths->second))}; }
        _field_totalPercentTenths = (_lenient ? doof::json_as_int_lenient(_iterator_totalPercentTenths->second) : doof::json_as_int(_iterator_totalPercentTenths->second));
    } else {
        _field_totalPercentTenths = 1000;
    }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<CoverageFileReport>>>> _field_files;
    if (auto _iterator_files = _object->find("files"); _iterator_files != _object->end()) {
            if (!(doof::json_is_array(_iterator_files->second))) { return doof::Failure<std::string>{"Field \"files\" expected array but got " + std::string(doof::json_type_name(_iterator_files->second))}; }
        _field_files = [&]() { const auto* _array = doof::json_as_array(_iterator_files->second); auto _values = std::make_shared<std::vector<std::shared_ptr<CoverageFileReport>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::json_decode_value(CoverageFileReport::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_files = std::make_shared<std::vector<std::shared_ptr<CoverageFileReport>>>(std::vector<std::shared_ptr<CoverageFileReport>>{});
    }
        return doof::Success<std::shared_ptr<CoverageReport>>{std::make_shared<CoverageReport>(_field_totalCovered.value(), _field_totalLines.value(), _field_totalPercentTenths.value(), _field_files.value())};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}

doof::JsonObject DiscoveredTest::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["id"] = doof::json_value(this->id);
    (*_json)["name"] = doof::json_value(this->name);
    (*_json)["modulePath"] = doof::json_value(this->modulePath);
    (*_json)["moduleDisplayPath"] = doof::json_value(this->moduleDisplayPath);
    (*_json)["usesMocks"] = doof::json_value(this->usesMocks);
    return _json;
}
doof::Result<std::shared_ptr<DiscoveredTest>, std::string> DiscoveredTest::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
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
    std::optional<bool> _field_usesMocks;
    if (auto _iterator_usesMocks = _object->find("usesMocks"); _iterator_usesMocks != _object->end()) {
            if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_usesMocks->second) : doof::json_is_boolean(_iterator_usesMocks->second)))) { return doof::Failure<std::string>{"Field \"usesMocks\" expected boolean but got " + std::string(doof::json_type_name(_iterator_usesMocks->second))}; }
        _field_usesMocks = (_lenient ? doof::json_as_bool_lenient(_iterator_usesMocks->second) : doof::json_as_bool(_iterator_usesMocks->second));
    } else {
        _field_usesMocks = false;
    }
        return doof::Success<std::shared_ptr<DiscoveredTest>>{std::make_shared<DiscoveredTest>(_field_id, _field_name, _field_modulePath, _field_moduleDisplayPath, _field_usesMocks.value())};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}

doof::JsonObject TestCompilationGroup::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["outputName"] = doof::json_value(this->outputName);
    (*_json)["tests"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->tests->size()); for (const auto& _element : *this->tests) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<TestCompilationGroup>, std::string> TestCompilationGroup::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_outputName = _object->find("outputName");
    if (_iterator_outputName == _object->end()) { return doof::Failure<std::string>{"Missing required field \"outputName\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_outputName->second) : doof::json_is_string(_iterator_outputName->second)))) { return doof::Failure<std::string>{"Field \"outputName\" expected string but got " + std::string(doof::json_type_name(_iterator_outputName->second))}; }
    auto _field_outputName = (_lenient ? doof::json_as_string_lenient(_iterator_outputName->second) : doof::json_as_string(_iterator_outputName->second));
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>>> _field_tests;
    if (auto _iterator_tests = _object->find("tests"); _iterator_tests != _object->end()) {
            if (!(doof::json_is_array(_iterator_tests->second))) { return doof::Failure<std::string>{"Field \"tests\" expected array but got " + std::string(doof::json_type_name(_iterator_tests->second))}; }
        _field_tests = [&]() { const auto* _array = doof::json_as_array(_iterator_tests->second); auto _values = std::make_shared<std::vector<std::shared_ptr<DiscoveredTest>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::json_decode_value(DiscoveredTest::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_tests = std::make_shared<std::vector<std::shared_ptr<DiscoveredTest>>>(std::vector<std::shared_ptr<DiscoveredTest>>{});
    }
        return doof::Success<std::shared_ptr<TestCompilationGroup>>{std::make_shared<TestCompilationGroup>(_field_outputName, _field_tests.value())};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}

doof::JsonObject TestDiscovery::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["tests"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->tests->size()); for (const auto& _element : *this->tests) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["errors"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->errors->size()); for (const auto& _element : *this->errors) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<TestDiscovery>, std::string> TestDiscovery::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>>> _field_tests;
    if (auto _iterator_tests = _object->find("tests"); _iterator_tests != _object->end()) {
            if (!(doof::json_is_array(_iterator_tests->second))) { return doof::Failure<std::string>{"Field \"tests\" expected array but got " + std::string(doof::json_type_name(_iterator_tests->second))}; }
        _field_tests = [&]() { const auto* _array = doof::json_as_array(_iterator_tests->second); auto _values = std::make_shared<std::vector<std::shared_ptr<DiscoveredTest>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::json_decode_value(DiscoveredTest::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_tests = std::make_shared<std::vector<std::shared_ptr<DiscoveredTest>>>(std::vector<std::shared_ptr<DiscoveredTest>>{});
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_errors;
    if (auto _iterator_errors = _object->find("errors"); _iterator_errors != _object->end()) {
            if (!(doof::json_is_array(_iterator_errors->second))) { return doof::Failure<std::string>{"Field \"errors\" expected array but got " + std::string(doof::json_type_name(_iterator_errors->second))}; }
        _field_errors = [&]() { const auto* _array = doof::json_as_array(_iterator_errors->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_errors = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
        return doof::Success<std::shared_ptr<TestDiscovery>>{std::make_shared<TestDiscovery>(_field_tests.value(), _field_errors.value())};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}
std::shared_ptr<TestDiscovery> discoverModuleTests(const std::shared_ptr<::app_src_ast_::Program>& program, const std::string& modulePath, const std::string& rootDirectory) {
    const auto result = std::make_shared<TestDiscovery>(std::make_shared<std::vector<std::shared_ptr<DiscoveredTest>>>(std::vector<std::shared_ptr<DiscoveredTest>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    auto usesMocks = false;
    const auto& _iterable_1 = program->statements;
    for (const auto& statement : *_iterable_1) {
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MockImportDirective>>(_case_subject)) {
                (usesMocks = true);
        }
        else {
        }
        }
    }
    const auto& _iterable_2 = program->statements;
    for (const auto& statement : *_iterable_2) {
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
                const auto& _iterable_3 = list->specifiers;
                for (const auto& specifier : *_iterable_3) {
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
    const auto& _iterable_4 = tests;
    for (const auto& test : *_iterable_4) {
        if (!test->usesMocks) {
            shared->tests->push_back(test);
            continue;
        }
        std::shared_ptr<TestCompilationGroup> group = nullptr;
        const auto& _iterable_5 = mocked;
        for (const auto& existing : *_iterable_5) {
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
    const auto& _iterable_6 = mocked;
    for (const auto& group : *_iterable_6) {
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
    const auto& _iterable_7 = tests;
    for (const auto& test : *_iterable_7) {
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
    const auto& _iterable_8 = doof::string_split(output, std::string("\n"));
    for (const auto& line : *_iterable_8) {
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
    const auto& _iterable_9 = doof::string_split(output, std::string("\n"));
    for (const auto& line : *_iterable_9) {
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
        const auto& _iterable_10 = module->instrumentedLines;
        for (const auto& line : *_iterable_10) {
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
    const auto& _iterable_11 = report->files;
    for (const auto& file : *_iterable_11) {
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
    const auto& _iterable_12 = lines;
    for (const auto& existing : *_iterable_12) {
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
    const auto& _iterable_13 = statements;
    for (const auto& statement : *_iterable_13) {
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
    const auto& _iterable_14 = tests;
    for (const auto& test : *_iterable_14) {
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
    const auto components = doof::string_split(path, std::string("/"));
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

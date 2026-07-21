#include "src_emitter_header.hpp"
#include <cmath>
#include "src_ast.hpp"
#include "src_emitter_context.hpp"
#include "src_emitter_decl.hpp"
#include "src_emitter_expr.hpp"
#include "src_emitter_json.hpp"
#include "src_emitter_types.hpp"
#include "src_semantic.hpp"
#include "src_emitter_names.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_emitter_header_ {
using namespace ::app_src_ast_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_decl_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_json_;
using namespace ::app_src_emitter_types_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_names_;

doof::JsonObject HeaderPlan::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["functionSignatures"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->functionSignatures->size()); for (const auto& _element : *this->functionSignatures) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["nativeAdapterSignatures"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->nativeAdapterSignatures->size()); for (const auto& _element : *this->nativeAdapterSignatures) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["genericFunctionDefinitions"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->genericFunctionDefinitions->size()); for (const auto& _element : *this->genericFunctionDefinitions) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["exportedValueDefinitions"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->exportedValueDefinitions->size()); for (const auto& _element : *this->exportedValueDefinitions) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["earlyClassDefinitions"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->earlyClassDefinitions->size()); for (const auto& _element : *this->earlyClassDefinitions) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["classDefinitions"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->classDefinitions->size()); for (const auto& _element : *this->classDefinitions) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["interfaceAliases"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->interfaceAliases->size()); for (const auto& _element : *this->interfaceAliases) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["enumDefinitions"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->enumDefinitions->size()); for (const auto& _element : *this->enumDefinitions) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["typeAliases"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->typeAliases->size()); for (const auto& _element : *this->typeAliases) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["classForwardDeclarations"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->classForwardDeclarations->size()); for (const auto& _element : *this->classForwardDeclarations) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["typeOnlyForwardDeclarations"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->typeOnlyForwardDeclarations->size()); for (const auto& _element : *this->typeOnlyForwardDeclarations) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["typeOnlyModuleIncludes"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->typeOnlyModuleIncludes->size()); for (const auto& _element : *this->typeOnlyModuleIncludes) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["moduleIncludes"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->moduleIncludes->size()); for (const auto& _element : *this->moduleIncludes) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["nativeIncludes"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->nativeIncludes->size()); for (const auto& _element : *this->nativeIncludes) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["nativeAliases"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->nativeAliases->size()); for (const auto& _element : *this->nativeAliases) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["nativeNamespaces"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->nativeNamespaces->size()); for (const auto& _element : *this->nativeNamespaces) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["hasMain"] = doof::json_value(this->hasMain);
    (*_json)["mainReturnsInt"] = doof::json_value(this->mainReturnsInt);
    (*_json)["mainAcceptsArgs"] = doof::json_value(this->mainAcceptsArgs);
    return _json;
}
doof::Result<std::shared_ptr<HeaderPlan>, std::string> HeaderPlan::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_functionSignatures;
    if (auto _iterator_functionSignatures = _object->find("functionSignatures"); _iterator_functionSignatures != _object->end()) {
        if (!(doof::json_is_array(_iterator_functionSignatures->second))) { return doof::Failure<std::string>{"Field \"functionSignatures\" expected array but got " + std::string(doof::json_type_name(_iterator_functionSignatures->second))}; }
        _field_functionSignatures = [&]() { const auto* _array = doof::json_as_array(_iterator_functionSignatures->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_functionSignatures = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_nativeAdapterSignatures;
    if (auto _iterator_nativeAdapterSignatures = _object->find("nativeAdapterSignatures"); _iterator_nativeAdapterSignatures != _object->end()) {
        if (!(doof::json_is_array(_iterator_nativeAdapterSignatures->second))) { return doof::Failure<std::string>{"Field \"nativeAdapterSignatures\" expected array but got " + std::string(doof::json_type_name(_iterator_nativeAdapterSignatures->second))}; }
        _field_nativeAdapterSignatures = [&]() { const auto* _array = doof::json_as_array(_iterator_nativeAdapterSignatures->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_nativeAdapterSignatures = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_genericFunctionDefinitions;
    if (auto _iterator_genericFunctionDefinitions = _object->find("genericFunctionDefinitions"); _iterator_genericFunctionDefinitions != _object->end()) {
        if (!(doof::json_is_array(_iterator_genericFunctionDefinitions->second))) { return doof::Failure<std::string>{"Field \"genericFunctionDefinitions\" expected array but got " + std::string(doof::json_type_name(_iterator_genericFunctionDefinitions->second))}; }
        _field_genericFunctionDefinitions = [&]() { const auto* _array = doof::json_as_array(_iterator_genericFunctionDefinitions->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_genericFunctionDefinitions = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_exportedValueDefinitions;
    if (auto _iterator_exportedValueDefinitions = _object->find("exportedValueDefinitions"); _iterator_exportedValueDefinitions != _object->end()) {
        if (!(doof::json_is_array(_iterator_exportedValueDefinitions->second))) { return doof::Failure<std::string>{"Field \"exportedValueDefinitions\" expected array but got " + std::string(doof::json_type_name(_iterator_exportedValueDefinitions->second))}; }
        _field_exportedValueDefinitions = [&]() { const auto* _array = doof::json_as_array(_iterator_exportedValueDefinitions->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_exportedValueDefinitions = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_earlyClassDefinitions;
    if (auto _iterator_earlyClassDefinitions = _object->find("earlyClassDefinitions"); _iterator_earlyClassDefinitions != _object->end()) {
        if (!(doof::json_is_array(_iterator_earlyClassDefinitions->second))) { return doof::Failure<std::string>{"Field \"earlyClassDefinitions\" expected array but got " + std::string(doof::json_type_name(_iterator_earlyClassDefinitions->second))}; }
        _field_earlyClassDefinitions = [&]() { const auto* _array = doof::json_as_array(_iterator_earlyClassDefinitions->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_earlyClassDefinitions = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_classDefinitions;
    if (auto _iterator_classDefinitions = _object->find("classDefinitions"); _iterator_classDefinitions != _object->end()) {
        if (!(doof::json_is_array(_iterator_classDefinitions->second))) { return doof::Failure<std::string>{"Field \"classDefinitions\" expected array but got " + std::string(doof::json_type_name(_iterator_classDefinitions->second))}; }
        _field_classDefinitions = [&]() { const auto* _array = doof::json_as_array(_iterator_classDefinitions->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_classDefinitions = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_interfaceAliases;
    if (auto _iterator_interfaceAliases = _object->find("interfaceAliases"); _iterator_interfaceAliases != _object->end()) {
        if (!(doof::json_is_array(_iterator_interfaceAliases->second))) { return doof::Failure<std::string>{"Field \"interfaceAliases\" expected array but got " + std::string(doof::json_type_name(_iterator_interfaceAliases->second))}; }
        _field_interfaceAliases = [&]() { const auto* _array = doof::json_as_array(_iterator_interfaceAliases->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_interfaceAliases = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_enumDefinitions;
    if (auto _iterator_enumDefinitions = _object->find("enumDefinitions"); _iterator_enumDefinitions != _object->end()) {
        if (!(doof::json_is_array(_iterator_enumDefinitions->second))) { return doof::Failure<std::string>{"Field \"enumDefinitions\" expected array but got " + std::string(doof::json_type_name(_iterator_enumDefinitions->second))}; }
        _field_enumDefinitions = [&]() { const auto* _array = doof::json_as_array(_iterator_enumDefinitions->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_enumDefinitions = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_typeAliases;
    if (auto _iterator_typeAliases = _object->find("typeAliases"); _iterator_typeAliases != _object->end()) {
        if (!(doof::json_is_array(_iterator_typeAliases->second))) { return doof::Failure<std::string>{"Field \"typeAliases\" expected array but got " + std::string(doof::json_type_name(_iterator_typeAliases->second))}; }
        _field_typeAliases = [&]() { const auto* _array = doof::json_as_array(_iterator_typeAliases->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_typeAliases = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_classForwardDeclarations;
    if (auto _iterator_classForwardDeclarations = _object->find("classForwardDeclarations"); _iterator_classForwardDeclarations != _object->end()) {
        if (!(doof::json_is_array(_iterator_classForwardDeclarations->second))) { return doof::Failure<std::string>{"Field \"classForwardDeclarations\" expected array but got " + std::string(doof::json_type_name(_iterator_classForwardDeclarations->second))}; }
        _field_classForwardDeclarations = [&]() { const auto* _array = doof::json_as_array(_iterator_classForwardDeclarations->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_classForwardDeclarations = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_typeOnlyForwardDeclarations;
    if (auto _iterator_typeOnlyForwardDeclarations = _object->find("typeOnlyForwardDeclarations"); _iterator_typeOnlyForwardDeclarations != _object->end()) {
        if (!(doof::json_is_array(_iterator_typeOnlyForwardDeclarations->second))) { return doof::Failure<std::string>{"Field \"typeOnlyForwardDeclarations\" expected array but got " + std::string(doof::json_type_name(_iterator_typeOnlyForwardDeclarations->second))}; }
        _field_typeOnlyForwardDeclarations = [&]() { const auto* _array = doof::json_as_array(_iterator_typeOnlyForwardDeclarations->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_typeOnlyForwardDeclarations = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_typeOnlyModuleIncludes;
    if (auto _iterator_typeOnlyModuleIncludes = _object->find("typeOnlyModuleIncludes"); _iterator_typeOnlyModuleIncludes != _object->end()) {
        if (!(doof::json_is_array(_iterator_typeOnlyModuleIncludes->second))) { return doof::Failure<std::string>{"Field \"typeOnlyModuleIncludes\" expected array but got " + std::string(doof::json_type_name(_iterator_typeOnlyModuleIncludes->second))}; }
        _field_typeOnlyModuleIncludes = [&]() { const auto* _array = doof::json_as_array(_iterator_typeOnlyModuleIncludes->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_typeOnlyModuleIncludes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_moduleIncludes;
    if (auto _iterator_moduleIncludes = _object->find("moduleIncludes"); _iterator_moduleIncludes != _object->end()) {
        if (!(doof::json_is_array(_iterator_moduleIncludes->second))) { return doof::Failure<std::string>{"Field \"moduleIncludes\" expected array but got " + std::string(doof::json_type_name(_iterator_moduleIncludes->second))}; }
        _field_moduleIncludes = [&]() { const auto* _array = doof::json_as_array(_iterator_moduleIncludes->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_moduleIncludes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_nativeIncludes;
    if (auto _iterator_nativeIncludes = _object->find("nativeIncludes"); _iterator_nativeIncludes != _object->end()) {
        if (!(doof::json_is_array(_iterator_nativeIncludes->second))) { return doof::Failure<std::string>{"Field \"nativeIncludes\" expected array but got " + std::string(doof::json_type_name(_iterator_nativeIncludes->second))}; }
        _field_nativeIncludes = [&]() { const auto* _array = doof::json_as_array(_iterator_nativeIncludes->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_nativeIncludes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_nativeAliases;
    if (auto _iterator_nativeAliases = _object->find("nativeAliases"); _iterator_nativeAliases != _object->end()) {
        if (!(doof::json_is_array(_iterator_nativeAliases->second))) { return doof::Failure<std::string>{"Field \"nativeAliases\" expected array but got " + std::string(doof::json_type_name(_iterator_nativeAliases->second))}; }
        _field_nativeAliases = [&]() { const auto* _array = doof::json_as_array(_iterator_nativeAliases->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_nativeAliases = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_nativeNamespaces;
    if (auto _iterator_nativeNamespaces = _object->find("nativeNamespaces"); _iterator_nativeNamespaces != _object->end()) {
        if (!(doof::json_is_array(_iterator_nativeNamespaces->second))) { return doof::Failure<std::string>{"Field \"nativeNamespaces\" expected array but got " + std::string(doof::json_type_name(_iterator_nativeNamespaces->second))}; }
        _field_nativeNamespaces = [&]() { const auto* _array = doof::json_as_array(_iterator_nativeNamespaces->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_nativeNamespaces = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    std::optional<bool> _field_hasMain;
    if (auto _iterator_hasMain = _object->find("hasMain"); _iterator_hasMain != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_hasMain->second) : doof::json_is_boolean(_iterator_hasMain->second)))) { return doof::Failure<std::string>{"Field \"hasMain\" expected boolean but got " + std::string(doof::json_type_name(_iterator_hasMain->second))}; }
        _field_hasMain = (_lenient ? doof::json_as_bool_lenient(_iterator_hasMain->second) : doof::json_as_bool(_iterator_hasMain->second));
    } else {
        _field_hasMain = false;
    }
    std::optional<bool> _field_mainReturnsInt;
    if (auto _iterator_mainReturnsInt = _object->find("mainReturnsInt"); _iterator_mainReturnsInt != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_mainReturnsInt->second) : doof::json_is_boolean(_iterator_mainReturnsInt->second)))) { return doof::Failure<std::string>{"Field \"mainReturnsInt\" expected boolean but got " + std::string(doof::json_type_name(_iterator_mainReturnsInt->second))}; }
        _field_mainReturnsInt = (_lenient ? doof::json_as_bool_lenient(_iterator_mainReturnsInt->second) : doof::json_as_bool(_iterator_mainReturnsInt->second));
    } else {
        _field_mainReturnsInt = false;
    }
    std::optional<bool> _field_mainAcceptsArgs;
    if (auto _iterator_mainAcceptsArgs = _object->find("mainAcceptsArgs"); _iterator_mainAcceptsArgs != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_mainAcceptsArgs->second) : doof::json_is_boolean(_iterator_mainAcceptsArgs->second)))) { return doof::Failure<std::string>{"Field \"mainAcceptsArgs\" expected boolean but got " + std::string(doof::json_type_name(_iterator_mainAcceptsArgs->second))}; }
        _field_mainAcceptsArgs = (_lenient ? doof::json_as_bool_lenient(_iterator_mainAcceptsArgs->second) : doof::json_as_bool(_iterator_mainAcceptsArgs->second));
    } else {
        _field_mainAcceptsArgs = false;
    }
    return doof::Success<std::shared_ptr<HeaderPlan>>{std::make_shared<HeaderPlan>(_field_functionSignatures.value(), _field_nativeAdapterSignatures.value(), _field_genericFunctionDefinitions.value(), _field_exportedValueDefinitions.value(), _field_earlyClassDefinitions.value(), _field_classDefinitions.value(), _field_interfaceAliases.value(), _field_enumDefinitions.value(), _field_typeAliases.value(), _field_classForwardDeclarations.value(), _field_typeOnlyForwardDeclarations.value(), _field_typeOnlyModuleIncludes.value(), _field_moduleIncludes.value(), _field_nativeIncludes.value(), _field_nativeAliases.value(), _field_nativeNamespaces.value(), _field_hasMain.value(), _field_mainReturnsInt.value(), _field_mainAcceptsArgs.value())};
}
std::shared_ptr<HeaderPlan> planHeader(std::shared_ptr<::app_src_ast_::Program> program, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    return planHeaders(std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{program}), context);
}
std::shared_ptr<HeaderPlan> planHeaders(std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto plan = std::make_shared<HeaderPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, false, false);
    const auto& _iterable_1 = programs;
    for (const auto& program : *_iterable_1) {
        const auto& _iterable_2 = program->statements;
        for (const auto& statement : *_iterable_2) {
            collect(statement, plan, context);
        }
    }
    const auto& _iterable_3 = context->imports;
    for (const auto& imported : *_iterable_3) {
        if (((!doof::is_null(imported->symbol)) && ((doof::kind(imported->symbol) == std::string("class")) || (doof::kind(imported->symbol) == std::string("struct")))) && !surfaceSymbolIsGeneric(context, doof::unwrap_optional(imported->symbol))) {
            const auto declaration = ((((std::string("namespace ") + ::app_src_emitter_names_::moduleNamespace(imported->symbol->module)) + std::string(" { struct ")) + imported->symbol->name) + std::string("; }\n"));
            addUnique(plan->typeOnlyForwardDeclarations, declaration);
        } else if ((!doof::is_null(imported->symbol)) && (doof::kind(imported->symbol) == std::string("enum"))) {
            const auto declaration = ((((std::string("namespace ") + ::app_src_emitter_names_::moduleNamespace(imported->symbol->module)) + std::string(" { enum class ")) + imported->symbol->name) + std::string("; }\n"));
            addUnique(plan->typeOnlyForwardDeclarations, declaration);
        }
        if (imported->typeOnly && !hasNonTypeOnlyImport(context->imports, imported->sourceModule)) {
            const auto includeName = ::app_src_emitter_names_::moduleHeaderName(imported->sourceModule);
            addUnique(plan->typeOnlyModuleIncludes, includeName);
        }
    }
    const auto& _iterable_4 = plan->nativeNamespaces;
    for (const auto& namespace_ : *_iterable_4) {
        if (namespace_ != std::string("")) {
            const auto& _iterable_5 = context->imports;
            for (const auto& imported : *_iterable_5) {
                if (!doof::is_null(imported->symbol)) {
                    if (doof::kind(imported->symbol) == std::string("function")) {
                        if (imported->symbol->native_ || !surfaceFunctionIsGeneric(context, doof::unwrap_optional(imported->symbol))) {
                            const auto target = (imported->symbol->native_ ? imported->symbol->nativeCppName : ((::app_src_emitter_names_::moduleNamespace(imported->symbol->module) + std::string("::")) + imported->symbol->name));
                            addUnique(plan->nativeAliases, ((((std::string("namespace ") + namespace_) + std::string(" { using ::")) + target) + std::string("; }\n")));
                        }
                    } else if (!surfaceSymbolIsGeneric(context, doof::unwrap_optional(imported->symbol))) {
                        addNativeSymbolAlias(doof::unwrap_optional(imported->symbol), namespace_, plan);
                    }
                    collectNativeModuleSurfaceAliases(imported->symbol->module, namespace_, plan, context);
                }
            }
        }
    }
    return plan;
}
void collectNativeModuleSurfaceAliases(std::string modulePath, std::string namespace_, std::shared_ptr<HeaderPlan> plan, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto& _iterable_6 = context->moduleSurfaces;
    for (const auto& surface : *_iterable_6) {
        if (surface->path != modulePath) {
            continue;
        }
        const auto& _iterable_7 = surface->exports;
        for (const auto& symbol : *_iterable_7) {
            if (isNativeAliasType(symbol) && !surfaceTypeIsGeneric(surface, symbol->name)) {
                addNativeSymbolAlias(symbol, namespace_, plan);
            }
        }
        const auto& _iterable_8 = surface->imports;
        for (const auto& imported : *_iterable_8) {
            if (((!doof::is_null(imported->symbol)) && isNativeAliasType(doof::unwrap_optional(imported->symbol))) && !surfaceSymbolIsGeneric(context, doof::unwrap_optional(imported->symbol))) {
                addNativeSymbolAlias(doof::unwrap_optional(imported->symbol), namespace_, plan);
            }
        }
        return;
    }
}
bool surfaceTypeIsGeneric(std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface> surface, std::string name) {
    const auto& _iterable_9 = surface->genericTypes;
    for (const auto& genericName : *_iterable_9) {
        if (genericName == name) {
            return true;
        }
    }
    return false;
}
bool isNativeAliasType(std::shared_ptr<::app_src_semantic_::Symbol> symbol) {
    return (((((symbol->kind == std::string("class")) || (symbol->kind == std::string("struct"))) || (symbol->kind == std::string("enum"))) || (symbol->kind == std::string("interface"))) || (symbol->kind == std::string("type-alias")));
}
void collect(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement, std::shared_ptr<HeaderPlan> plan, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            if (class_->native_) {
                const auto rawInclude = ((class_->nativeHeader == std::string("")) ? (class_->name + std::string(".hpp")) : class_->nativeHeader);
                const auto include = ::app_src_emitter_names_::moduleNativeHeaderPath(context->modulePath, rawInclude);
                addUnique(plan->nativeIncludes, include);
                const auto namespace_ = nativeNamespace(class_->nativeCppName);
                addUnique(plan->nativeNamespaces, namespace_);
                collectNativeClassAliases(class_, namespace_, plan, context);
            } else if ((static_cast<int32_t>((class_->typeParams)->size()) == 0) || isNativeTemplateClass(context, class_->name)) {
                if (static_cast<int32_t>((class_->typeParams)->size()) == 0) {
                    plan->classForwardDeclarations->push_back(((std::string("struct ") + class_->name) + std::string(";\n")));
                }
                const auto definition = ::app_src_emitter_decl_::emitClassDeclaration(class_, context, std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>>(std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>{}));
                if (classCanEmitBeforeModuleIncludes(class_)) {
                    plan->earlyClassDefinitions->push_back(definition);
                } else {
                    plan->classDefinitions->push_back(definition);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
            if (static_cast<int32_t>((interface_->typeParams)->size()) == 0) {
                plan->interfaceAliases->push_back(::app_src_emitter_decl_::emitInterfaceAlias(interface_, context));
                const auto declaration = ::app_src_emitter_json_::emitInterfaceJsonDeclaration(interface_);
                if (declaration != std::string("")) {
                    plan->functionSignatures->push_back(declaration);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
            plan->enumDefinitions->push_back(emitEnumDeclaration(enum_, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
            if (static_cast<int32_t>((alias->typeParams)->size()) == 0) {
                plan->typeAliases->push_back(emitTypeAlias(alias, context));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            if (const_->exported) {
                plan->exportedValueDefinitions->push_back((::app_src_emitter_decl_::emitDescriptionComment(const_->description, std::string("")) + emitExportedValue(const_->name, const_->value, context)));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            if (readonly_->exported) {
                plan->exportedValueDefinitions->push_back((::app_src_emitter_decl_::emitDescriptionComment(readonly_->description, std::string("")) + emitExportedValue(readonly_->name, readonly_->value, context)));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
            if (fn->native_) {
                if (fn->nativeHeader != std::string("")) {
                    addUnique(plan->nativeIncludes, ::app_src_emitter_names_::moduleNativeHeaderPath(context->modulePath, fn->nativeHeader));
                }
                const auto namespace_ = nativeNamespace(fn->nativeCppName);
                addUnique(plan->nativeNamespaces, namespace_);
                if (!doof::is_null(fn->resolvedType)) {
                    collectNativeTypeAliases(doof::unwrap_optional(fn->resolvedType), namespace_, plan, context);
                }
                return;
            }
            if (fn->name == std::string("main")) {
                (plan->hasMain = true);
                (plan->mainReturnsInt = functionReturnsInt(fn));
                (plan->mainAcceptsArgs = (static_cast<int32_t>((fn->params)->size()) == 1));
                plan->functionSignatures->push_back(::app_src_emitter_decl_::emitFunctionDeclaration(fn, std::string("doof_main"), context->modulePath, context));
            } else if (static_cast<int32_t>((fn->typeParams)->size()) > 0) {
            } else {
                plan->functionSignatures->push_back(::app_src_emitter_decl_::emitFunctionDeclaration(fn, std::string(""), context->modulePath, context));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            collect(export_->declaration, plan, context);
    }
    else {
    }
    }
}
bool classCanEmitBeforeModuleIncludes(std::shared_ptr<::app_src_ast_::ClassDeclaration> class_) {
    if (!class_->struct_ || (static_cast<int32_t>((class_->typeParams)->size()) > 0)) {
        return false;
    }
    const auto& _iterable_10 = class_->fields;
    for (const auto& field : *_iterable_10) {
        if ((!field->static_ && (!doof::is_null(field->resolvedType))) && typeNeedsCompleteNominalDefinition(doof::unwrap_optional(field->resolvedType))) {
            return false;
        }
    }
    return true;
}
bool typeNeedsCompleteNominalDefinition(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            if ((class_->symbol->kind == std::string("struct")) || class_->symbol->native_) {
                return true;
            }
            const auto& _iterable_11 = class_->typeArgs;
            for (const auto& argument : *_iterable_11) {
                if (typeNeedsCompleteNominalDefinition(argument)) {
                    return true;
                }
            }
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
            const auto& _iterable_12 = interface_->typeArgs;
            for (const auto& argument : *_iterable_12) {
                if (typeNeedsCompleteNominalDefinition(argument)) {
                    return true;
                }
            }
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            return typeNeedsCompleteNominalDefinition(array->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            return (typeNeedsCompleteNominalDefinition(map->keyType) || typeNeedsCompleteNominalDefinition(map->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
            return typeNeedsCompleteNominalDefinition(set_->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
            return typeNeedsCompleteNominalDefinition(stream->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            return (typeNeedsCompleteNominalDefinition(result->valueType) || typeNeedsCompleteNominalDefinition(result->errorType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            const auto& _iterable_13 = tuple->elements;
            for (const auto& element : *_iterable_13) {
                if (typeNeedsCompleteNominalDefinition(element)) {
                    return true;
                }
            }
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            const auto& _iterable_14 = union_->types;
            for (const auto& member : *_iterable_14) {
                if (typeNeedsCompleteNominalDefinition(member)) {
                    return true;
                }
            }
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            const auto& _iterable_15 = function_->params;
            for (const auto& parameter : *_iterable_15) {
                if (typeNeedsCompleteNominalDefinition(parameter->type_)) {
                    return true;
                }
            }
            return typeNeedsCompleteNominalDefinition(function_->returnType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
            return typeNeedsCompleteNominalDefinition(weak_->inner);
    }
    else {
            return false;
    }
    }
}
bool isNativeTemplateClass(std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::string name) {
    const auto key = ((context->modulePath + std::string("::")) + name);
    const auto& _iterable_16 = context->nativeTemplateClassKeys;
    for (const auto& existing : *_iterable_16) {
        if (existing == key) {
            return true;
        }
    }
    return false;
}
void collectNativeClassAliases(std::shared_ptr<::app_src_ast_::ClassDeclaration> class_, std::string namespace_, std::shared_ptr<HeaderPlan> plan, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto& _iterable_17 = class_->fields;
    for (const auto& field : *_iterable_17) {
        if (!doof::is_null(field->resolvedType)) {
            collectNativeTypeAliases(doof::unwrap_optional(field->resolvedType), namespace_, plan, context);
        }
    }
    const auto& _iterable_18 = class_->methods;
    for (const auto& method : *_iterable_18) {
        if (!doof::is_null(method->resolvedType)) {
            collectNativeTypeAliases(doof::unwrap_optional(method->resolvedType), namespace_, plan, context);
        }
    }
}
void collectNativeTypeAliases(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_, std::string namespace_, std::shared_ptr<HeaderPlan> plan, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            if (!surfaceSymbolIsGeneric(context, class_->symbol)) {
                addNativeSymbolAlias(class_->symbol, namespace_, plan);
            }
            const auto& _iterable_19 = class_->typeArgs;
            for (const auto& argument : *_iterable_19) {
                collectNativeTypeAliases(argument, namespace_, plan, context);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
            addNativeSymbolAlias(enum_->symbol, namespace_, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
            if (!surfaceSymbolIsGeneric(context, interface_->symbol)) {
                addNativeSymbolAlias(interface_->symbol, namespace_, plan);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            collectNativeTypeAliases(array->elementType, namespace_, plan, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            collectNativeTypeAliases(map->keyType, namespace_, plan, context);
            collectNativeTypeAliases(map->valueType, namespace_, plan, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
            collectNativeTypeAliases(set_->elementType, namespace_, plan, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
            collectNativeTypeAliases(stream->elementType, namespace_, plan, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            collectNativeTypeAliases(result->valueType, namespace_, plan, context);
            collectNativeTypeAliases(result->errorType, namespace_, plan, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            const auto& _iterable_20 = tuple->elements;
            for (const auto& element : *_iterable_20) {
                collectNativeTypeAliases(element, namespace_, plan, context);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            const auto& _iterable_21 = union_->types;
            for (const auto& member : *_iterable_21) {
                collectNativeTypeAliases(member, namespace_, plan, context);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
            collectNativeTypeAliases(weak_->inner, namespace_, plan, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            const auto& _iterable_22 = function_->params;
            for (const auto& parameter : *_iterable_22) {
                collectNativeTypeAliases(parameter->type_, namespace_, plan, context);
            }
            collectNativeTypeAliases(function_->returnType, namespace_, plan, context);
    }
    else {
    }
    }
}
bool surfaceSymbolIsGeneric(std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::shared_ptr<::app_src_semantic_::Symbol> symbol) {
    const auto& _iterable_23 = context->moduleSurfaces;
    for (const auto& surface : *_iterable_23) {
        if (surface->path == symbol->module) {
            return surfaceTypeIsGeneric(surface, symbol->name);
        }
    }
    return false;
}
bool surfaceFunctionIsGeneric(std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::shared_ptr<::app_src_semantic_::Symbol> symbol) {
    const auto& _iterable_24 = context->moduleSurfaces;
    for (const auto& surface : *_iterable_24) {
        if (surface->path == symbol->module) {
            const auto& _iterable_25 = surface->genericFunctions;
            for (const auto& genericName : *_iterable_25) {
                if (genericName == symbol->name) {
                    return true;
                }
            }
            return false;
        }
    }
    return false;
}
void addNativeSymbolAlias(std::shared_ptr<::app_src_semantic_::Symbol> symbol, std::string namespace_, std::shared_ptr<HeaderPlan> plan) {
    if (symbol->native_ || (symbol->module == std::string(""))) {
        return;
    }
    if (((symbol->kind == std::string("class")) || (symbol->kind == std::string("struct"))) || (symbol->kind == std::string("interface"))) {
        addUnique(plan->typeOnlyForwardDeclarations, ((((std::string("namespace ") + ::app_src_emitter_names_::moduleNamespace(symbol->module)) + std::string(" { struct ")) + symbol->name) + std::string("; }\n")));
    } else if (symbol->kind == std::string("enum")) {
        addUnique(plan->typeOnlyForwardDeclarations, ((((std::string("namespace ") + ::app_src_emitter_names_::moduleNamespace(symbol->module)) + std::string(" { enum class ")) + symbol->name) + std::string("; }\n")));
    }
    const auto alias = ((((((std::string("using ") + symbol->name) + std::string(" = ::")) + ::app_src_emitter_names_::moduleNamespace(symbol->module)) + std::string("::")) + symbol->name) + std::string(";"));
    addUnique(plan->nativeAliases, ((namespace_ == std::string("")) ? (alias + std::string("\n")) : ((((std::string("namespace ") + namespace_) + std::string(" { ")) + alias) + std::string(" }\n"))));
}
std::string renderHeader(std::shared_ptr<HeaderPlan> plan, std::string guardName) {
    auto result = std::string("#pragma once\n");
    (result = (result + std::string("#include \"doof_runtime.hpp\"\n")));
    (result = (result + std::string("#include <cstdint>\n#include <cmath>\n#include <functional>\n")));
    (result = (result + std::string("#include <memory>\n#include <optional>\n#include <ostream>\n#include <string>\n")));
    (result = (result + std::string("#include <tuple>\n#include <type_traits>\n#include <variant>\n#include <vector>\n")));
    const auto& _iterable_26 = plan->typeOnlyForwardDeclarations;
    for (const auto& declaration : *_iterable_26) {
        (result = (result + declaration));
    }
    if (static_cast<int32_t>((plan->typeOnlyForwardDeclarations)->size()) > 0) {
        (result = (result + std::string("\n")));
    }
    (result = (((result + std::string("namespace ")) + guardName) + std::string(" {\n")));
    const auto& _iterable_27 = plan->classForwardDeclarations;
    for (const auto& declaration : *_iterable_27) {
        (result = ((result + std::string("    ")) + declaration));
    }
    (result = (result + std::string("}\n\n")));
    if (static_cast<int32_t>((plan->earlyClassDefinitions)->size()) > 0) {
        (result = (((result + std::string("namespace ")) + guardName) + std::string(" {\n")));
        const auto& _iterable_28 = plan->earlyClassDefinitions;
        for (const auto& definition : *_iterable_28) {
            (result = ((result + std::string("    ")) + definition));
        }
        (result = (result + std::string("}\n\n")));
    }
    const auto& _iterable_29 = plan->moduleIncludes;
    for (const auto& include : *_iterable_29) {
        if (!containsValue(plan->typeOnlyModuleIncludes, include)) {
            (result = (((result + std::string("#include \"")) + include) + std::string("\"\n")));
        }
    }
    if (static_cast<int32_t>((plan->moduleIncludes)->size()) > 0) {
        (result = (result + std::string("\n")));
    }
    const auto& _iterable_30 = plan->nativeAliases;
    for (const auto& alias : *_iterable_30) {
        (result = (result + alias));
    }
    const auto& _iterable_31 = plan->nativeIncludes;
    for (const auto& include : *_iterable_31) {
        if (doof::string_startsWith(include, std::string("<"))) {
            (result = (((result + std::string("#include ")) + include) + std::string("\n")));
        } else {
            (result = (((result + std::string("#include \"")) + include) + std::string("\"\n")));
        }
    }
    if ((static_cast<int32_t>((plan->nativeAliases)->size()) > 0) || (static_cast<int32_t>((plan->nativeIncludes)->size()) > 0)) {
        (result = (result + std::string("\n")));
    }
    (result = (((result + std::string("namespace ")) + guardName) + std::string(" {\n")));
    const auto& _iterable_32 = plan->interfaceAliases;
    for (const auto& alias : *_iterable_32) {
        (result = ((result + std::string("    ")) + alias));
    }
    const auto& _iterable_33 = plan->enumDefinitions;
    for (const auto& definition : *_iterable_33) {
        (result = ((result + std::string("    ")) + definition));
    }
    const auto& _iterable_34 = plan->nativeAdapterSignatures;
    for (const auto& signature : *_iterable_34) {
        (result = ((result + std::string("    ")) + signature));
    }
    const auto& _iterable_35 = plan->classDefinitions;
    for (const auto& definition : *_iterable_35) {
        (result = ((result + std::string("    ")) + definition));
    }
    const auto& _iterable_36 = plan->typeAliases;
    for (const auto& alias : *_iterable_36) {
        (result = ((result + std::string("    ")) + alias));
    }
    const auto& _iterable_37 = plan->functionSignatures;
    for (const auto& signature : *_iterable_37) {
        (result = ((result + std::string("    ")) + signature));
    }
    (result = (result + std::string("}\n\n")));
    (result = (((result + std::string("namespace ")) + guardName) + std::string(" {\n")));
    const auto& _iterable_38 = plan->exportedValueDefinitions;
    for (const auto& definition : *_iterable_38) {
        (result = ((result + std::string("    ")) + definition));
    }
    const auto& _iterable_39 = plan->genericFunctionDefinitions;
    for (const auto& definition : *_iterable_39) {
        (result = (result + definition));
    }
    return (result + std::string("}\n"));
}
std::string emitExportedValue(std::string name, std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> value, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    return ((((std::string("inline const auto ") + name) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(value, context, std::monostate{})) + std::string(";\n"));
}
void addUnique(std::shared_ptr<std::vector<std::string>> values, std::string value) {
    const auto& _iterable_40 = values;
    for (const auto& existing : *_iterable_40) {
        if (existing == value) {
            return;
        }
    }
    values->push_back(value);
}
bool hasNonTypeOnlyImport(std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>> imports, std::string sourceModule) {
    const auto& _iterable_41 = imports;
    for (const auto& imported : *_iterable_41) {
        if ((imported->sourceModule == sourceModule) && !imported->typeOnly) {
            return true;
        }
    }
    return false;
}
bool containsValue(std::shared_ptr<std::vector<std::string>> values, std::string value) {
    const auto& _iterable_42 = values;
    for (const auto& existing : *_iterable_42) {
        if (existing == value) {
            return true;
        }
    }
    return false;
}
std::string nativeNamespace(std::string cppName) {
    auto separator = -1;
    for (int32_t i = 0; i < static_cast<int32_t>(cppName.size()); ++i) {
        if (((i + 1) < static_cast<int32_t>(cppName.size())) && (doof::string_substring(cppName, i, (i + 2)) == std::string("::"))) {
            (separator = i);
        }
    }
    if (separator < 0) {
        return std::string("");
    }
    return doof::string_substring(cppName, 0, separator);
}
std::string emitEnumDeclaration(std::shared_ptr<::app_src_ast_::EnumDeclaration> declaration, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    auto result = (((::app_src_emitter_decl_::emitDescriptionComment(declaration->description, std::string("")) + std::string("enum class ")) + declaration->name) + std::string(" {\n"));
    for (int32_t i = 0; i < static_cast<int32_t>((declaration->variants)->size()); ++i) {
        const auto variant = (*declaration->variants)[i];
        (result = (((result + ::app_src_emitter_decl_::emitDescriptionComment(variant->description, std::string("    "))) + std::string("    ")) + variant->name));
        if (!doof::is_null(variant->value)) {
            (result = ((result + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(variant->value), context, std::monostate{})));
        }
        if ((i + 1) < static_cast<int32_t>((declaration->variants)->size())) {
            (result = (result + std::string(",")));
        }
        (result = (result + std::string("\n")));
    }
    (result = (result + std::string("};\n")));
    (result = (((((result + std::string("inline const char* ")) + declaration->name) + std::string("_name(")) + declaration->name) + std::string(" value) {\n")));
    (result = (result + std::string("  switch (value) {\n")));
    const auto& _iterable_43 = declaration->variants;
    for (const auto& variant : *_iterable_43) {
        (result = (((((((result + std::string("    case ")) + declaration->name) + std::string("::")) + variant->name) + std::string(": return \"")) + variant->name) + std::string("\";\n")));
    }
    (result = (result + std::string("  }\n  return \"\";\n}\n")));
    (result = (((((result + std::string("inline std::optional<")) + declaration->name) + std::string("> ")) + declaration->name) + std::string("_fromName(std::string_view value) {\n")));
    const auto& _iterable_44 = declaration->variants;
    for (const auto& variant : *_iterable_44) {
        (result = (((((((result + std::string("  if (value == \"")) + variant->name) + std::string("\") return ")) + declaration->name) + std::string("::")) + variant->name) + std::string(";\n")));
    }
    (result = (result + std::string("  return std::nullopt;\n}\n")));
    (result = (((((result + std::string("inline std::optional<")) + declaration->name) + std::string("> ")) + declaration->name) + std::string("_fromValue(int32_t value) {\n")));
    (result = (((result + std::string("  switch (static_cast<")) + declaration->name) + std::string(">(value)) {\n")));
    const auto& _iterable_45 = declaration->variants;
    for (const auto& variant : *_iterable_45) {
        (result = (((((((((result + std::string("    case ")) + declaration->name) + std::string("::")) + variant->name) + std::string(": return ")) + declaration->name) + std::string("::")) + variant->name) + std::string(";\n")));
    }
    (result = (result + std::string("    default: return std::nullopt;\n  }\n}\n")));
    return (((((result + std::string("inline std::ostream& operator<<(std::ostream& output, ")) + declaration->name) + std::string(" value) { return output << ")) + declaration->name) + std::string("_name(value); }\n"));
}
std::string emitTypeAlias(std::shared_ptr<::app_src_ast_::TypeAliasDeclaration> alias, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    if (doof::is_null(alias->resolvedType)) {
        doof::panic(((std::string("Type alias ") + alias->name) + std::string(" was not checked before emission")));
    }
    return (((((::app_src_emitter_decl_::emitDescriptionComment(alias->description, std::string("")) + std::string("using ")) + alias->name) + std::string(" = ")) + ::app_src_emitter_types_::emitType(doof::unwrap_optional(alias->resolvedType), context->modulePath)) + std::string(";\n"));
}
bool functionReturnsInt(std::shared_ptr<::app_src_ast_::FunctionDeclaration> fn) {
    {
        auto _case_subject = doof::unwrap_optional(fn->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            {
                auto _case_subject = function_->returnType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
                    const auto& primitive = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
                    return (primitive->name == std::string("int"));
            }
            else {
                    return false;
            }
            }
    }
    else {
            return false;
    }
    }
    return false;
}
}

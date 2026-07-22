#include "src_emitter_wasm.hpp"
#include <cmath>
#include "src_ast.hpp"
#include "src_analyzer.hpp"
#include "src_emitter_context.hpp"
#include "src_emitter_expr.hpp"
#include "src_emitter_json.hpp"
#include "src_emitter_names.hpp"
#include "src_emitter_types.hpp"
#include "src_json_semantics.hpp"
#include "src_semantic.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_emitter_wasm_ {
using namespace ::app_src_ast_;
using namespace ::app_src_analyzer_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_json_;
using namespace ::app_src_emitter_names_;
using namespace ::app_src_emitter_types_;
using namespace ::app_src_json_semantics_;
using namespace ::app_src_semantic_;

doof::JsonObject WasmEmission::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["source"] = doof::json_value(this->source);
    (*_json)["exportNames"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->exportNames->size()); for (const auto& _element : *this->exportNames) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<WasmEmission>, std::string> WasmEmission::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_source = _object->find("source");
    if (_iterator_source == _object->end()) { return doof::Failure<std::string>{"Missing required field \"source\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_source->second) : doof::json_is_string(_iterator_source->second)))) { return doof::Failure<std::string>{"Field \"source\" expected string but got " + std::string(doof::json_type_name(_iterator_source->second))}; }
    auto _field_source = (_lenient ? doof::json_as_string_lenient(_iterator_source->second) : doof::json_as_string(_iterator_source->second));
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_exportNames;
    if (auto _iterator_exportNames = _object->find("exportNames"); _iterator_exportNames != _object->end()) {
        if (!(doof::json_is_array(_iterator_exportNames->second))) { return doof::Failure<std::string>{"Field \"exportNames\" expected array but got " + std::string(doof::json_type_name(_iterator_exportNames->second))}; }
        _field_exportNames = [&]() { const auto* _array = doof::json_as_array(_iterator_exportNames->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_exportNames = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    return doof::Success<std::shared_ptr<WasmEmission>>{std::make_shared<WasmEmission>(_field_source, _field_exportNames.value())};
}
doof::Result<std::shared_ptr<WasmEmission>, std::string> emitWasmSupport(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::string entry) {
    const auto info = findModule(result, entry);
    if (doof::is_null(info)) {
        return doof::Failure<std::string>{ (std::string("Module not found: ") + entry) };
    }
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>> exports = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>>(std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>{});
    collectExportedFunctions(doof::unwrap_optional(info), exports);
    std::shared_ptr<std::vector<std::string>> names = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_1 = exports;
    for (const auto& fn : *_iterable_1) {
        if (fn->name == std::string("main")) {
            continue;
        }
        auto _try_value_2 = validateWasmFunction(fn, result);
        if (doof::is_failure(_try_value_2)) return doof::Failure<std::string>{doof::failure_error(_try_value_2)};
        const auto name = (std::string("doof_export_") + ::app_src_emitter_expr_::cppIdentifier(fn->name));
        for (int32_t index = 0; index < static_cast<int32_t>((names)->size()); ++index) {
            if ((*names)[index] == name) {
                return doof::Failure<std::string>{ (((std::string("WebAssembly export name collision for ") + fn->name) + std::string(" at ")) + name) };
            }
        }
        names->push_back(name);
    }
    const auto programs = allPrograms(result);
    const auto context = ::app_src_emitter_context_::createEmitContextForModule(info->program, entry, programs);
    (context->imports = info->imports);
    (context->namespaceImports = info->namespaceImports);
    auto source = wasmPreamble(doof::unwrap_optional(info));
    auto exportIndex = 0;
    const auto& _iterable_3 = exports;
    for (const auto& fn : *_iterable_3) {
        if (fn->name == std::string("main")) {
            continue;
        }
        (source = (source + emitWasmWrapper(fn, (*names)[exportIndex], context)));
        (exportIndex += 1);
    }
    return doof::Success<std::shared_ptr<WasmEmission>>{ std::make_shared<WasmEmission>(source, names) };
}
void collectExportedFunctions(std::shared_ptr<::app_src_analyzer_::ModuleInfo> info, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>> result) {
    const auto& _iterable_4 = info->program->statements;
    for (const auto& statement : *_iterable_4) {
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
                const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
                if (fn->exported || moduleExportsFunction(info, fn->name)) {
                    result->push_back(fn);
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
                const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
                {
                    auto _case_subject = export_->declaration;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
                        const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
                        result->push_back(fn);
                }
                else {
                }
                }
        }
        else {
        }
        }
    }
}
bool moduleExportsFunction(std::shared_ptr<::app_src_analyzer_::ModuleInfo> info, std::string name) {
    const auto& _iterable_5 = info->exports;
    for (const auto& symbol : *_iterable_5) {
        const auto sourceName = ((symbol->originalName == std::string("")) ? symbol->name : symbol->originalName);
        if (((symbol->kind == std::string("function")) && (symbol->module == info->path)) && (sourceName == name)) {
            return true;
        }
    }
    return false;
}
doof::Result<void, std::string> validateWasmFunction(std::shared_ptr<::app_src_ast_::FunctionDeclaration> fn, std::shared_ptr<::app_src_analyzer_::AnalysisResult> analysis) {
    if (static_cast<int32_t>((fn->typeParams)->size()) > 0) {
        return doof::Failure<std::string>{ ((std::string("WebAssembly export \"") + fn->name) + std::string("\" cannot be generic")) };
    }
    auto _binding_value_6 = fn->resolvedType;
    if (doof::is_null(_binding_value_6)) {
        const auto& resolved = _binding_value_6;
        return doof::Failure<std::string>{ ((std::string("WebAssembly export \"") + fn->name) + std::string("\" is missing a resolved function type")) };
    }
    const auto resolved = doof::unwrap_optional(_binding_value_6);
    {
        auto _case_subject = resolved;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& type_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            const auto& _iterable_7 = fn->params;
            for (const auto& parameter : *_iterable_7) {
                if (doof::is_null(parameter->resolvedType) || !isWasmJsonType(doof::unwrap_optional(parameter->resolvedType), analysis)) {
                    return doof::Failure<std::string>{ ((((std::string("Parameter \"") + parameter->name) + std::string("\" of WebAssembly export \"")) + fn->name) + std::string("\" must be supported by the JSON ABI")) };
                }
            }
            {
                auto _case_subject = type_->returnType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
                    return doof::Success<void>{};
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                    const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
                    {
                        auto _case_subject = result->valueType;
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
                    }
                    else {
                            if (!isWasmJsonType(result->valueType, analysis)) {
                                return doof::Failure<std::string>{ ((std::string("Success type of WebAssembly export \"") + fn->name) + std::string("\" must be supported by the JSON ABI")) };
                            }
                    }
                    }
                    if (!isWasmJsonType(result->errorType, analysis)) {
                        return doof::Failure<std::string>{ ((std::string("Error type of WebAssembly export \"") + fn->name) + std::string("\" must be supported by the JSON ABI")) };
                    }
                    return doof::Success<void>{};
            }
            else {
                    if (!isWasmJsonType(type_->returnType, analysis)) {
                        return doof::Failure<std::string>{ ((std::string("Return type of WebAssembly export \"") + fn->name) + std::string("\" must be supported by the JSON ABI")) };
                    }
                    return doof::Success<void>{};
            }
            }
            doof::unreachable();
    }
    else {
            return doof::Failure<std::string>{ ((std::string("WebAssembly export \"") + fn->name) + std::string("\" is missing a resolved function type")) };
    }
    }
    doof::unreachable();
    return doof::Success<void>{};
}
bool isWasmJsonType(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_, std::shared_ptr<::app_src_analyzer_::AnalysisResult> analysis) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            const auto declaration = findClass(analysis, class_);
            return (((!doof::is_null(declaration)) && ::app_src_json_semantics_::canGenerateJsonSerialization(doof::unwrap_optional(declaration), allPrograms(analysis))) && ::app_src_json_semantics_::canGenerateJsonDeserialization(doof::unwrap_optional(declaration), allPrograms(analysis)));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            return isWasmJsonType(array->elementType, analysis);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            const auto inner = ::app_src_json_semantics_::nullableJsonMember(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_));
            return ((!doof::is_null(inner)) && isWasmJsonType(doof::unwrap_optional(inner), analysis));
    }
    else {
            return false;
    }
    }
    doof::unreachable();
    return false;
}
std::string wasmPreamble(std::shared_ptr<::app_src_analyzer_::ModuleInfo> info) {
    return ((((((((((std::string("#include \"") + ::app_src_emitter_names_::moduleHeaderName(info->path)) + std::string("\"\n")) + std::string("#include \"doof_runtime.hpp\"\n#include \"std/json/native_json.hpp\"\n#include <cstring>\n\n")) + std::string("namespace {\n")) + std::string("char* __doof_wasm_return_text(const std::string& text) { auto* out = static_cast<char*>(std::malloc(text.size() + 1)); if (out == nullptr) return nullptr; std::memcpy(out, text.c_str(), text.size() + 1); return out; }\n")) + std::string("doof::JsonValue __doof_wasm_object(std::initializer_list<std::pair<std::string, doof::JsonValue>> values) { return doof::json_value(std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(values)); }\n")) + std::string("char* __doof_wasm_success(const doof::JsonValue& value) { return __doof_wasm_return_text(doof_json::format(__doof_wasm_object({{\"ok\", doof::json_value(true)}, {\"value\", value}}))); }\n")) + std::string("char* __doof_wasm_failure(const doof::JsonValue& error) { return __doof_wasm_return_text(doof_json::format(__doof_wasm_object({{\"ok\", doof::json_value(false)}, {\"error\", error}}))); }\n")) + std::string("char* __doof_wasm_failure_message(int32_t code, const std::string& message) { return __doof_wasm_failure(doof::json_error(code, message)); }\n")) + std::string("}\n\nextern \"C\" void doof_free(char* ptr) { std::free(ptr); }\n\n"));
}
std::string emitWasmWrapper(std::shared_ptr<::app_src_ast_::FunctionDeclaration> fn, std::string exportName, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    auto _binding_value_8 = fn->resolvedType;
    if (doof::is_null(_binding_value_8)) {
        const auto& resolved = _binding_value_8;
        doof::panic(std::string("checked wasm function lost its resolved type"));
    }
    const auto resolved = doof::unwrap_optional(_binding_value_8);
    auto _binding_value_9 = [&]() -> doof::Result<std::shared_ptr<::app_src_semantic_::FunctionType>, std::string> { auto _as_value = resolved; if (doof::variant_is<std::shared_ptr<::app_src_semantic_::FunctionType>>(_as_value)) return doof::Success<std::shared_ptr<::app_src_semantic_::FunctionType>>{doof::variant_narrow<std::shared_ptr<::app_src_semantic_::FunctionType>>(_as_value)}; return doof::Failure<std::string>{"Union narrowing failed"}; }();
    if (doof::is_failure(_binding_value_9)) {
        const auto& type_ = _binding_value_9;
        doof::panic(std::string("checked wasm function lost its function type"));
    }
    const auto type_ = doof::success_value(_binding_value_9);
    auto source = ((std::string("extern \"C\" char* ") + exportName) + std::string("(const char* params_json) {\n    try {\n"));
    (source = (source + std::string("        const bool _lenient = false;\n")));
    (source = (source + std::string("        auto& __domain = doof::detail::ApplicationDomain::shared(); doof::detail::ActiveActorScope __scope(&__domain);\n")));
    (source = (source + std::string("        auto __parsed = doof_json::parse(params_json == nullptr ? std::string(\"{}\") : std::string(params_json));\n")));
    (source = (source + std::string("        if (doof::is_failure(__parsed)) return __doof_wasm_failure_message(400, std::string(\"Invalid JSON params: \" ) + doof::failure_error(__parsed));\n")));
    (source = (source + std::string("        const auto* __params = doof::json_as_object(doof::success_value(__parsed));\n")));
    (source = (source + std::string("        if (__params == nullptr) return __doof_wasm_failure_message(400, \"Invalid JSON params: expected object\");\n")));
    const auto& _iterable_10 = fn->params;
    for (const auto& parameter : *_iterable_10) {
        (source = (source + emitParameter(parameter, context)));
    }
    auto arguments = std::string("");
    const auto& _iterable_11 = fn->params;
    for (const auto& parameter : *_iterable_11) {
        if (arguments != std::string("")) {
            (arguments = (arguments + std::string(", ")));
        }
        (arguments = (arguments + ::app_src_emitter_expr_::cppIdentifier(parameter->name)));
    }
    const auto call = ((((((std::string("::") + ::app_src_emitter_names_::moduleNamespace(context->modulePath)) + std::string("::")) + ::app_src_emitter_expr_::cppIdentifier(fn->name)) + std::string("(")) + arguments) + std::string(")"));
    {
        auto _case_subject = type_->returnType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
            (source = (((source + std::string("        ")) + call) + std::string(";\n        return __doof_wasm_success(doof::json_value(nullptr));\n")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            (source = (((((source + std::string("        auto __result = ")) + call) + std::string(";\n        if (doof::is_failure(__result)) return __doof_wasm_failure(")) + ::app_src_emitter_json_::emitJsonField(std::string("doof::failure_error(__result)"), result->errorType, context)) + std::string(");\n")));
            {
                auto _case_subject = result->valueType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
                    (source = (source + std::string("        return __doof_wasm_success(doof::json_value(nullptr));\n")));
            }
            else {
                    (source = (((source + std::string("        auto __value = doof::success_value(__result);\n        return __doof_wasm_success(")) + ::app_src_emitter_json_::emitJsonField(std::string("__value"), result->valueType, context)) + std::string(");\n")));
            }
            }
    }
    else {
            (source = (((((source + std::string("        auto __value = ")) + call) + std::string(";\n        return __doof_wasm_success(")) + ::app_src_emitter_json_::emitJsonField(std::string("__value"), type_->returnType, context)) + std::string(");\n")));
    }
    }
    return (source + std::string("    } catch (const doof::Panic& error) { return __doof_wasm_failure_message(500, std::string(\"panic: \" ) + error.what()); } catch (const std::exception& error) { return __doof_wasm_failure_message(500, error.what()); }\n}\n\n"));
}
std::string emitParameter(std::shared_ptr<::app_src_ast_::Parameter> parameter, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto type_ = doof::unwrap_optional(parameter->resolvedType);
    const auto name = ::app_src_emitter_expr_::cppIdentifier(parameter->name);
    const auto iterator = (std::string("__it_") + name);
    auto source = ((((std::string("        auto ") + iterator) + std::string(" = __params->find(\"")) + parameter->name) + std::string("\");\n"));
    if (!doof::is_null(parameter->defaultValue)) {
        (source = (((((((((((source + std::string("        ")) + ::app_src_emitter_types_::emitContextType(type_, context)) + std::string(" ")) + name) + std::string(";\n        if (")) + iterator) + std::string(" == __params->end()) { ")) + name) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(parameter->defaultValue), context, doof::optional_value(type_))) + std::string("; } else {\n")));
        (source = (((((((source + std::string("            if (!(")) + ::app_src_emitter_json_::emitJsonTypeCheck((iterator + std::string("->second")), type_)) + std::string(")) return __doof_wasm_failure_message(400, \"Parameter ")) + parameter->name) + std::string(" expected ")) + ::app_src_emitter_json_::jsonTypeName(type_)) + std::string("\");\n")));
        return (((((source + std::string("            ")) + name) + std::string(" = ")) + ::app_src_emitter_json_::emitJsonRead((iterator + std::string("->second")), type_, context)) + std::string(";\n        }\n"));
    }
    (source = (((((source + std::string("        if (")) + iterator) + std::string(" == __params->end()) return __doof_wasm_failure_message(400, \"Missing required parameter \\\"")) + parameter->name) + std::string("\\\"\");\n")));
    (source = (((((((source + std::string("        if (!(")) + ::app_src_emitter_json_::emitJsonTypeCheck((iterator + std::string("->second")), type_)) + std::string(")) return __doof_wasm_failure_message(400, \"Parameter ")) + parameter->name) + std::string(" expected ")) + ::app_src_emitter_json_::jsonTypeName(type_)) + std::string("\");\n")));
    return (((((source + std::string("        auto ")) + name) + std::string(" = ")) + ::app_src_emitter_json_::emitJsonRead((iterator + std::string("->second")), type_, context)) + std::string(";\n"));
}
std::shared_ptr<::app_src_analyzer_::ModuleInfo> findModule(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::string path) {
    const auto& _iterable_12 = result->modules;
    for (const auto& module : *_iterable_12) {
        if (module->path == path) {
            return module;
        }
    }
    return nullptr;
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> allPrograms(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{});
    const auto& _iterable_13 = result->modules;
    for (const auto& module : *_iterable_13) {
        programs->push_back(module->program);
    }
    return programs;
}
std::shared_ptr<::app_src_ast_::ClassDeclaration> findClass(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::shared_ptr<::app_src_semantic_::ClassType> type_) {
    const auto module = findModule(result, type_->symbol->module);
    if (doof::is_null(module)) {
        return nullptr;
    }
    const auto& _iterable_14 = module->program->statements;
    for (const auto& statement : *_iterable_14) {
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
                if (class_->name == type_->name) {
                    return class_;
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
                const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
                {
                    auto _case_subject = export_->declaration;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                        const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
                        if (class_->name == type_->name) {
                            return class_;
                        }
                }
                else {
                }
                }
        }
        else {
        }
        }
    }
    return nullptr;
}
}

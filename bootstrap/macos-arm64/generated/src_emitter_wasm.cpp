#include "src_emitter_wasm.hpp"

namespace app_src_emitter_wasm_ {
using namespace ::app_src_ast_;
using namespace ::app_src_analyzer_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_json_;
using namespace ::app_src_emitter_monomorphize_;
using namespace ::app_src_emitter_names_;
using namespace ::app_src_emitter_module_;
using namespace ::app_src_emitter_types_;
using namespace ::app_src_json_semantics_;
using namespace ::app_src_semantic_;

#line 27 "/src/emitter-wasm.do"
doof::Result<std::shared_ptr<WasmEmission>, std::string> emitWasmSupport(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& entry, const std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan>& instantiations) {
#line 28 "/src/emitter-wasm.do"
    const auto info = findModule(result, entry);
#line 29 "/src/emitter-wasm.do"
    if (doof::is_null(info)) {
#line 29 "/src/emitter-wasm.do"
        return doof::Failure<std::string>{ (std::string("Module not found: ") + entry) };
    }
#line 30 "/src/emitter-wasm.do"
    const auto jsonPlan = [&]() -> std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan> { auto _coalesce_1 = instantiations; if (doof::is_null(_coalesce_1)) return ::app_src_emitter_monomorphize_::buildInstantiationPlan(result); return doof::unwrap_optional(_coalesce_1); }();
#line 31 "/src/emitter-wasm.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>> exports = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>>(std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>{});
#line 32 "/src/emitter-wasm.do"
    collectExportedFunctions(doof::unwrap_optional(info), exports);
#line 33 "/src/emitter-wasm.do"
    std::shared_ptr<std::vector<std::string>> names = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("doof_initialize")});
#line 34 "/src/emitter-wasm.do"
    std::shared_ptr<std::vector<std::string>> functionNames = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 35 "/src/emitter-wasm.do"
    const auto& _iterable_3 = exports;
    for (const auto& fn : *_iterable_3) {
#line 36 "/src/emitter-wasm.do"
        if (fn->name == std::string("main")) {
#line 36 "/src/emitter-wasm.do"
            continue;
        }
#line 37 "/src/emitter-wasm.do"
        auto _try_value_4 = validateWasmFunction(fn, result);
        if (doof::is_failure(_try_value_4)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_4))};
#line 38 "/src/emitter-wasm.do"
        addWasmJsonDemands(fn, result, jsonPlan);
#line 39 "/src/emitter-wasm.do"
        const auto name = (std::string("doof_export_") + ::app_src_emitter_expr_::cppIdentifier(fn->name));
#line 40 "/src/emitter-wasm.do"
        const auto& _iterable_6 = functionNames;
        for (const auto& existing : *_iterable_6) {
#line 41 "/src/emitter-wasm.do"
            if (existing == name) {
#line 42 "/src/emitter-wasm.do"
                return doof::Failure<std::string>{ (((std::string("WebAssembly export name collision for ") + fn->name) + std::string(" at ")) + name) };
            }
        }
#line 45 "/src/emitter-wasm.do"
        functionNames->push_back(name);
    }
#line 48 "/src/emitter-wasm.do"
    const auto programs = allPrograms(result);
#line 49 "/src/emitter-wasm.do"
    const auto context = ::app_src_emitter_context_::createEmitContextForModule(info->program, entry, programs);
#line 50 "/src/emitter-wasm.do"
    (context->imports = info->imports);
#line 51 "/src/emitter-wasm.do"
    (context->namespaceImports = info->namespaceImports);
#line 52 "/src/emitter-wasm.do"
    auto source = wasmPreamble(doof::unwrap_optional(info), result, entry);
#line 53 "/src/emitter-wasm.do"
    auto exportIndex = 0;
#line 54 "/src/emitter-wasm.do"
    const auto& _iterable_8 = exports;
    for (const auto& fn : *_iterable_8) {
#line 55 "/src/emitter-wasm.do"
        if (fn->name == std::string("main")) {
#line 55 "/src/emitter-wasm.do"
            continue;
        }
#line 56 "/src/emitter-wasm.do"
        (source = (source + emitWasmWrapper(fn, doof::array_at(functionNames, exportIndex, "src/emitter-wasm", 56), context)));
#line 57 "/src/emitter-wasm.do"
        (exportIndex += 1);
    }
#line 59 "/src/emitter-wasm.do"
    const auto& _iterable_10 = functionNames;
    for (const auto& name : *_iterable_10) {
#line 59 "/src/emitter-wasm.do"
        names->push_back(name);
    }
#line 60 "/src/emitter-wasm.do"
    return doof::Success<std::shared_ptr<WasmEmission>>{ std::make_shared<WasmEmission>(source, names) };
}
#line 63 "/src/emitter-wasm.do"
void addWasmJsonDemands(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, const std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan>& plan) {
#line 64 "/src/emitter-wasm.do"
    const auto& _iterable_12 = fn->params;
    for (const auto& parameter : *_iterable_12) {
#line 65 "/src/emitter-wasm.do"
        if (!doof::is_null(parameter->resolvedType)) {
#line 65 "/src/emitter-wasm.do"
            ::app_src_emitter_monomorphize_::addJsonDeserializationDemand(plan, doof::unwrap_optional(parameter->resolvedType), analysis);
        }
    }
#line 67 "/src/emitter-wasm.do"
    if (doof::is_null(fn->resolvedType)) {
#line 67 "/src/emitter-wasm.do"
        return;
    }
#line 68 "/src/emitter-wasm.do"
    {
        auto _case_subject = doof::unwrap_optional(fn->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 70 "/src/emitter-wasm.do"
            {
                auto _case_subject = function_->returnType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                    const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 72 "/src/emitter-wasm.do"
                    ::app_src_emitter_monomorphize_::addJsonSerializationDemand(plan, result->valueType, analysis);
#line 73 "/src/emitter-wasm.do"
                    ::app_src_emitter_monomorphize_::addJsonSerializationDemand(plan, result->errorType, analysis);
            }
            else {
#line 75 "/src/emitter-wasm.do"
                    ::app_src_emitter_monomorphize_::addJsonSerializationDemand(plan, function_->returnType, analysis);
            }
            }
    }
    else {
    }
    }
}
#line 82 "/src/emitter-wasm.do"
void collectExportedFunctions(const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>>& result) {
#line 83 "/src/emitter-wasm.do"
    const auto& _iterable_14 = info->program->statements;
    for (const auto& statement : *_iterable_14) {
#line 84 "/src/emitter-wasm.do"
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
                const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
#line 85 "/src/emitter-wasm.do"
                if (fn->exported || moduleExportsFunction(info, fn->name)) {
#line 85 "/src/emitter-wasm.do"
                    result->push_back(fn);
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
                const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 87 "/src/emitter-wasm.do"
                {
                    auto _case_subject = export_->declaration;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
                        const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
#line 88 "/src/emitter-wasm.do"
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
#line 97 "/src/emitter-wasm.do"
bool moduleExportsFunction(const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::string& name) {
#line 98 "/src/emitter-wasm.do"
    const auto& _iterable_16 = info->exports;
    for (const auto& symbol : *_iterable_16) {
#line 99 "/src/emitter-wasm.do"
        const auto sourceName = ((symbol->originalName == std::string("")) ? symbol->name : symbol->originalName);
#line 100 "/src/emitter-wasm.do"
        if (((symbol->kind == std::string("function")) && (symbol->module == info->path)) && (sourceName == name)) {
#line 100 "/src/emitter-wasm.do"
            return true;
        }
    }
#line 102 "/src/emitter-wasm.do"
    return false;
}
#line 105 "/src/emitter-wasm.do"
doof::Result<void, std::string> validateWasmFunction(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis) {
#line 106 "/src/emitter-wasm.do"
    if (static_cast<int32_t>((fn->typeParams)->size()) > 0) {
#line 106 "/src/emitter-wasm.do"
        return doof::Failure<std::string>{ ((std::string("WebAssembly export \"") + fn->name) + std::string("\" cannot be generic")) };
    }
#line 107 "/src/emitter-wasm.do"
    auto _binding_value_17 = fn->resolvedType;
    if (doof::is_null(_binding_value_17)) {
        const auto& resolved = _binding_value_17;
#line 108 "/src/emitter-wasm.do"
        return doof::Failure<std::string>{ ((std::string("WebAssembly export \"") + fn->name) + std::string("\" is missing a resolved function type")) };
    }
    const auto resolved = doof::unwrap_optional(_binding_value_17);
#line 110 "/src/emitter-wasm.do"
    {
        auto _case_subject = resolved;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& type_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 112 "/src/emitter-wasm.do"
            const auto& _iterable_19 = fn->params;
            for (const auto& parameter : *_iterable_19) {
#line 113 "/src/emitter-wasm.do"
                if (doof::is_null(parameter->resolvedType) || !isWasmJsonType(doof::unwrap_optional(parameter->resolvedType), analysis)) {
#line 114 "/src/emitter-wasm.do"
                    return doof::Failure<std::string>{ ((((std::string("Parameter \"") + parameter->name) + std::string("\" of WebAssembly export \"")) + fn->name) + std::string("\" must be supported by the JSON ABI")) };
                }
            }
#line 117 "/src/emitter-wasm.do"
            {
                auto _case_subject = type_->returnType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
#line 118 "/src/emitter-wasm.do"
                    return doof::Success<void>{};
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                    const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 120 "/src/emitter-wasm.do"
                    {
                        auto _case_subject = result->valueType;
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
                    }
                    else {
#line 122 "/src/emitter-wasm.do"
                            if (!isWasmJsonType(result->valueType, analysis)) {
#line 122 "/src/emitter-wasm.do"
                                return doof::Failure<std::string>{ ((std::string("Success type of WebAssembly export \"") + fn->name) + std::string("\" must be supported by the JSON ABI")) };
                            }
                    }
                    }
#line 124 "/src/emitter-wasm.do"
                    if (!isWasmJsonType(result->errorType, analysis)) {
#line 124 "/src/emitter-wasm.do"
                        return doof::Failure<std::string>{ ((std::string("Error type of WebAssembly export \"") + fn->name) + std::string("\" must be supported by the JSON ABI")) };
                    }
#line 125 "/src/emitter-wasm.do"
                    return doof::Success<void>{};
            }
            else {
#line 128 "/src/emitter-wasm.do"
                    if (!isWasmJsonType(type_->returnType, analysis)) {
#line 128 "/src/emitter-wasm.do"
                        return doof::Failure<std::string>{ ((std::string("Return type of WebAssembly export \"") + fn->name) + std::string("\" must be supported by the JSON ABI")) };
                    }
#line 129 "/src/emitter-wasm.do"
                    return doof::Success<void>{};
            }
            }
            doof::unreachable();
    }
    else {
#line 133 "/src/emitter-wasm.do"
            return doof::Failure<std::string>{ ((std::string("WebAssembly export \"") + fn->name) + std::string("\" is missing a resolved function type")) };
    }
    }
    doof::unreachable();
#line 135 "/src/emitter-wasm.do"
    return doof::Success<void>{};
}
#line 138 "/src/emitter-wasm.do"
bool isWasmJsonType(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis) {
#line 139 "/src/emitter-wasm.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
#line 140 "/src/emitter-wasm.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 141 "/src/emitter-wasm.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
#line 142 "/src/emitter-wasm.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
#line 143 "/src/emitter-wasm.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 145 "/src/emitter-wasm.do"
            const auto declaration = findClass(analysis, class_);
#line 146 "/src/emitter-wasm.do"
            return (((!doof::is_null(declaration)) && ::app_src_json_semantics_::canGenerateJsonSerialization(doof::unwrap_optional(declaration), allPrograms(analysis), nullptr)) && ::app_src_json_semantics_::canGenerateJsonDeserialization(doof::unwrap_optional(declaration), allPrograms(analysis), nullptr));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 148 "/src/emitter-wasm.do"
            return isWasmJsonType(array->elementType, analysis);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 150 "/src/emitter-wasm.do"
            const auto inner = ::app_src_json_semantics_::nullableJsonMember(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_));
#line 151 "/src/emitter-wasm.do"
            return ((!doof::is_null(inner)) && isWasmJsonType(doof::unwrap_optional(inner), analysis));
    }
    else {
#line 153 "/src/emitter-wasm.do"
            return false;
    }
    }
    doof::unreachable();
#line 155 "/src/emitter-wasm.do"
    return false;
}
#line 158 "/src/emitter-wasm.do"
std::string wasmPreamble(const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& entry) {
#line 159 "/src/emitter-wasm.do"
    auto declarations = std::string("");
#line 160 "/src/emitter-wasm.do"
    auto calls = std::string("");
#line 161 "/src/emitter-wasm.do"
    const auto& _iterable_21 = ::app_src_emitter_module_::planModuleInitializationOrder(result, entry, std::string("wasm"));
    for (const auto& path : *_iterable_21) {
#line 162 "/src/emitter-wasm.do"
        const auto namespace_ = ::app_src_emitter_names_::moduleNamespace(path);
#line 163 "/src/emitter-wasm.do"
        (declarations = (((declarations + std::string("namespace ")) + namespace_) + std::string(" { void __doof_initialize_module(); }\n")));
#line 164 "/src/emitter-wasm.do"
        (calls = (((calls + std::string("        ::")) + namespace_) + std::string("::__doof_initialize_module();\n")));
    }
#line 166 "/src/emitter-wasm.do"
    return ((((((((((((((((((((((((((std::string("#include \"") + ::app_src_emitter_names_::moduleHeaderName(info->path)) + std::string("\"\n")) + std::string("#include \"doof_runtime.hpp\"\n#include \"std/json/native_json.hpp\"\n#include <cstring>\n\n")) + declarations) + std::string("\n")) + std::string("namespace {\n")) + std::string("int __doof_wasm_initialization_state = 0;\n")) + std::string("char* __doof_wasm_return_text(const std::string& text) { auto* out = static_cast<char*>(std::malloc(text.size() + 1)); if (out == nullptr) return nullptr; std::memcpy(out, text.c_str(), text.size() + 1); return out; }\n")) + std::string("doof::JsonValue __doof_wasm_object(std::initializer_list<std::pair<std::string, doof::JsonValue>> values) { return doof::json_value(std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(values)); }\n")) + std::string("char* __doof_wasm_success(const doof::JsonValue& value) { return __doof_wasm_return_text(doof_json::format(__doof_wasm_object({{\"ok\", doof::json_value(true)}, {\"value\", value}}))); }\n")) + std::string("char* __doof_wasm_failure(const doof::JsonValue& error) { return __doof_wasm_return_text(doof_json::format(__doof_wasm_object({{\"ok\", doof::json_value(false)}, {\"error\", error}}))); }\n")) + std::string("char* __doof_wasm_failure_message(int32_t code, const std::string& message) { return __doof_wasm_failure(doof::json_error(code, message)); }\n")) + std::string("}\n\nextern \"C\" void doof_free(char* ptr) { std::free(ptr); }\n\n")) + std::string("extern \"C\" char* doof_initialize() {\n")) + std::string("    try {\n")) + std::string("        if (__doof_wasm_initialization_state == 2) return __doof_wasm_success(doof::json_value(nullptr));\n")) + std::string("        if (__doof_wasm_initialization_state == 1) return __doof_wasm_failure_message(500, \"Doof module initialization is already in progress\");\n")) + std::string("        if (__doof_wasm_initialization_state == 3) return __doof_wasm_failure_message(500, \"Doof module initialization previously failed\");\n")) + std::string("        __doof_wasm_initialization_state = 1;\n")) + std::string("        auto& __domain = doof::detail::ApplicationDomain::shared(); doof::detail::ActiveActorScope __scope(&__domain);\n")) + calls) + std::string("        __doof_wasm_initialization_state = 2;\n")) + std::string("        return __doof_wasm_success(doof::json_value(nullptr));\n")) + std::string("    } catch (const doof::Panic& error) { __doof_wasm_initialization_state = 3; return __doof_wasm_failure_message(500, std::string(\"panic: \") + error.what()); }\n")) + std::string("      catch (const std::exception& error) { __doof_wasm_initialization_state = 3; return __doof_wasm_failure_message(500, error.what()); }\n")) + std::string("}\n\n"));
}
#line 192 "/src/emitter-wasm.do"
std::string emitWasmWrapper(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::string& exportName, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 193 "/src/emitter-wasm.do"
    auto _binding_value_22 = fn->resolvedType;
    if (doof::is_null(_binding_value_22)) {
        const auto& resolved = _binding_value_22;
#line 193 "/src/emitter-wasm.do"
        doof::panic(std::string("checked wasm function lost its resolved type"));
    }
    const auto resolved = doof::unwrap_optional(_binding_value_22);
#line 194 "/src/emitter-wasm.do"
    auto _binding_value_23 = [&]() -> doof::Result<std::shared_ptr<::app_src_semantic_::FunctionType>, std::string> { auto _as_value = resolved; if (doof::variant_is<std::shared_ptr<::app_src_semantic_::FunctionType>>(_as_value)) return doof::Success<std::shared_ptr<::app_src_semantic_::FunctionType>>{doof::variant_narrow<std::shared_ptr<::app_src_semantic_::FunctionType>>(_as_value)}; return doof::Failure<std::string>{"Union narrowing failed"}; }();
    if (doof::is_failure(_binding_value_23)) {
        const auto& type_ = _binding_value_23;
#line 194 "/src/emitter-wasm.do"
        doof::panic(std::string("checked wasm function lost its function type"));
    }
    const auto type_ = doof::success_value(_binding_value_23);
#line 195 "/src/emitter-wasm.do"
    auto source = ((std::string("extern \"C\" char* ") + exportName) + std::string("(const char* params_json) {\n    try {\n"));
#line 196 "/src/emitter-wasm.do"
    (source = (source + std::string("        if (__doof_wasm_initialization_state == 3) return __doof_wasm_failure_message(500, \"Doof module initialization previously failed\");\n")));
#line 197 "/src/emitter-wasm.do"
    (source = (source + std::string("        if (__doof_wasm_initialization_state != 2) return __doof_wasm_failure_message(503, \"Call doof_initialize before invoking Doof exports\");\n")));
#line 198 "/src/emitter-wasm.do"
    (source = (source + std::string("        const bool _lenient = false;\n")));
#line 199 "/src/emitter-wasm.do"
    (source = (source + std::string("        auto& __domain = doof::detail::ApplicationDomain::shared(); doof::detail::ActiveActorScope __scope(&__domain);\n")));
#line 200 "/src/emitter-wasm.do"
    (source = (source + std::string("        auto __parsed = doof_json::parse(params_json == nullptr \? std::string(\"{}\") : std::string(params_json));\n")));
#line 201 "/src/emitter-wasm.do"
    (source = (source + std::string("        if (doof::is_failure(__parsed)) return __doof_wasm_failure_message(400, std::string(\"Invalid JSON params: \" ) + doof::failure_error(__parsed));\n")));
#line 202 "/src/emitter-wasm.do"
    (source = (source + std::string("        const auto* __params = doof::json_as_object(doof::success_value(__parsed));\n")));
#line 203 "/src/emitter-wasm.do"
    (source = (source + std::string("        if (__params == nullptr) return __doof_wasm_failure_message(400, \"Invalid JSON params: expected object\");\n")));
#line 204 "/src/emitter-wasm.do"
    const auto& _iterable_25 = fn->params;
    for (const auto& parameter : *_iterable_25) {
#line 204 "/src/emitter-wasm.do"
        (source = (source + emitParameter(parameter, context)));
    }
#line 205 "/src/emitter-wasm.do"
    auto arguments = std::string("");
#line 206 "/src/emitter-wasm.do"
    const auto& _iterable_27 = fn->params;
    for (const auto& parameter : *_iterable_27) {
#line 207 "/src/emitter-wasm.do"
        if (arguments != std::string("")) {
#line 207 "/src/emitter-wasm.do"
            (arguments = (arguments + std::string(", ")));
        }
#line 208 "/src/emitter-wasm.do"
        (arguments = (arguments + ::app_src_emitter_expr_::cppIdentifier(parameter->name)));
    }
#line 210 "/src/emitter-wasm.do"
    const auto call = ((((((std::string("::") + ::app_src_emitter_names_::moduleNamespace(context->modulePath)) + std::string("::")) + ::app_src_emitter_expr_::cppIdentifier(fn->name)) + std::string("(")) + arguments) + std::string(")"));
#line 211 "/src/emitter-wasm.do"
    {
        auto _case_subject = type_->returnType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
#line 212 "/src/emitter-wasm.do"
            (source = (((source + std::string("        ")) + call) + std::string(";\n        return __doof_wasm_success(doof::json_value(nullptr));\n")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 214 "/src/emitter-wasm.do"
            (source = (((((source + std::string("        auto __result = ")) + call) + std::string(";\n        if (doof::is_failure(__result)) return __doof_wasm_failure(")) + ::app_src_emitter_json_::emitJsonField(std::string("doof::failure_error(__result)"), result->errorType, context)) + std::string(");\n")));
#line 215 "/src/emitter-wasm.do"
            {
                auto _case_subject = result->valueType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
#line 216 "/src/emitter-wasm.do"
                    (source = (source + std::string("        return __doof_wasm_success(doof::json_value(nullptr));\n")));
            }
            else {
#line 217 "/src/emitter-wasm.do"
                    (source = (((source + std::string("        auto __value = doof::success_value(__result);\n        return __doof_wasm_success(")) + ::app_src_emitter_json_::emitJsonField(std::string("__value"), result->valueType, context)) + std::string(");\n")));
            }
            }
    }
    else {
#line 220 "/src/emitter-wasm.do"
            (source = (((((source + std::string("        auto __value = ")) + call) + std::string(";\n        return __doof_wasm_success(")) + ::app_src_emitter_json_::emitJsonField(std::string("__value"), type_->returnType, context)) + std::string(");\n")));
    }
    }
#line 222 "/src/emitter-wasm.do"
    return (source + std::string("    } catch (const doof::Panic& error) { return __doof_wasm_failure_message(500, std::string(\"panic: \" ) + error.what()); } catch (const std::exception& error) { return __doof_wasm_failure_message(500, error.what()); }\n}\n\n"));
}
#line 225 "/src/emitter-wasm.do"
std::string emitParameter(const std::shared_ptr<::app_src_ast_::Parameter>& parameter, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 226 "/src/emitter-wasm.do"
    const auto type_ = doof::unwrap_optional(parameter->resolvedType);
#line 227 "/src/emitter-wasm.do"
    const auto name = ::app_src_emitter_expr_::cppIdentifier(parameter->name);
#line 228 "/src/emitter-wasm.do"
    const auto iterator = (std::string("__it_") + name);
#line 229 "/src/emitter-wasm.do"
    auto source = ((((std::string("        auto ") + iterator) + std::string(" = __params->find(\"")) + parameter->name) + std::string("\");\n"));
#line 230 "/src/emitter-wasm.do"
    if (!doof::is_null(parameter->defaultValue)) {
#line 231 "/src/emitter-wasm.do"
        (source = (((((((((((source + std::string("        ")) + ::app_src_emitter_types_::emitContextType(type_, context)) + std::string(" ")) + name) + std::string(";\n        if (")) + iterator) + std::string(" == __params->end()) { ")) + name) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(parameter->defaultValue), context, doof::optional_value(type_))) + std::string("; } else {\n")));
#line 232 "/src/emitter-wasm.do"
        (source = (((((((source + std::string("            if (!(")) + ::app_src_emitter_json_::emitJsonTypeCheck((iterator + std::string("->second")), type_)) + std::string(")) return __doof_wasm_failure_message(400, \"Parameter ")) + parameter->name) + std::string(" expected ")) + ::app_src_emitter_json_::jsonTypeName(type_)) + std::string("\");\n")));
#line 233 "/src/emitter-wasm.do"
        return (((((source + std::string("            ")) + name) + std::string(" = ")) + ::app_src_emitter_json_::emitJsonRead((iterator + std::string("->second")), type_, context)) + std::string(";\n        }\n"));
    }
#line 235 "/src/emitter-wasm.do"
    (source = (((((source + std::string("        if (")) + iterator) + std::string(" == __params->end()) return __doof_wasm_failure_message(400, \"Missing required parameter \\\"")) + parameter->name) + std::string("\\\"\");\n")));
#line 236 "/src/emitter-wasm.do"
    (source = (((((((source + std::string("        if (!(")) + ::app_src_emitter_json_::emitJsonTypeCheck((iterator + std::string("->second")), type_)) + std::string(")) return __doof_wasm_failure_message(400, \"Parameter ")) + parameter->name) + std::string(" expected ")) + ::app_src_emitter_json_::jsonTypeName(type_)) + std::string("\");\n")));
#line 237 "/src/emitter-wasm.do"
    return (((((source + std::string("        auto ")) + name) + std::string(" = ")) + ::app_src_emitter_json_::emitJsonRead((iterator + std::string("->second")), type_, context)) + std::string(";\n"));
}
#line 240 "/src/emitter-wasm.do"
std::shared_ptr<::app_src_analyzer_::ModuleInfo> findModule(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& path) {
#line 241 "/src/emitter-wasm.do"
    const auto& _iterable_29 = result->modules;
    for (const auto& module : *_iterable_29) {
#line 241 "/src/emitter-wasm.do"
        if (module->path == path) {
#line 241 "/src/emitter-wasm.do"
            return module;
        }
    }
#line 242 "/src/emitter-wasm.do"
    return nullptr;
}
#line 245 "/src/emitter-wasm.do"
std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> allPrograms(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
#line 246 "/src/emitter-wasm.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{});
#line 247 "/src/emitter-wasm.do"
    const auto& _iterable_31 = result->modules;
    for (const auto& module : *_iterable_31) {
#line 247 "/src/emitter-wasm.do"
        programs->push_back(module->program);
    }
#line 248 "/src/emitter-wasm.do"
    return programs;
}
#line 251 "/src/emitter-wasm.do"
std::shared_ptr<::app_src_ast_::ClassDeclaration> findClass(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<::app_src_semantic_::ClassType>& type_) {
#line 252 "/src/emitter-wasm.do"
    const auto module = findModule(result, type_->symbol->module);
#line 253 "/src/emitter-wasm.do"
    if (doof::is_null(module)) {
#line 253 "/src/emitter-wasm.do"
        return nullptr;
    }
#line 254 "/src/emitter-wasm.do"
    const auto& _iterable_33 = module->program->statements;
    for (const auto& statement : *_iterable_33) {
#line 255 "/src/emitter-wasm.do"
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 256 "/src/emitter-wasm.do"
                if (class_->name == type_->name) {
#line 256 "/src/emitter-wasm.do"
                    return class_;
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
                const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 258 "/src/emitter-wasm.do"
                {
                    auto _case_subject = export_->declaration;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                        const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 259 "/src/emitter-wasm.do"
                        if (class_->name == type_->name) {
#line 259 "/src/emitter-wasm.do"
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
#line 266 "/src/emitter-wasm.do"
    return nullptr;
}
#line 1 "<doof-generated>"
}

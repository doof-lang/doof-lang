#include "src_parser_types.hpp"

namespace app_src_parser_types_ {
using namespace ::app_src_parser_;
using namespace ::app_src_lexer_;
using namespace ::app_src_ast_;
#line 8 "/src/parser-types.do"
std::variant<std::monostate, std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> parseOptionalType(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 9 "/src/parser-types.do"
    if (!parser->match(::app_src_lexer_::TokenType::Colon)) {
#line 9 "/src/parser-types.do"
        return std::monostate{};
    }
#line 10 "/src/parser-types.do"
    return doof::optional_value(parseTypeAnnotation(parser));
}
#line 13 "/src/parser-types.do"
std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> parseTypeAnnotation(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 14 "/src/parser-types.do"
    const auto first = parseTypeMember(parser);
#line 15 "/src/parser-types.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>> types = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>{first});
#line 16 "/src/parser-types.do"
    while (parser->match(::app_src_lexer_::TokenType::Pipe)) {
#line 16 "/src/parser-types.do"
        types->push_back(parseTypeMember(parser));
    }
#line 17 "/src/parser-types.do"
    std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> result = first;
#line 18 "/src/parser-types.do"
    if (static_cast<int32_t>((types)->size()) > 1) {
#line 18 "/src/parser-types.do"
        (result = doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>(std::make_shared<::app_src_ast_::UnionType>(std::string("union-type"), types, std::monostate{}, ::app_src_ast_::SourceSpan{std::visit([](auto&& _obj) { return _obj->span; }, first).start, std::visit([](auto&& _obj) { return _obj->span; }, doof::array_at(types, (static_cast<int32_t>((types)->size()) - 1), "src/parser-types", 18)).end})));
    }
#line 19 "/src/parser-types.do"
    return result;
}
#line 22 "/src/parser-types.do"
std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> parseTypeMember(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 23 "/src/parser-types.do"
    auto start = parser->location();
#line 24 "/src/parser-types.do"
    if (parser->match(::app_src_lexer_::TokenType::Weak)) {
#line 25 "/src/parser-types.do"
        const auto inner = parseTypeAnnotation(parser);
#line 26 "/src/parser-types.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>(std::make_shared<::app_src_ast_::WeakType>(std::string("weak-type"), inner, std::monostate{}, ::app_src_ast_::SourceSpan{start, std::visit([](auto&& _obj) { return _obj->span; }, inner).end}));
    }
#line 28 "/src/parser-types.do"
    auto readonlyPrefix = parser->match(::app_src_lexer_::TokenType::Readonly);
#line 29 "/src/parser-types.do"
    auto result = parsePrimaryType(parser);
#line 30 "/src/parser-types.do"
    while (parser->check(::app_src_lexer_::TokenType::LeftBracket) && (parser->peek(1).kind == ::app_src_lexer_::TokenType::RightBracket)) {
#line 31 "/src/parser-types.do"
        auto start = std::visit([](auto&& _obj) { return _obj->span; }, result).start;
#line 32 "/src/parser-types.do"
        parser->advance();
#line 33 "/src/parser-types.do"
        parser->advance();
#line 34 "/src/parser-types.do"
        (result = doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>(std::make_shared<::app_src_ast_::ArrayType>(std::string("array-type"), result, readonlyPrefix, std::monostate{}, ::app_src_ast_::SourceSpan{start, parser->location()})));
#line 35 "/src/parser-types.do"
        (readonlyPrefix = false);
    }
#line 37 "/src/parser-types.do"
    if (readonlyPrefix) {
#line 38 "/src/parser-types.do"
        {
            auto _case_subject = result;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 40 "/src/parser-types.do"
                if ((named->name == std::string("Array")) || (named->name == std::string("ReadonlyArray"))) {
#line 41 "/src/parser-types.do"
                    (named->name = std::string("ReadonlyArray"));
#line 42 "/src/parser-types.do"
                    (readonlyPrefix = false);
                } else if ((named->name == std::string("Map")) || (named->name == std::string("ReadonlyMap"))) {
#line 44 "/src/parser-types.do"
                    (named->name = std::string("ReadonlyMap"));
#line 45 "/src/parser-types.do"
                    (readonlyPrefix = false);
                } else if ((named->name == std::string("Set")) || (named->name == std::string("ReadonlySet"))) {
#line 47 "/src/parser-types.do"
                    (named->name = std::string("ReadonlySet"));
#line 48 "/src/parser-types.do"
                    (readonlyPrefix = false);
                }
        }
        else {
        }
        }
    }
#line 54 "/src/parser-types.do"
    if (readonlyPrefix) {
#line 54 "/src/parser-types.do"
        parser->fail(std::string("Unexpected readonly type modifier; expected an array, Array<T>, Map<K, V>, or Set<T> type"));
    }
#line 55 "/src/parser-types.do"
    return result;
}
#line 58 "/src/parser-types.do"
std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> parsePrimaryType(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 59 "/src/parser-types.do"
    auto start = parser->location();
#line 60 "/src/parser-types.do"
    if (parser->check(::app_src_lexer_::TokenType::LeftParen)) {
#line 61 "/src/parser-types.do"
        if ((parser->peek(1).kind != ::app_src_lexer_::TokenType::RightParen) && !((parser->peek(1).kind == ::app_src_lexer_::TokenType::Identifier) && (parser->peek(2).kind == ::app_src_lexer_::TokenType::Colon))) {
#line 62 "/src/parser-types.do"
            parser->advance();
#line 63 "/src/parser-types.do"
            const auto inner = parseTypeAnnotation(parser);
#line 64 "/src/parser-types.do"
            parser->expect(::app_src_lexer_::TokenType::RightParen, std::string(""));
#line 65 "/src/parser-types.do"
            return inner;
        }
#line 67 "/src/parser-types.do"
        parser->advance();
#line 68 "/src/parser-types.do"
        std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::FunctionTypeParam>>> params = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::FunctionTypeParam>>>(std::vector<std::shared_ptr<::app_src_ast_::FunctionTypeParam>>{});
#line 69 "/src/parser-types.do"
        while (!parser->check(::app_src_lexer_::TokenType::RightParen) && !parser->atEnd()) {
#line 70 "/src/parser-types.do"
            auto paramStart = parser->location();
#line 71 "/src/parser-types.do"
            const auto paramName = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")));
#line 72 "/src/parser-types.do"
            parser->expect(::app_src_lexer_::TokenType::Colon, std::string(""));
#line 73 "/src/parser-types.do"
            const auto paramType = parseTypeAnnotation(parser);
#line 74 "/src/parser-types.do"
            params->push_back(std::make_shared<::app_src_ast_::FunctionTypeParam>(paramName, paramType, parser->span(paramStart)));
#line 75 "/src/parser-types.do"
            if (!parser->match(::app_src_lexer_::TokenType::Comma)) {
#line 75 "/src/parser-types.do"
                break;
            }
        }
#line 77 "/src/parser-types.do"
        parser->expect(::app_src_lexer_::TokenType::RightParen, std::string(""));
#line 78 "/src/parser-types.do"
        parser->expect(::app_src_lexer_::TokenType::Colon, std::string(""));
#line 79 "/src/parser-types.do"
        const auto returnType = parseTypeAnnotation(parser);
#line 80 "/src/parser-types.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>(std::make_shared<::app_src_ast_::AstFunctionType>(std::string("function-type"), params, returnType, std::monostate{}, parser->span(start)));
    }
#line 82 "/src/parser-types.do"
    auto nameToken = parser->advance();
#line 83 "/src/parser-types.do"
    if ((((nameToken.kind != ::app_src_lexer_::TokenType::Identifier) && (nameToken.kind != ::app_src_lexer_::TokenType::None)) && (nameToken.kind != ::app_src_lexer_::TokenType::Void)) && (nameToken.kind != ::app_src_lexer_::TokenType::Null)) {
#line 84 "/src/parser-types.do"
        parser->fail(std::string("Expected a type name"));
    }
#line 86 "/src/parser-types.do"
    const auto name = parser->text(nameToken);
#line 87 "/src/parser-types.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>> typeArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>{});
#line 88 "/src/parser-types.do"
    if (parser->match(::app_src_lexer_::TokenType::Less)) {
#line 89 "/src/parser-types.do"
        while (!parser->check(::app_src_lexer_::TokenType::Greater) && !parser->atEnd()) {
#line 90 "/src/parser-types.do"
            typeArgs->push_back(parseTypeAnnotation(parser));
#line 91 "/src/parser-types.do"
            if (!parser->match(::app_src_lexer_::TokenType::Comma)) {
#line 91 "/src/parser-types.do"
                break;
            }
        }
#line 93 "/src/parser-types.do"
        parser->expect(::app_src_lexer_::TokenType::Greater, std::string(""));
    }
#line 95 "/src/parser-types.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>(std::make_shared<::app_src_ast_::NamedType>(std::string("named-type"), name, typeArgs, nullptr, std::monostate{}, parser->span(start)));
}
#line 1 "<doof-generated>"
}

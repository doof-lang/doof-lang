#include "src_parser_types.hpp"
#include <cmath>
#include "src_parser.hpp"
#include "src_lexer.hpp"
#include "src_ast.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_parser_types_ {
using namespace ::app_src_parser_;
using namespace ::app_src_lexer_;
using namespace ::app_src_ast_;
std::variant<std::monostate, std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> parseOptionalType(std::shared_ptr<::app_src_parser_::Parser> parser) {
    if (!parser->match(::app_src_lexer_::TokenType::Colon)) {
        return std::monostate{};
    }
    return doof::optional_value(parseTypeAnnotation(parser));
}
std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> parseTypeAnnotation(std::shared_ptr<::app_src_parser_::Parser> parser) {
    const auto first = parseTypeMember(parser);
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>> types = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>{first});
    while (parser->match(::app_src_lexer_::TokenType::Pipe)) {
        types->push_back(parseTypeMember(parser));
    }
    std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> result = first;
    if (static_cast<int32_t>((types)->size()) > 1) {
        (result = doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>(std::make_shared<::app_src_ast_::UnionType>(std::string("union-type"), types, std::monostate{}, ::app_src_ast_::SourceSpan{doof::span(first).start, doof::span((*types)[(static_cast<int32_t>((types)->size()) - 1)]).end})));
    }
    return result;
}
std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> parseTypeMember(std::shared_ptr<::app_src_parser_::Parser> parser) {
    auto start = parser->location();
    if (parser->match(::app_src_lexer_::TokenType::Weak)) {
        const auto inner = parseTypeAnnotation(parser);
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>(std::make_shared<::app_src_ast_::WeakType>(std::string("weak-type"), inner, std::monostate{}, ::app_src_ast_::SourceSpan{start, doof::span(inner).end}));
    }
    auto readonlyPrefix = parser->match(::app_src_lexer_::TokenType::Readonly);
    auto result = parsePrimaryType(parser);
    while (parser->check(::app_src_lexer_::TokenType::LeftBracket) && (parser->peek(1).kind == ::app_src_lexer_::TokenType::RightBracket)) {
        auto start = doof::span(result).start;
        parser->advance();
        parser->advance();
        (result = doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>(std::make_shared<::app_src_ast_::ArrayType>(std::string("array-type"), result, readonlyPrefix, std::monostate{}, ::app_src_ast_::SourceSpan{start, parser->location()})));
        (readonlyPrefix = false);
    }
    if (readonlyPrefix) {
        {
            auto _case_subject = result;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
                if ((named->name == std::string("Array")) || (named->name == std::string("ReadonlyArray"))) {
                    (named->name = std::string("ReadonlyArray"));
                    (readonlyPrefix = false);
                } else if ((named->name == std::string("Map")) || (named->name == std::string("ReadonlyMap"))) {
                    (named->name = std::string("ReadonlyMap"));
                    (readonlyPrefix = false);
                } else if ((named->name == std::string("Set")) || (named->name == std::string("ReadonlySet"))) {
                    (named->name = std::string("ReadonlySet"));
                    (readonlyPrefix = false);
                }
        }
        else {
        }
        }
    }
    if (readonlyPrefix) {
        parser->fail(std::string("Unexpected readonly type modifier; expected an array, Array<T>, Map<K, V>, or Set<T> type"));
    }
    return result;
}
std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> parsePrimaryType(std::shared_ptr<::app_src_parser_::Parser> parser) {
    auto start = parser->location();
    if (parser->check(::app_src_lexer_::TokenType::LeftParen)) {
        if ((parser->peek(1).kind != ::app_src_lexer_::TokenType::RightParen) && !((parser->peek(1).kind == ::app_src_lexer_::TokenType::Identifier) && (parser->peek(2).kind == ::app_src_lexer_::TokenType::Colon))) {
            parser->advance();
            const auto inner = parseTypeAnnotation(parser);
            parser->expect(::app_src_lexer_::TokenType::RightParen, std::string(""));
            return inner;
        }
        parser->advance();
        std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::FunctionTypeParam>>> params = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::FunctionTypeParam>>>(std::vector<std::shared_ptr<::app_src_ast_::FunctionTypeParam>>{});
        while (!parser->check(::app_src_lexer_::TokenType::RightParen) && !parser->atEnd()) {
            auto paramStart = parser->location();
            const auto paramName = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")));
            parser->expect(::app_src_lexer_::TokenType::Colon, std::string(""));
            const auto paramType = parseTypeAnnotation(parser);
            params->push_back(std::make_shared<::app_src_ast_::FunctionTypeParam>(paramName, paramType, parser->span(paramStart)));
            if (!parser->match(::app_src_lexer_::TokenType::Comma)) {
                break;
            }
        }
        parser->expect(::app_src_lexer_::TokenType::RightParen, std::string(""));
        parser->expect(::app_src_lexer_::TokenType::Colon, std::string(""));
        const auto returnType = parseTypeAnnotation(parser);
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>(std::make_shared<::app_src_ast_::AstFunctionType>(std::string("function-type"), params, returnType, std::monostate{}, parser->span(start)));
    }
    auto nameToken = parser->advance();
    if ((((nameToken.kind != ::app_src_lexer_::TokenType::Identifier) && (nameToken.kind != ::app_src_lexer_::TokenType::None)) && (nameToken.kind != ::app_src_lexer_::TokenType::Void)) && (nameToken.kind != ::app_src_lexer_::TokenType::Null)) {
        parser->fail(std::string("Expected a type name"));
    }
    const auto name = parser->text(nameToken);
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>> typeArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>{});
    if (parser->match(::app_src_lexer_::TokenType::Less)) {
        while (!parser->check(::app_src_lexer_::TokenType::Greater) && !parser->atEnd()) {
            typeArgs->push_back(parseTypeAnnotation(parser));
            if (!parser->match(::app_src_lexer_::TokenType::Comma)) {
                break;
            }
        }
        parser->expect(::app_src_lexer_::TokenType::Greater, std::string(""));
    }
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>(std::make_shared<::app_src_ast_::NamedType>(std::string("named-type"), name, typeArgs, nullptr, std::monostate{}, parser->span(start)));
}
}

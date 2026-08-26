#include "src_parser_statements.hpp"

namespace app_src_parser_statements_ {
using namespace ::app_src_parser_;
using namespace ::app_src_lexer_;
using namespace ::app_src_ast_;
#line 16 "/src/parser-statements.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseStatement(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 17 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Mock)) {
#line 17 "/src/parser-statements.do"
        return parser->parseMockImport();
    }
#line 18 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Export)) {
#line 18 "/src/parser-statements.do"
        return parser->parseExport();
    }
#line 19 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Import)) {
#line 19 "/src/parser-statements.do"
        return parser->parseImport();
    }
#line 20 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Const)) {
#line 20 "/src/parser-statements.do"
        return parser->parseConst(false);
    }
#line 21 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Readonly) && (parser->peek(1).kind != ::app_src_lexer_::TokenType::LeftBracket)) {
#line 21 "/src/parser-statements.do"
        return parser->parseReadonly(false);
    }
#line 22 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Let)) {
#line 22 "/src/parser-statements.do"
        return parser->parseLet();
    }
#line 23 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Function)) {
#line 23 "/src/parser-statements.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(parser->parseFunction(false, false, false, false, false));
    }
#line 24 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Isolated) && (parser->peek(1).kind == ::app_src_lexer_::TokenType::Function)) {
#line 25 "/src/parser-statements.do"
        parser->advance();
#line 26 "/src/parser-statements.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(parser->parseFunction(false, false, true, false, false));
    }
#line 28 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Class) || parser->check(::app_src_lexer_::TokenType::Struct)) {
#line 28 "/src/parser-statements.do"
        return parser->parseClass(false, false);
    }
#line 29 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Private)) {
#line 30 "/src/parser-statements.do"
        parser->advance();
#line 31 "/src/parser-statements.do"
        if (parser->check(::app_src_lexer_::TokenType::Function)) {
#line 31 "/src/parser-statements.do"
            return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(parser->parseFunction(false, false, false, true, false));
        }
#line 32 "/src/parser-statements.do"
        if (parser->check(::app_src_lexer_::TokenType::Class) || parser->check(::app_src_lexer_::TokenType::Struct)) {
#line 32 "/src/parser-statements.do"
            return parser->parseClass(false, true);
        }
#line 33 "/src/parser-statements.do"
        parser->fail(std::string("Expected function, class, or struct after private"));
    }
#line 35 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Interface)) {
#line 35 "/src/parser-statements.do"
        return parser->parseInterface(false);
    }
#line 36 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Enum)) {
#line 36 "/src/parser-statements.do"
        return parser->parseEnum(false);
    }
#line 37 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Type)) {
#line 37 "/src/parser-statements.do"
        return parser->parseTypeAlias(false);
    }
#line 38 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Return)) {
#line 38 "/src/parser-statements.do"
        return parseReturn(parser);
    }
#line 39 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Yield)) {
#line 39 "/src/parser-statements.do"
        return parseYield(parser);
    }
#line 40 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Try)) {
#line 40 "/src/parser-statements.do"
        return parseTryStatement(parser);
    }
#line 41 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::If)) {
#line 41 "/src/parser-statements.do"
        return parseIfStatement(parser);
    }
#line 42 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Case)) {
#line 42 "/src/parser-statements.do"
        return parseCaseStatement(parser);
    }
#line 43 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::While)) {
#line 43 "/src/parser-statements.do"
        return parseWhile(parser, std::nullopt);
    }
#line 44 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::For)) {
#line 44 "/src/parser-statements.do"
        return parseFor(parser, std::nullopt);
    }
#line 45 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::With)) {
#line 45 "/src/parser-statements.do"
        return parseWith(parser);
    }
#line 46 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Break)) {
#line 46 "/src/parser-statements.do"
        return parseBreak(parser);
    }
#line 47 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Continue)) {
#line 47 "/src/parser-statements.do"
        return parseContinue(parser);
    }
#line 49 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Identifier)) {
#line 50 "/src/parser-statements.do"
        if ((parser->peek(1).kind == ::app_src_lexer_::TokenType::Colon) && looksLikeTypedImmutableBinding(parser)) {
#line 51 "/src/parser-statements.do"
            return parseTypedImmutableBinding(parser);
        }
    }
#line 54 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Underscore) && (parser->peek(1).kind == ::app_src_lexer_::TokenType::ColonEqual)) {
#line 55 "/src/parser-statements.do"
        return parseDiscardElseBinding(parser);
    }
#line 57 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::LeftBracket)) {
#line 58 "/src/parser-statements.do"
        if (looksLikePattern(parser, ::app_src_lexer_::TokenType::ColonEqual)) {
#line 59 "/src/parser-statements.do"
            return parseDestructuring(parser, std::string("array"), std::string("immutable"), ::app_src_lexer_::TokenType::ColonEqual);
        }
#line 61 "/src/parser-statements.do"
        if (looksLikePattern(parser, ::app_src_lexer_::TokenType::Equal)) {
#line 62 "/src/parser-statements.do"
            return parseDestructuring(parser, std::string("array"), std::string("assignment"), ::app_src_lexer_::TokenType::Equal);
        }
    }
#line 65 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::LeftParen)) {
#line 66 "/src/parser-statements.do"
        if (looksLikePattern(parser, ::app_src_lexer_::TokenType::ColonEqual)) {
#line 67 "/src/parser-statements.do"
            return parseDestructuring(parser, std::string("positional"), std::string("immutable"), ::app_src_lexer_::TokenType::ColonEqual);
        }
#line 69 "/src/parser-statements.do"
        if (looksLikePattern(parser, ::app_src_lexer_::TokenType::Equal)) {
#line 70 "/src/parser-statements.do"
            return parseDestructuring(parser, std::string("positional"), std::string("assignment"), ::app_src_lexer_::TokenType::Equal);
        }
    }
#line 73 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::LeftBrace)) {
#line 74 "/src/parser-statements.do"
        if (looksLikePattern(parser, ::app_src_lexer_::TokenType::ColonEqual)) {
#line 75 "/src/parser-statements.do"
            return parseDestructuring(parser, std::string("named"), std::string("immutable"), ::app_src_lexer_::TokenType::ColonEqual);
        }
#line 77 "/src/parser-statements.do"
        if (looksLikePattern(parser, ::app_src_lexer_::TokenType::Equal)) {
#line 78 "/src/parser-statements.do"
            return parseDestructuring(parser, std::string("named"), std::string("assignment"), ::app_src_lexer_::TokenType::Equal);
        }
    }
#line 81 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::LeftBrace)) {
#line 81 "/src/parser-statements.do"
        parser->fail(std::string("Bare block statements are not allowed"));
    }
#line 83 "/src/parser-statements.do"
    return parseExpressionStatement(parser);
}
#line 86 "/src/parser-statements.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseReturn(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 87 "/src/parser-statements.do"
    auto start = parser->location();
#line 88 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::Return, std::string(""));
#line 89 "/src/parser-statements.do"
    if ((parser->check(::app_src_lexer_::TokenType::RightBrace) || parser->check(::app_src_lexer_::TokenType::EndOfFile)) || parser->check(::app_src_lexer_::TokenType::Semicolon)) {
#line 90 "/src/parser-statements.do"
        parser->consumeSemicolon();
#line 91 "/src/parser-statements.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::ReturnStatement>(std::string("return-statement"), std::monostate{}, std::monostate{}, parser->span(start)));
    }
#line 93 "/src/parser-statements.do"
    const auto value = parser->parseExpression();
#line 94 "/src/parser-statements.do"
    parser->consumeSemicolon();
#line 95 "/src/parser-statements.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::ReturnStatement>(std::string("return-statement"), doof::optional_value(value), std::monostate{}, parser->span(start)));
}
#line 98 "/src/parser-statements.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseYield(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 99 "/src/parser-statements.do"
    auto start = parser->location();
#line 100 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::Yield, std::string(""));
#line 101 "/src/parser-statements.do"
    const auto value = parser->parseExpression();
#line 102 "/src/parser-statements.do"
    parser->consumeSemicolon();
#line 103 "/src/parser-statements.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::YieldStatement>(std::string("yield-statement"), value, parser->span(start)));
}
#line 106 "/src/parser-statements.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseIfStatement(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 107 "/src/parser-statements.do"
    auto start = parser->location();
#line 108 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::If, std::string(""));
#line 109 "/src/parser-statements.do"
    const auto condition = parser->parseExpression();
#line 110 "/src/parser-statements.do"
    const auto body = parseBlock(parser);
#line 111 "/src/parser-statements.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::IfBranch>>> elseIfs = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::IfBranch>>>(std::vector<std::shared_ptr<::app_src_ast_::IfBranch>>{});
#line 112 "/src/parser-statements.do"
    std::shared_ptr<::app_src_ast_::Block> else_ = nullptr;
#line 113 "/src/parser-statements.do"
    while (parser->match(::app_src_lexer_::TokenType::Else)) {
#line 114 "/src/parser-statements.do"
        if (parser->match(::app_src_lexer_::TokenType::If)) {
#line 115 "/src/parser-statements.do"
            auto branchStart = parser->location();
#line 116 "/src/parser-statements.do"
            const auto branchCondition = parser->parseExpression();
#line 117 "/src/parser-statements.do"
            const auto branchBody = parseBlock(parser);
#line 118 "/src/parser-statements.do"
            elseIfs->push_back(std::make_shared<::app_src_ast_::IfBranch>(branchCondition, branchBody, parser->span(branchStart)));
        } else {
#line 120 "/src/parser-statements.do"
            (else_ = parseBlock(parser));
#line 121 "/src/parser-statements.do"
            break;
        }
    }
#line 124 "/src/parser-statements.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::IfStatement>(std::string("if-statement"), condition, body, elseIfs, else_, parser->span(start)));
}
#line 127 "/src/parser-statements.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseCaseStatement(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 128 "/src/parser-statements.do"
    auto start = parser->location();
#line 129 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::Case, std::string(""));
#line 130 "/src/parser-statements.do"
    const auto subject = parser->parseExpression();
#line 131 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::LeftBrace, std::string(""));
#line 132 "/src/parser-statements.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::CaseArm>>> arms = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::CaseArm>>>(std::vector<std::shared_ptr<::app_src_ast_::CaseArm>>{});
#line 133 "/src/parser-statements.do"
    while (!parser->check(::app_src_lexer_::TokenType::RightBrace) && !parser->atEnd()) {
#line 134 "/src/parser-statements.do"
        auto armStart = parser->location();
#line 135 "/src/parser-statements.do"
        std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>> patterns = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>{parseCasePattern(parser)});
#line 136 "/src/parser-statements.do"
        while (parser->match(::app_src_lexer_::TokenType::Pipe)) {
#line 136 "/src/parser-statements.do"
            patterns->push_back(parseCasePattern(parser));
        }
#line 137 "/src/parser-statements.do"
        parser->expect(::app_src_lexer_::TokenType::RightArrow, std::string(""));
#line 138 "/src/parser-statements.do"
        const auto body = (parser->check(::app_src_lexer_::TokenType::LeftBrace) ? parseBlock(parser) : parseInlineCaseArm(parser));
#line 139 "/src/parser-statements.do"
        arms->push_back(std::make_shared<::app_src_ast_::CaseArm>(std::string("case-arm"), patterns, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>, std::shared_ptr<::app_src_ast_::Block>>>(body), parser->span(armStart)));
#line 140 "/src/parser-statements.do"
        parser->match(::app_src_lexer_::TokenType::Comma);
    }
#line 142 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::RightBrace, std::string(""));
#line 143 "/src/parser-statements.do"
    parser->consumeSemicolon();
#line 144 "/src/parser-statements.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::CaseStatement>(std::string("case-statement"), subject, arms, std::nullopt, parser->span(start)));
}
#line 147 "/src/parser-statements.do"
std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> parseCaseExpression(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 148 "/src/parser-statements.do"
    auto start = parser->location();
#line 149 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::Case, std::string(""));
#line 150 "/src/parser-statements.do"
    const auto subject = parser->parseExpression();
#line 151 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::LeftBrace, std::string(""));
#line 152 "/src/parser-statements.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::CaseExpressionArm>>> arms = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::CaseExpressionArm>>>(std::vector<std::shared_ptr<::app_src_ast_::CaseExpressionArm>>{});
#line 153 "/src/parser-statements.do"
    while (!parser->check(::app_src_lexer_::TokenType::RightBrace) && !parser->atEnd()) {
#line 154 "/src/parser-statements.do"
        auto armStart = parser->location();
#line 155 "/src/parser-statements.do"
        std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>> patterns = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>{parseCasePattern(parser)});
#line 156 "/src/parser-statements.do"
        while (parser->match(::app_src_lexer_::TokenType::Pipe)) {
#line 156 "/src/parser-statements.do"
            patterns->push_back(parseCasePattern(parser));
        }
#line 157 "/src/parser-statements.do"
        parser->expect(::app_src_lexer_::TokenType::RightArrow, std::string(""));
#line 158 "/src/parser-statements.do"
        const auto body = parseCaseExpressionBody(parser);
#line 159 "/src/parser-statements.do"
        arms->push_back(std::make_shared<::app_src_ast_::CaseExpressionArm>(std::string("case-expression-arm"), patterns, body, parser->span(armStart)));
#line 160 "/src/parser-statements.do"
        parser->match(::app_src_lexer_::TokenType::Comma);
    }
#line 162 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::RightBrace, std::string(""));
#line 163 "/src/parser-statements.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(std::make_shared<::app_src_ast_::CaseExpression>(std::string("case-expression"), subject, arms, std::monostate{}, parser->span(start)));
}
#line 168 "/src/parser-statements.do"
std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>, std::shared_ptr<::app_src_ast_::Block>> parseCaseExpressionBody(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 169 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::LeftBrace)) {
#line 169 "/src/parser-statements.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>, std::shared_ptr<::app_src_ast_::Block>>>(parseBlock(parser));
    }
#line 170 "/src/parser-statements.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>, std::shared_ptr<::app_src_ast_::Block>>>(parser->parseExpression());
}
#line 173 "/src/parser-statements.do"
std::shared_ptr<::app_src_ast_::Block> parseInlineCaseArm(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 174 "/src/parser-statements.do"
    const auto statement = parseStatement(parser);
#line 175 "/src/parser-statements.do"
    return std::make_shared<::app_src_ast_::Block>(std::string("block"), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>{statement}), std::visit([](auto&& _obj) { return _obj->span; }, statement));
}
#line 178 "/src/parser-statements.do"
std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>> parseCasePattern(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 179 "/src/parser-statements.do"
    auto start = parser->location();
#line 180 "/src/parser-statements.do"
    if (parser->match(::app_src_lexer_::TokenType::Underscore)) {
#line 181 "/src/parser-statements.do"
        if (parser->match(::app_src_lexer_::TokenType::Colon)) {
#line 182 "/src/parser-statements.do"
            const auto typeValue = parser->parseTypeAnnotation();
#line 183 "/src/parser-statements.do"
            return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>(std::make_shared<::app_src_ast_::TypePattern>(std::string("type-pattern"), std::string("_"), typeValue, std::monostate{}, parser->span(start)));
        }
#line 185 "/src/parser-statements.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>(std::make_shared<::app_src_ast_::WildcardPattern>(std::string("wildcard-pattern"), parser->span(start)));
    }
#line 187 "/src/parser-statements.do"
    if (parser->match(::app_src_lexer_::TokenType::DotDotLess)) {
#line 188 "/src/parser-statements.do"
        const auto end = parser->parseAdditive();
#line 189 "/src/parser-statements.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>(std::make_shared<::app_src_ast_::RangePattern>(std::string("range-pattern"), std::monostate{}, doof::optional_value(end), false, parser->span(start)));
    }
#line 193 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Identifier) && (parser->peek(1).kind == ::app_src_lexer_::TokenType::Colon)) {
#line 194 "/src/parser-statements.do"
        const auto name = parser->text(parser->advance());
#line 195 "/src/parser-statements.do"
        parser->advance();
#line 196 "/src/parser-statements.do"
        const auto typeValue = parser->parseTypeAnnotation();
#line 197 "/src/parser-statements.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>(std::make_shared<::app_src_ast_::TypePattern>(std::string("type-pattern"), name, typeValue, std::monostate{}, parser->span(start)));
    }
#line 201 "/src/parser-statements.do"
    const auto value = parser->parseAdditive();
#line 202 "/src/parser-statements.do"
    if (parser->match(::app_src_lexer_::TokenType::DotDot)) {
#line 203 "/src/parser-statements.do"
        if ((((parser->check(::app_src_lexer_::TokenType::RightArrow) || parser->check(::app_src_lexer_::TokenType::Pipe)) || parser->check(::app_src_lexer_::TokenType::Comma)) || parser->check(::app_src_lexer_::TokenType::RightBrace)) || parser->atEnd()) {
#line 204 "/src/parser-statements.do"
            return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>(std::make_shared<::app_src_ast_::RangePattern>(std::string("range-pattern"), doof::optional_value(value), std::monostate{}, true, parser->span(start)));
        }
#line 208 "/src/parser-statements.do"
        const auto end = parser->parseAdditive();
#line 209 "/src/parser-statements.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>(std::make_shared<::app_src_ast_::RangePattern>(std::string("range-pattern"), doof::optional_value(value), doof::optional_value(end), true, parser->span(start)));
    }
#line 213 "/src/parser-statements.do"
    if (parser->match(::app_src_lexer_::TokenType::DotDotLess)) {
#line 214 "/src/parser-statements.do"
        const auto end = parser->parseAdditive();
#line 215 "/src/parser-statements.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>(std::make_shared<::app_src_ast_::RangePattern>(std::string("range-pattern"), doof::optional_value(value), doof::optional_value(end), false, parser->span(start)));
    }
#line 219 "/src/parser-statements.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>(std::make_shared<::app_src_ast_::ValuePattern>(std::string("value-pattern"), value, parser->span(start)));
}
#line 222 "/src/parser-statements.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseWhile(const std::shared_ptr<::app_src_parser_::Parser>& parser, const std::optional<std::string>& label) {
#line 223 "/src/parser-statements.do"
    auto start = parser->location();
#line 224 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::While, std::string(""));
#line 225 "/src/parser-statements.do"
    const auto condition = parser->parseExpression();
#line 226 "/src/parser-statements.do"
    const auto body = parseBlock(parser);
#line 227 "/src/parser-statements.do"
    std::shared_ptr<::app_src_ast_::Block> then_ = nullptr;
#line 228 "/src/parser-statements.do"
    if (parser->match(::app_src_lexer_::TokenType::Then)) {
#line 228 "/src/parser-statements.do"
        (then_ = parseBlock(parser));
    }
#line 229 "/src/parser-statements.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::WhileStatement>(std::string("while-statement"), condition, body, label, then_, parser->span(start)));
}
#line 232 "/src/parser-statements.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseFor(const std::shared_ptr<::app_src_parser_::Parser>& parser, const std::optional<std::string>& label) {
#line 233 "/src/parser-statements.do"
    auto start = parser->location();
#line 234 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::For, std::string(""));
#line 235 "/src/parser-statements.do"
    if (discardableBindingToken(parser->current().kind) && ((parser->peek(1).kind == ::app_src_lexer_::TokenType::Of) || (parser->peek(1).kind == ::app_src_lexer_::TokenType::Comma))) {
#line 236 "/src/parser-statements.do"
        std::shared_ptr<std::vector<std::string>> bindings = std::make_shared<std::vector<std::string>>(std::vector<std::string>{parseDiscardableBindingName(parser, std::string("Expected loop binding name or '_'"))});
#line 237 "/src/parser-statements.do"
        while (parser->match(::app_src_lexer_::TokenType::Comma)) {
#line 237 "/src/parser-statements.do"
            bindings->push_back(parseDiscardableBindingName(parser, std::string("Expected loop binding name or '_'")));
        }
#line 238 "/src/parser-statements.do"
        parser->expect(::app_src_lexer_::TokenType::Of, std::string(""));
#line 239 "/src/parser-statements.do"
        (parser->inForIterable = true);
#line 240 "/src/parser-statements.do"
        const auto iterable = parser->parseExpression();
#line 241 "/src/parser-statements.do"
        (parser->inForIterable = false);
#line 242 "/src/parser-statements.do"
        const auto body = parseBlock(parser);
#line 243 "/src/parser-statements.do"
        std::shared_ptr<::app_src_ast_::Block> then_ = nullptr;
#line 244 "/src/parser-statements.do"
        if (parser->match(::app_src_lexer_::TokenType::Then)) {
#line 244 "/src/parser-statements.do"
            (then_ = parseBlock(parser));
        }
#line 245 "/src/parser-statements.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::ForOfStatement>(std::string("for-of-statement"), bindings, iterable, body, label, then_, parser->span(start)));
    }
#line 247 "/src/parser-statements.do"
    std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> init = std::monostate{};
#line 248 "/src/parser-statements.do"
    if (!parser->check(::app_src_lexer_::TokenType::Semicolon)) {
#line 249 "/src/parser-statements.do"
        if (parser->check(::app_src_lexer_::TokenType::Let)) {
#line 249 "/src/parser-statements.do"
            (init = doof::optional_value(parseLetNoSemicolon(parser)));
        } else {
#line 250 "/src/parser-statements.do"
            (init = doof::optional_value(parseExpressionStatementNoSemicolon(parser)));
        }
    }
#line 252 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::Semicolon, std::string(""));
#line 253 "/src/parser-statements.do"
    std::variant<std::monostate, std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> condition = std::monostate{};
#line 254 "/src/parser-statements.do"
    if (!parser->check(::app_src_lexer_::TokenType::Semicolon)) {
#line 254 "/src/parser-statements.do"
        (condition = doof::optional_value(parser->parseExpression()));
    }
#line 255 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::Semicolon, std::string(""));
#line 256 "/src/parser-statements.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>> update = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>{});
#line 257 "/src/parser-statements.do"
    while (!parser->check(::app_src_lexer_::TokenType::LeftBrace) && !parser->atEnd()) {
#line 258 "/src/parser-statements.do"
        update->push_back(parser->parseExpression());
#line 259 "/src/parser-statements.do"
        if (!parser->match(::app_src_lexer_::TokenType::Comma)) {
#line 259 "/src/parser-statements.do"
            break;
        }
    }
#line 261 "/src/parser-statements.do"
    const auto body = parseBlock(parser);
#line 262 "/src/parser-statements.do"
    std::shared_ptr<::app_src_ast_::Block> then_ = nullptr;
#line 263 "/src/parser-statements.do"
    if (parser->match(::app_src_lexer_::TokenType::Then)) {
#line 263 "/src/parser-statements.do"
        (then_ = parseBlock(parser));
    }
#line 264 "/src/parser-statements.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::ForStatement>(std::string("for-statement"), init, condition, update, body, label, then_, parser->span(start)));
}
#line 267 "/src/parser-statements.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseLetNoSemicolon(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 268 "/src/parser-statements.do"
    auto start = parser->location();
#line 269 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::Let, std::string(""));
#line 270 "/src/parser-statements.do"
    const auto name = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")));
#line 271 "/src/parser-statements.do"
    const auto typeValue = parser->parseOptionalType();
#line 272 "/src/parser-statements.do"
    const auto value = parseInitializer(parser);
#line 273 "/src/parser-statements.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::LetDeclaration>(std::string("let-declaration"), name, typeValue, value, std::monostate{}, false, parser->span(start)));
}
#line 276 "/src/parser-statements.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseExpressionStatementNoSemicolon(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 277 "/src/parser-statements.do"
    auto start = parser->location();
#line 278 "/src/parser-statements.do"
    const auto value = parser->parseExpression();
#line 279 "/src/parser-statements.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::ExpressionStatement>(std::string("expression-statement"), value, parser->span(start)));
}
#line 282 "/src/parser-statements.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseWith(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 283 "/src/parser-statements.do"
    auto start = parser->location();
#line 284 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::With, std::string(""));
#line 285 "/src/parser-statements.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::WithBinding>>> bindings = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::WithBinding>>>(std::vector<std::shared_ptr<::app_src_ast_::WithBinding>>{});
#line 286 "/src/parser-statements.do"
    while (!parser->check(::app_src_lexer_::TokenType::LeftBrace) && !parser->atEnd()) {
#line 287 "/src/parser-statements.do"
        auto bindingStart = parser->location();
#line 288 "/src/parser-statements.do"
        const auto name = parseDiscardableBindingName(parser, std::string("Expected scoped binding name or '_'"));
#line 289 "/src/parser-statements.do"
        const auto typeValue = parser->parseOptionalType();
#line 290 "/src/parser-statements.do"
        parser->expect(::app_src_lexer_::TokenType::ColonEqual, std::string(""));
#line 291 "/src/parser-statements.do"
        const auto value = parser->parseExpression();
#line 292 "/src/parser-statements.do"
        bindings->push_back(std::make_shared<::app_src_ast_::WithBinding>(name, typeValue, value, std::monostate{}, parser->span(bindingStart)));
#line 293 "/src/parser-statements.do"
        if (!parser->match(::app_src_lexer_::TokenType::Comma)) {
#line 293 "/src/parser-statements.do"
            break;
        }
    }
#line 295 "/src/parser-statements.do"
    const auto body = parseBlock(parser);
#line 296 "/src/parser-statements.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::WithStatement>(std::string("with-statement"), bindings, body, parser->span(start)));
}
#line 299 "/src/parser-statements.do"
bool discardableBindingToken(::app_src_lexer_::TokenType kind) {
#line 300 "/src/parser-statements.do"
    return ((kind == ::app_src_lexer_::TokenType::Identifier) || (kind == ::app_src_lexer_::TokenType::Underscore));
}
#line 303 "/src/parser-statements.do"
std::string parseDiscardableBindingName(const std::shared_ptr<::app_src_parser_::Parser>& parser, const std::string& message) {
#line 304 "/src/parser-statements.do"
    if (discardableBindingToken(parser->current().kind)) {
#line 304 "/src/parser-statements.do"
        return parser->text(parser->advance());
    }
#line 305 "/src/parser-statements.do"
    parser->fail(message);
#line 306 "/src/parser-statements.do"
    return std::string("<error>");
}
#line 309 "/src/parser-statements.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseBreak(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 310 "/src/parser-statements.do"
    auto start = parser->location();
#line 311 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::Break, std::string(""));
#line 312 "/src/parser-statements.do"
    std::optional<std::string> label = std::nullopt;
#line 313 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Identifier) && parser->sameLineAsPrevious()) {
#line 313 "/src/parser-statements.do"
        (label = parser->text(parser->advance()));
    }
#line 314 "/src/parser-statements.do"
    parser->consumeSemicolon();
#line 315 "/src/parser-statements.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::BreakStatement>(std::string("break-statement"), label, parser->span(start)));
}
#line 318 "/src/parser-statements.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseContinue(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 319 "/src/parser-statements.do"
    auto start = parser->location();
#line 320 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::Continue, std::string(""));
#line 321 "/src/parser-statements.do"
    std::optional<std::string> label = std::nullopt;
#line 322 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Identifier) && parser->sameLineAsPrevious()) {
#line 322 "/src/parser-statements.do"
        (label = parser->text(parser->advance()));
    }
#line 323 "/src/parser-statements.do"
    parser->consumeSemicolon();
#line 324 "/src/parser-statements.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::ContinueStatement>(std::string("continue-statement"), label, parser->span(start)));
}
#line 327 "/src/parser-statements.do"
std::shared_ptr<::app_src_ast_::Block> parseBlock(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 328 "/src/parser-statements.do"
    auto start = parser->location();
#line 329 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::LeftBrace, std::string(""));
#line 330 "/src/parser-statements.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>> statements = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>{});
#line 331 "/src/parser-statements.do"
    while (!parser->check(::app_src_lexer_::TokenType::RightBrace) && !parser->atEnd()) {
#line 331 "/src/parser-statements.do"
        statements->push_back(parseStatement(parser));
    }
#line 332 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::RightBrace, std::string(""));
#line 333 "/src/parser-statements.do"
    return std::make_shared<::app_src_ast_::Block>(std::string("block"), statements, parser->span(start));
}
#line 336 "/src/parser-statements.do"
bool looksLikePattern(const std::shared_ptr<::app_src_parser_::Parser>& parser, ::app_src_lexer_::TokenType separator) {
#line 337 "/src/parser-statements.do"
    auto depth = 0;
#line 338 "/src/parser-statements.do"
    auto index = 0;
#line 339 "/src/parser-statements.do"
    while (index < 128) {
#line 340 "/src/parser-statements.do"
        auto token = parser->peek(index);
#line 341 "/src/parser-statements.do"
        if (token.kind == ::app_src_lexer_::TokenType::EndOfFile) {
#line 341 "/src/parser-statements.do"
            return false;
        }
#line 342 "/src/parser-statements.do"
        if (((token.kind == ::app_src_lexer_::TokenType::LeftBracket) || (token.kind == ::app_src_lexer_::TokenType::LeftParen)) || (token.kind == ::app_src_lexer_::TokenType::LeftBrace)) {
#line 342 "/src/parser-statements.do"
            (depth = (depth + 1));
        }
#line 343 "/src/parser-statements.do"
        if (((token.kind == ::app_src_lexer_::TokenType::RightBracket) || (token.kind == ::app_src_lexer_::TokenType::RightParen)) || (token.kind == ::app_src_lexer_::TokenType::RightBrace)) {
#line 343 "/src/parser-statements.do"
            (depth = (depth - 1));
        }
#line 344 "/src/parser-statements.do"
        if ((depth == 0) && (token.kind == separator)) {
#line 344 "/src/parser-statements.do"
            return true;
        }
#line 345 "/src/parser-statements.do"
        if ((depth == 0) && (token.kind == ::app_src_lexer_::TokenType::Equal)) {
#line 345 "/src/parser-statements.do"
            return (separator == ::app_src_lexer_::TokenType::Equal);
        }
#line 346 "/src/parser-statements.do"
        (index = (index + 1));
    }
#line 348 "/src/parser-statements.do"
    return false;
}
#line 351 "/src/parser-statements.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseDestructuring(const std::shared_ptr<::app_src_parser_::Parser>& parser, const std::string& shape, const std::string& bindingKind, ::app_src_lexer_::TokenType separator) {
#line 352 "/src/parser-statements.do"
    auto start = parser->location();
#line 353 "/src/parser-statements.do"
    auto close = ::app_src_lexer_::TokenType::RightParen;
#line 354 "/src/parser-statements.do"
    auto open = ::app_src_lexer_::TokenType::LeftParen;
#line 355 "/src/parser-statements.do"
    if (shape == std::string("array")) {
#line 355 "/src/parser-statements.do"
        (close = ::app_src_lexer_::TokenType::RightBracket);
#line 355 "/src/parser-statements.do"
        (open = ::app_src_lexer_::TokenType::LeftBracket);
    }
#line 356 "/src/parser-statements.do"
    if (shape == std::string("named")) {
#line 356 "/src/parser-statements.do"
        (close = ::app_src_lexer_::TokenType::RightBrace);
#line 356 "/src/parser-statements.do"
        (open = ::app_src_lexer_::TokenType::LeftBrace);
    }
#line 357 "/src/parser-statements.do"
    parser->expect(open, std::string(""));
#line 358 "/src/parser-statements.do"
    std::shared_ptr<std::vector<std::string>> bindings = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 359 "/src/parser-statements.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::DestructureBinding>>> namedBindings = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::DestructureBinding>>>(std::vector<std::shared_ptr<::app_src_ast_::DestructureBinding>>{});
#line 360 "/src/parser-statements.do"
    while (!parser->check(close) && !parser->atEnd()) {
#line 361 "/src/parser-statements.do"
        auto bindingStart = parser->location();
#line 362 "/src/parser-statements.do"
        if (shape == std::string("named")) {
#line 363 "/src/parser-statements.do"
            const auto name = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")));
#line 364 "/src/parser-statements.do"
            std::optional<std::string> alias = std::nullopt;
#line 365 "/src/parser-statements.do"
            if (parser->match(::app_src_lexer_::TokenType::As)) {
#line 365 "/src/parser-statements.do"
                (alias = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string(""))));
            }
#line 366 "/src/parser-statements.do"
            namedBindings->push_back(std::make_shared<::app_src_ast_::DestructureBinding>(name, alias, parser->span(bindingStart)));
        } else if (parser->check(::app_src_lexer_::TokenType::Underscore)) {
#line 367 "/src/parser-statements.do"
            bindings->push_back(std::string("_"));
#line 367 "/src/parser-statements.do"
            parser->advance();
        } else {
#line 368 "/src/parser-statements.do"
            bindings->push_back(parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string(""))));
        }
#line 369 "/src/parser-statements.do"
        if (!parser->match(::app_src_lexer_::TokenType::Comma)) {
#line 369 "/src/parser-statements.do"
            break;
        }
    }
#line 371 "/src/parser-statements.do"
    parser->expect(close, std::string(""));
#line 372 "/src/parser-statements.do"
    parser->expect(separator, std::string(""));
#line 373 "/src/parser-statements.do"
    const auto value = parser->parseExpression();
#line 374 "/src/parser-statements.do"
    parser->consumeSemicolon();
#line 375 "/src/parser-statements.do"
    auto kind = ((shape == std::string("array")) ? std::string("array-destructuring") : ((shape == std::string("named")) ? std::string("named-destructuring") : std::string("positional-destructuring")));
#line 376 "/src/parser-statements.do"
    if (bindingKind == std::string("assignment")) {
#line 376 "/src/parser-statements.do"
        (kind = (kind + std::string("-assignment")));
    }
#line 377 "/src/parser-statements.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::DestructuringStatement>(kind, bindings, namedBindings, bindingKind, value, parser->span(start)));
}
#line 380 "/src/parser-statements.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseExpressionStatement(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 381 "/src/parser-statements.do"
    auto start = parser->location();
#line 382 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Identifier) && (parser->peek(1).kind == ::app_src_lexer_::TokenType::LeftArrow)) {
#line 383 "/src/parser-statements.do"
        const auto name = parser->text(parser->advance());
#line 384 "/src/parser-statements.do"
        parser->advance();
#line 385 "/src/parser-statements.do"
        auto blockStart = parser->location();
#line 386 "/src/parser-statements.do"
        if (!parser->check(::app_src_lexer_::TokenType::LeftBrace)) {
#line 386 "/src/parser-statements.do"
            parser->fail(std::string("Expected block after '<-'"));
        }
#line 387 "/src/parser-statements.do"
        const auto body = parseBlock(parser);
#line 388 "/src/parser-statements.do"
        const auto value = std::make_shared<::app_src_ast_::YieldBlockExpression>(std::string("yield-block-expression"), body, std::monostate{}, parser->span(blockStart));
#line 389 "/src/parser-statements.do"
        parser->consumeSemicolon();
#line 390 "/src/parser-statements.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::YieldBlockAssignmentStatement>(std::string("yield-block-assignment-statement"), name, value, std::monostate{}, parser->span(start)));
    }
#line 392 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Identifier) && (parser->peek(1).kind == ::app_src_lexer_::TokenType::ColonEqual)) {
#line 393 "/src/parser-statements.do"
        const auto name = parser->text(parser->advance());
#line 394 "/src/parser-statements.do"
        parser->advance();
#line 395 "/src/parser-statements.do"
        const auto rhs = parser->parseExpression();
#line 396 "/src/parser-statements.do"
        std::shared_ptr<::app_src_ast_::Block> else_ = nullptr;
#line 397 "/src/parser-statements.do"
        std::optional<std::string> failureName = std::nullopt;
#line 398 "/src/parser-statements.do"
        if (parser->check(::app_src_lexer_::TokenType::Else)) {
#line 399 "/src/parser-statements.do"
            const auto capture = parseElseCaptureAndBlock(parser);
#line 400 "/src/parser-statements.do"
            (else_ = capture->block);
#line 401 "/src/parser-statements.do"
            (failureName = capture->failureName);
        }
#line 403 "/src/parser-statements.do"
        parser->consumeSemicolon();
#line 404 "/src/parser-statements.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::ImmutableBinding>(std::string("immutable-binding"), name, std::monostate{}, rhs, false, else_, failureName, std::monostate{}, false, parser->span(start)));
    }
#line 406 "/src/parser-statements.do"
    auto value = parser->parseExpression();
#line 407 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Else)) {
#line 408 "/src/parser-statements.do"
        const auto capture = parseElseCaptureAndBlock(parser);
#line 409 "/src/parser-statements.do"
        parser->consumeSemicolon();
#line 410 "/src/parser-statements.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::ImmutableBinding>(std::string("immutable-binding"), std::string("_"), std::monostate{}, value, false, capture->block, capture->failureName, std::monostate{}, false, parser->span(start)));
    }
#line 415 "/src/parser-statements.do"
    (value = parseTrailingLambdaExpressionStatement(parser, value));
#line 416 "/src/parser-statements.do"
    parser->consumeSemicolon();
#line 417 "/src/parser-statements.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::ExpressionStatement>(std::string("expression-statement"), value, parser->span(start)));
}
#line 422 "/src/parser-statements.do"
std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> parseTrailingLambdaExpressionStatement(const std::shared_ptr<::app_src_parser_::Parser>& parser, const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression) {
#line 423 "/src/parser-statements.do"
    if ((!parser->previousIs(::app_src_lexer_::TokenType::RightParen) || !parser->check(::app_src_lexer_::TokenType::LeftBrace)) || !parser->sameLineAsPrevious()) {
#line 424 "/src/parser-statements.do"
        return expression;
    }
#line 426 "/src/parser-statements.do"
    {
        auto _case_subject = expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject)) {
            const auto& call = std::get<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject);
#line 428 "/src/parser-statements.do"
            const auto block = parseBlock(parser);
#line 429 "/src/parser-statements.do"
            const auto lambda = std::make_shared<::app_src_ast_::LambdaExpression>(std::string("lambda-expression"), std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Parameter>>>(std::vector<std::shared_ptr<::app_src_ast_::Parameter>>{}), std::monostate{}, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>, std::shared_ptr<::app_src_ast_::Block>>>(block), true, true, std::monostate{}, block->span);
#line 433 "/src/parser-statements.do"
            call->args->push_back(std::make_shared<::app_src_ast_::CallArgument>(std::nullopt, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(lambda), block->span));
#line 434 "/src/parser-statements.do"
            (call->span = ::app_src_ast_::SourceSpan{call->span.start, block->span.end});
#line 435 "/src/parser-statements.do"
            if (parser->sameLineAsPrevious() && (((((((parser->check(::app_src_lexer_::TokenType::Dot) || parser->check(::app_src_lexer_::TokenType::DoubleColon)) || parser->check(::app_src_lexer_::TokenType::QuestionDot)) || parser->check(::app_src_lexer_::TokenType::BangDot)) || parser->check(::app_src_lexer_::TokenType::LeftParen)) || parser->check(::app_src_lexer_::TokenType::LeftBracket)) || parser->check(::app_src_lexer_::TokenType::QuestionBracket)) || parser->check(::app_src_lexer_::TokenType::Bang))) {
#line 441 "/src/parser-statements.do"
                parser->fail(std::string("Chaining after a trailing lambda is not allowed; use an explicit lambda instead"));
            }
#line 443 "/src/parser-statements.do"
            return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(call);
    }
    else {
#line 445 "/src/parser-statements.do"
            return expression;
    }
    }
    doof::unreachable();
}
#line 449 "/src/parser-statements.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseTryStatement(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 450 "/src/parser-statements.do"
    auto start = parser->location();
#line 451 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::Try, std::string(""));
#line 452 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Bang) || (parser->check(::app_src_lexer_::TokenType::Identifier) && (parser->text(parser->current()) == std::string("\?")))) {
#line 453 "/src/parser-statements.do"
        auto operator_ = std::string("try!");
#line 454 "/src/parser-statements.do"
        if (parser->match(::app_src_lexer_::TokenType::Bang)) {
#line 454 "/src/parser-statements.do"
            (operator_ = std::string("try!"));
        } else {
#line 455 "/src/parser-statements.do"
            parser->advance();
#line 455 "/src/parser-statements.do"
            (operator_ = std::string("try\?"));
        }
#line 456 "/src/parser-statements.do"
        const auto operand = parser->parseUnary();
#line 457 "/src/parser-statements.do"
        parser->consumeSemicolon();
#line 458 "/src/parser-statements.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::ExpressionStatement>(std::string("expression-statement"), doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(std::make_shared<::app_src_ast_::UnaryExpression>(std::string("unary-expression"), operator_, operand, true, std::monostate{}, ::app_src_ast_::SourceSpan{start, std::visit([](auto&& _obj) { return _obj->span; }, operand).end})), parser->span(start)));
    }
#line 464 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Const)) {
#line 465 "/src/parser-statements.do"
        {
            auto _case_subject = parser->parseConst(false);
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
                const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 466 "/src/parser-statements.do"
                return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::TryStatement>(std::string("try-statement"), doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>>>(binding), parser->span(start)));
        }
        else {
#line 467 "/src/parser-statements.do"
                parser->fail(std::string("Expected const declaration after try"));
        }
        }
    }
#line 470 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Readonly)) {
#line 471 "/src/parser-statements.do"
        {
            auto _case_subject = parser->parseReadonly(false);
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
                const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 472 "/src/parser-statements.do"
                return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::TryStatement>(std::string("try-statement"), doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>>>(binding), parser->span(start)));
        }
        else {
#line 473 "/src/parser-statements.do"
                parser->fail(std::string("Expected readonly declaration after try"));
        }
        }
    }
#line 476 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Let)) {
#line 477 "/src/parser-statements.do"
        {
            auto _case_subject = parser->parseLet();
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
                const auto& binding = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 478 "/src/parser-statements.do"
                return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::TryStatement>(std::string("try-statement"), doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>>>(binding), parser->span(start)));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
                const auto& binding = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
#line 479 "/src/parser-statements.do"
                return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::TryStatement>(std::string("try-statement"), doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>>>(binding), parser->span(start)));
        }
        else {
#line 480 "/src/parser-statements.do"
                parser->fail(std::string("Expected named let declaration after try"));
        }
        }
    }
#line 483 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::LeftBracket)) {
#line 484 "/src/parser-statements.do"
        if (looksLikePattern(parser, ::app_src_lexer_::TokenType::ColonEqual)) {
#line 484 "/src/parser-statements.do"
            return wrapTryDestructuring(parser, start, std::string("array"), std::string("immutable"), ::app_src_lexer_::TokenType::ColonEqual);
        }
#line 485 "/src/parser-statements.do"
        if (looksLikePattern(parser, ::app_src_lexer_::TokenType::Equal)) {
#line 485 "/src/parser-statements.do"
            return wrapTryDestructuring(parser, start, std::string("array"), std::string("assignment"), ::app_src_lexer_::TokenType::Equal);
        }
    }
#line 487 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::LeftParen)) {
#line 488 "/src/parser-statements.do"
        if (looksLikePattern(parser, ::app_src_lexer_::TokenType::ColonEqual)) {
#line 488 "/src/parser-statements.do"
            return wrapTryDestructuring(parser, start, std::string("positional"), std::string("immutable"), ::app_src_lexer_::TokenType::ColonEqual);
        }
#line 489 "/src/parser-statements.do"
        if (looksLikePattern(parser, ::app_src_lexer_::TokenType::Equal)) {
#line 489 "/src/parser-statements.do"
            return wrapTryDestructuring(parser, start, std::string("positional"), std::string("assignment"), ::app_src_lexer_::TokenType::Equal);
        }
    }
#line 491 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::LeftBrace)) {
#line 492 "/src/parser-statements.do"
        if (looksLikePattern(parser, ::app_src_lexer_::TokenType::ColonEqual)) {
#line 492 "/src/parser-statements.do"
            return wrapTryDestructuring(parser, start, std::string("named"), std::string("immutable"), ::app_src_lexer_::TokenType::ColonEqual);
        }
#line 493 "/src/parser-statements.do"
        if (looksLikePattern(parser, ::app_src_lexer_::TokenType::Equal)) {
#line 493 "/src/parser-statements.do"
            return wrapTryDestructuring(parser, start, std::string("named"), std::string("assignment"), ::app_src_lexer_::TokenType::Equal);
        }
    }
#line 495 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Identifier) && (parser->peek(1).kind == ::app_src_lexer_::TokenType::ColonEqual)) {
#line 496 "/src/parser-statements.do"
        const auto name = parser->text(parser->advance());
#line 497 "/src/parser-statements.do"
        parser->advance();
#line 498 "/src/parser-statements.do"
        const auto value = parser->parseExpression();
#line 499 "/src/parser-statements.do"
        std::shared_ptr<::app_src_ast_::Block> else_ = nullptr;
#line 500 "/src/parser-statements.do"
        if (parser->match(::app_src_lexer_::TokenType::Else)) {
#line 500 "/src/parser-statements.do"
            (else_ = parseBlock(parser));
        }
#line 501 "/src/parser-statements.do"
        parser->consumeSemicolon();
#line 502 "/src/parser-statements.do"
        const auto binding = std::make_shared<::app_src_ast_::ImmutableBinding>(std::string("immutable-binding"), name, std::monostate{}, value, false, else_, std::nullopt, std::monostate{}, false, parser->span(start));
#line 506 "/src/parser-statements.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::TryStatement>(std::string("try-statement"), doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>>>(binding), parser->span(start)));
    }
#line 508 "/src/parser-statements.do"
    const auto value = parser->parseExpression();
#line 509 "/src/parser-statements.do"
    parser->consumeSemicolon();
#line 510 "/src/parser-statements.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::TryStatement>(std::string("try-statement"), doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>>>(std::make_shared<::app_src_ast_::ExpressionStatement>(std::string("expression-statement"), value, parser->span(start))), parser->span(start)));
}
#line 517 "/src/parser-statements.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> wrapTryDestructuring(const std::shared_ptr<::app_src_parser_::Parser>& parser, ::app_src_ast_::AstLocation start, const std::string& shape, const std::string& bindingKind, ::app_src_lexer_::TokenType separator) {
#line 518 "/src/parser-statements.do"
    {
        auto _case_subject = parseDestructuring(parser, shape, bindingKind, separator);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
#line 519 "/src/parser-statements.do"
            return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::TryStatement>(std::string("try-statement"), doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>>>(binding), parser->span(start)));
    }
    else {
#line 520 "/src/parser-statements.do"
            parser->fail(std::string("Expected destructuring after try"));
    }
    }
#line 522 "/src/parser-statements.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::ExpressionStatement>(std::string("expression-statement"), doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(std::make_shared<::app_src_ast_::Identifier>(std::string("identifier"), std::string("<error>"), std::monostate{}, nullptr, parser->locationSpan())), parser->span(start)));
}
#line 525 "/src/parser-statements.do"
std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> parseInitializer(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 526 "/src/parser-statements.do"
    if (parser->match(::app_src_lexer_::TokenType::Equal)) {
#line 526 "/src/parser-statements.do"
        return parser->parseExpression();
    }
#line 527 "/src/parser-statements.do"
    parser->fail(std::string("Expected '=' in declaration"));
#line 528 "/src/parser-statements.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(std::make_shared<::app_src_ast_::Identifier>(std::string("identifier"), std::string("<error>"), std::monostate{}, nullptr, parser->locationSpan()));
}
#line 531 "/src/parser-statements.do"
bool looksLikeTypedImmutableBinding(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 532 "/src/parser-statements.do"
    auto index = 2;
#line 533 "/src/parser-statements.do"
    while (index < 64) {
#line 534 "/src/parser-statements.do"
        auto token = parser->peek(index);
#line 535 "/src/parser-statements.do"
        if (((token.kind == ::app_src_lexer_::TokenType::EndOfFile) || (token.kind == ::app_src_lexer_::TokenType::Semicolon)) || (token.kind == ::app_src_lexer_::TokenType::LeftBrace)) {
#line 535 "/src/parser-statements.do"
            return false;
        }
#line 536 "/src/parser-statements.do"
        if (token.kind == ::app_src_lexer_::TokenType::ColonEqual) {
#line 536 "/src/parser-statements.do"
            return true;
        }
#line 537 "/src/parser-statements.do"
        (index = (index + 1));
    }
#line 539 "/src/parser-statements.do"
    return false;
}
#line 542 "/src/parser-statements.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseTypedImmutableBinding(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 543 "/src/parser-statements.do"
    auto start = parser->location();
#line 544 "/src/parser-statements.do"
    const auto name = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")));
#line 545 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::Colon, std::string(""));
#line 546 "/src/parser-statements.do"
    const auto typeValue = parser->parseTypeAnnotation();
#line 547 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::ColonEqual, std::string(""));
#line 548 "/src/parser-statements.do"
    const auto value = parser->parseExpression();
#line 549 "/src/parser-statements.do"
    std::shared_ptr<::app_src_ast_::Block> else_ = nullptr;
#line 550 "/src/parser-statements.do"
    std::optional<std::string> failureName = std::nullopt;
#line 551 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Else)) {
#line 552 "/src/parser-statements.do"
        const auto capture = parseElseCaptureAndBlock(parser);
#line 553 "/src/parser-statements.do"
        (else_ = capture->block);
#line 554 "/src/parser-statements.do"
        (failureName = capture->failureName);
    }
#line 556 "/src/parser-statements.do"
    parser->consumeSemicolon();
#line 557 "/src/parser-statements.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::ImmutableBinding>(std::string("immutable-binding"), name, doof::optional_value(typeValue), value, false, else_, failureName, std::monostate{}, false, parser->span(start)));
}
#line 560 "/src/parser-statements.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseDiscardElseBinding(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 561 "/src/parser-statements.do"
    auto start = parser->location();
#line 562 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::Underscore, std::string(""));
#line 563 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::ColonEqual, std::string(""));
#line 564 "/src/parser-statements.do"
    const auto value = parser->parseExpression();
#line 565 "/src/parser-statements.do"
    if (!parser->check(::app_src_lexer_::TokenType::Else)) {
#line 565 "/src/parser-statements.do"
        parser->fail(std::string("Discard binding '_' requires an else block"));
    }
#line 566 "/src/parser-statements.do"
    const auto capture = parseElseCaptureAndBlock(parser);
#line 567 "/src/parser-statements.do"
    parser->consumeSemicolon();
#line 568 "/src/parser-statements.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::ImmutableBinding>(std::string("immutable-binding"), std::string("_"), std::monostate{}, value, false, capture->block, capture->failureName, std::monostate{}, false, parser->span(start)));
}

#line 579 "/src/parser-statements.do"
std::shared_ptr<ElseCapture> parseElseCaptureAndBlock(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 580 "/src/parser-statements.do"
    parser->expect(::app_src_lexer_::TokenType::Else, std::string(""));
#line 581 "/src/parser-statements.do"
    std::optional<std::string> failureName = std::nullopt;
#line 582 "/src/parser-statements.do"
    if (parser->check(::app_src_lexer_::TokenType::Identifier) && (parser->peek(1).kind == ::app_src_lexer_::TokenType::LeftBrace)) {
#line 583 "/src/parser-statements.do"
        (failureName = parser->text(parser->advance()));
    }
#line 585 "/src/parser-statements.do"
    return std::make_shared<ElseCapture>(failureName, parseBlock(parser));
}
#line 1 "<doof-generated>"
}

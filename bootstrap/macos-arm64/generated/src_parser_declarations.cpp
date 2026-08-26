#include "src_parser_declarations.hpp"

namespace app_src_parser_declarations_ {
using namespace ::app_src_parser_;
using namespace ::app_src_lexer_;
using namespace ::app_src_ast_;

#line 20 "/src/parser-declarations.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseExport(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 21 "/src/parser-declarations.do"
    auto start = parser->location();
#line 22 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::Export, std::string(""));
#line 23 "/src/parser-declarations.do"
    if (parser->check(::app_src_lexer_::TokenType::Import)) {
#line 24 "/src/parser-declarations.do"
        parser->advance();
#line 25 "/src/parser-declarations.do"
        if (parser->check(::app_src_lexer_::TokenType::Class)) {
#line 25 "/src/parser-declarations.do"
            return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(parseNativeClass(parser, true, start));
        }
#line 26 "/src/parser-declarations.do"
        const auto isolated_ = parser->match(::app_src_lexer_::TokenType::Isolated);
#line 27 "/src/parser-declarations.do"
        if (parser->check(::app_src_lexer_::TokenType::Function)) {
#line 27 "/src/parser-declarations.do"
            return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(parseNativeFunction(parser, true, isolated_, start));
        }
#line 28 "/src/parser-declarations.do"
        parser->fail(std::string("Expected class or function after export import"));
    }
#line 30 "/src/parser-declarations.do"
    if (parser->check(::app_src_lexer_::TokenType::Const)) {
#line 30 "/src/parser-declarations.do"
        return parseConst(parser, true);
    }
#line 31 "/src/parser-declarations.do"
    if (parser->check(::app_src_lexer_::TokenType::Readonly)) {
#line 31 "/src/parser-declarations.do"
        return parseReadonly(parser, true);
    }
#line 32 "/src/parser-declarations.do"
    if (parser->check(::app_src_lexer_::TokenType::Function)) {
#line 32 "/src/parser-declarations.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(parseFunction(parser, true, false, false, false, false));
    }
#line 33 "/src/parser-declarations.do"
    if (parser->check(::app_src_lexer_::TokenType::Isolated) && (parser->peek(1).kind == ::app_src_lexer_::TokenType::Function)) {
#line 34 "/src/parser-declarations.do"
        parser->advance();
#line 35 "/src/parser-declarations.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(parseFunction(parser, true, false, true, false, false));
    }
#line 37 "/src/parser-declarations.do"
    if (parser->check(::app_src_lexer_::TokenType::Class) || parser->check(::app_src_lexer_::TokenType::Struct)) {
#line 37 "/src/parser-declarations.do"
        return parseClass(parser, true, false);
    }
#line 38 "/src/parser-declarations.do"
    if (parser->check(::app_src_lexer_::TokenType::Interface)) {
#line 38 "/src/parser-declarations.do"
        return parseInterface(parser, true);
    }
#line 39 "/src/parser-declarations.do"
    if (parser->check(::app_src_lexer_::TokenType::Enum)) {
#line 39 "/src/parser-declarations.do"
        return parseEnum(parser, true);
    }
#line 40 "/src/parser-declarations.do"
    if (parser->check(::app_src_lexer_::TokenType::Type)) {
#line 40 "/src/parser-declarations.do"
        return parseTypeAlias(parser, true);
    }
#line 41 "/src/parser-declarations.do"
    if (parser->check(::app_src_lexer_::TokenType::Identifier) || parser->check(::app_src_lexer_::TokenType::LeftBrace)) {
#line 42 "/src/parser-declarations.do"
        parser->expect(::app_src_lexer_::TokenType::LeftBrace, std::string(""));
#line 43 "/src/parser-declarations.do"
        std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::ExportSpecifier>>> specifiers = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::ExportSpecifier>>>(std::vector<std::shared_ptr<::app_src_ast_::ExportSpecifier>>{});
#line 44 "/src/parser-declarations.do"
        while (!parser->check(::app_src_lexer_::TokenType::RightBrace) && !parser->atEnd()) {
#line 45 "/src/parser-declarations.do"
            auto itemStart = parser->location();
#line 46 "/src/parser-declarations.do"
            const auto name = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")));
#line 47 "/src/parser-declarations.do"
            std::optional<std::string> alias = std::nullopt;
#line 48 "/src/parser-declarations.do"
            if (parser->match(::app_src_lexer_::TokenType::As)) {
#line 48 "/src/parser-declarations.do"
                (alias = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string(""))));
            }
#line 49 "/src/parser-declarations.do"
            specifiers->push_back(std::make_shared<::app_src_ast_::ExportSpecifier>(name, alias, parser->span(itemStart)));
#line 50 "/src/parser-declarations.do"
            if (!parser->match(::app_src_lexer_::TokenType::Comma)) {
#line 50 "/src/parser-declarations.do"
                break;
            }
        }
#line 52 "/src/parser-declarations.do"
        parser->expect(::app_src_lexer_::TokenType::RightBrace, std::string(""));
#line 53 "/src/parser-declarations.do"
        std::optional<std::string> sourceValue = std::nullopt;
#line 54 "/src/parser-declarations.do"
        if (parser->match(::app_src_lexer_::TokenType::From)) {
#line 54 "/src/parser-declarations.do"
            (sourceValue = parser->text(parser->expect(::app_src_lexer_::TokenType::StringLiteral, std::string(""))));
        }
#line 55 "/src/parser-declarations.do"
        parser->consumeSemicolon();
#line 56 "/src/parser-declarations.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::ExportList>(std::string("export-list"), specifiers, sourceValue, parser->span(start)));
    }
#line 58 "/src/parser-declarations.do"
    parser->fail(std::string("Expected a declaration or export list after export"));
#line 59 "/src/parser-declarations.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::ExportList>(std::string("export-list"), std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::ExportSpecifier>>>(std::vector<std::shared_ptr<::app_src_ast_::ExportSpecifier>>{}), std::nullopt, parser->span(start)));
}
#line 62 "/src/parser-declarations.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseConst(const std::shared_ptr<::app_src_parser_::Parser>& parser, bool exported) {
#line 63 "/src/parser-declarations.do"
    auto start = parser->location();
#line 64 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::Const, std::string(""));
#line 65 "/src/parser-declarations.do"
    const auto name = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")));
#line 66 "/src/parser-declarations.do"
    const auto description = parseDescription(parser);
#line 67 "/src/parser-declarations.do"
    const auto typeValue = parser->parseOptionalType();
#line 68 "/src/parser-declarations.do"
    const auto value = parseInitializer(parser);
#line 69 "/src/parser-declarations.do"
    parser->consumeSemicolon();
#line 70 "/src/parser-declarations.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::ConstDeclaration>(std::string("const-declaration"), name, description, typeValue, value, exported, std::monostate{}, false, parser->span(start)));
}
#line 73 "/src/parser-declarations.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseReadonly(const std::shared_ptr<::app_src_parser_::Parser>& parser, bool exported) {
#line 74 "/src/parser-declarations.do"
    auto start = parser->location();
#line 75 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::Readonly, std::string(""));
#line 76 "/src/parser-declarations.do"
    const auto name = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")));
#line 77 "/src/parser-declarations.do"
    const auto description = parseDescription(parser);
#line 78 "/src/parser-declarations.do"
    const auto typeValue = parser->parseOptionalType();
#line 79 "/src/parser-declarations.do"
    const auto value = parseInitializer(parser);
#line 80 "/src/parser-declarations.do"
    parser->consumeSemicolon();
#line 81 "/src/parser-declarations.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::ReadonlyDeclaration>(std::string("readonly-declaration"), name, description, typeValue, value, exported, std::monostate{}, false, parser->span(start)));
}
#line 84 "/src/parser-declarations.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseLet(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 85 "/src/parser-declarations.do"
    auto start = parser->location();
#line 86 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::Let, std::string(""));
#line 87 "/src/parser-declarations.do"
    if (parser->check(::app_src_lexer_::TokenType::LeftBracket) && parser->looksLikePattern(::app_src_lexer_::TokenType::Equal)) {
#line 88 "/src/parser-declarations.do"
        return parser->parseDestructuring(std::string("array"), std::string("let"), ::app_src_lexer_::TokenType::Equal);
    }
#line 90 "/src/parser-declarations.do"
    if (parser->check(::app_src_lexer_::TokenType::LeftParen) && parser->looksLikePattern(::app_src_lexer_::TokenType::Equal)) {
#line 91 "/src/parser-declarations.do"
        return parser->parseDestructuring(std::string("positional"), std::string("let"), ::app_src_lexer_::TokenType::Equal);
    }
#line 93 "/src/parser-declarations.do"
    if (parser->check(::app_src_lexer_::TokenType::LeftBrace) && parser->looksLikePattern(::app_src_lexer_::TokenType::Equal)) {
#line 94 "/src/parser-declarations.do"
        return parser->parseDestructuring(std::string("named"), std::string("let"), ::app_src_lexer_::TokenType::Equal);
    }
#line 96 "/src/parser-declarations.do"
    const auto name = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")));
#line 97 "/src/parser-declarations.do"
    const auto typeValue = parser->parseOptionalType();
#line 98 "/src/parser-declarations.do"
    const auto value = parseInitializer(parser);
#line 99 "/src/parser-declarations.do"
    parser->consumeSemicolon();
#line 100 "/src/parser-declarations.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::LetDeclaration>(std::string("let-declaration"), name, typeValue, value, std::monostate{}, false, parser->span(start)));
}
#line 103 "/src/parser-declarations.do"
std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> parseInitializer(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 104 "/src/parser-declarations.do"
    if (parser->match(::app_src_lexer_::TokenType::Equal)) {
#line 104 "/src/parser-declarations.do"
        return parser->parseExpression();
    }
#line 105 "/src/parser-declarations.do"
    if (parser->match(::app_src_lexer_::TokenType::LeftArrow)) {
#line 106 "/src/parser-declarations.do"
        auto start = parser->location();
#line 107 "/src/parser-declarations.do"
        if (!parser->check(::app_src_lexer_::TokenType::LeftBrace)) {
#line 107 "/src/parser-declarations.do"
            parser->fail(std::string("Expected block after '<-'"));
        }
#line 108 "/src/parser-declarations.do"
        const auto body = parser->parseBlock();
#line 109 "/src/parser-declarations.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(std::make_shared<::app_src_ast_::YieldBlockExpression>(std::string("yield-block-expression"), body, std::monostate{}, parser->span(start)));
    }
#line 111 "/src/parser-declarations.do"
    parser->fail(std::string("Expected '=' or '<-' in declaration"));
#line 112 "/src/parser-declarations.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(std::make_shared<::app_src_ast_::Identifier>(std::string("identifier"), std::string("<error>"), std::monostate{}, nullptr, parser->locationSpan()));
}
#line 115 "/src/parser-declarations.do"
std::shared_ptr<::app_src_ast_::FunctionDeclaration> parseFunction(const std::shared_ptr<::app_src_parser_::Parser>& parser, bool exported, bool static_, bool isolated_, bool private_, bool legacyMethod) {
#line 116 "/src/parser-declarations.do"
    auto start = parser->location();
#line 117 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::Function, std::string(""));
#line 118 "/src/parser-declarations.do"
    const auto name = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")));
#line 119 "/src/parser-declarations.do"
    const auto legacyMethodFunctionSpan = [&]() -> std::optional<::app_src_ast_::SourceSpan> { if (legacyMethod) { return parser->span(start); } return std::nullopt; }();
#line 120 "/src/parser-declarations.do"
    const auto description = parseDescription(parser);
#line 121 "/src/parser-declarations.do"
    const auto parsedTypeParams = parseTypeParameters(parser);
#line 122 "/src/parser-declarations.do"
    const auto typeParams = parsedTypeParams->names;
#line 123 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::LeftParen, std::string(""));
#line 124 "/src/parser-declarations.do"
    const auto params = parseParameters(parser);
#line 125 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::RightParen, std::string(""));
#line 126 "/src/parser-declarations.do"
    const auto returnType = parser->parseOptionalType();
#line 127 "/src/parser-declarations.do"
    if (parser->check(::app_src_lexer_::TokenType::Arrow)) {
#line 128 "/src/parser-declarations.do"
        const auto body = parseExpressionBody(parser);
#line 129 "/src/parser-declarations.do"
        const auto result = makeFunctionExpression(parser, name, description, typeParams, parsedTypeParams->constraints, params, returnType, body, exported, static_, isolated_, private_, start);
#line 130 "/src/parser-declarations.do"
        (result->legacyMethodFunctionSpan = legacyMethodFunctionSpan);
#line 131 "/src/parser-declarations.do"
        return result;
    }
#line 133 "/src/parser-declarations.do"
    const auto body = parser->parseBlock();
#line 134 "/src/parser-declarations.do"
    const auto result = makeFunctionBlock(parser, name, description, typeParams, parsedTypeParams->constraints, params, returnType, body, exported, static_, isolated_, private_, start);
#line 135 "/src/parser-declarations.do"
    (result->legacyMethodFunctionSpan = legacyMethodFunctionSpan);
#line 136 "/src/parser-declarations.do"
    return result;
}
#line 139 "/src/parser-declarations.do"
std::shared_ptr<::app_src_ast_::FunctionDeclaration> parseMethod(const std::shared_ptr<::app_src_parser_::Parser>& parser, bool static_, bool isolated_, bool private_) {
#line 140 "/src/parser-declarations.do"
    auto start = parser->location();
#line 141 "/src/parser-declarations.do"
    const auto name = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")));
#line 142 "/src/parser-declarations.do"
    const auto description = parseDescription(parser);
#line 143 "/src/parser-declarations.do"
    const auto parsedTypeParams = parseTypeParameters(parser);
#line 144 "/src/parser-declarations.do"
    const auto typeParams = parsedTypeParams->names;
#line 145 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::LeftParen, std::string(""));
#line 146 "/src/parser-declarations.do"
    const auto params = parseParameters(parser);
#line 147 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::RightParen, std::string(""));
#line 148 "/src/parser-declarations.do"
    const auto returnType = parser->parseOptionalType();
#line 149 "/src/parser-declarations.do"
    if (parser->check(::app_src_lexer_::TokenType::Arrow)) {
#line 150 "/src/parser-declarations.do"
        const auto body = parseExpressionBody(parser);
#line 151 "/src/parser-declarations.do"
        return makeFunctionExpression(parser, name, description, typeParams, parsedTypeParams->constraints, params, returnType, body, false, static_, isolated_, private_, start);
    }
#line 153 "/src/parser-declarations.do"
    const auto body = parser->parseBlock();
#line 154 "/src/parser-declarations.do"
    return makeFunctionBlock(parser, name, description, typeParams, parsedTypeParams->constraints, params, returnType, body, false, static_, isolated_, private_, start);
}
#line 157 "/src/parser-declarations.do"
std::shared_ptr<::app_src_ast_::FunctionDeclaration> makeFunctionExpression(const std::shared_ptr<::app_src_parser_::Parser>& parser, const std::string& name, const std::string& description, const std::shared_ptr<std::vector<std::string>>& typeParams, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>>& typeParamConstraints, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Parameter>>>& params, const std::variant<std::monostate, std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>& returnType, const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& body, bool exported, bool static_, bool isolated_, bool private_, ::app_src_ast_::AstLocation start) {
#line 158 "/src/parser-declarations.do"
    return std::make_shared<::app_src_ast_::FunctionDeclaration>(std::string("function-declaration"), name, description, typeParams, typeParamConstraints, params, returnType, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>, std::shared_ptr<::app_src_ast_::Block>>>(body), exported, static_, isolated_, false, private_, false, false, std::string(""), std::string(""), std::nullopt, std::monostate{}, parser->span(start));
}
#line 164 "/src/parser-declarations.do"
std::shared_ptr<::app_src_ast_::FunctionDeclaration> makeFunctionBlock(const std::shared_ptr<::app_src_parser_::Parser>& parser, const std::string& name, const std::string& description, const std::shared_ptr<std::vector<std::string>>& typeParams, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>>& typeParamConstraints, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Parameter>>>& params, const std::variant<std::monostate, std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>& returnType, const std::shared_ptr<::app_src_ast_::Block>& body, bool exported, bool static_, bool isolated_, bool private_, ::app_src_ast_::AstLocation start) {
#line 165 "/src/parser-declarations.do"
    return std::make_shared<::app_src_ast_::FunctionDeclaration>(std::string("function-declaration"), name, description, typeParams, typeParamConstraints, params, returnType, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>, std::shared_ptr<::app_src_ast_::Block>>>(body), exported, static_, isolated_, false, private_, false, false, std::string(""), std::string(""), std::nullopt, std::monostate{}, parser->span(start));
}
#line 171 "/src/parser-declarations.do"
std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> parseExpressionBody(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 172 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::Arrow, std::string(""));
#line 173 "/src/parser-declarations.do"
    const auto value = parser->parseExpression();
#line 174 "/src/parser-declarations.do"
    parser->consumeSemicolon();
#line 175 "/src/parser-declarations.do"
    return value;
}
#line 178 "/src/parser-declarations.do"
std::shared_ptr<ParsedTypeParameters> parseTypeParameters(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 179 "/src/parser-declarations.do"
    const std::shared_ptr<std::vector<std::string>> names = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 180 "/src/parser-declarations.do"
    const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>> constraints = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>>(std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>{});
#line 181 "/src/parser-declarations.do"
    if (!parser->match(::app_src_lexer_::TokenType::Less)) {
#line 181 "/src/parser-declarations.do"
        return std::make_shared<ParsedTypeParameters>(names, constraints);
    }
#line 182 "/src/parser-declarations.do"
    while (!parser->check(::app_src_lexer_::TokenType::Greater) && !parser->atEnd()) {
#line 183 "/src/parser-declarations.do"
        names->push_back(parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string(""))));
#line 184 "/src/parser-declarations.do"
        std::variant<std::monostate, std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> constraint = std::monostate{};
#line 185 "/src/parser-declarations.do"
        if (parser->match(::app_src_lexer_::TokenType::Colon)) {
#line 186 "/src/parser-declarations.do"
            (constraint = doof::optional_value(parser->parseTypeAnnotation()));
        }
#line 188 "/src/parser-declarations.do"
        constraints->push_back(std::make_shared<::app_src_ast_::TypeParameterConstraint>(constraint));
#line 189 "/src/parser-declarations.do"
        if (!parser->match(::app_src_lexer_::TokenType::Comma)) {
#line 189 "/src/parser-declarations.do"
            break;
        }
    }
#line 191 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::Greater, std::string(""));
#line 192 "/src/parser-declarations.do"
    return std::make_shared<ParsedTypeParameters>(names, constraints);
}
#line 195 "/src/parser-declarations.do"
std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Parameter>>> parseParameters(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 196 "/src/parser-declarations.do"
    const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Parameter>>> params = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Parameter>>>(std::vector<std::shared_ptr<::app_src_ast_::Parameter>>{});
#line 197 "/src/parser-declarations.do"
    while (!parser->check(::app_src_lexer_::TokenType::RightParen) && !parser->atEnd()) {
#line 198 "/src/parser-declarations.do"
        auto start = parser->location();
#line 199 "/src/parser-declarations.do"
        const auto name = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("Expected named function parameter name")));
#line 200 "/src/parser-declarations.do"
        const auto description = parseDescription(parser);
#line 201 "/src/parser-declarations.do"
        const auto typeValue = parser->parseOptionalType();
#line 202 "/src/parser-declarations.do"
        std::variant<std::monostate, std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> defaultValue = std::monostate{};
#line 203 "/src/parser-declarations.do"
        if (parser->match(::app_src_lexer_::TokenType::Equal)) {
#line 203 "/src/parser-declarations.do"
            (defaultValue = doof::optional_value(parser->parseExpression()));
        }
#line 204 "/src/parser-declarations.do"
        params->push_back(std::make_shared<::app_src_ast_::Parameter>(name, description, typeValue, defaultValue, std::monostate{}, parser->span(start)));
#line 205 "/src/parser-declarations.do"
        if (!parser->match(::app_src_lexer_::TokenType::Comma)) {
#line 205 "/src/parser-declarations.do"
            break;
        }
    }
#line 207 "/src/parser-declarations.do"
    return params;
}
#line 210 "/src/parser-declarations.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseClass(const std::shared_ptr<::app_src_parser_::Parser>& parser, bool exported, bool private_) {
#line 211 "/src/parser-declarations.do"
    auto start = parser->location();
#line 212 "/src/parser-declarations.do"
    const auto struct_ = parser->check(::app_src_lexer_::TokenType::Struct);
#line 213 "/src/parser-declarations.do"
    parser->advance();
#line 214 "/src/parser-declarations.do"
    const auto name = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")));
#line 215 "/src/parser-declarations.do"
    const auto description = parseDescription(parser);
#line 216 "/src/parser-declarations.do"
    const auto parsedTypeParams = parseTypeParameters(parser);
#line 217 "/src/parser-declarations.do"
    const auto typeParams = parsedTypeParams->names;
#line 218 "/src/parser-declarations.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::NamedType>>> implements_ = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::NamedType>>>(std::vector<std::shared_ptr<::app_src_ast_::NamedType>>{});
#line 219 "/src/parser-declarations.do"
    if (parser->match(::app_src_lexer_::TokenType::Implements)) {
#line 220 "/src/parser-declarations.do"
        implements_->push_back(parseNamedType(parser));
#line 221 "/src/parser-declarations.do"
        while (parser->match(::app_src_lexer_::TokenType::Comma)) {
#line 221 "/src/parser-declarations.do"
            implements_->push_back(parseNamedType(parser));
        }
    }
#line 223 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::LeftBrace, std::string(""));
#line 225 "/src/parser-declarations.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::ClassField>>> fields = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::ClassField>>>(std::vector<std::shared_ptr<::app_src_ast_::ClassField>>{});
#line 226 "/src/parser-declarations.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>> methods = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>>(std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>{});
#line 227 "/src/parser-declarations.do"
    std::shared_ptr<::app_src_ast_::Block> destructor_ = nullptr;
#line 228 "/src/parser-declarations.do"
    while (!parser->check(::app_src_lexer_::TokenType::RightBrace) && !parser->atEnd()) {
#line 229 "/src/parser-declarations.do"
        if (parser->check(::app_src_lexer_::TokenType::Function)) {
#line 230 "/src/parser-declarations.do"
            methods->push_back(parseFunction(parser, false, false, false, false, true));
        } else if (parser->check(::app_src_lexer_::TokenType::Static) && (parser->peek(1).kind == ::app_src_lexer_::TokenType::Function)) {
#line 232 "/src/parser-declarations.do"
            parser->advance();
#line 233 "/src/parser-declarations.do"
            methods->push_back(parseFunction(parser, false, true, false, false, true));
        } else if (parser->check(::app_src_lexer_::TokenType::Private) && (parser->peek(1).kind == ::app_src_lexer_::TokenType::Function)) {
#line 235 "/src/parser-declarations.do"
            parser->advance();
#line 236 "/src/parser-declarations.do"
            methods->push_back(parseFunction(parser, false, false, false, true, true));
        } else if (parser->check(::app_src_lexer_::TokenType::Isolated)) {
#line 238 "/src/parser-declarations.do"
            parser->advance();
#line 239 "/src/parser-declarations.do"
            const auto static_ = parser->match(::app_src_lexer_::TokenType::Static);
#line 240 "/src/parser-declarations.do"
            if (parser->check(::app_src_lexer_::TokenType::Function)) {
#line 241 "/src/parser-declarations.do"
                methods->push_back(parseFunction(parser, false, static_, true, false, true));
            } else {
#line 243 "/src/parser-declarations.do"
                if (!checkAheadMethod(parser, 0)) {
#line 243 "/src/parser-declarations.do"
                    parser->fail(std::string("Expected class method after 'isolated'"));
                }
#line 244 "/src/parser-declarations.do"
                methods->push_back(parseMethod(parser, static_, true, false));
            }
        } else if (parser->check(::app_src_lexer_::TokenType::Private)) {
#line 247 "/src/parser-declarations.do"
            parser->advance();
#line 248 "/src/parser-declarations.do"
            if (parser->check(::app_src_lexer_::TokenType::Function)) {
#line 249 "/src/parser-declarations.do"
                methods->push_back(parseFunction(parser, false, false, false, true, true));
            } else if (parser->match(::app_src_lexer_::TokenType::Isolated)) {
#line 251 "/src/parser-declarations.do"
                const auto static_ = parser->match(::app_src_lexer_::TokenType::Static);
#line 252 "/src/parser-declarations.do"
                if (parser->check(::app_src_lexer_::TokenType::Function)) {
#line 253 "/src/parser-declarations.do"
                    methods->push_back(parseFunction(parser, false, static_, true, true, true));
                } else {
#line 255 "/src/parser-declarations.do"
                    if (!checkAheadMethod(parser, 0)) {
#line 255 "/src/parser-declarations.do"
                        parser->fail(std::string("Expected class method after 'private isolated'"));
                    }
#line 256 "/src/parser-declarations.do"
                    methods->push_back(parseMethod(parser, static_, true, true));
                }
            } else if (checkAheadMethod(parser, 0)) {
#line 259 "/src/parser-declarations.do"
                methods->push_back(parseMethod(parser, false, false, true));
            } else if (parser->check(::app_src_lexer_::TokenType::Static)) {
#line 261 "/src/parser-declarations.do"
                parser->advance();
#line 262 "/src/parser-declarations.do"
                if (checkAheadMethod(parser, 0)) {
#line 263 "/src/parser-declarations.do"
                    methods->push_back(parseMethod(parser, true, false, true));
                } else {
#line 265 "/src/parser-declarations.do"
                    fields->push_back(parseClassField(parser, true, true));
                }
            } else {
#line 268 "/src/parser-declarations.do"
                fields->push_back(parseClassField(parser, false, true));
            }
        } else if (parser->check(::app_src_lexer_::TokenType::Destructor)) {
#line 271 "/src/parser-declarations.do"
            if (!doof::is_null(destructor_)) {
#line 271 "/src/parser-declarations.do"
                parser->fail(std::string("A class may declare at most one destructor"));
            }
#line 272 "/src/parser-declarations.do"
            parser->advance();
#line 273 "/src/parser-declarations.do"
            (destructor_ = parser->parseBlock());
        } else if (parser->check(::app_src_lexer_::TokenType::Static)) {
#line 275 "/src/parser-declarations.do"
            if (checkAheadMethod(parser, 1)) {
#line 276 "/src/parser-declarations.do"
                parser->advance();
#line 277 "/src/parser-declarations.do"
                methods->push_back(parseMethod(parser, true, false, false));
            } else {
#line 279 "/src/parser-declarations.do"
                parser->advance();
#line 280 "/src/parser-declarations.do"
                fields->push_back(parseClassField(parser, true, false));
            }
        } else if (checkAheadMethod(parser, 0)) {
#line 283 "/src/parser-declarations.do"
            methods->push_back(parseMethod(parser, false, false, false));
        } else {
#line 285 "/src/parser-declarations.do"
            fields->push_back(parseClassField(parser, false, false));
        }
    }
#line 288 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::RightBrace, std::string(""));
#line 289 "/src/parser-declarations.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::ClassDeclaration>(std::string("class-declaration"), name, description, struct_, typeParams, parsedTypeParams->constraints, implements_, fields, methods, destructor_, exported, private_, false, std::string(""), std::string(""), nullptr, false, parser->span(start)));
}
#line 292 "/src/parser-declarations.do"
bool checkAheadMethod(const std::shared_ptr<::app_src_parser_::Parser>& parser, int32_t offset) {
#line 293 "/src/parser-declarations.do"
    if (parser->peek(offset).kind != ::app_src_lexer_::TokenType::Identifier) {
#line 293 "/src/parser-declarations.do"
        return false;
    }
#line 294 "/src/parser-declarations.do"
    auto suffixOffset = (offset + 1);
#line 295 "/src/parser-declarations.do"
    if (parser->peek(suffixOffset).kind == ::app_src_lexer_::TokenType::StringLiteral) {
#line 295 "/src/parser-declarations.do"
        (suffixOffset += 1);
    }
#line 296 "/src/parser-declarations.do"
    return ((parser->peek(suffixOffset).kind == ::app_src_lexer_::TokenType::LeftParen) || (parser->peek(suffixOffset).kind == ::app_src_lexer_::TokenType::Less));
}
#line 299 "/src/parser-declarations.do"
std::shared_ptr<::app_src_ast_::NamedType> parseNamedType(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 300 "/src/parser-declarations.do"
    auto start = parser->location();
#line 301 "/src/parser-declarations.do"
    const auto name = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")));
#line 302 "/src/parser-declarations.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>> typeArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>{});
#line 303 "/src/parser-declarations.do"
    if (parser->match(::app_src_lexer_::TokenType::Less)) {
#line 304 "/src/parser-declarations.do"
        while (!parser->check(::app_src_lexer_::TokenType::Greater) && !parser->atEnd()) {
#line 305 "/src/parser-declarations.do"
            typeArgs->push_back(parser->parseTypeAnnotation());
#line 306 "/src/parser-declarations.do"
            if (!parser->match(::app_src_lexer_::TokenType::Comma)) {
#line 306 "/src/parser-declarations.do"
                break;
            }
        }
#line 308 "/src/parser-declarations.do"
        parser->expect(::app_src_lexer_::TokenType::Greater, std::string(""));
    }
#line 310 "/src/parser-declarations.do"
    return std::make_shared<::app_src_ast_::NamedType>(std::string("named-type"), name, typeArgs, nullptr, std::monostate{}, parser->span(start));
}
#line 313 "/src/parser-declarations.do"
std::shared_ptr<::app_src_ast_::ClassField> parseClassField(const std::shared_ptr<::app_src_parser_::Parser>& parser, bool static_, bool private_) {
#line 314 "/src/parser-declarations.do"
    auto start = parser->location();
#line 315 "/src/parser-declarations.do"
    if (parser->check(::app_src_lexer_::TokenType::Private) || parser->check(::app_src_lexer_::TokenType::Static)) {
#line 316 "/src/parser-declarations.do"
        parser->fail(std::string("Field modifiers must use '[private] [static] [let|readonly|const] [weak] name' order without duplicates"));
    }
#line 318 "/src/parser-declarations.do"
    const auto const_ = parser->match(::app_src_lexer_::TokenType::Const);
#line 319 "/src/parser-declarations.do"
    const auto let_ = parser->match(::app_src_lexer_::TokenType::Let);
#line 320 "/src/parser-declarations.do"
    const auto readonly_ = parser->match(::app_src_lexer_::TokenType::Readonly);
#line 321 "/src/parser-declarations.do"
    if ((((const_ ? 1 : 0) + (let_ ? 1 : 0)) + (readonly_ ? 1 : 0)) > 1) {
#line 322 "/src/parser-declarations.do"
        parser->fail(std::string("Field declarations accept only one of 'let', 'readonly', or 'const'"));
    }
#line 324 "/src/parser-declarations.do"
    if ((parser->check(::app_src_lexer_::TokenType::Const) || parser->check(::app_src_lexer_::TokenType::Let)) || parser->check(::app_src_lexer_::TokenType::Readonly)) {
#line 325 "/src/parser-declarations.do"
        parser->fail(std::string("Field declarations accept only one of 'let', 'readonly', or 'const'"));
    }
#line 327 "/src/parser-declarations.do"
    if (parser->check(::app_src_lexer_::TokenType::Private) || parser->check(::app_src_lexer_::TokenType::Static)) {
#line 328 "/src/parser-declarations.do"
        parser->fail(std::string("Field modifiers must use '[private] [static] [let|readonly|const] [weak] name' order without duplicates"));
    }
#line 330 "/src/parser-declarations.do"
    const auto weak_ = parser->match(::app_src_lexer_::TokenType::Weak);
#line 331 "/src/parser-declarations.do"
    if (parser->check(::app_src_lexer_::TokenType::Weak)) {
#line 331 "/src/parser-declarations.do"
        parser->fail(std::string("Field declarations accept 'weak' at most once"));
    }
#line 332 "/src/parser-declarations.do"
    std::shared_ptr<std::vector<std::string>> names = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 333 "/src/parser-declarations.do"
    std::shared_ptr<std::vector<std::string>> descriptions = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 334 "/src/parser-declarations.do"
    names->push_back(parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string(""))));
#line 335 "/src/parser-declarations.do"
    descriptions->push_back(parseDescription(parser));
#line 336 "/src/parser-declarations.do"
    while (parser->match(::app_src_lexer_::TokenType::Comma)) {
#line 337 "/src/parser-declarations.do"
        names->push_back(parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string(""))));
#line 338 "/src/parser-declarations.do"
        descriptions->push_back(parseDescription(parser));
    }
#line 340 "/src/parser-declarations.do"
    const auto typeValue = parser->parseOptionalType();
#line 341 "/src/parser-declarations.do"
    std::variant<std::monostate, std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> defaultValue = std::monostate{};
#line 342 "/src/parser-declarations.do"
    if (parser->match(::app_src_lexer_::TokenType::Equal)) {
#line 342 "/src/parser-declarations.do"
        (defaultValue = doof::optional_value(parser->parseExpression()));
    }
#line 343 "/src/parser-declarations.do"
    if (const_ && doof::is_null(defaultValue)) {
#line 343 "/src/parser-declarations.do"
        parser->fail(std::string("Const class fields require a fixed value"));
    }
#line 344 "/src/parser-declarations.do"
    parser->consumeSemicolon();
#line 345 "/src/parser-declarations.do"
    return std::make_shared<::app_src_ast_::ClassField>(std::string("class-field"), names, descriptions, typeValue, defaultValue, static_, const_, let_, readonly_, weak_, private_, std::monostate{}, false, parser->span(start));
}
#line 348 "/src/parser-declarations.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseInterface(const std::shared_ptr<::app_src_parser_::Parser>& parser, bool exported) {
#line 349 "/src/parser-declarations.do"
    auto start = parser->location();
#line 350 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::Interface, std::string(""));
#line 351 "/src/parser-declarations.do"
    const auto name = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")));
#line 352 "/src/parser-declarations.do"
    const auto description = parseDescription(parser);
#line 353 "/src/parser-declarations.do"
    const auto parsedTypeParams = parseTypeParameters(parser);
#line 354 "/src/parser-declarations.do"
    const auto typeParams = parsedTypeParams->names;
#line 355 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::LeftBrace, std::string(""));
#line 356 "/src/parser-declarations.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::InterfaceField>>> fields = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::InterfaceField>>>(std::vector<std::shared_ptr<::app_src_ast_::InterfaceField>>{});
#line 357 "/src/parser-declarations.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>> methods = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>>(std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>{});
#line 358 "/src/parser-declarations.do"
    while (!parser->check(::app_src_lexer_::TokenType::RightBrace) && !parser->atEnd()) {
#line 359 "/src/parser-declarations.do"
        auto memberStart = parser->location();
#line 360 "/src/parser-declarations.do"
        const auto let_ = parser->match(::app_src_lexer_::TokenType::Let);
#line 361 "/src/parser-declarations.do"
        const auto readonly_ = parser->match(::app_src_lexer_::TokenType::Readonly);
#line 362 "/src/parser-declarations.do"
        if (parser->check(::app_src_lexer_::TokenType::Let) || parser->check(::app_src_lexer_::TokenType::Readonly)) {
#line 363 "/src/parser-declarations.do"
            parser->fail(std::string("Interface fields accept only one of 'let' or 'readonly'"));
        }
#line 365 "/src/parser-declarations.do"
        const auto memberName = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")));
#line 366 "/src/parser-declarations.do"
        const auto memberDescription = parseDescription(parser);
#line 367 "/src/parser-declarations.do"
        if (parser->check(::app_src_lexer_::TokenType::LeftParen)) {
#line 368 "/src/parser-declarations.do"
            parser->expect(::app_src_lexer_::TokenType::LeftParen, std::string(""));
#line 369 "/src/parser-declarations.do"
            const auto params = parseParameters(parser);
#line 370 "/src/parser-declarations.do"
            parser->expect(::app_src_lexer_::TokenType::RightParen, std::string(""));
#line 371 "/src/parser-declarations.do"
            const auto returnType = parser->parseOptionalType();
#line 372 "/src/parser-declarations.do"
            parser->consumeSemicolon();
#line 373 "/src/parser-declarations.do"
            methods->push_back(std::make_shared<::app_src_ast_::FunctionDeclaration>(std::string("function-declaration"), memberName, memberDescription, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>>(std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>{}), params, returnType, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::Block>(std::string("block"), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>{}), parser->span(memberStart))), false, false, false, false, false, true, false, std::string(""), std::string(""), std::nullopt, std::monostate{}, parser->span(memberStart)));
        } else {
#line 381 "/src/parser-declarations.do"
            parser->expect(::app_src_lexer_::TokenType::Colon, std::string(""));
#line 382 "/src/parser-declarations.do"
            const auto typeValue = parser->parseTypeAnnotation();
#line 383 "/src/parser-declarations.do"
            parser->consumeSemicolon();
#line 384 "/src/parser-declarations.do"
            fields->push_back(std::make_shared<::app_src_ast_::InterfaceField>(std::string("interface-field"), memberName, memberDescription, typeValue, let_, readonly_, std::monostate{}, parser->span(memberStart)));
        }
    }
#line 387 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::RightBrace, std::string(""));
#line 388 "/src/parser-declarations.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::InterfaceDeclaration>(std::string("interface-declaration"), name, description, typeParams, parsedTypeParams->constraints, fields, methods, exported, nullptr, false, parser->span(start)));
}
#line 391 "/src/parser-declarations.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseEnum(const std::shared_ptr<::app_src_parser_::Parser>& parser, bool exported) {
#line 392 "/src/parser-declarations.do"
    auto start = parser->location();
#line 393 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::Enum, std::string(""));
#line 394 "/src/parser-declarations.do"
    const auto name = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")));
#line 395 "/src/parser-declarations.do"
    const auto description = parseDescription(parser);
#line 396 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::LeftBrace, std::string(""));
#line 397 "/src/parser-declarations.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::EnumVariant>>> variants = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::EnumVariant>>>(std::vector<std::shared_ptr<::app_src_ast_::EnumVariant>>{});
#line 398 "/src/parser-declarations.do"
    while (!parser->check(::app_src_lexer_::TokenType::RightBrace) && !parser->atEnd()) {
#line 399 "/src/parser-declarations.do"
        auto variantStart = parser->location();
#line 400 "/src/parser-declarations.do"
        const auto variantName = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")));
#line 401 "/src/parser-declarations.do"
        const auto variantDescription = parseDescription(parser);
#line 402 "/src/parser-declarations.do"
        std::variant<std::monostate, std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> enumValue = std::monostate{};
#line 403 "/src/parser-declarations.do"
        if (parser->match(::app_src_lexer_::TokenType::Equal)) {
#line 403 "/src/parser-declarations.do"
            (enumValue = doof::optional_value(parser->parseExpression()));
        }
#line 404 "/src/parser-declarations.do"
        variants->push_back(std::make_shared<::app_src_ast_::EnumVariant>(std::string("enum-variant"), variantName, variantDescription, enumValue, parser->span(variantStart)));
#line 405 "/src/parser-declarations.do"
        if (!parser->match(::app_src_lexer_::TokenType::Comma)) {
#line 405 "/src/parser-declarations.do"
            parser->consumeSemicolon();
        }
    }
#line 407 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::RightBrace, std::string(""));
#line 408 "/src/parser-declarations.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::EnumDeclaration>(std::string("enum-declaration"), name, description, variants, exported, parser->span(start)));
}
#line 411 "/src/parser-declarations.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseTypeAlias(const std::shared_ptr<::app_src_parser_::Parser>& parser, bool exported) {
#line 412 "/src/parser-declarations.do"
    auto start = parser->location();
#line 413 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::Type, std::string(""));
#line 414 "/src/parser-declarations.do"
    const auto name = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")));
#line 415 "/src/parser-declarations.do"
    const auto description = parseDescription(parser);
#line 416 "/src/parser-declarations.do"
    const auto parsedTypeParams = parseTypeParameters(parser);
#line 417 "/src/parser-declarations.do"
    const auto typeParams = parsedTypeParams->names;
#line 418 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::Equal, std::string(""));
#line 419 "/src/parser-declarations.do"
    const auto typeValue = parser->parseTypeAnnotation();
#line 420 "/src/parser-declarations.do"
    parser->consumeSemicolon();
#line 421 "/src/parser-declarations.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::TypeAliasDeclaration>(std::string("type-alias-declaration"), name, description, typeParams, parsedTypeParams->constraints, typeValue, exported, std::monostate{}, parser->span(start)));
}
#line 424 "/src/parser-declarations.do"
std::string parseDescription(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 425 "/src/parser-declarations.do"
    if (!parser->check(::app_src_lexer_::TokenType::StringLiteral)) {
#line 425 "/src/parser-declarations.do"
        return std::string("");
    }
#line 426 "/src/parser-declarations.do"
    return parser->text(parser->advance());
}
#line 429 "/src/parser-declarations.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseImport(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 430 "/src/parser-declarations.do"
    auto start = parser->location();
#line 431 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::Import, std::string(""));
#line 432 "/src/parser-declarations.do"
    if (parser->check(::app_src_lexer_::TokenType::Class)) {
#line 432 "/src/parser-declarations.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(parseNativeClass(parser, false, start));
    }
#line 433 "/src/parser-declarations.do"
    const auto isolated_ = parser->match(::app_src_lexer_::TokenType::Isolated);
#line 434 "/src/parser-declarations.do"
    if (parser->check(::app_src_lexer_::TokenType::Function)) {
#line 434 "/src/parser-declarations.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(parseNativeFunction(parser, false, isolated_, start));
    }
#line 435 "/src/parser-declarations.do"
    if (isolated_) {
#line 435 "/src/parser-declarations.do"
        parser->fail(std::string("Expected function after import isolated"));
    }
#line 436 "/src/parser-declarations.do"
    const auto typeOnly = parser->match(::app_src_lexer_::TokenType::Type);
#line 437 "/src/parser-declarations.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::NamedImport>, std::shared_ptr<::app_src_ast_::NamespaceImport>>>> specifiers = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::NamedImport>, std::shared_ptr<::app_src_ast_::NamespaceImport>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::NamedImport>, std::shared_ptr<::app_src_ast_::NamespaceImport>>>{});
#line 438 "/src/parser-declarations.do"
    if (parser->match(::app_src_lexer_::TokenType::Star)) {
#line 439 "/src/parser-declarations.do"
        parser->match(::app_src_lexer_::TokenType::As);
#line 440 "/src/parser-declarations.do"
        const auto alias = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")));
#line 441 "/src/parser-declarations.do"
        specifiers->push_back(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::NamedImport>, std::shared_ptr<::app_src_ast_::NamespaceImport>>>(std::make_shared<::app_src_ast_::NamespaceImport>(std::string("namespace-import-specifier"), alias, parser->span(start))));
    } else {
#line 443 "/src/parser-declarations.do"
        parser->expect(::app_src_lexer_::TokenType::LeftBrace, std::string(""));
#line 444 "/src/parser-declarations.do"
        while (!parser->check(::app_src_lexer_::TokenType::RightBrace) && !parser->atEnd()) {
#line 445 "/src/parser-declarations.do"
            auto itemStart = parser->location();
#line 446 "/src/parser-declarations.do"
            const auto name = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")));
#line 447 "/src/parser-declarations.do"
            std::optional<std::string> alias = std::nullopt;
#line 448 "/src/parser-declarations.do"
            if (parser->match(::app_src_lexer_::TokenType::As)) {
#line 448 "/src/parser-declarations.do"
                (alias = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string(""))));
            }
#line 449 "/src/parser-declarations.do"
            specifiers->push_back(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::NamedImport>, std::shared_ptr<::app_src_ast_::NamespaceImport>>>(std::make_shared<::app_src_ast_::NamedImport>(std::string("named-import-specifier"), name, alias, parser->span(itemStart))));
#line 450 "/src/parser-declarations.do"
            if (!parser->match(::app_src_lexer_::TokenType::Comma)) {
#line 450 "/src/parser-declarations.do"
                break;
            }
        }
#line 452 "/src/parser-declarations.do"
        parser->expect(::app_src_lexer_::TokenType::RightBrace, std::string(""));
    }
#line 454 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::From, std::string(""));
#line 455 "/src/parser-declarations.do"
    const auto sourceValue = parser->text(parser->expect(::app_src_lexer_::TokenType::StringLiteral, std::string("")));
#line 456 "/src/parser-declarations.do"
    parser->consumeSemicolon();
#line 457 "/src/parser-declarations.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::ImportDeclaration>(std::string("import-declaration"), specifiers, sourceValue, typeOnly, parser->span(start)));
}
#line 460 "/src/parser-declarations.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> parseMockImport(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 461 "/src/parser-declarations.do"
    auto start = parser->location();
#line 462 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::Mock, std::string(""));
#line 463 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::Import, std::string("Expected import after mock"));
#line 464 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::For, std::string(""));
#line 465 "/src/parser-declarations.do"
    const auto sourcePattern = parser->text(parser->expect(::app_src_lexer_::TokenType::StringLiteral, std::string("")));
#line 466 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::LeftBrace, std::string(""));
#line 468 "/src/parser-declarations.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::MockImportMapping>>> mappings = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::MockImportMapping>>>(std::vector<std::shared_ptr<::app_src_ast_::MockImportMapping>>{});
#line 469 "/src/parser-declarations.do"
    while (!parser->check(::app_src_lexer_::TokenType::RightBrace) && !parser->atEnd()) {
#line 470 "/src/parser-declarations.do"
        auto mappingStart = parser->location();
#line 471 "/src/parser-declarations.do"
        const auto dependency = parser->text(parser->expect(::app_src_lexer_::TokenType::StringLiteral, std::string("")));
#line 472 "/src/parser-declarations.do"
        parser->expect(::app_src_lexer_::TokenType::Arrow, std::string("Expected => in mock import mapping"));
#line 473 "/src/parser-declarations.do"
        const auto replacement = parser->text(parser->expect(::app_src_lexer_::TokenType::StringLiteral, std::string("")));
#line 474 "/src/parser-declarations.do"
        mappings->push_back(std::make_shared<::app_src_ast_::MockImportMapping>(dependency, replacement, parser->span(mappingStart)));
#line 475 "/src/parser-declarations.do"
        if (!parser->match(::app_src_lexer_::TokenType::Comma)) {
#line 475 "/src/parser-declarations.do"
            parser->match(::app_src_lexer_::TokenType::Semicolon);
        }
    }
#line 478 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::RightBrace, std::string(""));
#line 479 "/src/parser-declarations.do"
    parser->consumeSemicolon();
#line 480 "/src/parser-declarations.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::MockImportDirective>(std::string("mock-import-directive"), sourcePattern, mappings, parser->span(start)));
}
#line 483 "/src/parser-declarations.do"
std::shared_ptr<::app_src_ast_::ClassDeclaration> parseNativeClass(const std::shared_ptr<::app_src_parser_::Parser>& parser, bool exported, ::app_src_ast_::AstLocation start) {
#line 484 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::Class, std::string(""));
#line 485 "/src/parser-declarations.do"
    const auto name = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")));
#line 486 "/src/parser-declarations.do"
    auto headerPath = std::string("");
#line 487 "/src/parser-declarations.do"
    if (parser->match(::app_src_lexer_::TokenType::From)) {
#line 487 "/src/parser-declarations.do"
        (headerPath = parser->text(parser->expect(::app_src_lexer_::TokenType::StringLiteral, std::string(""))));
    }
#line 488 "/src/parser-declarations.do"
    auto cppName = std::string("");
#line 489 "/src/parser-declarations.do"
    if (parser->match(::app_src_lexer_::TokenType::As)) {
#line 489 "/src/parser-declarations.do"
        (cppName = parseCppQualifiedName(parser));
    }
#line 491 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::LeftBrace, std::string(""));
#line 492 "/src/parser-declarations.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::ClassField>>> fields = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::ClassField>>>(std::vector<std::shared_ptr<::app_src_ast_::ClassField>>{});
#line 493 "/src/parser-declarations.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>> methods = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>>(std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>{});
#line 494 "/src/parser-declarations.do"
    while (!parser->check(::app_src_lexer_::TokenType::RightBrace) && !parser->atEnd()) {
#line 495 "/src/parser-declarations.do"
        if ((((parser->check(::app_src_lexer_::TokenType::Identifier) && (parser->peek(1).kind == ::app_src_lexer_::TokenType::LeftParen)) || ((parser->check(::app_src_lexer_::TokenType::Static) && (parser->peek(1).kind == ::app_src_lexer_::TokenType::Identifier)) && (parser->peek(2).kind == ::app_src_lexer_::TokenType::LeftParen))) || ((parser->check(::app_src_lexer_::TokenType::Isolated) && (parser->peek(1).kind == ::app_src_lexer_::TokenType::Identifier)) && (parser->peek(2).kind == ::app_src_lexer_::TokenType::LeftParen))) || (((parser->check(::app_src_lexer_::TokenType::Isolated) && (parser->peek(1).kind == ::app_src_lexer_::TokenType::Static)) && (parser->peek(2).kind == ::app_src_lexer_::TokenType::Identifier)) && (parser->peek(3).kind == ::app_src_lexer_::TokenType::LeftParen))) {
#line 499 "/src/parser-declarations.do"
            methods->push_back(parseNativeMethod(parser));
        } else if (parser->match(::app_src_lexer_::TokenType::Static)) {
#line 501 "/src/parser-declarations.do"
            fields->push_back(parseClassField(parser, true, false));
        } else {
#line 503 "/src/parser-declarations.do"
            fields->push_back(parseClassField(parser, false, false));
        }
    }
#line 506 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::RightBrace, std::string(""));
#line 507 "/src/parser-declarations.do"
    return std::make_shared<::app_src_ast_::ClassDeclaration>(std::string("class-declaration"), name, std::string(""), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>>(std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::NamedType>>>(std::vector<std::shared_ptr<::app_src_ast_::NamedType>>{}), fields, methods, nullptr, exported, false, true, headerPath, cppName, nullptr, false, parser->span(start));
}
#line 514 "/src/parser-declarations.do"
std::shared_ptr<::app_src_ast_::FunctionDeclaration> parseNativeMethod(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 515 "/src/parser-declarations.do"
    auto start = parser->location();
#line 516 "/src/parser-declarations.do"
    const auto isolated_ = parser->match(::app_src_lexer_::TokenType::Isolated);
#line 517 "/src/parser-declarations.do"
    const auto static_ = parser->match(::app_src_lexer_::TokenType::Static);
#line 518 "/src/parser-declarations.do"
    const auto name = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")));
#line 519 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::LeftParen, std::string(""));
#line 520 "/src/parser-declarations.do"
    const auto params = parseParameters(parser);
#line 521 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::RightParen, std::string(""));
#line 522 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::Colon, std::string(""));
#line 523 "/src/parser-declarations.do"
    const auto returnType = parser->parseTypeAnnotation();
#line 524 "/src/parser-declarations.do"
    if (parser->check(::app_src_lexer_::TokenType::Arrow)) {
#line 525 "/src/parser-declarations.do"
        const auto body = parseExpressionBody(parser);
#line 526 "/src/parser-declarations.do"
        return std::make_shared<::app_src_ast_::FunctionDeclaration>(std::string("function-declaration"), name, std::string(""), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>>(std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>{}), params, doof::optional_value(returnType), doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>, std::shared_ptr<::app_src_ast_::Block>>>(body), false, static_, isolated_, false, false, false, false, std::string(""), std::string(""), std::nullopt, std::monostate{}, parser->span(start));
    }
#line 532 "/src/parser-declarations.do"
    if (parser->check(::app_src_lexer_::TokenType::LeftBrace)) {
#line 533 "/src/parser-declarations.do"
        const auto body = parser->parseBlock();
#line 534 "/src/parser-declarations.do"
        return std::make_shared<::app_src_ast_::FunctionDeclaration>(std::string("function-declaration"), name, std::string(""), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>>(std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>{}), params, doof::optional_value(returnType), doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>, std::shared_ptr<::app_src_ast_::Block>>>(body), false, static_, isolated_, false, false, false, false, std::string(""), std::string(""), std::nullopt, std::monostate{}, parser->span(start));
    }
#line 540 "/src/parser-declarations.do"
    parser->consumeSemicolon();
#line 541 "/src/parser-declarations.do"
    const auto body = std::make_shared<::app_src_ast_::Block>(std::string("block"), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>{}), parser->span(start));
#line 542 "/src/parser-declarations.do"
    return std::make_shared<::app_src_ast_::FunctionDeclaration>(std::string("function-declaration"), name, std::string(""), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>>(std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>{}), params, doof::optional_value(returnType), doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>, std::shared_ptr<::app_src_ast_::Block>>>(body), false, static_, isolated_, false, false, true, false, std::string(""), std::string(""), std::nullopt, std::monostate{}, parser->span(start));
}
#line 549 "/src/parser-declarations.do"
std::shared_ptr<::app_src_ast_::FunctionDeclaration> parseNativeFunction(const std::shared_ptr<::app_src_parser_::Parser>& parser, bool exported, bool isolated_, ::app_src_ast_::AstLocation start) {
#line 550 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::Function, std::string(""));
#line 551 "/src/parser-declarations.do"
    const auto name = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")));
#line 552 "/src/parser-declarations.do"
    const auto parsedTypeParams = parseTypeParameters(parser);
#line 553 "/src/parser-declarations.do"
    const auto typeParams = parsedTypeParams->names;
#line 554 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::LeftParen, std::string(""));
#line 555 "/src/parser-declarations.do"
    const auto params = parseParameters(parser);
#line 556 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::RightParen, std::string(""));
#line 557 "/src/parser-declarations.do"
    parser->expect(::app_src_lexer_::TokenType::Colon, std::string(""));
#line 558 "/src/parser-declarations.do"
    const auto returnType = parser->parseTypeAnnotation();
#line 559 "/src/parser-declarations.do"
    auto headerPath = std::string("");
#line 560 "/src/parser-declarations.do"
    if (parser->match(::app_src_lexer_::TokenType::From)) {
#line 560 "/src/parser-declarations.do"
        (headerPath = parser->text(parser->expect(::app_src_lexer_::TokenType::StringLiteral, std::string(""))));
    }
#line 561 "/src/parser-declarations.do"
    auto cppName = std::string("");
#line 562 "/src/parser-declarations.do"
    if (parser->match(::app_src_lexer_::TokenType::As)) {
#line 562 "/src/parser-declarations.do"
        (cppName = parseCppQualifiedName(parser));
    }
#line 563 "/src/parser-declarations.do"
    parser->consumeSemicolon();
#line 564 "/src/parser-declarations.do"
    return std::make_shared<::app_src_ast_::FunctionDeclaration>(std::string("function-declaration"), name, std::string(""), typeParams, parsedTypeParams->constraints, params, doof::optional_value(returnType), doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>, std::shared_ptr<::app_src_ast_::Block>>>(std::make_shared<::app_src_ast_::Block>(std::string("block"), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>{}), parser->span(start))), exported, false, isolated_, false, false, true, true, headerPath, cppName, std::nullopt, std::monostate{}, parser->span(start));
}
#line 572 "/src/parser-declarations.do"
std::string parseCppQualifiedName(const std::shared_ptr<::app_src_parser_::Parser>& parser) {
#line 573 "/src/parser-declarations.do"
    auto result = parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")));
#line 574 "/src/parser-declarations.do"
    while (parser->match(::app_src_lexer_::TokenType::DoubleColon)) {
#line 575 "/src/parser-declarations.do"
        (result = ((result + std::string("::")) + parser->text(parser->expect(::app_src_lexer_::TokenType::Identifier, std::string("")))));
    }
#line 577 "/src/parser-declarations.do"
    return result;
}
#line 1 "<doof-generated>"
}

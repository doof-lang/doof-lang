#pragma once
#include "doof_runtime.hpp"
#include <cstdint>
#include <cmath>
#include <functional>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <variant>
#include <vector>
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_lexer_ {
    struct Token;
    struct LexerDiagnostic;
    struct Lexer;
}

namespace app_src_lexer_ {
    struct LexerDiagnostic {
    std::string severity;
    std::string message;
    int32_t line;
    int32_t column;
    LexerDiagnostic(std::string severity, std::string message, int32_t line, int32_t column) : severity(severity), message(message), line(line), column(column) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<LexerDiagnostic, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
}

namespace app_src_lexer_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    enum class TokenType {
    IntLiteral,
    LongLiteral,
    FloatLiteral,
    DoubleLiteral,
    StringLiteral,
    CharLiteral,
    TemplateLiteralStart,
    TemplateLiteralMiddle,
    TemplateLiteralEnd,
    Identifier,
    CallerIntrinsic,
    Const,
    Readonly,
    Let,
    Function,
    Return,
    Yield,
    If,
    Else,
    Then,
    While,
    For,
    Of,
    Break,
    Continue,
    Case,
    Class,
    Struct,
    Interface,
    Implements,
    Enum,
    Type,
    Import,
    Export,
    From,
    As,
    True,
    False,
    Null,
    Void,
    Try,
    Catch,
    Static,
    This,
    Weak,
    Destructor,
    Async,
    Retire,
    Isolated,
    Private,
    With,
    Mock,
    Plus,
    Minus,
    Star,
    Slash,
    Backslash,
    Percent,
    StarStar,
    Ampersand,
    Pipe,
    Caret,
    Tilde,
    LessLess,
    GreaterGreater,
    GreaterGreaterGreater,
    AmpersandAmpersand,
    PipePipe,
    Bang,
    QuestionQuestion,
    EqualEqual,
    BangEqual,
    Less,
    LessEqual,
    Greater,
    GreaterEqual,
    Equal,
    ColonEqual,
    LeftArrow,
    PlusEqual,
    MinusEqual,
    StarEqual,
    SlashEqual,
    BackslashEqual,
    PercentEqual,
    StarStarEqual,
    AmpersandEqual,
    PipeEqual,
    CaretEqual,
    LessLessEqual,
    GreaterGreaterEqual,
    QuestionQuestionEqual,
    LeftParen,
    RightParen,
    LeftBrace,
    RightBrace,
    LeftBracket,
    RightBracket,
    Dot,
    DotDot,
    DotDotLess,
    Comma,
    Colon,
    DoubleColon,
    Semicolon,
    RightArrow,
    Arrow,
    QuestionDot,
    BangDot,
    QuestionBracket,
    Underscore,
    DollarBrace,
    Ellipsis,
    EndOfFile
};
inline const char* TokenType_name(TokenType value) {
  switch (value) {
    case TokenType::IntLiteral: return "IntLiteral";
    case TokenType::LongLiteral: return "LongLiteral";
    case TokenType::FloatLiteral: return "FloatLiteral";
    case TokenType::DoubleLiteral: return "DoubleLiteral";
    case TokenType::StringLiteral: return "StringLiteral";
    case TokenType::CharLiteral: return "CharLiteral";
    case TokenType::TemplateLiteralStart: return "TemplateLiteralStart";
    case TokenType::TemplateLiteralMiddle: return "TemplateLiteralMiddle";
    case TokenType::TemplateLiteralEnd: return "TemplateLiteralEnd";
    case TokenType::Identifier: return "Identifier";
    case TokenType::CallerIntrinsic: return "CallerIntrinsic";
    case TokenType::Const: return "Const";
    case TokenType::Readonly: return "Readonly";
    case TokenType::Let: return "Let";
    case TokenType::Function: return "Function";
    case TokenType::Return: return "Return";
    case TokenType::Yield: return "Yield";
    case TokenType::If: return "If";
    case TokenType::Else: return "Else";
    case TokenType::Then: return "Then";
    case TokenType::While: return "While";
    case TokenType::For: return "For";
    case TokenType::Of: return "Of";
    case TokenType::Break: return "Break";
    case TokenType::Continue: return "Continue";
    case TokenType::Case: return "Case";
    case TokenType::Class: return "Class";
    case TokenType::Struct: return "Struct";
    case TokenType::Interface: return "Interface";
    case TokenType::Implements: return "Implements";
    case TokenType::Enum: return "Enum";
    case TokenType::Type: return "Type";
    case TokenType::Import: return "Import";
    case TokenType::Export: return "Export";
    case TokenType::From: return "From";
    case TokenType::As: return "As";
    case TokenType::True: return "True";
    case TokenType::False: return "False";
    case TokenType::Null: return "Null";
    case TokenType::Void: return "Void";
    case TokenType::Try: return "Try";
    case TokenType::Catch: return "Catch";
    case TokenType::Static: return "Static";
    case TokenType::This: return "This";
    case TokenType::Weak: return "Weak";
    case TokenType::Destructor: return "Destructor";
    case TokenType::Async: return "Async";
    case TokenType::Retire: return "Retire";
    case TokenType::Isolated: return "Isolated";
    case TokenType::Private: return "Private";
    case TokenType::With: return "With";
    case TokenType::Mock: return "Mock";
    case TokenType::Plus: return "Plus";
    case TokenType::Minus: return "Minus";
    case TokenType::Star: return "Star";
    case TokenType::Slash: return "Slash";
    case TokenType::Backslash: return "Backslash";
    case TokenType::Percent: return "Percent";
    case TokenType::StarStar: return "StarStar";
    case TokenType::Ampersand: return "Ampersand";
    case TokenType::Pipe: return "Pipe";
    case TokenType::Caret: return "Caret";
    case TokenType::Tilde: return "Tilde";
    case TokenType::LessLess: return "LessLess";
    case TokenType::GreaterGreater: return "GreaterGreater";
    case TokenType::GreaterGreaterGreater: return "GreaterGreaterGreater";
    case TokenType::AmpersandAmpersand: return "AmpersandAmpersand";
    case TokenType::PipePipe: return "PipePipe";
    case TokenType::Bang: return "Bang";
    case TokenType::QuestionQuestion: return "QuestionQuestion";
    case TokenType::EqualEqual: return "EqualEqual";
    case TokenType::BangEqual: return "BangEqual";
    case TokenType::Less: return "Less";
    case TokenType::LessEqual: return "LessEqual";
    case TokenType::Greater: return "Greater";
    case TokenType::GreaterEqual: return "GreaterEqual";
    case TokenType::Equal: return "Equal";
    case TokenType::ColonEqual: return "ColonEqual";
    case TokenType::LeftArrow: return "LeftArrow";
    case TokenType::PlusEqual: return "PlusEqual";
    case TokenType::MinusEqual: return "MinusEqual";
    case TokenType::StarEqual: return "StarEqual";
    case TokenType::SlashEqual: return "SlashEqual";
    case TokenType::BackslashEqual: return "BackslashEqual";
    case TokenType::PercentEqual: return "PercentEqual";
    case TokenType::StarStarEqual: return "StarStarEqual";
    case TokenType::AmpersandEqual: return "AmpersandEqual";
    case TokenType::PipeEqual: return "PipeEqual";
    case TokenType::CaretEqual: return "CaretEqual";
    case TokenType::LessLessEqual: return "LessLessEqual";
    case TokenType::GreaterGreaterEqual: return "GreaterGreaterEqual";
    case TokenType::QuestionQuestionEqual: return "QuestionQuestionEqual";
    case TokenType::LeftParen: return "LeftParen";
    case TokenType::RightParen: return "RightParen";
    case TokenType::LeftBrace: return "LeftBrace";
    case TokenType::RightBrace: return "RightBrace";
    case TokenType::LeftBracket: return "LeftBracket";
    case TokenType::RightBracket: return "RightBracket";
    case TokenType::Dot: return "Dot";
    case TokenType::DotDot: return "DotDot";
    case TokenType::DotDotLess: return "DotDotLess";
    case TokenType::Comma: return "Comma";
    case TokenType::Colon: return "Colon";
    case TokenType::DoubleColon: return "DoubleColon";
    case TokenType::Semicolon: return "Semicolon";
    case TokenType::RightArrow: return "RightArrow";
    case TokenType::Arrow: return "Arrow";
    case TokenType::QuestionDot: return "QuestionDot";
    case TokenType::BangDot: return "BangDot";
    case TokenType::QuestionBracket: return "QuestionBracket";
    case TokenType::Underscore: return "Underscore";
    case TokenType::DollarBrace: return "DollarBrace";
    case TokenType::Ellipsis: return "Ellipsis";
    case TokenType::EndOfFile: return "EndOfFile";
  }
  return "";
}
inline std::optional<TokenType> TokenType_fromName(std::string_view value) {
  if (value == "IntLiteral") return TokenType::IntLiteral;
  if (value == "LongLiteral") return TokenType::LongLiteral;
  if (value == "FloatLiteral") return TokenType::FloatLiteral;
  if (value == "DoubleLiteral") return TokenType::DoubleLiteral;
  if (value == "StringLiteral") return TokenType::StringLiteral;
  if (value == "CharLiteral") return TokenType::CharLiteral;
  if (value == "TemplateLiteralStart") return TokenType::TemplateLiteralStart;
  if (value == "TemplateLiteralMiddle") return TokenType::TemplateLiteralMiddle;
  if (value == "TemplateLiteralEnd") return TokenType::TemplateLiteralEnd;
  if (value == "Identifier") return TokenType::Identifier;
  if (value == "CallerIntrinsic") return TokenType::CallerIntrinsic;
  if (value == "Const") return TokenType::Const;
  if (value == "Readonly") return TokenType::Readonly;
  if (value == "Let") return TokenType::Let;
  if (value == "Function") return TokenType::Function;
  if (value == "Return") return TokenType::Return;
  if (value == "Yield") return TokenType::Yield;
  if (value == "If") return TokenType::If;
  if (value == "Else") return TokenType::Else;
  if (value == "Then") return TokenType::Then;
  if (value == "While") return TokenType::While;
  if (value == "For") return TokenType::For;
  if (value == "Of") return TokenType::Of;
  if (value == "Break") return TokenType::Break;
  if (value == "Continue") return TokenType::Continue;
  if (value == "Case") return TokenType::Case;
  if (value == "Class") return TokenType::Class;
  if (value == "Struct") return TokenType::Struct;
  if (value == "Interface") return TokenType::Interface;
  if (value == "Implements") return TokenType::Implements;
  if (value == "Enum") return TokenType::Enum;
  if (value == "Type") return TokenType::Type;
  if (value == "Import") return TokenType::Import;
  if (value == "Export") return TokenType::Export;
  if (value == "From") return TokenType::From;
  if (value == "As") return TokenType::As;
  if (value == "True") return TokenType::True;
  if (value == "False") return TokenType::False;
  if (value == "Null") return TokenType::Null;
  if (value == "Void") return TokenType::Void;
  if (value == "Try") return TokenType::Try;
  if (value == "Catch") return TokenType::Catch;
  if (value == "Static") return TokenType::Static;
  if (value == "This") return TokenType::This;
  if (value == "Weak") return TokenType::Weak;
  if (value == "Destructor") return TokenType::Destructor;
  if (value == "Async") return TokenType::Async;
  if (value == "Retire") return TokenType::Retire;
  if (value == "Isolated") return TokenType::Isolated;
  if (value == "Private") return TokenType::Private;
  if (value == "With") return TokenType::With;
  if (value == "Mock") return TokenType::Mock;
  if (value == "Plus") return TokenType::Plus;
  if (value == "Minus") return TokenType::Minus;
  if (value == "Star") return TokenType::Star;
  if (value == "Slash") return TokenType::Slash;
  if (value == "Backslash") return TokenType::Backslash;
  if (value == "Percent") return TokenType::Percent;
  if (value == "StarStar") return TokenType::StarStar;
  if (value == "Ampersand") return TokenType::Ampersand;
  if (value == "Pipe") return TokenType::Pipe;
  if (value == "Caret") return TokenType::Caret;
  if (value == "Tilde") return TokenType::Tilde;
  if (value == "LessLess") return TokenType::LessLess;
  if (value == "GreaterGreater") return TokenType::GreaterGreater;
  if (value == "GreaterGreaterGreater") return TokenType::GreaterGreaterGreater;
  if (value == "AmpersandAmpersand") return TokenType::AmpersandAmpersand;
  if (value == "PipePipe") return TokenType::PipePipe;
  if (value == "Bang") return TokenType::Bang;
  if (value == "QuestionQuestion") return TokenType::QuestionQuestion;
  if (value == "EqualEqual") return TokenType::EqualEqual;
  if (value == "BangEqual") return TokenType::BangEqual;
  if (value == "Less") return TokenType::Less;
  if (value == "LessEqual") return TokenType::LessEqual;
  if (value == "Greater") return TokenType::Greater;
  if (value == "GreaterEqual") return TokenType::GreaterEqual;
  if (value == "Equal") return TokenType::Equal;
  if (value == "ColonEqual") return TokenType::ColonEqual;
  if (value == "LeftArrow") return TokenType::LeftArrow;
  if (value == "PlusEqual") return TokenType::PlusEqual;
  if (value == "MinusEqual") return TokenType::MinusEqual;
  if (value == "StarEqual") return TokenType::StarEqual;
  if (value == "SlashEqual") return TokenType::SlashEqual;
  if (value == "BackslashEqual") return TokenType::BackslashEqual;
  if (value == "PercentEqual") return TokenType::PercentEqual;
  if (value == "StarStarEqual") return TokenType::StarStarEqual;
  if (value == "AmpersandEqual") return TokenType::AmpersandEqual;
  if (value == "PipeEqual") return TokenType::PipeEqual;
  if (value == "CaretEqual") return TokenType::CaretEqual;
  if (value == "LessLessEqual") return TokenType::LessLessEqual;
  if (value == "GreaterGreaterEqual") return TokenType::GreaterGreaterEqual;
  if (value == "QuestionQuestionEqual") return TokenType::QuestionQuestionEqual;
  if (value == "LeftParen") return TokenType::LeftParen;
  if (value == "RightParen") return TokenType::RightParen;
  if (value == "LeftBrace") return TokenType::LeftBrace;
  if (value == "RightBrace") return TokenType::RightBrace;
  if (value == "LeftBracket") return TokenType::LeftBracket;
  if (value == "RightBracket") return TokenType::RightBracket;
  if (value == "Dot") return TokenType::Dot;
  if (value == "DotDot") return TokenType::DotDot;
  if (value == "DotDotLess") return TokenType::DotDotLess;
  if (value == "Comma") return TokenType::Comma;
  if (value == "Colon") return TokenType::Colon;
  if (value == "DoubleColon") return TokenType::DoubleColon;
  if (value == "Semicolon") return TokenType::Semicolon;
  if (value == "RightArrow") return TokenType::RightArrow;
  if (value == "Arrow") return TokenType::Arrow;
  if (value == "QuestionDot") return TokenType::QuestionDot;
  if (value == "BangDot") return TokenType::BangDot;
  if (value == "QuestionBracket") return TokenType::QuestionBracket;
  if (value == "Underscore") return TokenType::Underscore;
  if (value == "DollarBrace") return TokenType::DollarBrace;
  if (value == "Ellipsis") return TokenType::Ellipsis;
  if (value == "EndOfFile") return TokenType::EndOfFile;
  return std::nullopt;
}
inline std::optional<TokenType> TokenType_fromValue(int32_t value) {
  switch (static_cast<TokenType>(value)) {
    case TokenType::IntLiteral: return TokenType::IntLiteral;
    case TokenType::LongLiteral: return TokenType::LongLiteral;
    case TokenType::FloatLiteral: return TokenType::FloatLiteral;
    case TokenType::DoubleLiteral: return TokenType::DoubleLiteral;
    case TokenType::StringLiteral: return TokenType::StringLiteral;
    case TokenType::CharLiteral: return TokenType::CharLiteral;
    case TokenType::TemplateLiteralStart: return TokenType::TemplateLiteralStart;
    case TokenType::TemplateLiteralMiddle: return TokenType::TemplateLiteralMiddle;
    case TokenType::TemplateLiteralEnd: return TokenType::TemplateLiteralEnd;
    case TokenType::Identifier: return TokenType::Identifier;
    case TokenType::CallerIntrinsic: return TokenType::CallerIntrinsic;
    case TokenType::Const: return TokenType::Const;
    case TokenType::Readonly: return TokenType::Readonly;
    case TokenType::Let: return TokenType::Let;
    case TokenType::Function: return TokenType::Function;
    case TokenType::Return: return TokenType::Return;
    case TokenType::Yield: return TokenType::Yield;
    case TokenType::If: return TokenType::If;
    case TokenType::Else: return TokenType::Else;
    case TokenType::Then: return TokenType::Then;
    case TokenType::While: return TokenType::While;
    case TokenType::For: return TokenType::For;
    case TokenType::Of: return TokenType::Of;
    case TokenType::Break: return TokenType::Break;
    case TokenType::Continue: return TokenType::Continue;
    case TokenType::Case: return TokenType::Case;
    case TokenType::Class: return TokenType::Class;
    case TokenType::Struct: return TokenType::Struct;
    case TokenType::Interface: return TokenType::Interface;
    case TokenType::Implements: return TokenType::Implements;
    case TokenType::Enum: return TokenType::Enum;
    case TokenType::Type: return TokenType::Type;
    case TokenType::Import: return TokenType::Import;
    case TokenType::Export: return TokenType::Export;
    case TokenType::From: return TokenType::From;
    case TokenType::As: return TokenType::As;
    case TokenType::True: return TokenType::True;
    case TokenType::False: return TokenType::False;
    case TokenType::Null: return TokenType::Null;
    case TokenType::Void: return TokenType::Void;
    case TokenType::Try: return TokenType::Try;
    case TokenType::Catch: return TokenType::Catch;
    case TokenType::Static: return TokenType::Static;
    case TokenType::This: return TokenType::This;
    case TokenType::Weak: return TokenType::Weak;
    case TokenType::Destructor: return TokenType::Destructor;
    case TokenType::Async: return TokenType::Async;
    case TokenType::Retire: return TokenType::Retire;
    case TokenType::Isolated: return TokenType::Isolated;
    case TokenType::Private: return TokenType::Private;
    case TokenType::With: return TokenType::With;
    case TokenType::Mock: return TokenType::Mock;
    case TokenType::Plus: return TokenType::Plus;
    case TokenType::Minus: return TokenType::Minus;
    case TokenType::Star: return TokenType::Star;
    case TokenType::Slash: return TokenType::Slash;
    case TokenType::Backslash: return TokenType::Backslash;
    case TokenType::Percent: return TokenType::Percent;
    case TokenType::StarStar: return TokenType::StarStar;
    case TokenType::Ampersand: return TokenType::Ampersand;
    case TokenType::Pipe: return TokenType::Pipe;
    case TokenType::Caret: return TokenType::Caret;
    case TokenType::Tilde: return TokenType::Tilde;
    case TokenType::LessLess: return TokenType::LessLess;
    case TokenType::GreaterGreater: return TokenType::GreaterGreater;
    case TokenType::GreaterGreaterGreater: return TokenType::GreaterGreaterGreater;
    case TokenType::AmpersandAmpersand: return TokenType::AmpersandAmpersand;
    case TokenType::PipePipe: return TokenType::PipePipe;
    case TokenType::Bang: return TokenType::Bang;
    case TokenType::QuestionQuestion: return TokenType::QuestionQuestion;
    case TokenType::EqualEqual: return TokenType::EqualEqual;
    case TokenType::BangEqual: return TokenType::BangEqual;
    case TokenType::Less: return TokenType::Less;
    case TokenType::LessEqual: return TokenType::LessEqual;
    case TokenType::Greater: return TokenType::Greater;
    case TokenType::GreaterEqual: return TokenType::GreaterEqual;
    case TokenType::Equal: return TokenType::Equal;
    case TokenType::ColonEqual: return TokenType::ColonEqual;
    case TokenType::LeftArrow: return TokenType::LeftArrow;
    case TokenType::PlusEqual: return TokenType::PlusEqual;
    case TokenType::MinusEqual: return TokenType::MinusEqual;
    case TokenType::StarEqual: return TokenType::StarEqual;
    case TokenType::SlashEqual: return TokenType::SlashEqual;
    case TokenType::BackslashEqual: return TokenType::BackslashEqual;
    case TokenType::PercentEqual: return TokenType::PercentEqual;
    case TokenType::StarStarEqual: return TokenType::StarStarEqual;
    case TokenType::AmpersandEqual: return TokenType::AmpersandEqual;
    case TokenType::PipeEqual: return TokenType::PipeEqual;
    case TokenType::CaretEqual: return TokenType::CaretEqual;
    case TokenType::LessLessEqual: return TokenType::LessLessEqual;
    case TokenType::GreaterGreaterEqual: return TokenType::GreaterGreaterEqual;
    case TokenType::QuestionQuestionEqual: return TokenType::QuestionQuestionEqual;
    case TokenType::LeftParen: return TokenType::LeftParen;
    case TokenType::RightParen: return TokenType::RightParen;
    case TokenType::LeftBrace: return TokenType::LeftBrace;
    case TokenType::RightBrace: return TokenType::RightBrace;
    case TokenType::LeftBracket: return TokenType::LeftBracket;
    case TokenType::RightBracket: return TokenType::RightBracket;
    case TokenType::Dot: return TokenType::Dot;
    case TokenType::DotDot: return TokenType::DotDot;
    case TokenType::DotDotLess: return TokenType::DotDotLess;
    case TokenType::Comma: return TokenType::Comma;
    case TokenType::Colon: return TokenType::Colon;
    case TokenType::DoubleColon: return TokenType::DoubleColon;
    case TokenType::Semicolon: return TokenType::Semicolon;
    case TokenType::RightArrow: return TokenType::RightArrow;
    case TokenType::Arrow: return TokenType::Arrow;
    case TokenType::QuestionDot: return TokenType::QuestionDot;
    case TokenType::BangDot: return TokenType::BangDot;
    case TokenType::QuestionBracket: return TokenType::QuestionBracket;
    case TokenType::Underscore: return TokenType::Underscore;
    case TokenType::DollarBrace: return TokenType::DollarBrace;
    case TokenType::Ellipsis: return TokenType::Ellipsis;
    case TokenType::EndOfFile: return TokenType::EndOfFile;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, TokenType value) { return output << TokenType_name(value); }
    struct Token {
    TokenType kind;
    int32_t length;
    int32_t valueOffset;
    int32_t valueLength;
    bool needsDecode;
    int32_t line;
    int32_t column;
    int32_t offset;
    Token(TokenType kind, int32_t length, int32_t valueOffset, int32_t valueLength, bool needsDecode, int32_t line, int32_t column, int32_t offset) : kind(kind), length(length), valueOffset(valueOffset), valueLength(valueLength), needsDecode(needsDecode), line(line), column(column), offset(offset) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<Token, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct Lexer : public std::enable_shared_from_this<Lexer> {
    std::string source;
    int32_t pos = 0;
    int32_t line = 1;
    int32_t column = 1;
    std::shared_ptr<std::vector<Token>> tokens = std::make_shared<std::vector<Token>>(std::vector<Token>{});
    std::shared_ptr<std::vector<LexerDiagnostic>> diagnostics = std::make_shared<std::vector<LexerDiagnostic>>(std::vector<LexerDiagnostic>{});
    std::shared_ptr<std::vector<char32_t>> templateDelimiters = std::make_shared<std::vector<char32_t>>(std::vector<char32_t>{});
    std::shared_ptr<std::vector<int32_t>> braceDepth = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
    Lexer(std::string source, int32_t pos = 0, int32_t line = 1, int32_t column = 1, std::shared_ptr<std::vector<Token>> tokens = std::make_shared<std::vector<Token>>(std::vector<Token>{}), std::shared_ptr<std::vector<LexerDiagnostic>> diagnostics = std::make_shared<std::vector<LexerDiagnostic>>(std::vector<LexerDiagnostic>{}), std::shared_ptr<std::vector<char32_t>> templateDelimiters = std::make_shared<std::vector<char32_t>>(std::vector<char32_t>{}), std::shared_ptr<std::vector<int32_t>> braceDepth = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{})) : source(source), pos(pos), line(line), column(column), tokens(tokens), diagnostics(diagnostics), templateDelimiters(templateDelimiters), braceDepth(braceDepth) {}
    std::shared_ptr<std::vector<Token>> tokenize();
    char32_t peek(int32_t offset = 0);
    char32_t advance();
    void addToken(TokenType kind, int32_t tokenOffset, int32_t tokenLength, int32_t valueOffset, int32_t valueLength, bool needsDecode, int32_t tokenLine, int32_t tokenColumn);
    void diagnostic(std::string message, int32_t diagnosticLine, int32_t diagnosticColumn);
    void skipWhitespaceAndComments();
    bool isDigit(char32_t ch);
    bool isHexDigit(char32_t ch);
    bool isBaseDigit(char32_t ch, int32_t base);
    bool isIdentStart(char32_t ch);
    bool isIdentPart(char32_t ch);
    void readDigits(int32_t base);
    void readNumber();
    void readNumericSuffix(int32_t valueStart, int32_t valueEnd, int32_t tokenLine, int32_t tokenColumn);
    void readIdentifier();
    void readQuoted(char32_t delimiter);
    void readTemplateContinuation();
    void readChar();
    void emit(TokenType kind, int32_t tokenLine, int32_t tokenColumn, int32_t start, int32_t count);
    void readOperatorOrPunctuation();
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<Lexer>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::string decodeEscapeCharacter(char32_t escaped);
    std::string tokenValue(Token token, std::string source);
    TokenType keywordType(std::string word);
}

namespace app_src_lexer_ {
}

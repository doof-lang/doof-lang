#pragma once
#include "doof_runtime.hpp"
namespace app_src_lexer_ { enum class TokenType; }
namespace app_src_lexer_ { struct Token; }
namespace app_src_lexer_ { struct LexerDiagnostic; }
namespace app_src_lexer_ { struct Lexer; }

namespace app_src_lexer_ {
    struct Token;
    struct LexerDiagnostic;
    struct Lexer;
}

namespace app_src_lexer_ {
    enum class TokenType {
    IntLiteral = 0,
    LongLiteral = 1,
    FloatLiteral = 2,
    DoubleLiteral = 3,
    StringLiteral = 4,
    CharLiteral = 5,
    TemplateLiteralStart = 6,
    TemplateLiteralMiddle = 7,
    TemplateLiteralEnd = 8,
    Identifier = 9,
    CallerIntrinsic = 10,
    Const = 11,
    Readonly = 12,
    Let = 13,
    Function = 14,
    Return = 15,
    Yield = 16,
    If = 17,
    Else = 18,
    Then = 19,
    While = 20,
    For = 21,
    Of = 22,
    Break = 23,
    Continue = 24,
    Case = 25,
    Class = 26,
    Struct = 27,
    Interface = 28,
    Implements = 29,
    Enum = 30,
    Type = 31,
    Import = 32,
    Export = 33,
    From = 34,
    As = 35,
    True = 36,
    False = 37,
    None = 38,
    Null = 39,
    Void = 40,
    Try = 41,
    Catch = 42,
    Static = 43,
    This = 44,
    Weak = 45,
    Destructor = 46,
    Async = 47,
    Retire = 48,
    Isolated = 49,
    Private = 50,
    With = 51,
    Mock = 52,
    Plus = 53,
    Minus = 54,
    Star = 55,
    Slash = 56,
    Backslash = 57,
    Percent = 58,
    StarStar = 59,
    Ampersand = 60,
    Pipe = 61,
    Caret = 62,
    Tilde = 63,
    LessLess = 64,
    GreaterGreater = 65,
    GreaterGreaterGreater = 66,
    AmpersandAmpersand = 67,
    PipePipe = 68,
    Bang = 69,
    QuestionQuestion = 70,
    EqualEqual = 71,
    BangEqual = 72,
    Less = 73,
    LessEqual = 74,
    Greater = 75,
    GreaterEqual = 76,
    Equal = 77,
    ColonEqual = 78,
    LeftArrow = 79,
    PlusEqual = 80,
    MinusEqual = 81,
    StarEqual = 82,
    SlashEqual = 83,
    BackslashEqual = 84,
    PercentEqual = 85,
    StarStarEqual = 86,
    AmpersandEqual = 87,
    PipeEqual = 88,
    CaretEqual = 89,
    LessLessEqual = 90,
    GreaterGreaterEqual = 91,
    QuestionQuestionEqual = 92,
    LeftParen = 93,
    RightParen = 94,
    LeftBrace = 95,
    RightBrace = 96,
    LeftBracket = 97,
    RightBracket = 98,
    Dot = 99,
    DotDot = 100,
    DotDotLess = 101,
    Comma = 102,
    Colon = 103,
    DoubleColon = 104,
    Semicolon = 105,
    RightArrow = 106,
    Arrow = 107,
    QuestionDot = 108,
    BangDot = 109,
    QuestionBracket = 110,
    Underscore = 111,
    DollarBrace = 112,
    TagOpen = 113,
    TagText = 114,
    Ellipsis = 115,
    EndOfFile = 116
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
    case TokenType::None: return "None";
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
    case TokenType::TagOpen: return "TagOpen";
    case TokenType::TagText: return "TagText";
    case TokenType::Ellipsis: return "Ellipsis";
    case TokenType::EndOfFile: return "EndOfFile";
  }
  doof::panic(std::string("Invalid TokenType enum value: ") + doof::to_string(static_cast<int32_t>(value)));
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
  if (value == "None") return TokenType::None;
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
  if (value == "TagOpen") return TokenType::TagOpen;
  if (value == "TagText") return TokenType::TagText;
  if (value == "Ellipsis") return TokenType::Ellipsis;
  if (value == "EndOfFile") return TokenType::EndOfFile;
  return std::nullopt;
}
inline int32_t TokenType_value(TokenType value) { return static_cast<int32_t>(value); }
inline std::optional<TokenType> TokenType_fromValue(int32_t value) {
  if (value == 0) return TokenType::IntLiteral;
  if (value == 1) return TokenType::LongLiteral;
  if (value == 2) return TokenType::FloatLiteral;
  if (value == 3) return TokenType::DoubleLiteral;
  if (value == 4) return TokenType::StringLiteral;
  if (value == 5) return TokenType::CharLiteral;
  if (value == 6) return TokenType::TemplateLiteralStart;
  if (value == 7) return TokenType::TemplateLiteralMiddle;
  if (value == 8) return TokenType::TemplateLiteralEnd;
  if (value == 9) return TokenType::Identifier;
  if (value == 10) return TokenType::CallerIntrinsic;
  if (value == 11) return TokenType::Const;
  if (value == 12) return TokenType::Readonly;
  if (value == 13) return TokenType::Let;
  if (value == 14) return TokenType::Function;
  if (value == 15) return TokenType::Return;
  if (value == 16) return TokenType::Yield;
  if (value == 17) return TokenType::If;
  if (value == 18) return TokenType::Else;
  if (value == 19) return TokenType::Then;
  if (value == 20) return TokenType::While;
  if (value == 21) return TokenType::For;
  if (value == 22) return TokenType::Of;
  if (value == 23) return TokenType::Break;
  if (value == 24) return TokenType::Continue;
  if (value == 25) return TokenType::Case;
  if (value == 26) return TokenType::Class;
  if (value == 27) return TokenType::Struct;
  if (value == 28) return TokenType::Interface;
  if (value == 29) return TokenType::Implements;
  if (value == 30) return TokenType::Enum;
  if (value == 31) return TokenType::Type;
  if (value == 32) return TokenType::Import;
  if (value == 33) return TokenType::Export;
  if (value == 34) return TokenType::From;
  if (value == 35) return TokenType::As;
  if (value == 36) return TokenType::True;
  if (value == 37) return TokenType::False;
  if (value == 38) return TokenType::None;
  if (value == 39) return TokenType::Null;
  if (value == 40) return TokenType::Void;
  if (value == 41) return TokenType::Try;
  if (value == 42) return TokenType::Catch;
  if (value == 43) return TokenType::Static;
  if (value == 44) return TokenType::This;
  if (value == 45) return TokenType::Weak;
  if (value == 46) return TokenType::Destructor;
  if (value == 47) return TokenType::Async;
  if (value == 48) return TokenType::Retire;
  if (value == 49) return TokenType::Isolated;
  if (value == 50) return TokenType::Private;
  if (value == 51) return TokenType::With;
  if (value == 52) return TokenType::Mock;
  if (value == 53) return TokenType::Plus;
  if (value == 54) return TokenType::Minus;
  if (value == 55) return TokenType::Star;
  if (value == 56) return TokenType::Slash;
  if (value == 57) return TokenType::Backslash;
  if (value == 58) return TokenType::Percent;
  if (value == 59) return TokenType::StarStar;
  if (value == 60) return TokenType::Ampersand;
  if (value == 61) return TokenType::Pipe;
  if (value == 62) return TokenType::Caret;
  if (value == 63) return TokenType::Tilde;
  if (value == 64) return TokenType::LessLess;
  if (value == 65) return TokenType::GreaterGreater;
  if (value == 66) return TokenType::GreaterGreaterGreater;
  if (value == 67) return TokenType::AmpersandAmpersand;
  if (value == 68) return TokenType::PipePipe;
  if (value == 69) return TokenType::Bang;
  if (value == 70) return TokenType::QuestionQuestion;
  if (value == 71) return TokenType::EqualEqual;
  if (value == 72) return TokenType::BangEqual;
  if (value == 73) return TokenType::Less;
  if (value == 74) return TokenType::LessEqual;
  if (value == 75) return TokenType::Greater;
  if (value == 76) return TokenType::GreaterEqual;
  if (value == 77) return TokenType::Equal;
  if (value == 78) return TokenType::ColonEqual;
  if (value == 79) return TokenType::LeftArrow;
  if (value == 80) return TokenType::PlusEqual;
  if (value == 81) return TokenType::MinusEqual;
  if (value == 82) return TokenType::StarEqual;
  if (value == 83) return TokenType::SlashEqual;
  if (value == 84) return TokenType::BackslashEqual;
  if (value == 85) return TokenType::PercentEqual;
  if (value == 86) return TokenType::StarStarEqual;
  if (value == 87) return TokenType::AmpersandEqual;
  if (value == 88) return TokenType::PipeEqual;
  if (value == 89) return TokenType::CaretEqual;
  if (value == 90) return TokenType::LessLessEqual;
  if (value == 91) return TokenType::GreaterGreaterEqual;
  if (value == 92) return TokenType::QuestionQuestionEqual;
  if (value == 93) return TokenType::LeftParen;
  if (value == 94) return TokenType::RightParen;
  if (value == 95) return TokenType::LeftBrace;
  if (value == 96) return TokenType::RightBrace;
  if (value == 97) return TokenType::LeftBracket;
  if (value == 98) return TokenType::RightBracket;
  if (value == 99) return TokenType::Dot;
  if (value == 100) return TokenType::DotDot;
  if (value == 101) return TokenType::DotDotLess;
  if (value == 102) return TokenType::Comma;
  if (value == 103) return TokenType::Colon;
  if (value == 104) return TokenType::DoubleColon;
  if (value == 105) return TokenType::Semicolon;
  if (value == 106) return TokenType::RightArrow;
  if (value == 107) return TokenType::Arrow;
  if (value == 108) return TokenType::QuestionDot;
  if (value == 109) return TokenType::BangDot;
  if (value == 110) return TokenType::QuestionBracket;
  if (value == 111) return TokenType::Underscore;
  if (value == 112) return TokenType::DollarBrace;
  if (value == 113) return TokenType::TagOpen;
  if (value == 114) return TokenType::TagText;
  if (value == 115) return TokenType::Ellipsis;
  if (value == 116) return TokenType::EndOfFile;
  return std::nullopt;
}
inline std::shared_ptr<std::vector<TokenType>> TokenType_values() { return std::make_shared<std::vector<TokenType>>(std::initializer_list<TokenType>{TokenType::IntLiteral, TokenType::LongLiteral, TokenType::FloatLiteral, TokenType::DoubleLiteral, TokenType::StringLiteral, TokenType::CharLiteral, TokenType::TemplateLiteralStart, TokenType::TemplateLiteralMiddle, TokenType::TemplateLiteralEnd, TokenType::Identifier, TokenType::CallerIntrinsic, TokenType::Const, TokenType::Readonly, TokenType::Let, TokenType::Function, TokenType::Return, TokenType::Yield, TokenType::If, TokenType::Else, TokenType::Then, TokenType::While, TokenType::For, TokenType::Of, TokenType::Break, TokenType::Continue, TokenType::Case, TokenType::Class, TokenType::Struct, TokenType::Interface, TokenType::Implements, TokenType::Enum, TokenType::Type, TokenType::Import, TokenType::Export, TokenType::From, TokenType::As, TokenType::True, TokenType::False, TokenType::None, TokenType::Null, TokenType::Void, TokenType::Try, TokenType::Catch, TokenType::Static, TokenType::This, TokenType::Weak, TokenType::Destructor, TokenType::Async, TokenType::Retire, TokenType::Isolated, TokenType::Private, TokenType::With, TokenType::Mock, TokenType::Plus, TokenType::Minus, TokenType::Star, TokenType::Slash, TokenType::Backslash, TokenType::Percent, TokenType::StarStar, TokenType::Ampersand, TokenType::Pipe, TokenType::Caret, TokenType::Tilde, TokenType::LessLess, TokenType::GreaterGreater, TokenType::GreaterGreaterGreater, TokenType::AmpersandAmpersand, TokenType::PipePipe, TokenType::Bang, TokenType::QuestionQuestion, TokenType::EqualEqual, TokenType::BangEqual, TokenType::Less, TokenType::LessEqual, TokenType::Greater, TokenType::GreaterEqual, TokenType::Equal, TokenType::ColonEqual, TokenType::LeftArrow, TokenType::PlusEqual, TokenType::MinusEqual, TokenType::StarEqual, TokenType::SlashEqual, TokenType::BackslashEqual, TokenType::PercentEqual, TokenType::StarStarEqual, TokenType::AmpersandEqual, TokenType::PipeEqual, TokenType::CaretEqual, TokenType::LessLessEqual, TokenType::GreaterGreaterEqual, TokenType::QuestionQuestionEqual, TokenType::LeftParen, TokenType::RightParen, TokenType::LeftBrace, TokenType::RightBrace, TokenType::LeftBracket, TokenType::RightBracket, TokenType::Dot, TokenType::DotDot, TokenType::DotDotLess, TokenType::Comma, TokenType::Colon, TokenType::DoubleColon, TokenType::Semicolon, TokenType::RightArrow, TokenType::Arrow, TokenType::QuestionDot, TokenType::BangDot, TokenType::QuestionBracket, TokenType::Underscore, TokenType::DollarBrace, TokenType::TagOpen, TokenType::TagText, TokenType::Ellipsis, TokenType::EndOfFile}); }
inline doof::JsonValue TokenType_toJsonValue(TokenType value) { return doof::json_value(TokenType_value(value)); }
inline doof::Result<TokenType, std::string> TokenType_fromJsonValue(const doof::JsonValue& value, bool) {
  if (!(doof::json_is_integer(value))) return doof::Failure<std::string>{std::string("Expected integer for enum TokenType, got ") + doof::json_type_name(value)};
  auto resolved = TokenType_fromValue(doof::json_as_int(value));
  if (!resolved.has_value()) return doof::Failure<std::string>{std::string("Unknown backing value for enum TokenType: ") + doof::to_string(doof::json_as_int(value)) + "; expected one of 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116"};
  return doof::Success<TokenType>{resolved.value()};
}
inline std::ostream& operator<<(std::ostream& output, TokenType value) { return output << TokenType_name(value); }
}

namespace app_src_lexer_ {
    struct LexerDiagnostic {
    std::string severity;
    std::string message;
    int32_t line;
    int32_t column;
    LexerDiagnostic(std::string severity, std::string message, int32_t line, int32_t column) : severity(severity), message(message), line(line), column(column) {}
    LexerDiagnostic() {}
    template <typename _DoofOther = LexerDiagnostic>
    bool operator==(const _DoofOther& _doof_other) const { return (this->severity == _doof_other.severity) && (this->message == _doof_other.message) && (this->line == _doof_other.line) && (this->column == _doof_other.column); }
    template <typename _DoofOther = LexerDiagnostic>
    bool operator!=(const _DoofOther& _doof_other) const { return !(*this == _doof_other); }
};
}

namespace doof { using TokenType = ::app_src_lexer_::TokenType; }
namespace doof { using Token = ::app_src_lexer_::Token; }
namespace doof { using LexerDiagnostic = ::app_src_lexer_::LexerDiagnostic; }
namespace doof { using Lexer = ::app_src_lexer_::Lexer; }
#include "doof_runtime.hpp"

namespace app_src_lexer_ {
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
    Token() {}
    template <typename _DoofOther = Token>
    bool operator==(const _DoofOther& _doof_other) const { return (this->kind == _doof_other.kind) && (this->length == _doof_other.length) && (this->valueOffset == _doof_other.valueOffset) && (this->valueLength == _doof_other.valueLength) && (this->needsDecode == _doof_other.needsDecode) && (this->line == _doof_other.line) && (this->column == _doof_other.column) && (this->offset == _doof_other.offset); }
    template <typename _DoofOther = Token>
    bool operator!=(const _DoofOther& _doof_other) const { return !(*this == _doof_other); }
};
    struct Lexer : public std::enable_shared_from_this<Lexer> {
    std::string source;
    int32_t pos;
    int32_t line;
    int32_t column;
    std::shared_ptr<std::vector<Token>> tokens;
    std::shared_ptr<std::vector<LexerDiagnostic>> diagnostics;
    std::shared_ptr<std::vector<char32_t>> templateDelimiters;
    std::shared_ptr<std::vector<int32_t>> braceDepth;
    std::shared_ptr<std::vector<int32_t>> interpolationLines;
    std::shared_ptr<std::vector<int32_t>> interpolationColumns;
    std::string tagMode;
    std::shared_ptr<std::vector<std::string>> tagModeStack;
    std::shared_ptr<std::vector<int32_t>> tagExpressionDepths;
    int32_t tagGenericDepth;
    int32_t tagAttributeDelimiterDepth;
    Lexer(std::string source, int32_t pos, int32_t line, int32_t column, std::shared_ptr<std::vector<Token>> tokens, std::shared_ptr<std::vector<LexerDiagnostic>> diagnostics, std::shared_ptr<std::vector<char32_t>> templateDelimiters, std::shared_ptr<std::vector<int32_t>> braceDepth, std::shared_ptr<std::vector<int32_t>> interpolationLines, std::shared_ptr<std::vector<int32_t>> interpolationColumns, std::string tagMode, std::shared_ptr<std::vector<std::string>> tagModeStack, std::shared_ptr<std::vector<int32_t>> tagExpressionDepths, int32_t tagGenericDepth, int32_t tagAttributeDelimiterDepth) : source(source), pos(pos), line(line), column(column), tokens(tokens), diagnostics(diagnostics), templateDelimiters(templateDelimiters), braceDepth(braceDepth), interpolationLines(interpolationLines), interpolationColumns(interpolationColumns), tagMode(tagMode), tagModeStack(tagModeStack), tagExpressionDepths(tagExpressionDepths), tagGenericDepth(tagGenericDepth), tagAttributeDelimiterDepth(tagAttributeDelimiterDepth) {}
    std::shared_ptr<std::vector<Token>> tokenize();
    void beginTag();
    void beginTagExpression();
    void readTagText();
    bool canStartTag();
    char32_t peek(int32_t offset);
    char32_t advance();
    void addToken(TokenType kind, int32_t tokenOffset, int32_t tokenLength, int32_t valueOffset, int32_t valueLength, bool needsDecode, int32_t tokenLine, int32_t tokenColumn);
    void diagnostic(const std::string& message, int32_t diagnosticLine, int32_t diagnosticColumn);
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
};
    std::string decodeEscapeCharacter(char32_t escaped);
    std::string tokenValue(Token token, const std::string& source);
    int32_t utf8SequenceLength(char32_t first);
    char32_t charTokenValue(Token token, const std::string& source);
    TokenType keywordType(const std::string& word);
}

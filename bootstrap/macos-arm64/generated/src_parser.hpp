#pragma once
#include "doof_runtime.hpp"
namespace app_src_lexer_ {
    struct Token;
    struct LexerDiagnostic;
    struct Lexer;
}

namespace app_src_semantic_ {
    struct SemanticLocation;
    struct SemanticSpan;
    struct Symbol;
    struct PrimitiveType;
    struct ClassType;
    struct EnumType;
    struct InterfaceType;
    struct FunctionType;
    struct FunctionParamType;
    struct ActorType;
    struct PromiseType;
    struct ArrayResolvedType;
    struct MapResolvedType;
    struct SetResolvedType;
    struct StreamResolvedType;
    struct RangeResolvedType;
    struct JsonValueResolvedType;
    struct ResultResolvedType;
    struct TupleResolvedType;
    struct UnionResolvedType;
    struct WeakResolvedType;
    struct NoneType;
    struct NeverType;
    struct UnknownType;
    struct TypeParameterType;
    struct ClassMetadataResolvedType;
    struct MethodReflectionResolvedType;
    struct Binding;
}

namespace app_src_ast_ {
    struct AstLocation;
    struct SourceSpan;
    struct NamedType;
    struct ArrayType;
    struct UnionType;
    struct AstFunctionType;
    struct WeakType;
    struct FunctionTypeParam;
    struct IntLiteral;
    struct LongLiteral;
    struct FloatLiteral;
    struct DoubleLiteral;
    struct StringLiteral;
    struct CharLiteral;
    struct BoolLiteral;
    struct NoneLiteral;
    struct Identifier;
    struct BinaryExpression;
    struct UnaryExpression;
    struct AssignmentExpression;
    struct MemberExpression;
    struct IndexExpression;
    struct CallArgument;
    struct CallExpression;
    struct ArrayLiteral;
    struct ObjectProperty;
    struct ObjectLiteral;
    struct TupleLiteral;
    struct LambdaExpression;
    struct IfExpression;
    struct ConstructExpression;
    struct DotShorthand;
    struct ThisExpression;
    struct CallerExpression;
    struct AsyncExpression;
    struct RetireExpression;
    struct AsExpression;
    struct ActorCreationExpression;
    struct YieldBlockExpression;
    struct CatchExpression;
    struct Parameter;
    struct Block;
    struct ConstDeclaration;
    struct ReadonlyDeclaration;
    struct ImmutableBinding;
    struct LetDeclaration;
    struct FunctionDeclaration;
    struct TypeParameterConstraint;
    struct ReturnStatement;
    struct YieldStatement;
    struct YieldBlockAssignmentStatement;
    struct IfStatement;
    struct CaseExpression;
    struct CaseStatement;
    struct CaseArm;
    struct CaseExpressionArm;
    struct TypePattern;
    struct WildcardPattern;
    struct ValuePattern;
    struct RangePattern;
    struct IfBranch;
    struct WhileStatement;
    struct ForStatement;
    struct ForOfStatement;
    struct WithBinding;
    struct WithStatement;
    struct BreakStatement;
    struct ContinueStatement;
    struct ExpressionStatement;
    struct DestructuringStatement;
    struct DestructureBinding;
    struct TryStatement;
    struct ClassDeclaration;
    struct ClassField;
    struct InterfaceDeclaration;
    struct InterfaceField;
    struct EnumDeclaration;
    struct EnumVariant;
    struct TypeAliasDeclaration;
    struct NamedImport;
    struct NamespaceImport;
    struct ImportDeclaration;
    struct MockImportMapping;
    struct MockImportDirective;
    struct ExportDeclaration;
    struct ExportSpecifier;
    struct ExportList;
    struct Program;
}

namespace app_src_parser_ {
    struct Parser;
}

namespace app_src_semantic_ {
    using doof_header_type_1 = std::variant<std::monostate, std::shared_ptr<PrimitiveType>, std::shared_ptr<ClassType>, std::shared_ptr<EnumType>, std::shared_ptr<InterfaceType>, std::shared_ptr<FunctionType>, std::shared_ptr<ActorType>, std::shared_ptr<PromiseType>, std::shared_ptr<ArrayResolvedType>, std::shared_ptr<MapResolvedType>, std::shared_ptr<SetResolvedType>, std::shared_ptr<StreamResolvedType>, std::shared_ptr<RangeResolvedType>, std::shared_ptr<JsonValueResolvedType>, std::shared_ptr<ResultResolvedType>, std::shared_ptr<TupleResolvedType>, std::shared_ptr<UnionResolvedType>, std::shared_ptr<WeakResolvedType>, std::shared_ptr<NoneType>, std::shared_ptr<NeverType>, std::shared_ptr<UnknownType>, std::shared_ptr<TypeParameterType>, std::shared_ptr<ClassMetadataResolvedType>, std::shared_ptr<MethodReflectionResolvedType>>;
}

namespace app_src_ast_ {
    using doof_header_type_2 = std::variant<std::monostate, std::shared_ptr<NamedType>, std::shared_ptr<ArrayType>, std::shared_ptr<UnionType>, std::shared_ptr<AstFunctionType>, std::shared_ptr<WeakType>>;
    using doof_header_type_3 = std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>;
    using doof_header_type_4 = std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>;
    using doof_header_type_5 = std::variant<std::monostate, std::shared_ptr<IntLiteral>, std::shared_ptr<LongLiteral>, std::shared_ptr<FloatLiteral>, std::shared_ptr<DoubleLiteral>, std::shared_ptr<StringLiteral>, std::shared_ptr<CharLiteral>, std::shared_ptr<BoolLiteral>, std::shared_ptr<NoneLiteral>, std::shared_ptr<Identifier>, std::shared_ptr<BinaryExpression>, std::shared_ptr<UnaryExpression>, std::shared_ptr<AssignmentExpression>, std::shared_ptr<MemberExpression>, std::shared_ptr<IndexExpression>, std::shared_ptr<CallExpression>, std::shared_ptr<ArrayLiteral>, std::shared_ptr<ObjectLiteral>, std::shared_ptr<TupleLiteral>, std::shared_ptr<LambdaExpression>, std::shared_ptr<IfExpression>, std::shared_ptr<CaseExpression>, std::shared_ptr<ConstructExpression>, std::shared_ptr<DotShorthand>, std::shared_ptr<ThisExpression>, std::shared_ptr<CallerExpression>, std::shared_ptr<AsyncExpression>, std::shared_ptr<RetireExpression>, std::shared_ptr<AsExpression>, std::shared_ptr<ActorCreationExpression>, std::shared_ptr<YieldBlockExpression>, std::shared_ptr<CatchExpression>>;
    using doof_header_type_6 = std::variant<std::shared_ptr<IntLiteral>, std::shared_ptr<LongLiteral>, std::shared_ptr<FloatLiteral>, std::shared_ptr<DoubleLiteral>, std::shared_ptr<StringLiteral>, std::shared_ptr<CharLiteral>, std::shared_ptr<BoolLiteral>, std::shared_ptr<NoneLiteral>, std::shared_ptr<Identifier>, std::shared_ptr<BinaryExpression>, std::shared_ptr<UnaryExpression>, std::shared_ptr<AssignmentExpression>, std::shared_ptr<MemberExpression>, std::shared_ptr<IndexExpression>, std::shared_ptr<CallExpression>, std::shared_ptr<ArrayLiteral>, std::shared_ptr<ObjectLiteral>, std::shared_ptr<TupleLiteral>, std::shared_ptr<LambdaExpression>, std::shared_ptr<IfExpression>, std::shared_ptr<CaseExpression>, std::shared_ptr<ConstructExpression>, std::shared_ptr<DotShorthand>, std::shared_ptr<ThisExpression>, std::shared_ptr<CallerExpression>, std::shared_ptr<AsyncExpression>, std::shared_ptr<RetireExpression>, std::shared_ptr<AsExpression>, std::shared_ptr<ActorCreationExpression>, std::shared_ptr<YieldBlockExpression>, std::shared_ptr<CatchExpression>, std::shared_ptr<Block>>;
    using doof_header_type_7 = std::variant<std::monostate, std::shared_ptr<ConstDeclaration>, std::shared_ptr<ReadonlyDeclaration>, std::shared_ptr<ImmutableBinding>, std::shared_ptr<LetDeclaration>, std::shared_ptr<FunctionDeclaration>, std::shared_ptr<ClassDeclaration>, std::shared_ptr<InterfaceDeclaration>, std::shared_ptr<EnumDeclaration>, std::shared_ptr<TypeAliasDeclaration>, std::shared_ptr<ImportDeclaration>, std::shared_ptr<MockImportDirective>, std::shared_ptr<ExportDeclaration>, std::shared_ptr<ExportList>, std::shared_ptr<IfStatement>, std::shared_ptr<CaseStatement>, std::shared_ptr<WhileStatement>, std::shared_ptr<ForStatement>, std::shared_ptr<ForOfStatement>, std::shared_ptr<WithStatement>, std::shared_ptr<ReturnStatement>, std::shared_ptr<YieldStatement>, std::shared_ptr<BreakStatement>, std::shared_ptr<ContinueStatement>, std::shared_ptr<ExpressionStatement>, std::shared_ptr<DestructuringStatement>, std::shared_ptr<TryStatement>, std::shared_ptr<YieldBlockAssignmentStatement>, std::shared_ptr<Block>>;
    using doof_header_type_8 = std::variant<std::shared_ptr<ConstDeclaration>, std::shared_ptr<ReadonlyDeclaration>, std::shared_ptr<ImmutableBinding>, std::shared_ptr<LetDeclaration>, std::shared_ptr<ExpressionStatement>, std::shared_ptr<DestructuringStatement>>;
}

namespace app_src_parser_declarations_ {
    using doof_header_type_9 = std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>;
}

namespace app_src_parser_statements_ {
    using doof_header_type_10 = std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>;
}

namespace app_src_parser_expressions_ {
    using doof_header_type_11 = std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>;
}

namespace app_src_parser_ {
    using doof_header_type_12 = std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>;
    using doof_header_type_13 = std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>;
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

namespace app_src_semantic_ {
    using ResolvedType = std::variant<std::shared_ptr<PrimitiveType>, std::shared_ptr<ClassType>, std::shared_ptr<EnumType>, std::shared_ptr<InterfaceType>, std::shared_ptr<FunctionType>, std::shared_ptr<ActorType>, std::shared_ptr<PromiseType>, std::shared_ptr<ArrayResolvedType>, std::shared_ptr<MapResolvedType>, std::shared_ptr<SetResolvedType>, std::shared_ptr<StreamResolvedType>, std::shared_ptr<RangeResolvedType>, std::shared_ptr<JsonValueResolvedType>, std::shared_ptr<ResultResolvedType>, std::shared_ptr<TupleResolvedType>, std::shared_ptr<UnionResolvedType>, std::shared_ptr<WeakResolvedType>, std::shared_ptr<NoneType>, std::shared_ptr<NeverType>, std::shared_ptr<UnknownType>, std::shared_ptr<TypeParameterType>, std::shared_ptr<ClassMetadataResolvedType>, std::shared_ptr<MethodReflectionResolvedType>>;
}

namespace app_src_ast_ {
    using TypeAnnotation = std::variant<std::shared_ptr<NamedType>, std::shared_ptr<ArrayType>, std::shared_ptr<UnionType>, std::shared_ptr<AstFunctionType>, std::shared_ptr<WeakType>>;
    using Expression = std::variant<std::shared_ptr<IntLiteral>, std::shared_ptr<LongLiteral>, std::shared_ptr<FloatLiteral>, std::shared_ptr<DoubleLiteral>, std::shared_ptr<StringLiteral>, std::shared_ptr<CharLiteral>, std::shared_ptr<BoolLiteral>, std::shared_ptr<NoneLiteral>, std::shared_ptr<Identifier>, std::shared_ptr<BinaryExpression>, std::shared_ptr<UnaryExpression>, std::shared_ptr<AssignmentExpression>, std::shared_ptr<MemberExpression>, std::shared_ptr<IndexExpression>, std::shared_ptr<CallExpression>, std::shared_ptr<ArrayLiteral>, std::shared_ptr<ObjectLiteral>, std::shared_ptr<TupleLiteral>, std::shared_ptr<LambdaExpression>, std::shared_ptr<IfExpression>, std::shared_ptr<CaseExpression>, std::shared_ptr<ConstructExpression>, std::shared_ptr<DotShorthand>, std::shared_ptr<ThisExpression>, std::shared_ptr<CallerExpression>, std::shared_ptr<AsyncExpression>, std::shared_ptr<RetireExpression>, std::shared_ptr<AsExpression>, std::shared_ptr<ActorCreationExpression>, std::shared_ptr<YieldBlockExpression>, std::shared_ptr<CatchExpression>>;
    using CasePattern = std::variant<std::shared_ptr<TypePattern>, std::shared_ptr<WildcardPattern>, std::shared_ptr<ValuePattern>, std::shared_ptr<RangePattern>>;
    using ImportSpecifier = std::variant<std::shared_ptr<NamedImport>, std::shared_ptr<NamespaceImport>>;
    using Statement = std::variant<std::shared_ptr<ConstDeclaration>, std::shared_ptr<ReadonlyDeclaration>, std::shared_ptr<ImmutableBinding>, std::shared_ptr<LetDeclaration>, std::shared_ptr<FunctionDeclaration>, std::shared_ptr<ClassDeclaration>, std::shared_ptr<InterfaceDeclaration>, std::shared_ptr<EnumDeclaration>, std::shared_ptr<TypeAliasDeclaration>, std::shared_ptr<ImportDeclaration>, std::shared_ptr<MockImportDirective>, std::shared_ptr<ExportDeclaration>, std::shared_ptr<ExportList>, std::shared_ptr<IfStatement>, std::shared_ptr<CaseStatement>, std::shared_ptr<WhileStatement>, std::shared_ptr<ForStatement>, std::shared_ptr<ForOfStatement>, std::shared_ptr<WithStatement>, std::shared_ptr<ReturnStatement>, std::shared_ptr<YieldStatement>, std::shared_ptr<BreakStatement>, std::shared_ptr<ContinueStatement>, std::shared_ptr<ExpressionStatement>, std::shared_ptr<DestructuringStatement>, std::shared_ptr<TryStatement>, std::shared_ptr<YieldBlockAssignmentStatement>, std::shared_ptr<Block>>;
}

namespace app_src_lexer_ {
    struct LexerDiagnostic {
    std::string severity;
    std::string message;
    int32_t line;
    int32_t column;
    LexerDiagnostic(std::string severity, std::string message, int32_t line, int32_t column) : severity(severity), message(message), line(line), column(column) {}
    LexerDiagnostic() {}
};
}

namespace app_src_semantic_ {
    struct SemanticLocation {
    int32_t line;
    int32_t column;
    int32_t offset;
    SemanticLocation(int32_t line, int32_t column, int32_t offset) : line(line), column(column), offset(offset) {}
    SemanticLocation() {}
};
    struct Symbol : public std::enable_shared_from_this<Symbol> {
    std::string kind;
    std::string name;
    std::string module;
    bool exported;
    std::string originalName;
    bool native_;
    std::string nativeHeader;
    std::string nativeCppName;
    std::shared_ptr<std::vector<std::shared_ptr<Symbol>>> implementations;
    std::shared_ptr<std::vector<std::string>> implementedInterfaceTypes;
    std::shared_ptr<std::vector<std::string>> typeParams;
    std::shared_ptr<std::vector<ResolvedType>> streamElementTypes;
    Symbol(std::string kind, std::string name, std::string module, bool exported, std::string originalName, bool native_, std::string nativeHeader, std::string nativeCppName, std::shared_ptr<std::vector<std::shared_ptr<Symbol>>> implementations, std::shared_ptr<std::vector<std::string>> implementedInterfaceTypes, std::shared_ptr<std::vector<std::string>> typeParams, std::shared_ptr<std::vector<ResolvedType>> streamElementTypes) : kind(kind), name(name), module(module), exported(exported), originalName(originalName), native_(native_), nativeHeader(nativeHeader), nativeCppName(nativeCppName), implementations(implementations), implementedInterfaceTypes(implementedInterfaceTypes), typeParams(typeParams), streamElementTypes(streamElementTypes) {}
};
    struct PrimitiveType : public std::enable_shared_from_this<PrimitiveType> {
    std::string kind;
    std::string name;
    PrimitiveType(std::string kind, std::string name) : kind(kind), name(name) {}
};
    struct ClassType : public std::enable_shared_from_this<ClassType> {
    std::string kind;
    std::string name;
    std::shared_ptr<Symbol> symbol;
    std::shared_ptr<std::vector<ResolvedType>> typeArgs;
    ClassType(std::string kind, std::string name, std::shared_ptr<Symbol> symbol, std::shared_ptr<std::vector<ResolvedType>> typeArgs) : kind(kind), name(name), symbol(symbol), typeArgs(typeArgs) {}
};
    struct EnumType : public std::enable_shared_from_this<EnumType> {
    std::string kind;
    std::string name;
    std::shared_ptr<Symbol> symbol;
    EnumType(std::string kind, std::string name, std::shared_ptr<Symbol> symbol) : kind(kind), name(name), symbol(symbol) {}
};
    struct InterfaceType : public std::enable_shared_from_this<InterfaceType> {
    std::string kind;
    std::string name;
    std::shared_ptr<Symbol> symbol;
    std::shared_ptr<std::vector<ResolvedType>> typeArgs;
    InterfaceType(std::string kind, std::string name, std::shared_ptr<Symbol> symbol, std::shared_ptr<std::vector<ResolvedType>> typeArgs) : kind(kind), name(name), symbol(symbol), typeArgs(typeArgs) {}
};
    struct FunctionType : public std::enable_shared_from_this<FunctionType> {
    std::string kind;
    std::shared_ptr<std::vector<std::shared_ptr<FunctionParamType>>> params;
    ResolvedType returnType;
    std::shared_ptr<std::vector<std::string>> typeParams;
    FunctionType(std::string kind, std::shared_ptr<std::vector<std::shared_ptr<FunctionParamType>>> params, ResolvedType returnType, std::shared_ptr<std::vector<std::string>> typeParams) : kind(kind), params(params), returnType(returnType), typeParams(typeParams) {}
};
    struct FunctionParamType : public std::enable_shared_from_this<FunctionParamType> {
    std::string name;
    ResolvedType type_;
    bool hasDefault;
    FunctionParamType(std::string name, ResolvedType type_, bool hasDefault) : name(name), type_(type_), hasDefault(hasDefault) {}
};
    struct ActorType : public std::enable_shared_from_this<ActorType> {
    std::string kind;
    std::shared_ptr<ClassType> innerClass;
    ActorType(std::string kind, std::shared_ptr<ClassType> innerClass) : kind(kind), innerClass(innerClass) {}
};
    struct PromiseType : public std::enable_shared_from_this<PromiseType> {
    std::string kind;
    ResolvedType valueType;
    PromiseType(std::string kind, ResolvedType valueType) : kind(kind), valueType(valueType) {}
};
    struct ArrayResolvedType : public std::enable_shared_from_this<ArrayResolvedType> {
    std::string kind;
    ResolvedType elementType;
    bool readonly_;
    ArrayResolvedType(std::string kind, ResolvedType elementType, bool readonly_) : kind(kind), elementType(elementType), readonly_(readonly_) {}
};
    struct MapResolvedType : public std::enable_shared_from_this<MapResolvedType> {
    std::string kind;
    ResolvedType keyType;
    ResolvedType valueType;
    bool readonly_;
    MapResolvedType(std::string kind, ResolvedType keyType, ResolvedType valueType, bool readonly_) : kind(kind), keyType(keyType), valueType(valueType), readonly_(readonly_) {}
};
    struct SetResolvedType : public std::enable_shared_from_this<SetResolvedType> {
    std::string kind;
    ResolvedType elementType;
    bool readonly_;
    SetResolvedType(std::string kind, ResolvedType elementType, bool readonly_) : kind(kind), elementType(elementType), readonly_(readonly_) {}
};
    struct StreamResolvedType : public std::enable_shared_from_this<StreamResolvedType> {
    std::string kind;
    ResolvedType elementType;
    StreamResolvedType(std::string kind, ResolvedType elementType) : kind(kind), elementType(elementType) {}
};
    struct RangeResolvedType : public std::enable_shared_from_this<RangeResolvedType> {
    std::string kind;
    RangeResolvedType(std::string kind) : kind(kind) {}
};
    struct JsonValueResolvedType : public std::enable_shared_from_this<JsonValueResolvedType> {
    std::string kind;
    JsonValueResolvedType(std::string kind) : kind(kind) {}
};
    struct ResultResolvedType : public std::enable_shared_from_this<ResultResolvedType> {
    std::string kind;
    ResolvedType valueType;
    ResolvedType errorType;
    ResultResolvedType(std::string kind, ResolvedType valueType, ResolvedType errorType) : kind(kind), valueType(valueType), errorType(errorType) {}
};
    struct TupleResolvedType : public std::enable_shared_from_this<TupleResolvedType> {
    std::string kind;
    std::shared_ptr<std::vector<ResolvedType>> elements;
    TupleResolvedType(std::string kind, std::shared_ptr<std::vector<ResolvedType>> elements) : kind(kind), elements(elements) {}
};
    struct UnionResolvedType : public std::enable_shared_from_this<UnionResolvedType> {
    std::string kind;
    std::shared_ptr<std::vector<ResolvedType>> types;
    UnionResolvedType(std::string kind, std::shared_ptr<std::vector<ResolvedType>> types) : kind(kind), types(types) {}
};
    struct WeakResolvedType : public std::enable_shared_from_this<WeakResolvedType> {
    std::string kind;
    ResolvedType inner;
    WeakResolvedType(std::string kind, ResolvedType inner) : kind(kind), inner(inner) {}
};
    struct NoneType : public std::enable_shared_from_this<NoneType> {
    std::string kind;
    NoneType(std::string kind) : kind(kind) {}
};
    struct NeverType : public std::enable_shared_from_this<NeverType> {
    std::string kind;
    NeverType(std::string kind) : kind(kind) {}
};
    struct UnknownType : public std::enable_shared_from_this<UnknownType> {
    std::string kind;
    UnknownType(std::string kind) : kind(kind) {}
};
    struct TypeParameterType : public std::enable_shared_from_this<TypeParameterType> {
    std::string kind;
    std::string name;
    std::string constraintName;
    doof_header_type_1 constraint;
    TypeParameterType(std::string kind, std::string name, std::string constraintName, doof_header_type_1 constraint) : kind(kind), name(name), constraintName(constraintName), constraint(constraint) {}
};
    struct ClassMetadataResolvedType : public std::enable_shared_from_this<ClassMetadataResolvedType> {
    std::string kind;
    ResolvedType classType;
    ClassMetadataResolvedType(std::string kind, ResolvedType classType) : kind(kind), classType(classType) {}
};
    struct MethodReflectionResolvedType : public std::enable_shared_from_this<MethodReflectionResolvedType> {
    std::string kind;
    ResolvedType classType;
    MethodReflectionResolvedType(std::string kind, ResolvedType classType) : kind(kind), classType(classType) {}
};
}

namespace app_src_ast_ {
    struct AstLocation {
    int32_t line;
    int32_t column;
    int32_t offset;
    AstLocation(int32_t line, int32_t column, int32_t offset) : line(line), column(column), offset(offset) {}
    AstLocation() {}
};
    struct TypeParameterConstraint : public std::enable_shared_from_this<TypeParameterConstraint> {
    doof_header_type_2 type_;
    TypeParameterConstraint(doof_header_type_2 type_) : type_(type_) {}
};
}

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
    std::string tokenValue(Token token, const std::string& source);
}

namespace app_src_semantic_ {
    struct SemanticSpan {
    SemanticLocation start;
    SemanticLocation end;
    SemanticSpan(SemanticLocation start, SemanticLocation end) : start(start), end(end) {}
    SemanticSpan() {}
};
    struct Binding : public std::enable_shared_from_this<Binding> {
    std::string name;
    std::string kind;
    ResolvedType type_;
    bool mutable_;
    SemanticSpan span;
    std::string module;
    std::shared_ptr<Symbol> symbol;
    std::string casePattern;
    std::string fieldMode;
    std::string fieldOwner;
    Binding(std::string name, std::string kind, ResolvedType type_, bool mutable_, SemanticSpan span, std::string module, std::shared_ptr<Symbol> symbol, std::string casePattern, std::string fieldMode, std::string fieldOwner) : name(name), kind(kind), type_(type_), mutable_(mutable_), span(span), module(module), symbol(symbol), casePattern(casePattern), fieldMode(fieldMode), fieldOwner(fieldOwner) {}
};
}

namespace app_src_ast_ {
    struct SourceSpan {
    AstLocation start;
    AstLocation end;
    SourceSpan(AstLocation start, AstLocation end) : start(start), end(end) {}
    SourceSpan() {}
};
    struct NamedType : public std::enable_shared_from_this<NamedType> {
    std::string kind;
    std::string name;
    std::shared_ptr<std::vector<TypeAnnotation>> typeArgs;
    std::shared_ptr<::app_src_semantic_::Symbol> resolvedSymbol;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    NamedType(std::string kind, std::string name, std::shared_ptr<std::vector<TypeAnnotation>> typeArgs, std::shared_ptr<::app_src_semantic_::Symbol> resolvedSymbol, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), name(name), typeArgs(typeArgs), resolvedSymbol(resolvedSymbol), resolvedType(resolvedType), span(span) {}
};
    struct ArrayType : public std::enable_shared_from_this<ArrayType> {
    std::string kind;
    TypeAnnotation elementType;
    bool readonly_;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    ArrayType(std::string kind, TypeAnnotation elementType, bool readonly_, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), elementType(elementType), readonly_(readonly_), resolvedType(resolvedType), span(span) {}
};
    struct UnionType : public std::enable_shared_from_this<UnionType> {
    std::string kind;
    std::shared_ptr<std::vector<TypeAnnotation>> types;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    UnionType(std::string kind, std::shared_ptr<std::vector<TypeAnnotation>> types, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), types(types), resolvedType(resolvedType), span(span) {}
};
    struct AstFunctionType : public std::enable_shared_from_this<AstFunctionType> {
    std::string kind;
    std::shared_ptr<std::vector<std::shared_ptr<FunctionTypeParam>>> params;
    TypeAnnotation returnType;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    AstFunctionType(std::string kind, std::shared_ptr<std::vector<std::shared_ptr<FunctionTypeParam>>> params, TypeAnnotation returnType, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), params(params), returnType(returnType), resolvedType(resolvedType), span(span) {}
};
    struct WeakType : public std::enable_shared_from_this<WeakType> {
    std::string kind;
    TypeAnnotation type_;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    WeakType(std::string kind, TypeAnnotation type_, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), type_(type_), resolvedType(resolvedType), span(span) {}
};
    struct FunctionTypeParam : public std::enable_shared_from_this<FunctionTypeParam> {
    std::string name;
    TypeAnnotation type_;
    SourceSpan span;
    FunctionTypeParam(std::string name, TypeAnnotation type_, SourceSpan span) : name(name), type_(type_), span(span) {}
};
    struct IntLiteral : public std::enable_shared_from_this<IntLiteral> {
    std::string kind;
    int32_t value;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    IntLiteral(std::string kind, int32_t value, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), value(value), resolvedType(resolvedType), span(span) {}
};
    struct LongLiteral : public std::enable_shared_from_this<LongLiteral> {
    std::string kind;
    int64_t value;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    LongLiteral(std::string kind, int64_t value, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), value(value), resolvedType(resolvedType), span(span) {}
};
    struct FloatLiteral : public std::enable_shared_from_this<FloatLiteral> {
    std::string kind;
    float value;
    std::string raw;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    FloatLiteral(std::string kind, float value, std::string raw, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), value(value), raw(raw), resolvedType(resolvedType), span(span) {}
};
    struct DoubleLiteral : public std::enable_shared_from_this<DoubleLiteral> {
    std::string kind;
    double value;
    std::string raw;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    DoubleLiteral(std::string kind, double value, std::string raw, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), value(value), raw(raw), resolvedType(resolvedType), span(span) {}
};
    struct StringLiteral : public std::enable_shared_from_this<StringLiteral> {
    std::string kind;
    std::string value;
    std::shared_ptr<std::vector<std::string>> parts;
    std::shared_ptr<std::vector<Expression>> interpolations;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    StringLiteral(std::string kind, std::string value, std::shared_ptr<std::vector<std::string>> parts, std::shared_ptr<std::vector<Expression>> interpolations, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), value(value), parts(parts), interpolations(interpolations), resolvedType(resolvedType), span(span) {}
};
    struct CharLiteral : public std::enable_shared_from_this<CharLiteral> {
    std::string kind;
    char32_t value;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    CharLiteral(std::string kind, char32_t value, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), value(value), resolvedType(resolvedType), span(span) {}
};
    struct BoolLiteral : public std::enable_shared_from_this<BoolLiteral> {
    std::string kind;
    bool value;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    BoolLiteral(std::string kind, bool value, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), value(value), resolvedType(resolvedType), span(span) {}
};
    struct NoneLiteral : public std::enable_shared_from_this<NoneLiteral> {
    std::string kind;
    std::string sourceSpelling;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    NoneLiteral(std::string kind, std::string sourceSpelling, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), sourceSpelling(sourceSpelling), resolvedType(resolvedType), span(span) {}
};
    struct Identifier : public std::enable_shared_from_this<Identifier> {
    std::string kind;
    std::string name;
    doof_header_type_3 resolvedType;
    std::shared_ptr<::app_src_semantic_::Binding> resolvedBinding;
    SourceSpan span;
    Identifier(std::string kind, std::string name, doof_header_type_3 resolvedType, std::shared_ptr<::app_src_semantic_::Binding> resolvedBinding, SourceSpan span) : kind(kind), name(name), resolvedType(resolvedType), resolvedBinding(resolvedBinding), span(span) {}
};
    struct BinaryExpression : public std::enable_shared_from_this<BinaryExpression> {
    std::string kind;
    std::string operator_;
    Expression left;
    Expression right;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    BinaryExpression(std::string kind, std::string operator_, Expression left, Expression right, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), operator_(operator_), left(left), right(right), resolvedType(resolvedType), span(span) {}
};
    struct UnaryExpression : public std::enable_shared_from_this<UnaryExpression> {
    std::string kind;
    std::string operator_;
    Expression operand;
    bool prefix;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    UnaryExpression(std::string kind, std::string operator_, Expression operand, bool prefix, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), operator_(operator_), operand(operand), prefix(prefix), resolvedType(resolvedType), span(span) {}
};
    struct AssignmentExpression : public std::enable_shared_from_this<AssignmentExpression> {
    std::string kind;
    std::string operator_;
    Expression target;
    Expression value;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    AssignmentExpression(std::string kind, std::string operator_, Expression target, Expression value, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), operator_(operator_), target(target), value(value), resolvedType(resolvedType), span(span) {}
};
    struct MemberExpression : public std::enable_shared_from_this<MemberExpression> {
    std::string kind;
    Expression object;
    std::string property;
    bool optional;
    bool force;
    std::shared_ptr<ClassDeclaration> resolvedStaticOwner;
    bool resolvedNamespaceAccess;
    std::shared_ptr<::app_src_semantic_::Symbol> resolvedNamespaceSymbol;
    bool resolvedCallableField;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    MemberExpression(std::string kind, Expression object, std::string property, bool optional, bool force, std::shared_ptr<ClassDeclaration> resolvedStaticOwner, bool resolvedNamespaceAccess, std::shared_ptr<::app_src_semantic_::Symbol> resolvedNamespaceSymbol, bool resolvedCallableField, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), object(object), property(property), optional(optional), force(force), resolvedStaticOwner(resolvedStaticOwner), resolvedNamespaceAccess(resolvedNamespaceAccess), resolvedNamespaceSymbol(resolvedNamespaceSymbol), resolvedCallableField(resolvedCallableField), resolvedType(resolvedType), span(span) {}
};
    struct IndexExpression : public std::enable_shared_from_this<IndexExpression> {
    std::string kind;
    Expression object;
    Expression index;
    bool optional;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    IndexExpression(std::string kind, Expression object, Expression index, bool optional, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), object(object), index(index), optional(optional), resolvedType(resolvedType), span(span) {}
};
    struct CallArgument : public std::enable_shared_from_this<CallArgument> {
    std::optional<std::string> name;
    Expression value;
    SourceSpan span;
    CallArgument(std::optional<std::string> name, Expression value, SourceSpan span) : name(name), value(value), span(span) {}
};
    struct CallExpression : public std::enable_shared_from_this<CallExpression> {
    std::string kind;
    Expression callee;
    std::shared_ptr<std::vector<std::shared_ptr<CallArgument>>> args;
    std::shared_ptr<std::vector<TypeAnnotation>> typeArgs;
    std::shared_ptr<std::vector<doof_header_type_4>> resolvedGenericTypeArgs;
    std::shared_ptr<FunctionDeclaration> resolvedFunction;
    std::string resolvedFunctionModule;
    std::shared_ptr<FunctionDeclaration> resolvedConstructor;
    std::shared_ptr<ClassDeclaration> resolvedClass;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    CallExpression(std::string kind, Expression callee, std::shared_ptr<std::vector<std::shared_ptr<CallArgument>>> args, std::shared_ptr<std::vector<TypeAnnotation>> typeArgs, std::shared_ptr<std::vector<doof_header_type_4>> resolvedGenericTypeArgs, std::shared_ptr<FunctionDeclaration> resolvedFunction, std::string resolvedFunctionModule, std::shared_ptr<FunctionDeclaration> resolvedConstructor, std::shared_ptr<ClassDeclaration> resolvedClass, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), callee(callee), args(args), typeArgs(typeArgs), resolvedGenericTypeArgs(resolvedGenericTypeArgs), resolvedFunction(resolvedFunction), resolvedFunctionModule(resolvedFunctionModule), resolvedConstructor(resolvedConstructor), resolvedClass(resolvedClass), resolvedType(resolvedType), span(span) {}
};
    struct ArrayLiteral : public std::enable_shared_from_this<ArrayLiteral> {
    std::string kind;
    std::shared_ptr<std::vector<Expression>> elements;
    bool readonly_;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    ArrayLiteral(std::string kind, std::shared_ptr<std::vector<Expression>> elements, bool readonly_, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), elements(elements), readonly_(readonly_), resolvedType(resolvedType), span(span) {}
};
    struct ObjectProperty : public std::enable_shared_from_this<ObjectProperty> {
    std::string name;
    doof_header_type_5 key;
    doof_header_type_5 value;
    doof_header_type_3 resolvedType;
    std::shared_ptr<::app_src_semantic_::Binding> resolvedBinding;
    SourceSpan span;
    ObjectProperty(std::string name, doof_header_type_5 key, doof_header_type_5 value, doof_header_type_3 resolvedType, std::shared_ptr<::app_src_semantic_::Binding> resolvedBinding, SourceSpan span) : name(name), key(key), value(value), resolvedType(resolvedType), resolvedBinding(resolvedBinding), span(span) {}
};
    struct ObjectLiteral : public std::enable_shared_from_this<ObjectLiteral> {
    std::string kind;
    std::shared_ptr<std::vector<std::shared_ptr<ObjectProperty>>> properties;
    doof_header_type_5 spread;
    std::shared_ptr<ClassDeclaration> resolvedClass;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    ObjectLiteral(std::string kind, std::shared_ptr<std::vector<std::shared_ptr<ObjectProperty>>> properties, doof_header_type_5 spread, std::shared_ptr<ClassDeclaration> resolvedClass, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), properties(properties), spread(spread), resolvedClass(resolvedClass), resolvedType(resolvedType), span(span) {}
};
    struct TupleLiteral : public std::enable_shared_from_this<TupleLiteral> {
    std::string kind;
    std::shared_ptr<std::vector<Expression>> elements;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    TupleLiteral(std::string kind, std::shared_ptr<std::vector<Expression>> elements, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), elements(elements), resolvedType(resolvedType), span(span) {}
};
    struct LambdaExpression : public std::enable_shared_from_this<LambdaExpression> {
    std::string kind;
    std::shared_ptr<std::vector<std::shared_ptr<Parameter>>> params;
    doof_header_type_2 returnType;
    doof_header_type_6 body;
    bool parameterless;
    bool trailing;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    LambdaExpression(std::string kind, std::shared_ptr<std::vector<std::shared_ptr<Parameter>>> params, doof_header_type_2 returnType, doof_header_type_6 body, bool parameterless, bool trailing, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), params(params), returnType(returnType), body(body), parameterless(parameterless), trailing(trailing), resolvedType(resolvedType), span(span) {}
};
    struct IfExpression : public std::enable_shared_from_this<IfExpression> {
    std::string kind;
    Expression condition;
    Expression then_;
    Expression else_;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    IfExpression(std::string kind, Expression condition, Expression then_, Expression else_, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), condition(condition), then_(then_), else_(else_), resolvedType(resolvedType), span(span) {}
};
    struct ConstructExpression : public std::enable_shared_from_this<ConstructExpression> {
    std::string kind;
    std::string type_;
    std::shared_ptr<std::vector<TypeAnnotation>> typeArgs;
    std::shared_ptr<std::vector<std::shared_ptr<ObjectProperty>>> args;
    doof_header_type_5 spread;
    std::shared_ptr<std::vector<std::string>> spreadFields;
    doof_header_type_3 resolvedSpreadType;
    bool named;
    std::shared_ptr<ClassDeclaration> resolvedClass;
    std::shared_ptr<FunctionDeclaration> resolvedConstructor;
    doof_header_type_3 resolvedConstructedType;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    ConstructExpression(std::string kind, std::string type_, std::shared_ptr<std::vector<TypeAnnotation>> typeArgs, std::shared_ptr<std::vector<std::shared_ptr<ObjectProperty>>> args, doof_header_type_5 spread, std::shared_ptr<std::vector<std::string>> spreadFields, doof_header_type_3 resolvedSpreadType, bool named, std::shared_ptr<ClassDeclaration> resolvedClass, std::shared_ptr<FunctionDeclaration> resolvedConstructor, doof_header_type_3 resolvedConstructedType, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), type_(type_), typeArgs(typeArgs), args(args), spread(spread), spreadFields(spreadFields), resolvedSpreadType(resolvedSpreadType), named(named), resolvedClass(resolvedClass), resolvedConstructor(resolvedConstructor), resolvedConstructedType(resolvedConstructedType), resolvedType(resolvedType), span(span) {}
};
    struct DotShorthand : public std::enable_shared_from_this<DotShorthand> {
    std::string kind;
    std::string name;
    std::string resolvedShorthandOwnerName;
    std::string resolvedShorthandOwnerKind;
    std::string resolvedShorthandOwnerModule;
    bool resolvedShorthandOwnerNative;
    std::string resolvedShorthandOwnerCppName;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    DotShorthand(std::string kind, std::string name, std::string resolvedShorthandOwnerName, std::string resolvedShorthandOwnerKind, std::string resolvedShorthandOwnerModule, bool resolvedShorthandOwnerNative, std::string resolvedShorthandOwnerCppName, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), name(name), resolvedShorthandOwnerName(resolvedShorthandOwnerName), resolvedShorthandOwnerKind(resolvedShorthandOwnerKind), resolvedShorthandOwnerModule(resolvedShorthandOwnerModule), resolvedShorthandOwnerNative(resolvedShorthandOwnerNative), resolvedShorthandOwnerCppName(resolvedShorthandOwnerCppName), resolvedType(resolvedType), span(span) {}
};
    struct ThisExpression : public std::enable_shared_from_this<ThisExpression> {
    std::string kind;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    ThisExpression(std::string kind, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), resolvedType(resolvedType), span(span) {}
};
    struct CallerExpression : public std::enable_shared_from_this<CallerExpression> {
    std::string kind;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    CallerExpression(std::string kind, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), resolvedType(resolvedType), span(span) {}
};
    struct AsyncExpression : public std::enable_shared_from_this<AsyncExpression> {
    std::string kind;
    doof_header_type_6 expression;
    std::shared_ptr<std::vector<std::string>> resolvedCaptureNames;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    AsyncExpression(std::string kind, doof_header_type_6 expression, std::shared_ptr<std::vector<std::string>> resolvedCaptureNames, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), expression(expression), resolvedCaptureNames(resolvedCaptureNames), resolvedType(resolvedType), span(span) {}
};
    struct RetireExpression : public std::enable_shared_from_this<RetireExpression> {
    std::string kind;
    Expression actor;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    RetireExpression(std::string kind, Expression actor, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), actor(actor), resolvedType(resolvedType), span(span) {}
};
    struct AsExpression : public std::enable_shared_from_this<AsExpression> {
    std::string kind;
    Expression expression;
    TypeAnnotation targetType;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    AsExpression(std::string kind, Expression expression, TypeAnnotation targetType, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), expression(expression), targetType(targetType), resolvedType(resolvedType), span(span) {}
};
    struct ActorCreationExpression : public std::enable_shared_from_this<ActorCreationExpression> {
    std::string kind;
    std::string className;
    std::shared_ptr<std::vector<Expression>> args;
    std::shared_ptr<FunctionDeclaration> resolvedConstructor;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    ActorCreationExpression(std::string kind, std::string className, std::shared_ptr<std::vector<Expression>> args, std::shared_ptr<FunctionDeclaration> resolvedConstructor, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), className(className), args(args), resolvedConstructor(resolvedConstructor), resolvedType(resolvedType), span(span) {}
};
    struct YieldBlockExpression : public std::enable_shared_from_this<YieldBlockExpression> {
    std::string kind;
    std::shared_ptr<Block> body;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    YieldBlockExpression(std::string kind, std::shared_ptr<Block> body, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), body(body), resolvedType(resolvedType), span(span) {}
};
    struct CatchExpression : public std::enable_shared_from_this<CatchExpression> {
    std::string kind;
    std::shared_ptr<Block> body;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    CatchExpression(std::string kind, std::shared_ptr<Block> body, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), body(body), resolvedType(resolvedType), span(span) {}
};
    struct Parameter : public std::enable_shared_from_this<Parameter> {
    std::string name;
    std::string description;
    doof_header_type_2 type_;
    doof_header_type_5 defaultValue;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    Parameter(std::string name, std::string description, doof_header_type_2 type_, doof_header_type_5 defaultValue, doof_header_type_3 resolvedType, SourceSpan span) : name(name), description(description), type_(type_), defaultValue(defaultValue), resolvedType(resolvedType), span(span) {}
};
    struct Block : public std::enable_shared_from_this<Block> {
    std::string kind;
    std::shared_ptr<std::vector<Statement>> statements;
    SourceSpan span;
    Block(std::string kind, std::shared_ptr<std::vector<Statement>> statements, SourceSpan span) : kind(kind), statements(statements), span(span) {}
};
    struct ConstDeclaration : public std::enable_shared_from_this<ConstDeclaration> {
    std::string kind;
    std::string name;
    std::string description;
    doof_header_type_2 type_;
    Expression value;
    bool exported;
    doof_header_type_3 resolvedType;
    bool moduleInitializerChecked;
    SourceSpan span;
    ConstDeclaration(std::string kind, std::string name, std::string description, doof_header_type_2 type_, Expression value, bool exported, doof_header_type_3 resolvedType, bool moduleInitializerChecked, SourceSpan span) : kind(kind), name(name), description(description), type_(type_), value(value), exported(exported), resolvedType(resolvedType), moduleInitializerChecked(moduleInitializerChecked), span(span) {}
};
    struct ReadonlyDeclaration : public std::enable_shared_from_this<ReadonlyDeclaration> {
    std::string kind;
    std::string name;
    std::string description;
    doof_header_type_2 type_;
    Expression value;
    bool exported;
    doof_header_type_3 resolvedType;
    bool moduleInitializerChecked;
    SourceSpan span;
    ReadonlyDeclaration(std::string kind, std::string name, std::string description, doof_header_type_2 type_, Expression value, bool exported, doof_header_type_3 resolvedType, bool moduleInitializerChecked, SourceSpan span) : kind(kind), name(name), description(description), type_(type_), value(value), exported(exported), resolvedType(resolvedType), moduleInitializerChecked(moduleInitializerChecked), span(span) {}
};
    struct ImmutableBinding : public std::enable_shared_from_this<ImmutableBinding> {
    std::string kind;
    std::string name;
    doof_header_type_2 type_;
    Expression value;
    bool exported;
    std::shared_ptr<Block> else_;
    std::optional<std::string> failureName;
    doof_header_type_3 resolvedType;
    bool moduleInitializerChecked;
    SourceSpan span;
    ImmutableBinding(std::string kind, std::string name, doof_header_type_2 type_, Expression value, bool exported, std::shared_ptr<Block> else_, std::optional<std::string> failureName, doof_header_type_3 resolvedType, bool moduleInitializerChecked, SourceSpan span) : kind(kind), name(name), type_(type_), value(value), exported(exported), else_(else_), failureName(failureName), resolvedType(resolvedType), moduleInitializerChecked(moduleInitializerChecked), span(span) {}
};
    struct LetDeclaration : public std::enable_shared_from_this<LetDeclaration> {
    std::string kind;
    std::string name;
    doof_header_type_2 type_;
    Expression value;
    doof_header_type_3 resolvedType;
    bool moduleInitializerChecked;
    SourceSpan span;
    LetDeclaration(std::string kind, std::string name, doof_header_type_2 type_, Expression value, doof_header_type_3 resolvedType, bool moduleInitializerChecked, SourceSpan span) : kind(kind), name(name), type_(type_), value(value), resolvedType(resolvedType), moduleInitializerChecked(moduleInitializerChecked), span(span) {}
};
    struct FunctionDeclaration : public std::enable_shared_from_this<FunctionDeclaration> {
    std::string kind;
    std::string name;
    std::string description;
    std::shared_ptr<std::vector<std::string>> typeParams;
    std::shared_ptr<std::vector<std::shared_ptr<TypeParameterConstraint>>> typeParamConstraints;
    std::shared_ptr<std::vector<std::shared_ptr<Parameter>>> params;
    doof_header_type_2 returnType;
    doof_header_type_6 body;
    bool exported;
    bool static_;
    bool isolated_;
    bool resolvedIsolated;
    bool private_;
    bool bodyless;
    bool native_;
    std::string nativeHeader;
    std::string nativeCppName;
    std::optional<SourceSpan> legacyMethodFunctionSpan;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    FunctionDeclaration(std::string kind, std::string name, std::string description, std::shared_ptr<std::vector<std::string>> typeParams, std::shared_ptr<std::vector<std::shared_ptr<TypeParameterConstraint>>> typeParamConstraints, std::shared_ptr<std::vector<std::shared_ptr<Parameter>>> params, doof_header_type_2 returnType, doof_header_type_6 body, bool exported, bool static_, bool isolated_, bool resolvedIsolated, bool private_, bool bodyless, bool native_, std::string nativeHeader, std::string nativeCppName, std::optional<SourceSpan> legacyMethodFunctionSpan, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), name(name), description(description), typeParams(typeParams), typeParamConstraints(typeParamConstraints), params(params), returnType(returnType), body(body), exported(exported), static_(static_), isolated_(isolated_), resolvedIsolated(resolvedIsolated), private_(private_), bodyless(bodyless), native_(native_), nativeHeader(nativeHeader), nativeCppName(nativeCppName), legacyMethodFunctionSpan(legacyMethodFunctionSpan), resolvedType(resolvedType), span(span) {}
};
    struct ReturnStatement : public std::enable_shared_from_this<ReturnStatement> {
    std::string kind;
    doof_header_type_5 value;
    doof_header_type_3 resolvedExpectedType;
    SourceSpan span;
    ReturnStatement(std::string kind, doof_header_type_5 value, doof_header_type_3 resolvedExpectedType, SourceSpan span) : kind(kind), value(value), resolvedExpectedType(resolvedExpectedType), span(span) {}
};
    struct YieldStatement : public std::enable_shared_from_this<YieldStatement> {
    std::string kind;
    Expression value;
    SourceSpan span;
    YieldStatement(std::string kind, Expression value, SourceSpan span) : kind(kind), value(value), span(span) {}
};
    struct YieldBlockAssignmentStatement : public std::enable_shared_from_this<YieldBlockAssignmentStatement> {
    std::string kind;
    std::string name;
    std::shared_ptr<YieldBlockExpression> value;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    YieldBlockAssignmentStatement(std::string kind, std::string name, std::shared_ptr<YieldBlockExpression> value, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), name(name), value(value), resolvedType(resolvedType), span(span) {}
};
    struct IfStatement : public std::enable_shared_from_this<IfStatement> {
    std::string kind;
    Expression condition;
    std::shared_ptr<Block> body;
    std::shared_ptr<std::vector<std::shared_ptr<IfBranch>>> elseIfs;
    std::shared_ptr<Block> else_;
    SourceSpan span;
    IfStatement(std::string kind, Expression condition, std::shared_ptr<Block> body, std::shared_ptr<std::vector<std::shared_ptr<IfBranch>>> elseIfs, std::shared_ptr<Block> else_, SourceSpan span) : kind(kind), condition(condition), body(body), elseIfs(elseIfs), else_(else_), span(span) {}
};
    struct CaseExpression : public std::enable_shared_from_this<CaseExpression> {
    std::string kind;
    Expression subject;
    std::shared_ptr<std::vector<std::shared_ptr<CaseExpressionArm>>> arms;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    CaseExpression(std::string kind, Expression subject, std::shared_ptr<std::vector<std::shared_ptr<CaseExpressionArm>>> arms, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), subject(subject), arms(arms), resolvedType(resolvedType), span(span) {}
};
    struct CaseStatement : public std::enable_shared_from_this<CaseStatement> {
    std::string kind;
    Expression subject;
    std::shared_ptr<std::vector<std::shared_ptr<CaseArm>>> arms;
    std::optional<bool> resolvedCompletes;
    SourceSpan span;
    CaseStatement(std::string kind, Expression subject, std::shared_ptr<std::vector<std::shared_ptr<CaseArm>>> arms, std::optional<bool> resolvedCompletes, SourceSpan span) : kind(kind), subject(subject), arms(arms), resolvedCompletes(resolvedCompletes), span(span) {}
};
    struct CaseArm : public std::enable_shared_from_this<CaseArm> {
    std::string kind;
    std::shared_ptr<std::vector<CasePattern>> patterns;
    doof_header_type_6 body;
    SourceSpan span;
    CaseArm(std::string kind, std::shared_ptr<std::vector<CasePattern>> patterns, doof_header_type_6 body, SourceSpan span) : kind(kind), patterns(patterns), body(body), span(span) {}
};
    struct CaseExpressionArm : public std::enable_shared_from_this<CaseExpressionArm> {
    std::string kind;
    std::shared_ptr<std::vector<CasePattern>> patterns;
    doof_header_type_6 body;
    SourceSpan span;
    CaseExpressionArm(std::string kind, std::shared_ptr<std::vector<CasePattern>> patterns, doof_header_type_6 body, SourceSpan span) : kind(kind), patterns(patterns), body(body), span(span) {}
};
    struct TypePattern : public std::enable_shared_from_this<TypePattern> {
    std::string kind;
    std::string name;
    TypeAnnotation type_;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    TypePattern(std::string kind, std::string name, TypeAnnotation type_, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), name(name), type_(type_), resolvedType(resolvedType), span(span) {}
};
    struct WildcardPattern : public std::enable_shared_from_this<WildcardPattern> {
    std::string kind;
    SourceSpan span;
    WildcardPattern(std::string kind, SourceSpan span) : kind(kind), span(span) {}
};
    struct ValuePattern : public std::enable_shared_from_this<ValuePattern> {
    std::string kind;
    Expression value;
    SourceSpan span;
    ValuePattern(std::string kind, Expression value, SourceSpan span) : kind(kind), value(value), span(span) {}
};
    struct RangePattern : public std::enable_shared_from_this<RangePattern> {
    std::string kind;
    doof_header_type_5 start;
    doof_header_type_5 end;
    bool inclusive;
    SourceSpan span;
    RangePattern(std::string kind, doof_header_type_5 start, doof_header_type_5 end, bool inclusive, SourceSpan span) : kind(kind), start(start), end(end), inclusive(inclusive), span(span) {}
};
    struct IfBranch : public std::enable_shared_from_this<IfBranch> {
    Expression condition;
    std::shared_ptr<Block> body;
    SourceSpan span;
    IfBranch(Expression condition, std::shared_ptr<Block> body, SourceSpan span) : condition(condition), body(body), span(span) {}
};
    struct WhileStatement : public std::enable_shared_from_this<WhileStatement> {
    std::string kind;
    Expression condition;
    std::shared_ptr<Block> body;
    std::optional<std::string> label;
    std::shared_ptr<Block> then_;
    SourceSpan span;
    WhileStatement(std::string kind, Expression condition, std::shared_ptr<Block> body, std::optional<std::string> label, std::shared_ptr<Block> then_, SourceSpan span) : kind(kind), condition(condition), body(body), label(label), then_(then_), span(span) {}
};
    struct ForStatement : public std::enable_shared_from_this<ForStatement> {
    std::string kind;
    doof_header_type_7 init;
    doof_header_type_5 condition;
    std::shared_ptr<std::vector<Expression>> update;
    std::shared_ptr<Block> body;
    std::optional<std::string> label;
    std::shared_ptr<Block> then_;
    SourceSpan span;
    ForStatement(std::string kind, doof_header_type_7 init, doof_header_type_5 condition, std::shared_ptr<std::vector<Expression>> update, std::shared_ptr<Block> body, std::optional<std::string> label, std::shared_ptr<Block> then_, SourceSpan span) : kind(kind), init(init), condition(condition), update(update), body(body), label(label), then_(then_), span(span) {}
};
    struct ForOfStatement : public std::enable_shared_from_this<ForOfStatement> {
    std::string kind;
    std::shared_ptr<std::vector<std::string>> bindings;
    Expression iterable;
    std::shared_ptr<Block> body;
    std::optional<std::string> label;
    std::shared_ptr<Block> then_;
    SourceSpan span;
    ForOfStatement(std::string kind, std::shared_ptr<std::vector<std::string>> bindings, Expression iterable, std::shared_ptr<Block> body, std::optional<std::string> label, std::shared_ptr<Block> then_, SourceSpan span) : kind(kind), bindings(bindings), iterable(iterable), body(body), label(label), then_(then_), span(span) {}
};
    struct WithBinding : public std::enable_shared_from_this<WithBinding> {
    std::string name;
    doof_header_type_2 type_;
    Expression value;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    WithBinding(std::string name, doof_header_type_2 type_, Expression value, doof_header_type_3 resolvedType, SourceSpan span) : name(name), type_(type_), value(value), resolvedType(resolvedType), span(span) {}
};
    struct WithStatement : public std::enable_shared_from_this<WithStatement> {
    std::string kind;
    std::shared_ptr<std::vector<std::shared_ptr<WithBinding>>> bindings;
    std::shared_ptr<Block> body;
    SourceSpan span;
    WithStatement(std::string kind, std::shared_ptr<std::vector<std::shared_ptr<WithBinding>>> bindings, std::shared_ptr<Block> body, SourceSpan span) : kind(kind), bindings(bindings), body(body), span(span) {}
};
    struct BreakStatement : public std::enable_shared_from_this<BreakStatement> {
    std::string kind;
    std::optional<std::string> label;
    SourceSpan span;
    BreakStatement(std::string kind, std::optional<std::string> label, SourceSpan span) : kind(kind), label(label), span(span) {}
};
    struct ContinueStatement : public std::enable_shared_from_this<ContinueStatement> {
    std::string kind;
    std::optional<std::string> label;
    SourceSpan span;
    ContinueStatement(std::string kind, std::optional<std::string> label, SourceSpan span) : kind(kind), label(label), span(span) {}
};
    struct ExpressionStatement : public std::enable_shared_from_this<ExpressionStatement> {
    std::string kind;
    Expression expression;
    SourceSpan span;
    ExpressionStatement(std::string kind, Expression expression, SourceSpan span) : kind(kind), expression(expression), span(span) {}
};
    struct DestructuringStatement : public std::enable_shared_from_this<DestructuringStatement> {
    std::string kind;
    std::shared_ptr<std::vector<std::string>> bindings;
    std::shared_ptr<std::vector<std::shared_ptr<DestructureBinding>>> namedBindings;
    std::string bindingKind;
    Expression value;
    SourceSpan span;
    DestructuringStatement(std::string kind, std::shared_ptr<std::vector<std::string>> bindings, std::shared_ptr<std::vector<std::shared_ptr<DestructureBinding>>> namedBindings, std::string bindingKind, Expression value, SourceSpan span) : kind(kind), bindings(bindings), namedBindings(namedBindings), bindingKind(bindingKind), value(value), span(span) {}
};
    struct DestructureBinding : public std::enable_shared_from_this<DestructureBinding> {
    std::string name;
    std::optional<std::string> alias;
    SourceSpan span;
    DestructureBinding(std::string name, std::optional<std::string> alias, SourceSpan span) : name(name), alias(alias), span(span) {}
};
    struct TryStatement : public std::enable_shared_from_this<TryStatement> {
    std::string kind;
    doof_header_type_8 binding;
    SourceSpan span;
    TryStatement(std::string kind, doof_header_type_8 binding, SourceSpan span) : kind(kind), binding(binding), span(span) {}
};
    struct ClassDeclaration : public std::enable_shared_from_this<ClassDeclaration> {
    std::string kind;
    std::string name;
    std::string description;
    bool struct_;
    std::shared_ptr<std::vector<std::string>> typeParams;
    std::shared_ptr<std::vector<std::shared_ptr<TypeParameterConstraint>>> typeParamConstraints;
    std::shared_ptr<std::vector<std::shared_ptr<NamedType>>> implements_;
    std::shared_ptr<std::vector<std::shared_ptr<ClassField>>> fields;
    std::shared_ptr<std::vector<std::shared_ptr<FunctionDeclaration>>> methods;
    std::shared_ptr<Block> destructor_;
    bool exported;
    bool private_;
    bool native_;
    std::string nativeHeader;
    std::string nativeCppName;
    std::shared_ptr<::app_src_semantic_::Symbol> resolvedSymbol;
    bool needsMetadata;
    SourceSpan span;
    ClassDeclaration(std::string kind, std::string name, std::string description, bool struct_, std::shared_ptr<std::vector<std::string>> typeParams, std::shared_ptr<std::vector<std::shared_ptr<TypeParameterConstraint>>> typeParamConstraints, std::shared_ptr<std::vector<std::shared_ptr<NamedType>>> implements_, std::shared_ptr<std::vector<std::shared_ptr<ClassField>>> fields, std::shared_ptr<std::vector<std::shared_ptr<FunctionDeclaration>>> methods, std::shared_ptr<Block> destructor_, bool exported, bool private_, bool native_, std::string nativeHeader, std::string nativeCppName, std::shared_ptr<::app_src_semantic_::Symbol> resolvedSymbol, bool needsMetadata, SourceSpan span) : kind(kind), name(name), description(description), struct_(struct_), typeParams(typeParams), typeParamConstraints(typeParamConstraints), implements_(implements_), fields(fields), methods(methods), destructor_(destructor_), exported(exported), private_(private_), native_(native_), nativeHeader(nativeHeader), nativeCppName(nativeCppName), resolvedSymbol(resolvedSymbol), needsMetadata(needsMetadata), span(span) {}
};
    struct ClassField : public std::enable_shared_from_this<ClassField> {
    std::string kind;
    std::shared_ptr<std::vector<std::string>> names;
    std::shared_ptr<std::vector<std::string>> descriptions;
    doof_header_type_2 type_;
    doof_header_type_5 defaultValue;
    bool static_;
    bool const_;
    bool let_;
    bool readonly_;
    bool weak_;
    bool private_;
    doof_header_type_3 resolvedType;
    bool moduleInitializerChecked;
    SourceSpan span;
    ClassField(std::string kind, std::shared_ptr<std::vector<std::string>> names, std::shared_ptr<std::vector<std::string>> descriptions, doof_header_type_2 type_, doof_header_type_5 defaultValue, bool static_, bool const_, bool let_, bool readonly_, bool weak_, bool private_, doof_header_type_3 resolvedType, bool moduleInitializerChecked, SourceSpan span) : kind(kind), names(names), descriptions(descriptions), type_(type_), defaultValue(defaultValue), static_(static_), const_(const_), let_(let_), readonly_(readonly_), weak_(weak_), private_(private_), resolvedType(resolvedType), moduleInitializerChecked(moduleInitializerChecked), span(span) {}
};
    struct InterfaceDeclaration : public std::enable_shared_from_this<InterfaceDeclaration> {
    std::string kind;
    std::string name;
    std::string description;
    std::shared_ptr<std::vector<std::string>> typeParams;
    std::shared_ptr<std::vector<std::shared_ptr<TypeParameterConstraint>>> typeParamConstraints;
    std::shared_ptr<std::vector<std::shared_ptr<InterfaceField>>> fields;
    std::shared_ptr<std::vector<std::shared_ptr<FunctionDeclaration>>> methods;
    bool exported;
    std::shared_ptr<::app_src_semantic_::Symbol> resolvedSymbol;
    bool needsJson;
    SourceSpan span;
    InterfaceDeclaration(std::string kind, std::string name, std::string description, std::shared_ptr<std::vector<std::string>> typeParams, std::shared_ptr<std::vector<std::shared_ptr<TypeParameterConstraint>>> typeParamConstraints, std::shared_ptr<std::vector<std::shared_ptr<InterfaceField>>> fields, std::shared_ptr<std::vector<std::shared_ptr<FunctionDeclaration>>> methods, bool exported, std::shared_ptr<::app_src_semantic_::Symbol> resolvedSymbol, bool needsJson, SourceSpan span) : kind(kind), name(name), description(description), typeParams(typeParams), typeParamConstraints(typeParamConstraints), fields(fields), methods(methods), exported(exported), resolvedSymbol(resolvedSymbol), needsJson(needsJson), span(span) {}
};
    struct InterfaceField : public std::enable_shared_from_this<InterfaceField> {
    std::string kind;
    std::string name;
    std::string description;
    TypeAnnotation type_;
    bool let_;
    bool readonly_;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    InterfaceField(std::string kind, std::string name, std::string description, TypeAnnotation type_, bool let_, bool readonly_, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), name(name), description(description), type_(type_), let_(let_), readonly_(readonly_), resolvedType(resolvedType), span(span) {}
};
    struct EnumDeclaration : public std::enable_shared_from_this<EnumDeclaration> {
    std::string kind;
    std::string name;
    std::string description;
    std::shared_ptr<std::vector<std::shared_ptr<EnumVariant>>> variants;
    std::string backingKind;
    bool exported;
    SourceSpan span;
    EnumDeclaration(std::string kind, std::string name, std::string description, std::shared_ptr<std::vector<std::shared_ptr<EnumVariant>>> variants, std::string backingKind, bool exported, SourceSpan span) : kind(kind), name(name), description(description), variants(variants), backingKind(backingKind), exported(exported), span(span) {}
};
    struct EnumVariant : public std::enable_shared_from_this<EnumVariant> {
    std::string kind;
    std::string name;
    std::string description;
    doof_header_type_5 value;
    std::optional<int32_t> resolvedIntValue;
    std::optional<std::string> resolvedStringValue;
    SourceSpan span;
    EnumVariant(std::string kind, std::string name, std::string description, doof_header_type_5 value, std::optional<int32_t> resolvedIntValue, std::optional<std::string> resolvedStringValue, SourceSpan span) : kind(kind), name(name), description(description), value(value), resolvedIntValue(resolvedIntValue), resolvedStringValue(resolvedStringValue), span(span) {}
};
    struct TypeAliasDeclaration : public std::enable_shared_from_this<TypeAliasDeclaration> {
    std::string kind;
    std::string name;
    std::string description;
    std::shared_ptr<std::vector<std::string>> typeParams;
    std::shared_ptr<std::vector<std::shared_ptr<TypeParameterConstraint>>> typeParamConstraints;
    TypeAnnotation type_;
    bool exported;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    TypeAliasDeclaration(std::string kind, std::string name, std::string description, std::shared_ptr<std::vector<std::string>> typeParams, std::shared_ptr<std::vector<std::shared_ptr<TypeParameterConstraint>>> typeParamConstraints, TypeAnnotation type_, bool exported, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), name(name), description(description), typeParams(typeParams), typeParamConstraints(typeParamConstraints), type_(type_), exported(exported), resolvedType(resolvedType), span(span) {}
};
    struct NamedImport : public std::enable_shared_from_this<NamedImport> {
    std::string kind;
    std::string name;
    std::optional<std::string> alias;
    SourceSpan span;
    NamedImport(std::string kind, std::string name, std::optional<std::string> alias, SourceSpan span) : kind(kind), name(name), alias(alias), span(span) {}
};
    struct NamespaceImport : public std::enable_shared_from_this<NamespaceImport> {
    std::string kind;
    std::string alias;
    SourceSpan span;
    NamespaceImport(std::string kind, std::string alias, SourceSpan span) : kind(kind), alias(alias), span(span) {}
};
    struct ImportDeclaration : public std::enable_shared_from_this<ImportDeclaration> {
    std::string kind;
    std::shared_ptr<std::vector<ImportSpecifier>> specifiers;
    std::string source;
    bool typeOnly;
    SourceSpan span;
    ImportDeclaration(std::string kind, std::shared_ptr<std::vector<ImportSpecifier>> specifiers, std::string source, bool typeOnly, SourceSpan span) : kind(kind), specifiers(specifiers), source(source), typeOnly(typeOnly), span(span) {}
};
    struct MockImportMapping : public std::enable_shared_from_this<MockImportMapping> {
    std::string dependency;
    std::string replacement;
    SourceSpan span;
    MockImportMapping(std::string dependency, std::string replacement, SourceSpan span) : dependency(dependency), replacement(replacement), span(span) {}
};
    struct MockImportDirective : public std::enable_shared_from_this<MockImportDirective> {
    std::string kind;
    std::string sourcePattern;
    std::shared_ptr<std::vector<std::shared_ptr<MockImportMapping>>> mappings;
    SourceSpan span;
    MockImportDirective(std::string kind, std::string sourcePattern, std::shared_ptr<std::vector<std::shared_ptr<MockImportMapping>>> mappings, SourceSpan span) : kind(kind), sourcePattern(sourcePattern), mappings(mappings), span(span) {}
};
    struct ExportDeclaration : public std::enable_shared_from_this<ExportDeclaration> {
    std::string kind;
    Statement declaration;
    SourceSpan span;
    ExportDeclaration(std::string kind, Statement declaration, SourceSpan span) : kind(kind), declaration(declaration), span(span) {}
};
    struct ExportSpecifier : public std::enable_shared_from_this<ExportSpecifier> {
    std::string name;
    std::optional<std::string> alias;
    SourceSpan span;
    ExportSpecifier(std::string name, std::optional<std::string> alias, SourceSpan span) : name(name), alias(alias), span(span) {}
};
    struct ExportList : public std::enable_shared_from_this<ExportList> {
    std::string kind;
    std::shared_ptr<std::vector<std::shared_ptr<ExportSpecifier>>> specifiers;
    std::optional<std::string> source;
    SourceSpan span;
    ExportList(std::string kind, std::shared_ptr<std::vector<std::shared_ptr<ExportSpecifier>>> specifiers, std::optional<std::string> source, SourceSpan span) : kind(kind), specifiers(specifiers), source(source), span(span) {}
};
    struct Program : public std::enable_shared_from_this<Program> {
    std::string kind;
    std::shared_ptr<std::vector<Statement>> statements;
    SourceSpan span;
    Program(std::string kind, std::shared_ptr<std::vector<Statement>> statements, SourceSpan span) : kind(kind), statements(statements), span(span) {}
};
}

namespace app_src_parser_declarations_ {
    doof_header_type_9 parseExport(const std::shared_ptr<::app_src_parser_::Parser>& parser);
    doof_header_type_9 parseConst(const std::shared_ptr<::app_src_parser_::Parser>& parser, bool exported);
    doof_header_type_9 parseReadonly(const std::shared_ptr<::app_src_parser_::Parser>& parser, bool exported);
    doof_header_type_9 parseLet(const std::shared_ptr<::app_src_parser_::Parser>& parser);
    std::shared_ptr<::app_src_ast_::FunctionDeclaration> parseFunction(const std::shared_ptr<::app_src_parser_::Parser>& parser, bool exported, bool static_, bool isolated_, bool private_, bool legacyMethod);
    doof_header_type_9 parseClass(const std::shared_ptr<::app_src_parser_::Parser>& parser, bool exported, bool private_);
    doof_header_type_9 parseInterface(const std::shared_ptr<::app_src_parser_::Parser>& parser, bool exported);
    doof_header_type_9 parseEnum(const std::shared_ptr<::app_src_parser_::Parser>& parser, bool exported);
    doof_header_type_9 parseTypeAlias(const std::shared_ptr<::app_src_parser_::Parser>& parser, bool exported);
    doof_header_type_9 parseImport(const std::shared_ptr<::app_src_parser_::Parser>& parser);
    doof_header_type_9 parseMockImport(const std::shared_ptr<::app_src_parser_::Parser>& parser);
}

namespace app_src_parser_statements_ {
    doof_header_type_10 parseStatement(const std::shared_ptr<::app_src_parser_::Parser>& parser);
    std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> parseCaseExpression(const std::shared_ptr<::app_src_parser_::Parser>& parser);
    std::shared_ptr<::app_src_ast_::Block> parseBlock(const std::shared_ptr<::app_src_parser_::Parser>& parser);
    bool looksLikePattern(const std::shared_ptr<::app_src_parser_::Parser>& parser, ::app_src_lexer_::TokenType separator);
    doof_header_type_10 parseDestructuring(const std::shared_ptr<::app_src_parser_::Parser>& parser, const std::string& shape, const std::string& bindingKind, ::app_src_lexer_::TokenType separator);
}

namespace app_src_parser_types_ {
    std::variant<std::monostate, std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> parseOptionalType(const std::shared_ptr<::app_src_parser_::Parser>& parser);
    std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> parseTypeAnnotation(const std::shared_ptr<::app_src_parser_::Parser>& parser);
}

namespace app_src_parser_expressions_ {
    doof_header_type_11 parseExpression(const std::shared_ptr<::app_src_parser_::Parser>& parser);
    doof_header_type_11 parseAdditive(const std::shared_ptr<::app_src_parser_::Parser>& parser);
    doof_header_type_11 parseUnary(const std::shared_ptr<::app_src_parser_::Parser>& parser);
}

namespace app_src_parser_ {
    struct Parser : public std::enable_shared_from_this<Parser> {
    std::string source;
    std::shared_ptr<std::vector<::app_src_lexer_::Token>> tokens;
    int32_t pos;
    bool inForIterable;
    bool inTagAttribute;
    int32_t tagAttributeDelimiterDepth;
    std::string errorMessage;
    int32_t errorLine;
    int32_t errorColumn;
    int32_t errorOffset;
    Parser(std::string source, std::shared_ptr<std::vector<::app_src_lexer_::Token>> tokens, int32_t pos, bool inForIterable, bool inTagAttribute, int32_t tagAttributeDelimiterDepth, std::string errorMessage, int32_t errorLine, int32_t errorColumn, int32_t errorOffset) : source(source), tokens(tokens), pos(pos), inForIterable(inForIterable), inTagAttribute(inTagAttribute), tagAttributeDelimiterDepth(tagAttributeDelimiterDepth), errorMessage(errorMessage), errorLine(errorLine), errorColumn(errorColumn), errorOffset(errorOffset) {}
    std::shared_ptr<::app_src_ast_::Program> parse();
    ::app_src_lexer_::Token current();
    ::app_src_lexer_::Token peek(int32_t offset);
    bool atEnd();
    ::app_src_lexer_::Token advance();
    bool check(::app_src_lexer_::TokenType kind);
    bool match(::app_src_lexer_::TokenType kind);
    ::app_src_lexer_::Token expect(::app_src_lexer_::TokenType kind, const std::string& message);
    void fail(const std::string& message);
    std::string expectedLabel(::app_src_lexer_::TokenType kind);
    std::string text(::app_src_lexer_::Token token);
    std::string currentText();
    ::app_src_ast_::AstLocation location();
    ::app_src_ast_::SourceSpan span(::app_src_ast_::AstLocation start);
    ::app_src_ast_::AstLocation previousEnd();
    bool sameLineAsPrevious();
    bool previousIs(::app_src_lexer_::TokenType kind);
    bool immediatelyAfterPrevious();
    void consumeSemicolon();
    ::app_src_ast_::SourceSpan locationSpan();
    doof_header_type_12 parseStatement();
    doof_header_type_12 parseExport();
    doof_header_type_12 parseConst(bool exported);
    doof_header_type_12 parseReadonly(bool exported);
    doof_header_type_12 parseLet();
    std::shared_ptr<::app_src_ast_::FunctionDeclaration> parseFunction(bool exported, bool static_, bool isolated_, bool private_, bool legacyMethod);
    doof_header_type_12 parseClass(bool exported, bool private_);
    doof_header_type_12 parseInterface(bool exported);
    doof_header_type_12 parseEnum(bool exported);
    doof_header_type_12 parseTypeAlias(bool exported);
    doof_header_type_12 parseImport();
    doof_header_type_12 parseMockImport();
    std::shared_ptr<::app_src_ast_::Block> parseBlock();
    doof_header_type_13 parseCaseExpression();
    bool looksLikePattern(::app_src_lexer_::TokenType separator);
    doof_header_type_12 parseDestructuring(const std::string& shape, const std::string& bindingKind, ::app_src_lexer_::TokenType separator);
    std::variant<std::monostate, std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> parseOptionalType();
    std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> parseTypeAnnotation();
    doof_header_type_13 parseExpression();
    doof_header_type_13 parseAdditive();
    doof_header_type_13 parseUnary();
};
    std::shared_ptr<::app_src_ast_::Program> parse(const std::string& source);
}

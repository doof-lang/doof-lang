#include "src_lexer.hpp"
#include <cmath>
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_lexer_ {

doof::JsonObject Token::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["kind"] = doof::json_value(TokenType_name(this->kind));
    (*_json)["length"] = doof::json_value(this->length);
    (*_json)["valueOffset"] = doof::json_value(this->valueOffset);
    (*_json)["valueLength"] = doof::json_value(this->valueLength);
    (*_json)["needsDecode"] = doof::json_value(this->needsDecode);
    (*_json)["line"] = doof::json_value(this->line);
    (*_json)["column"] = doof::json_value(this->column);
    (*_json)["offset"] = doof::json_value(this->offset);
    return _json;
}
doof::Result<Token, std::string> Token::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_kind = _object->find("kind");
    if (_iterator_kind == _object->end()) { return doof::Failure<std::string>{"Missing required field \"kind\""}; }
    if (!(doof::json_is_string(_iterator_kind->second))) { return doof::Failure<std::string>{"Field \"kind\" expected string but got " + std::string(doof::json_type_name(_iterator_kind->second))}; }
    auto _field_kind = TokenType_fromName(doof::json_as_string(_iterator_kind->second)).value();
    auto _iterator_length = _object->find("length");
    if (_iterator_length == _object->end()) { return doof::Failure<std::string>{"Missing required field \"length\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_length->second) : doof::json_is_number(_iterator_length->second)))) { return doof::Failure<std::string>{"Field \"length\" expected number but got " + std::string(doof::json_type_name(_iterator_length->second))}; }
    auto _field_length = (_lenient ? doof::json_as_int_lenient(_iterator_length->second) : doof::json_as_int(_iterator_length->second));
    auto _iterator_valueOffset = _object->find("valueOffset");
    if (_iterator_valueOffset == _object->end()) { return doof::Failure<std::string>{"Missing required field \"valueOffset\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_valueOffset->second) : doof::json_is_number(_iterator_valueOffset->second)))) { return doof::Failure<std::string>{"Field \"valueOffset\" expected number but got " + std::string(doof::json_type_name(_iterator_valueOffset->second))}; }
    auto _field_valueOffset = (_lenient ? doof::json_as_int_lenient(_iterator_valueOffset->second) : doof::json_as_int(_iterator_valueOffset->second));
    auto _iterator_valueLength = _object->find("valueLength");
    if (_iterator_valueLength == _object->end()) { return doof::Failure<std::string>{"Missing required field \"valueLength\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_valueLength->second) : doof::json_is_number(_iterator_valueLength->second)))) { return doof::Failure<std::string>{"Field \"valueLength\" expected number but got " + std::string(doof::json_type_name(_iterator_valueLength->second))}; }
    auto _field_valueLength = (_lenient ? doof::json_as_int_lenient(_iterator_valueLength->second) : doof::json_as_int(_iterator_valueLength->second));
    auto _iterator_needsDecode = _object->find("needsDecode");
    if (_iterator_needsDecode == _object->end()) { return doof::Failure<std::string>{"Missing required field \"needsDecode\""}; }
    if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_needsDecode->second) : doof::json_is_boolean(_iterator_needsDecode->second)))) { return doof::Failure<std::string>{"Field \"needsDecode\" expected boolean but got " + std::string(doof::json_type_name(_iterator_needsDecode->second))}; }
    auto _field_needsDecode = (_lenient ? doof::json_as_bool_lenient(_iterator_needsDecode->second) : doof::json_as_bool(_iterator_needsDecode->second));
    auto _iterator_line = _object->find("line");
    if (_iterator_line == _object->end()) { return doof::Failure<std::string>{"Missing required field \"line\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_line->second) : doof::json_is_number(_iterator_line->second)))) { return doof::Failure<std::string>{"Field \"line\" expected number but got " + std::string(doof::json_type_name(_iterator_line->second))}; }
    auto _field_line = (_lenient ? doof::json_as_int_lenient(_iterator_line->second) : doof::json_as_int(_iterator_line->second));
    auto _iterator_column = _object->find("column");
    if (_iterator_column == _object->end()) { return doof::Failure<std::string>{"Missing required field \"column\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_column->second) : doof::json_is_number(_iterator_column->second)))) { return doof::Failure<std::string>{"Field \"column\" expected number but got " + std::string(doof::json_type_name(_iterator_column->second))}; }
    auto _field_column = (_lenient ? doof::json_as_int_lenient(_iterator_column->second) : doof::json_as_int(_iterator_column->second));
    auto _iterator_offset = _object->find("offset");
    if (_iterator_offset == _object->end()) { return doof::Failure<std::string>{"Missing required field \"offset\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_offset->second) : doof::json_is_number(_iterator_offset->second)))) { return doof::Failure<std::string>{"Field \"offset\" expected number but got " + std::string(doof::json_type_name(_iterator_offset->second))}; }
    auto _field_offset = (_lenient ? doof::json_as_int_lenient(_iterator_offset->second) : doof::json_as_int(_iterator_offset->second));
    return doof::Success<Token>{Token{_field_kind, _field_length, _field_valueOffset, _field_valueLength, _field_needsDecode, _field_line, _field_column, _field_offset}};
}

doof::JsonObject LexerDiagnostic::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["severity"] = doof::json_value(this->severity);
    (*_json)["message"] = doof::json_value(this->message);
    (*_json)["line"] = doof::json_value(this->line);
    (*_json)["column"] = doof::json_value(this->column);
    return _json;
}
doof::Result<LexerDiagnostic, std::string> LexerDiagnostic::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_severity = _object->find("severity");
    if (_iterator_severity == _object->end()) { return doof::Failure<std::string>{"Missing required field \"severity\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_severity->second) : doof::json_is_string(_iterator_severity->second)))) { return doof::Failure<std::string>{"Field \"severity\" expected string but got " + std::string(doof::json_type_name(_iterator_severity->second))}; }
    auto _field_severity = (_lenient ? doof::json_as_string_lenient(_iterator_severity->second) : doof::json_as_string(_iterator_severity->second));
    auto _iterator_message = _object->find("message");
    if (_iterator_message == _object->end()) { return doof::Failure<std::string>{"Missing required field \"message\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_message->second) : doof::json_is_string(_iterator_message->second)))) { return doof::Failure<std::string>{"Field \"message\" expected string but got " + std::string(doof::json_type_name(_iterator_message->second))}; }
    auto _field_message = (_lenient ? doof::json_as_string_lenient(_iterator_message->second) : doof::json_as_string(_iterator_message->second));
    auto _iterator_line = _object->find("line");
    if (_iterator_line == _object->end()) { return doof::Failure<std::string>{"Missing required field \"line\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_line->second) : doof::json_is_number(_iterator_line->second)))) { return doof::Failure<std::string>{"Field \"line\" expected number but got " + std::string(doof::json_type_name(_iterator_line->second))}; }
    auto _field_line = (_lenient ? doof::json_as_int_lenient(_iterator_line->second) : doof::json_as_int(_iterator_line->second));
    auto _iterator_column = _object->find("column");
    if (_iterator_column == _object->end()) { return doof::Failure<std::string>{"Missing required field \"column\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_column->second) : doof::json_is_number(_iterator_column->second)))) { return doof::Failure<std::string>{"Field \"column\" expected number but got " + std::string(doof::json_type_name(_iterator_column->second))}; }
    auto _field_column = (_lenient ? doof::json_as_int_lenient(_iterator_column->second) : doof::json_as_int(_iterator_column->second));
    return doof::Success<LexerDiagnostic>{LexerDiagnostic{_field_severity, _field_message, _field_line, _field_column}};
}
std::string decodeEscapeCharacter(char32_t escaped) {
    if (escaped == U'\u006E') {
        return std::string("\n");
    }
    if (escaped == U'\u0074') {
        return std::string("\t");
    }
    if (escaped == U'\u0072') {
        return std::string("\r");
    }
    if (escaped == U'\\') {
        return std::string("\\");
    }
    if (escaped == U'\u0022') {
        return std::string("\"");
    }
    if (escaped == U'\'') {
        return std::string("'");
    }
    if (escaped == U'\u0060') {
        return std::string("`");
    }
    if (escaped == U'\u0024') {
        return std::string("$");
    }
    if (escaped == U'\u0030') {
        return std::string("");
    }
    return doof::to_string(escaped);
}
std::string tokenValue(Token token, std::string source) {
    const auto raw = doof::string_substring(source, token.valueOffset, (token.valueOffset + token.valueLength));
    if ((((token.kind == TokenType::IntLiteral) || (token.kind == TokenType::LongLiteral)) || (token.kind == TokenType::FloatLiteral)) || (token.kind == TokenType::DoubleLiteral)) {
        if (doof::string_contains(raw, std::string("_"))) {
            return doof::string_replaceAll(raw, std::string("_"), std::string(""));
        }
        return raw;
    }
    if (!token.needsDecode) {
        return raw;
    }
    auto value = std::string("");
    auto index = 0;
    while (index < static_cast<int32_t>(raw.size())) {
        if ((raw[index] == U'\\') && ((index + 1) < static_cast<int32_t>(raw.size()))) {
            (index = (index + 1));
            (value = (value + decodeEscapeCharacter(raw[index])));
        } else {
            (value = (value + doof::to_string(raw[index])));
        }
        (index = (index + 1));
    }
    return value;
}
TokenType keywordType(std::string word) {
    if (static_cast<int32_t>(word.size()) == 2) {
        if (word == std::string("if")) {
            return TokenType::If;
        }
        if (word == std::string("of")) {
            return TokenType::Of;
        }
        if (word == std::string("as")) {
            return TokenType::As;
        }
    } else if (static_cast<int32_t>(word.size()) == 3) {
        if (word == std::string("let")) {
            return TokenType::Let;
        }
        if (word == std::string("for")) {
            return TokenType::For;
        }
        if (word == std::string("try")) {
            return TokenType::Try;
        }
    } else if (static_cast<int32_t>(word.size()) == 4) {
        if (word == std::string("else")) {
            return TokenType::Else;
        }
        if (word == std::string("then")) {
            return TokenType::Then;
        }
        if (word == std::string("case")) {
            return TokenType::Case;
        }
        if (word == std::string("type")) {
            return TokenType::Type;
        }
        if (word == std::string("enum")) {
            return TokenType::Enum;
        }
        if (word == std::string("from")) {
            return TokenType::From;
        }
        if (word == std::string("true")) {
            return TokenType::True;
        }
        if (word == std::string("null")) {
            return TokenType::Null;
        }
        if (word == std::string("void")) {
            return TokenType::Void;
        }
        if (word == std::string("this")) {
            return TokenType::This;
        }
        if (word == std::string("weak")) {
            return TokenType::Weak;
        }
        if (word == std::string("with")) {
            return TokenType::With;
        }
        if (word == std::string("mock")) {
            return TokenType::Mock;
        }
    } else if (static_cast<int32_t>(word.size()) == 5) {
        if (word == std::string("const")) {
            return TokenType::Const;
        }
        if (word == std::string("yield")) {
            return TokenType::Yield;
        }
        if (word == std::string("while")) {
            return TokenType::While;
        }
        if (word == std::string("break")) {
            return TokenType::Break;
        }
        if (word == std::string("class")) {
            return TokenType::Class;
        }
        if (word == std::string("false")) {
            return TokenType::False;
        }
        if (word == std::string("catch")) {
            return TokenType::Catch;
        }
        if (word == std::string("async")) {
            return TokenType::Async;
        }
    } else if (static_cast<int32_t>(word.size()) == 6) {
        if (word == std::string("return")) {
            return TokenType::Return;
        }
        if (word == std::string("struct")) {
            return TokenType::Struct;
        }
        if (word == std::string("import")) {
            return TokenType::Import;
        }
        if (word == std::string("export")) {
            return TokenType::Export;
        }
        if (word == std::string("static")) {
            return TokenType::Static;
        }
        if (word == std::string("retire")) {
            return TokenType::Retire;
        }
    } else if (static_cast<int32_t>(word.size()) == 7) {
        if (word == std::string("private")) {
            return TokenType::Private;
        }
    } else if (static_cast<int32_t>(word.size()) == 8) {
        if (word == std::string("readonly")) {
            return TokenType::Readonly;
        }
        if (word == std::string("function")) {
            return TokenType::Function;
        }
        if (word == std::string("continue")) {
            return TokenType::Continue;
        }
        if (word == std::string("isolated")) {
            return TokenType::Isolated;
        }
    } else if (static_cast<int32_t>(word.size()) == 9) {
        if (word == std::string("interface")) {
            return TokenType::Interface;
        }
    } else if (static_cast<int32_t>(word.size()) == 10) {
        if (word == std::string("implements")) {
            return TokenType::Implements;
        }
        if (word == std::string("destructor")) {
            return TokenType::Destructor;
        }
    }
    return TokenType::Identifier;
}

std::shared_ptr<std::vector<Token>> Lexer::tokenize() {
    this->tokens->reserve(((static_cast<int32_t>(this->source.size()) / 2) + 16));
    while (this->pos < static_cast<int32_t>(this->source.size())) {
        skipWhitespaceAndComments();
        if (this->pos >= static_cast<int32_t>(this->source.size())) {
            break;
        }
        if (((static_cast<int32_t>((this->templateDelimiters)->size()) > 0) && (peek(0) == U'\u007D')) && ((*this->braceDepth)[(static_cast<int32_t>((this->braceDepth)->size()) - 1)] == 0)) {
            advance();
            const auto ignoredBrace = [&]() -> int32_t { auto _try_value = doof::array_pop(this->braceDepth); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
            readTemplateContinuation();
            continue;
        }
        const auto ch = peek(0);
        if ((ch == U'\u0022') || (ch == U'\u0060')) {
            readQuoted(ch);
        } else if (ch == U'\'') {
            readChar();
        } else if (isDigit(ch)) {
            readNumber();
        } else if (isIdentStart(ch)) {
            readIdentifier();
        } else {
            readOperatorOrPunctuation();
        }
    }
    addToken(TokenType::EndOfFile, this->pos, 0, this->pos, 0, false, this->line, this->column);
    return this->tokens;
}
char32_t Lexer::peek(int32_t offset) {
    if ((this->pos + offset) >= static_cast<int32_t>(this->source.size())) {
        return U'\0';
    }
    return this->source[(this->pos + offset)];
}
char32_t Lexer::advance() {
    const auto ch = this->source[this->pos];
    (this->pos = (this->pos + 1));
    if (ch == U'\n') {
        (this->line = (this->line + 1));
        (this->column = 1);
    } else {
        (this->column = (this->column + 1));
    }
    return ch;
}
void Lexer::addToken(TokenType kind, int32_t tokenOffset, int32_t tokenLength, int32_t valueOffset, int32_t valueLength, bool needsDecode, int32_t tokenLine, int32_t tokenColumn) {
    this->tokens->push_back(Token{kind, tokenLength, valueOffset, valueLength, needsDecode, tokenLine, tokenColumn, tokenOffset});
}
void Lexer::diagnostic(std::string message, int32_t diagnosticLine, int32_t diagnosticColumn) {
    this->diagnostics->push_back(LexerDiagnostic{std::string("error"), message, diagnosticLine, diagnosticColumn});
}
void Lexer::skipWhitespaceAndComments() {
    while (this->pos < static_cast<int32_t>(this->source.size())) {
        const auto ch = peek(0);
        if ((((ch == U'\u0020') || (ch == U'\t')) || (ch == U'\r')) || (ch == U'\n')) {
            advance();
        } else if ((ch == U'\u002F') && (peek(1) == U'\u002F')) {
            while ((this->pos < static_cast<int32_t>(this->source.size())) && (peek(0) != U'\n')) {
                advance();
            }
        } else if ((ch == U'\u002F') && (peek(1) == U'\u002A')) {
            const auto commentLine = this->line;
            const auto commentColumn = this->column;
            advance();
            advance();
            auto terminated = false;
            while (this->pos < static_cast<int32_t>(this->source.size())) {
                if ((peek(0) == U'\u002A') && (peek(1) == U'\u002F')) {
                    advance();
                    advance();
                    (terminated = true);
                    break;
                }
                advance();
            }
            if (!terminated) {
                diagnostic(std::string("Unterminated block comment"), commentLine, commentColumn);
            }
        } else {
            break;
        }
    }
}
bool Lexer::isDigit(char32_t ch) {
    return ((ch >= U'\u0030') && (ch <= U'\u0039'));
}
bool Lexer::isHexDigit(char32_t ch) {
    return ((((ch >= U'\u0030') && (ch <= U'\u0039')) || ((ch >= U'\u0061') && (ch <= U'\u0066'))) || ((ch >= U'\u0041') && (ch <= U'\u0046')));
}
bool Lexer::isBaseDigit(char32_t ch, int32_t base) {
    if (base == 10) {
        return isDigit(ch);
    }
    if (base == 16) {
        return isHexDigit(ch);
    }
    return ((ch == U'\u0030') || (ch == U'\u0031'));
}
bool Lexer::isIdentStart(char32_t ch) {
    return ((((ch >= U'\u0061') && (ch <= U'\u007A')) || ((ch >= U'\u0041') && (ch <= U'\u005A'))) || (ch == U'\u005F'));
}
bool Lexer::isIdentPart(char32_t ch) {
    return (isIdentStart(ch) || isDigit(ch));
}
void Lexer::readDigits(int32_t base) {
    auto sawDigit = false;
    while (this->pos < static_cast<int32_t>(this->source.size())) {
        const auto ch = peek(0);
        if (isBaseDigit(ch, base)) {
            advance();
            (sawDigit = true);
        } else if (ch == U'\u005F') {
            if (sawDigit && isBaseDigit(peek(1), base)) {
                advance();
            } else {
                const auto separatorLine = this->line;
                const auto separatorColumn = this->column;
                while (peek(0) == U'\u005F') {
                    advance();
                }
                diagnostic(std::string("Numeric separators must appear between digits"), separatorLine, separatorColumn);
            }
        } else {
            break;
        }
    }
}
void Lexer::readNumber() {
    const auto start = this->pos;
    const auto tokenLine = this->line;
    const auto tokenColumn = this->column;
    if ((peek(0) == U'\u0030') && ((peek(1) == U'\u0078') || (peek(1) == U'\u0058'))) {
        advance();
        advance();
        readDigits(16);
        readNumericSuffix(start, this->pos, tokenLine, tokenColumn);
        return;
    }
    if ((peek(0) == U'\u0030') && ((peek(1) == U'\u0062') || (peek(1) == U'\u0042'))) {
        advance();
        advance();
        readDigits(2);
        readNumericSuffix(start, this->pos, tokenLine, tokenColumn);
        return;
    }
    readDigits(10);
    if (((peek(0) == U'\u002E') && (peek(1) != U'\u002E')) && (peek(1) != U'\u003C')) {
        advance();
        readDigits(10);
        const auto valueEnd = this->pos;
        if ((peek(0) == U'\u0066') || (peek(0) == U'\u0046')) {
            advance();
            addToken(TokenType::FloatLiteral, start, (this->pos - start), start, (valueEnd - start), false, tokenLine, tokenColumn);
        } else {
            addToken(TokenType::DoubleLiteral, start, (this->pos - start), start, (valueEnd - start), false, tokenLine, tokenColumn);
        }
        return;
    }
    readNumericSuffix(start, this->pos, tokenLine, tokenColumn);
}
void Lexer::readNumericSuffix(int32_t valueStart, int32_t valueEnd, int32_t tokenLine, int32_t tokenColumn) {
    if ((peek(0) == U'\u004C') || (peek(0) == U'\u006C')) {
        advance();
        addToken(TokenType::LongLiteral, valueStart, (this->pos - valueStart), valueStart, (valueEnd - valueStart), false, tokenLine, tokenColumn);
    } else if ((peek(0) == U'\u0066') || (peek(0) == U'\u0046')) {
        advance();
        addToken(TokenType::FloatLiteral, valueStart, (this->pos - valueStart), valueStart, (valueEnd - valueStart), false, tokenLine, tokenColumn);
    } else {
        addToken(TokenType::IntLiteral, valueStart, (this->pos - valueStart), valueStart, (valueEnd - valueStart), false, tokenLine, tokenColumn);
    }
}
void Lexer::readIdentifier() {
    const auto start = this->pos;
    const auto tokenLine = this->line;
    const auto tokenColumn = this->column;
    while ((this->pos < static_cast<int32_t>(this->source.size())) && isIdentPart(peek(0))) {
        advance();
    }
    auto value = doof::string_substring(this->source, start, this->pos);
    if ((value == std::string("try")) && ((peek(0) == U'\u0021') || (peek(0) == U'\u003F'))) {
        advance();
        addToken(TokenType::Identifier, start, (this->pos - start), start, (this->pos - start), false, tokenLine, tokenColumn);
        return;
    }
    if (value == std::string("_")) {
        addToken(TokenType::Underscore, start, (this->pos - start), start, (this->pos - start), false, tokenLine, tokenColumn);
    } else {
        addToken(keywordType(value), start, (this->pos - start), start, (this->pos - start), false, tokenLine, tokenColumn);
    }
}
void Lexer::readQuoted(char32_t delimiter) {
    const auto start = this->pos;
    const auto tokenLine = this->line;
    const auto tokenColumn = this->column;
    advance();
    const auto contentStart = this->pos;
    auto needsDecode = false;
    auto closed = false;
    while ((this->pos < static_cast<int32_t>(this->source.size())) && (peek(0) != delimiter)) {
        if ((peek(0) == U'\u0024') && (peek(1) == U'\u007B')) {
            addToken(TokenType::TemplateLiteralStart, start, (this->pos - start), contentStart, (this->pos - contentStart), needsDecode, tokenLine, tokenColumn);
            advance();
            advance();
            this->templateDelimiters->push_back(delimiter);
            this->braceDepth->push_back(0);
            return;
        }
        if (peek(0) == U'\\') {
            (needsDecode = true);
            advance();
            advance();
        } else {
            advance();
        }
    }
    if (this->pos < static_cast<int32_t>(this->source.size())) {
        advance();
        (closed = true);
    } else {
        diagnostic(std::string("Unterminated string literal"), tokenLine, tokenColumn);
    }
    auto valueEnd = this->pos;
    if (closed) {
        (valueEnd = (this->pos - 1));
    }
    addToken(TokenType::StringLiteral, start, (this->pos - start), contentStart, (valueEnd - contentStart), needsDecode, tokenLine, tokenColumn);
}
void Lexer::readTemplateContinuation() {
    const auto start = this->pos;
    const auto tokenLine = this->line;
    const auto tokenColumn = this->column;
    const auto delimiter = (*this->templateDelimiters)[(static_cast<int32_t>((this->templateDelimiters)->size()) - 1)];
    const auto contentStart = this->pos;
    auto needsDecode = false;
    auto closed = false;
    while ((this->pos < static_cast<int32_t>(this->source.size())) && (peek(0) != delimiter)) {
        if ((peek(0) == U'\u0024') && (peek(1) == U'\u007B')) {
            addToken(TokenType::TemplateLiteralMiddle, start, (this->pos - start), contentStart, (this->pos - contentStart), needsDecode, tokenLine, tokenColumn);
            advance();
            advance();
            this->braceDepth->push_back(0);
            return;
        }
        if (peek(0) == U'\\') {
            (needsDecode = true);
            advance();
            advance();
        } else {
            advance();
        }
    }
    if (this->pos < static_cast<int32_t>(this->source.size())) {
        advance();
        (closed = true);
    } else {
        diagnostic(std::string("Unterminated template literal"), tokenLine, tokenColumn);
    }
    auto valueEnd = this->pos;
    if (closed) {
        (valueEnd = (this->pos - 1));
    }
    const auto ignoredDelimiter = [&]() -> char32_t { auto _try_value = doof::array_pop(this->templateDelimiters); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
    addToken(TokenType::TemplateLiteralEnd, start, (this->pos - start), contentStart, (valueEnd - contentStart), needsDecode, tokenLine, tokenColumn);
}
void Lexer::readChar() {
    const auto start = this->pos;
    const auto tokenLine = this->line;
    const auto tokenColumn = this->column;
    advance();
    const auto valueStart = this->pos;
    auto needsDecode = false;
    if (peek(0) == U'\\') {
        (needsDecode = true);
        advance();
        advance();
    } else if (this->pos < static_cast<int32_t>(this->source.size())) {
        advance();
    }
    const auto valueEnd = this->pos;
    if ((this->pos < static_cast<int32_t>(this->source.size())) && (peek(0) == U'\'')) {
        advance();
    }
    addToken(TokenType::CharLiteral, start, (this->pos - start), valueStart, (valueEnd - valueStart), needsDecode, tokenLine, tokenColumn);
}
void Lexer::emit(TokenType kind, int32_t tokenLine, int32_t tokenColumn, int32_t start, int32_t count) {
    if (count > 0) {
        advance();
    }
    if (count > 1) {
        advance();
    }
    if (count > 2) {
        advance();
    }
    if (count > 3) {
        advance();
    }
    if (count > 4) {
        advance();
    }
    if (count > 5) {
        advance();
    }
    if (count > 6) {
        advance();
    }
    addToken(kind, start, count, start, count, false, tokenLine, tokenColumn);
}
void Lexer::readOperatorOrPunctuation() {
    const auto start = this->pos;
    const auto tokenLine = this->line;
    const auto tokenColumn = this->column;
    const auto ch = peek(0);
    if (ch == U'\u0028') {
        emit(TokenType::LeftParen, tokenLine, tokenColumn, start, 1);
        return;
    }
    if (ch == U'\u0029') {
        emit(TokenType::RightParen, tokenLine, tokenColumn, start, 1);
        return;
    }
    if (ch == U'\u007B') {
        advance();
        if (static_cast<int32_t>((this->braceDepth)->size()) > 0) {
            ((*this->braceDepth)[(static_cast<int32_t>((this->braceDepth)->size()) - 1)] = ((*this->braceDepth)[(static_cast<int32_t>((this->braceDepth)->size()) - 1)] + 1));
        }
        addToken(TokenType::LeftBrace, start, 1, start, 1, false, tokenLine, tokenColumn);
        return;
    }
    if (ch == U'\u007D') {
        advance();
        if (static_cast<int32_t>((this->braceDepth)->size()) > 0) {
            ((*this->braceDepth)[(static_cast<int32_t>((this->braceDepth)->size()) - 1)] = ((*this->braceDepth)[(static_cast<int32_t>((this->braceDepth)->size()) - 1)] - 1));
        }
        addToken(TokenType::RightBrace, start, 1, start, 1, false, tokenLine, tokenColumn);
        return;
    }
    if (ch == U'\u005B') {
        emit(TokenType::LeftBracket, tokenLine, tokenColumn, start, 1);
        return;
    }
    if (ch == U'\u005D') {
        emit(TokenType::RightBracket, tokenLine, tokenColumn, start, 1);
        return;
    }
    if (ch == U'\u002C') {
        emit(TokenType::Comma, tokenLine, tokenColumn, start, 1);
        return;
    }
    if (ch == U'\u003B') {
        emit(TokenType::Semicolon, tokenLine, tokenColumn, start, 1);
        return;
    }
    if (ch == U'\u007E') {
        emit(TokenType::Tilde, tokenLine, tokenColumn, start, 1);
        return;
    }
    if (ch == U'\u002E') {
        if ((peek(1) == U'\u002E') && (peek(2) == U'\u002E')) {
            emit(TokenType::Ellipsis, tokenLine, tokenColumn, start, 3);
        } else if ((peek(1) == U'\u002E') && (peek(2) == U'\u003C')) {
            emit(TokenType::DotDotLess, tokenLine, tokenColumn, start, 3);
        } else if (peek(1) == U'\u002E') {
            emit(TokenType::DotDot, tokenLine, tokenColumn, start, 2);
        } else {
            emit(TokenType::Dot, tokenLine, tokenColumn, start, 1);
        }
        return;
    }
    if (ch == U'\u003A') {
        if (peek(1) == U'\u003A') {
            emit(TokenType::DoubleColon, tokenLine, tokenColumn, start, 2);
        } else if (peek(1) == U'\u003D') {
            emit(TokenType::ColonEqual, tokenLine, tokenColumn, start, 2);
        } else {
            emit(TokenType::Colon, tokenLine, tokenColumn, start, 1);
        }
        return;
    }
    if (ch == U'\u003D') {
        if (peek(1) == U'\u003D') {
            emit(TokenType::EqualEqual, tokenLine, tokenColumn, start, 2);
        } else if (peek(1) == U'\u003E') {
            emit(TokenType::Arrow, tokenLine, tokenColumn, start, 2);
        } else {
            emit(TokenType::Equal, tokenLine, tokenColumn, start, 1);
        }
        return;
    }
    if (ch == U'\u002B') {
        if (peek(1) == U'\u003D') {
            emit(TokenType::PlusEqual, tokenLine, tokenColumn, start, 2);
        } else {
            emit(TokenType::Plus, tokenLine, tokenColumn, start, 1);
        }
        return;
    }
    if (ch == U'\u002D') {
        if (peek(1) == U'\u003E') {
            emit(TokenType::RightArrow, tokenLine, tokenColumn, start, 2);
        } else if (peek(1) == U'\u003D') {
            emit(TokenType::MinusEqual, tokenLine, tokenColumn, start, 2);
        } else {
            emit(TokenType::Minus, tokenLine, tokenColumn, start, 1);
        }
        return;
    }
    if (ch == U'\u002A') {
        if ((peek(1) == U'\u002A') && (peek(2) == U'\u003D')) {
            emit(TokenType::StarStarEqual, tokenLine, tokenColumn, start, 3);
        } else if (peek(1) == U'\u002A') {
            emit(TokenType::StarStar, tokenLine, tokenColumn, start, 2);
        } else if (peek(1) == U'\u003D') {
            emit(TokenType::StarEqual, tokenLine, tokenColumn, start, 2);
        } else {
            emit(TokenType::Star, tokenLine, tokenColumn, start, 1);
        }
        return;
    }
    if (ch == U'\u002F') {
        if (peek(1) == U'\u003D') {
            emit(TokenType::SlashEqual, tokenLine, tokenColumn, start, 2);
        } else {
            emit(TokenType::Slash, tokenLine, tokenColumn, start, 1);
        }
        return;
    }
    if (ch == U'\u0025') {
        if (peek(1) == U'\u003D') {
            emit(TokenType::PercentEqual, tokenLine, tokenColumn, start, 2);
        } else {
            emit(TokenType::Percent, tokenLine, tokenColumn, start, 1);
        }
        return;
    }
    if (ch == U'\\') {
        if (peek(1) == U'\u003D') {
            emit(TokenType::BackslashEqual, tokenLine, tokenColumn, start, 2);
        } else {
            emit(TokenType::Backslash, tokenLine, tokenColumn, start, 1);
        }
        return;
    }
    if (ch == U'\u0026') {
        if (peek(1) == U'\u0026') {
            emit(TokenType::AmpersandAmpersand, tokenLine, tokenColumn, start, 2);
        } else if (peek(1) == U'\u003D') {
            emit(TokenType::AmpersandEqual, tokenLine, tokenColumn, start, 2);
        } else {
            emit(TokenType::Ampersand, tokenLine, tokenColumn, start, 1);
        }
        return;
    }
    if (ch == U'\u007C') {
        if (peek(1) == U'\u007C') {
            emit(TokenType::PipePipe, tokenLine, tokenColumn, start, 2);
        } else if (peek(1) == U'\u003D') {
            emit(TokenType::PipeEqual, tokenLine, tokenColumn, start, 2);
        } else {
            emit(TokenType::Pipe, tokenLine, tokenColumn, start, 1);
        }
        return;
    }
    if (ch == U'\u005E') {
        if (peek(1) == U'\u003D') {
            emit(TokenType::CaretEqual, tokenLine, tokenColumn, start, 2);
        } else {
            emit(TokenType::Caret, tokenLine, tokenColumn, start, 1);
        }
        return;
    }
    if (ch == U'\u003C') {
        if ((peek(1) == U'\u003C') && (peek(2) == U'\u003D')) {
            emit(TokenType::LessLessEqual, tokenLine, tokenColumn, start, 3);
        } else if (peek(1) == U'\u003C') {
            emit(TokenType::LessLess, tokenLine, tokenColumn, start, 2);
        } else if (peek(1) == U'\u002D') {
            emit(TokenType::LeftArrow, tokenLine, tokenColumn, start, 2);
        } else if (peek(1) == U'\u003D') {
            emit(TokenType::LessEqual, tokenLine, tokenColumn, start, 2);
        } else {
            emit(TokenType::Less, tokenLine, tokenColumn, start, 1);
        }
        return;
    }
    if (ch == U'\u003E') {
        if (((peek(1) == U'\u003E') && (peek(2) == U'\u003E')) && (peek(3) == U'\u003D')) {
            emit(TokenType::GreaterGreaterEqual, tokenLine, tokenColumn, start, 4);
        } else if ((peek(1) == U'\u003E') && (peek(2) == U'\u003E')) {
            emit(TokenType::GreaterGreaterGreater, tokenLine, tokenColumn, start, 3);
        } else if ((peek(1) == U'\u003E') && (peek(2) == U'\u003D')) {
            emit(TokenType::GreaterGreaterEqual, tokenLine, tokenColumn, start, 3);
        } else if (peek(1) == U'\u003E') {
            emit(TokenType::GreaterGreater, tokenLine, tokenColumn, start, 2);
        } else if (peek(1) == U'\u003D') {
            emit(TokenType::GreaterEqual, tokenLine, tokenColumn, start, 2);
        } else {
            emit(TokenType::Greater, tokenLine, tokenColumn, start, 1);
        }
        return;
    }
    if (ch == U'\u0021') {
        if (peek(1) == U'\u003D') {
            emit(TokenType::BangEqual, tokenLine, tokenColumn, start, 2);
        } else if (peek(1) == U'\u002E') {
            emit(TokenType::BangDot, tokenLine, tokenColumn, start, 2);
        } else {
            emit(TokenType::Bang, tokenLine, tokenColumn, start, 1);
        }
        return;
    }
    if (ch == U'\u003F') {
        if ((peek(1) == U'\u003F') && (peek(2) == U'\u003D')) {
            emit(TokenType::QuestionQuestionEqual, tokenLine, tokenColumn, start, 3);
        } else if (peek(1) == U'\u003F') {
            emit(TokenType::QuestionQuestion, tokenLine, tokenColumn, start, 2);
        } else if (peek(1) == U'\u002E') {
            emit(TokenType::QuestionDot, tokenLine, tokenColumn, start, 2);
        } else if (peek(1) == U'\u005B') {
            emit(TokenType::QuestionBracket, tokenLine, tokenColumn, start, 2);
        } else {
            emit(TokenType::Identifier, tokenLine, tokenColumn, start, 1);
        }
        return;
    }
    if ((((ch == U'\u0040') && ((this->pos + 7) <= static_cast<int32_t>(this->source.size()))) && (doof::string_substring(this->source, this->pos, (this->pos + 7)) == std::string("@caller"))) && !isIdentPart(peek(7))) {
        emit(TokenType::CallerIntrinsic, tokenLine, tokenColumn, start, 7);
        return;
    }
    diagnostic(((std::string("Unexpected character: '") + doof::to_string(ch)) + std::string("'")), this->line, this->column);
    advance();
}
doof::JsonObject Lexer::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["source"] = doof::json_value(this->source);
    (*_json)["pos"] = doof::json_value(this->pos);
    (*_json)["line"] = doof::json_value(this->line);
    (*_json)["column"] = doof::json_value(this->column);
    (*_json)["tokens"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->tokens->size()); for (const auto& _element : *this->tokens) { _array->push_back(doof::json_value(_element.toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["diagnostics"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->diagnostics->size()); for (const auto& _element : *this->diagnostics) { _array->push_back(doof::json_value(_element.toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["templateDelimiters"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->templateDelimiters->size()); for (const auto& _element : *this->templateDelimiters) { _array->push_back(doof::json_value(std::string(1, static_cast<char>(_element)))); } return doof::json_value(_array); }();
    (*_json)["braceDepth"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->braceDepth->size()); for (const auto& _element : *this->braceDepth) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<Lexer>, std::string> Lexer::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_source = _object->find("source");
    if (_iterator_source == _object->end()) { return doof::Failure<std::string>{"Missing required field \"source\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_source->second) : doof::json_is_string(_iterator_source->second)))) { return doof::Failure<std::string>{"Field \"source\" expected string but got " + std::string(doof::json_type_name(_iterator_source->second))}; }
    auto _field_source = (_lenient ? doof::json_as_string_lenient(_iterator_source->second) : doof::json_as_string(_iterator_source->second));
    std::optional<int32_t> _field_pos;
    if (auto _iterator_pos = _object->find("pos"); _iterator_pos != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_pos->second) : doof::json_is_number(_iterator_pos->second)))) { return doof::Failure<std::string>{"Field \"pos\" expected number but got " + std::string(doof::json_type_name(_iterator_pos->second))}; }
        _field_pos = (_lenient ? doof::json_as_int_lenient(_iterator_pos->second) : doof::json_as_int(_iterator_pos->second));
    } else {
        _field_pos = int32_t{0};
    }
    std::optional<int32_t> _field_line;
    if (auto _iterator_line = _object->find("line"); _iterator_line != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_line->second) : doof::json_is_number(_iterator_line->second)))) { return doof::Failure<std::string>{"Field \"line\" expected number but got " + std::string(doof::json_type_name(_iterator_line->second))}; }
        _field_line = (_lenient ? doof::json_as_int_lenient(_iterator_line->second) : doof::json_as_int(_iterator_line->second));
    } else {
        _field_line = int32_t{1};
    }
    std::optional<int32_t> _field_column;
    if (auto _iterator_column = _object->find("column"); _iterator_column != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_column->second) : doof::json_is_number(_iterator_column->second)))) { return doof::Failure<std::string>{"Field \"column\" expected number but got " + std::string(doof::json_type_name(_iterator_column->second))}; }
        _field_column = (_lenient ? doof::json_as_int_lenient(_iterator_column->second) : doof::json_as_int(_iterator_column->second));
    } else {
        _field_column = int32_t{1};
    }
    std::optional<std::shared_ptr<std::vector<Token>>> _field_tokens;
    if (auto _iterator_tokens = _object->find("tokens"); _iterator_tokens != _object->end()) {
        if (!(doof::json_is_array(_iterator_tokens->second))) { return doof::Failure<std::string>{"Field \"tokens\" expected array but got " + std::string(doof::json_type_name(_iterator_tokens->second))}; }
        _field_tokens = [&]() { const auto* _array = doof::json_as_array(_iterator_tokens->second); auto _values = std::make_shared<std::vector<Token>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(Token::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_tokens = std::shared_ptr<std::vector<Token>>{std::make_shared<std::vector<Token>>(std::vector<Token>{})};
    }
    std::optional<std::shared_ptr<std::vector<LexerDiagnostic>>> _field_diagnostics;
    if (auto _iterator_diagnostics = _object->find("diagnostics"); _iterator_diagnostics != _object->end()) {
        if (!(doof::json_is_array(_iterator_diagnostics->second))) { return doof::Failure<std::string>{"Field \"diagnostics\" expected array but got " + std::string(doof::json_type_name(_iterator_diagnostics->second))}; }
        _field_diagnostics = [&]() { const auto* _array = doof::json_as_array(_iterator_diagnostics->second); auto _values = std::make_shared<std::vector<LexerDiagnostic>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(LexerDiagnostic::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_diagnostics = std::shared_ptr<std::vector<LexerDiagnostic>>{std::make_shared<std::vector<LexerDiagnostic>>(std::vector<LexerDiagnostic>{})};
    }
    std::optional<std::shared_ptr<std::vector<char32_t>>> _field_templateDelimiters;
    if (auto _iterator_templateDelimiters = _object->find("templateDelimiters"); _iterator_templateDelimiters != _object->end()) {
        if (!(doof::json_is_array(_iterator_templateDelimiters->second))) { return doof::Failure<std::string>{"Field \"templateDelimiters\" expected array but got " + std::string(doof::json_type_name(_iterator_templateDelimiters->second))}; }
        _field_templateDelimiters = [&]() { const auto* _array = doof::json_as_array(_iterator_templateDelimiters->second); auto _values = std::make_shared<std::vector<char32_t>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(static_cast<char32_t>(doof::json_as_string(_element)[0])); } return _values; }();
    } else {
        _field_templateDelimiters = std::shared_ptr<std::vector<char32_t>>{std::make_shared<std::vector<char32_t>>(std::vector<char32_t>{})};
    }
    std::optional<std::shared_ptr<std::vector<int32_t>>> _field_braceDepth;
    if (auto _iterator_braceDepth = _object->find("braceDepth"); _iterator_braceDepth != _object->end()) {
        if (!(doof::json_is_array(_iterator_braceDepth->second))) { return doof::Failure<std::string>{"Field \"braceDepth\" expected array but got " + std::string(doof::json_type_name(_iterator_braceDepth->second))}; }
        _field_braceDepth = [&]() { const auto* _array = doof::json_as_array(_iterator_braceDepth->second); auto _values = std::make_shared<std::vector<int32_t>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_int_lenient(_element) : doof::json_as_int(_element))); } return _values; }();
    } else {
        _field_braceDepth = std::shared_ptr<std::vector<int32_t>>{std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{})};
    }
    return doof::Success<std::shared_ptr<Lexer>>{std::make_shared<Lexer>(_field_source, _field_pos.value(), _field_line.value(), _field_column.value(), _field_tokens.value(), _field_diagnostics.value(), _field_templateDelimiters.value(), _field_braceDepth.value())};
}
}

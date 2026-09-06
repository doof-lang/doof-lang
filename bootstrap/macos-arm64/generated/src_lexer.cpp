#include "src_lexer.hpp"

namespace app_src_lexer_ {


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
        return doof::to_string(U'\0');
    }
    return doof::to_string(escaped);
}
std::string tokenValue(Token token, const std::string& source) {
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
        if ((doof::string_at(raw, index, "src/lexer", 175) == U'\\') && ((index + 1) < static_cast<int32_t>(raw.size()))) {
            (index = (index + 1));
            (value = (value + decodeEscapeCharacter(doof::string_at(raw, index, "src/lexer", 177))));
            (index = (index + 1));
        } else {
            const auto width = utf8SequenceLength(doof::string_at(raw, index, "src/lexer", 180));
            (value = (value + doof::string_substring(raw, index, (index + width))));
            (index = (index + width));
        }
    }
    return value;
}
int32_t utf8SequenceLength(char32_t first) {
    const auto value = static_cast<int32_t>(first);
    if (value < 128) {
        return 1;
    }
    if ((value >= 194) && (value <= 223)) {
        return 2;
    }
    if ((value >= 224) && (value <= 239)) {
        return 3;
    }
    if ((value >= 240) && (value <= 244)) {
        return 4;
    }
    return 1;
}
char32_t charTokenValue(Token token, const std::string& source) {
    const auto value = tokenValue(token, source);
    if (static_cast<int32_t>(value.size()) == 0) {
        return U'\0';
    }
    return ::doof::char_from_utf8(value);
}
TokenType keywordType(const std::string& word) {
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
        if (word == std::string("none")) {
            return TokenType::None;
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
    (static_cast<void>(this->tokens->reserve(((static_cast<int32_t>(this->source.size()) / 2) + 16))), std::monostate{});
    if (((static_cast<int32_t>(this->source.size()) >= 2) && (doof::string_at(this->source, 0, "src/lexer", 283) == U'\u0023')) && (doof::string_at(this->source, 1, "src/lexer", 283) == U'\u0021')) {
        while ((this->pos < static_cast<int32_t>(this->source.size())) && (peek(0) != U'\n')) {
            advance();
        }
    }
    while (this->pos < static_cast<int32_t>(this->source.size())) {
        if (this->tagMode == std::string("children")) {
            if ((peek(0) == U'\u003C') && (peek(1) == U'\u002F')) {
                (static_cast<void>(emit(TokenType::Less, this->line, this->column, this->pos, 1)), std::monostate{});
                (static_cast<void>(emit(TokenType::Slash, this->line, this->column, this->pos, 1)), std::monostate{});
                (this->tagMode = std::string("closing-tag"));
                continue;
            }
            if ((peek(0) == U'\u003C') && isIdentStart(peek(1))) {
                (static_cast<void>(beginTag()), std::monostate{});
                continue;
            }
            if (peek(0) == U'\u007B') {
                (static_cast<void>(beginTagExpression()), std::monostate{});
                continue;
            }
            (static_cast<void>(readTagText()), std::monostate{});
            continue;
        }
        if ((this->tagMode == std::string("opening-tag")) || (this->tagMode == std::string("closing-tag"))) {
            (static_cast<void>(skipWhitespaceAndComments()), std::monostate{});
            if (this->pos >= static_cast<int32_t>(this->source.size())) {
                break;
            }
            if ((this->tagMode == std::string("opening-tag")) && (peek(0) == U'\u007B')) {
                (static_cast<void>(beginTagExpression()), std::monostate{});
                continue;
            }
            if (((this->tagMode == std::string("opening-tag")) && (this->tagAttributeDelimiterDepth == 0)) && (peek(0) == U'\u003C')) {
                (this->tagGenericDepth = (this->tagGenericDepth + 1));
                (static_cast<void>(emit(TokenType::Less, this->line, this->column, this->pos, 1)), std::monostate{});
                continue;
            }
            if (((peek(0) == U'\u003E') && (this->tagAttributeDelimiterDepth == 0)) && (this->tagGenericDepth > 0)) {
                (this->tagGenericDepth = (this->tagGenericDepth - 1));
                (static_cast<void>(emit(TokenType::Greater, this->line, this->column, this->pos, 1)), std::monostate{});
                continue;
            }
            if ((peek(0) == U'\u003E') && (this->tagAttributeDelimiterDepth == 0)) {
                (static_cast<void>(emit(TokenType::Greater, this->line, this->column, this->pos, 1)), std::monostate{});
                (this->tagAttributeDelimiterDepth = 0);
                if (this->tagMode == std::string("closing-tag")) {
                    (this->tagMode = [&]() -> std::string { auto _try_value = doof::array_pop(this->tagModeStack); if (doof::is_failure(_try_value)) doof::panic_at("src/lexer", 327, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
                } else if ((static_cast<int32_t>((this->tokens)->size()) >= 2) && (doof::array_at(this->tokens, (static_cast<int32_t>((this->tokens)->size()) - 2), "src/lexer", 328).kind == TokenType::Slash)) {
                    (this->tagMode = [&]() -> std::string { auto _try_value = doof::array_pop(this->tagModeStack); if (doof::is_failure(_try_value)) doof::panic_at("src/lexer", 329, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
                } else {
                    (this->tagMode = std::string("children"));
                }
                continue;
            }
            if (this->tagMode == std::string("opening-tag")) {
                if ((peek(0) == U'\u0028') || (peek(0) == U'\u005B')) {
                    (this->tagAttributeDelimiterDepth = (this->tagAttributeDelimiterDepth + 1));
                } else if (((peek(0) == U'\u0029') || (peek(0) == U'\u005D')) && (this->tagAttributeDelimiterDepth > 0)) {
                    (this->tagAttributeDelimiterDepth = (this->tagAttributeDelimiterDepth - 1));
                }
            }
        }
        (static_cast<void>(skipWhitespaceAndComments()), std::monostate{});
        if (this->pos >= static_cast<int32_t>(this->source.size())) {
            break;
        }
        if (((((this->tagMode == std::string("code")) || (this->tagMode == std::string("tag-expression"))) && (peek(0) == U'\u003C')) && isIdentStart(peek(1))) && canStartTag()) {
            (static_cast<void>(beginTag()), std::monostate{});
            continue;
        }
        if (((static_cast<int32_t>((this->templateDelimiters)->size()) > 0) && (peek(0) == U'\u007D')) && (doof::array_at(this->braceDepth, (static_cast<int32_t>((this->braceDepth)->size()) - 1), "src/lexer", 352) == 0)) {
            advance();
            const auto ignoredBrace = [&]() -> int32_t { auto _try_value = doof::array_pop(this->braceDepth); if (doof::is_failure(_try_value)) doof::panic_at("src/lexer", 354, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
            const auto ignoredLine = [&]() -> int32_t { auto _try_value = doof::array_pop(this->interpolationLines); if (doof::is_failure(_try_value)) doof::panic_at("src/lexer", 355, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
            const auto ignoredColumn = [&]() -> int32_t { auto _try_value = doof::array_pop(this->interpolationColumns); if (doof::is_failure(_try_value)) doof::panic_at("src/lexer", 356, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
            (static_cast<void>(readTemplateContinuation()), std::monostate{});
            continue;
        }
        if ((this->tagMode == std::string("tag-expression")) && (peek(0) == U'\u007D')) {
            const auto index = (static_cast<int32_t>((this->tagExpressionDepths)->size()) - 1);
            if (doof::array_at(this->tagExpressionDepths, index, "src/lexer", 363) == 0) {
                (static_cast<void>(emit(TokenType::RightBrace, this->line, this->column, this->pos, 1)), std::monostate{});
                const auto ignoredDepth = [&]() -> int32_t { auto _try_value = doof::array_pop(this->tagExpressionDepths); if (doof::is_failure(_try_value)) doof::panic_at("src/lexer", 365, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
                (this->tagMode = [&]() -> std::string { auto _try_value = doof::array_pop(this->tagModeStack); if (doof::is_failure(_try_value)) doof::panic_at("src/lexer", 366, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
                continue;
            }
            (doof::array_at(this->tagExpressionDepths, index, "src/lexer", 369) = (doof::array_at(this->tagExpressionDepths, index, "src/lexer", 369) - 1));
        } else if ((this->tagMode == std::string("tag-expression")) && (peek(0) == U'\u007B')) {
            const auto index = (static_cast<int32_t>((this->tagExpressionDepths)->size()) - 1);
            (doof::array_at(this->tagExpressionDepths, index, "src/lexer", 372) = (doof::array_at(this->tagExpressionDepths, index, "src/lexer", 372) + 1));
        }
        const auto ch = peek(0);
        if ((ch == U'\u0022') || (ch == U'\u0060')) {
            (static_cast<void>(readQuoted(ch)), std::monostate{});
        } else if (ch == U'\'') {
            (static_cast<void>(readChar()), std::monostate{});
        } else if (isDigit(ch)) {
            (static_cast<void>(readNumber()), std::monostate{});
        } else if (isIdentStart(ch)) {
            (static_cast<void>(readIdentifier()), std::monostate{});
        } else {
            (static_cast<void>(readOperatorOrPunctuation()), std::monostate{});
        }
    }
    if (static_cast<int32_t>((this->braceDepth)->size()) > 0) {
        (static_cast<void>(diagnostic(std::string("Unterminated string interpolation"), doof::array_at(this->interpolationLines, (static_cast<int32_t>((this->interpolationLines)->size()) - 1), "src/lexer", 390), doof::array_at(this->interpolationColumns, (static_cast<int32_t>((this->interpolationColumns)->size()) - 1), "src/lexer", 390))), std::monostate{});
    }
    (static_cast<void>(addToken(TokenType::EndOfFile, this->pos, 0, this->pos, 0, false, this->line, this->column)), std::monostate{});
    return this->tokens;
}
void Lexer::beginTag() {
    (static_cast<void>(this->tagModeStack->push_back(this->tagMode)), std::monostate{});
    (static_cast<void>(emit(TokenType::TagOpen, this->line, this->column, this->pos, 1)), std::monostate{});
    (this->tagMode = std::string("opening-tag"));
    (this->tagGenericDepth = 0);
    (this->tagAttributeDelimiterDepth = 0);
}
void Lexer::beginTagExpression() {
    (static_cast<void>(this->tagModeStack->push_back(this->tagMode)), std::monostate{});
    (static_cast<void>(this->tagExpressionDepths->push_back(0)), std::monostate{});
    (static_cast<void>(emit(TokenType::LeftBrace, this->line, this->column, this->pos, 1)), std::monostate{});
    (this->tagMode = std::string("tag-expression"));
}
void Lexer::readTagText() {
    const auto start = this->pos;
    const auto tokenLine = this->line;
    const auto tokenColumn = this->column;
    while (((this->pos < static_cast<int32_t>(this->source.size())) && (peek(0) != U'\u003C')) && (peek(0) != U'\u007B')) {
        advance();
    }
    if (this->pos > start) {
        (static_cast<void>(addToken(TokenType::TagText, start, (this->pos - start), start, (this->pos - start), false, tokenLine, tokenColumn)), std::monostate{});
    }
}
bool Lexer::canStartTag() {
    if (static_cast<int32_t>((this->tokens)->size()) == 0) {
        return true;
    }
    if (this->line > doof::array_at(this->tokens, (static_cast<int32_t>((this->tokens)->size()) - 1), "src/lexer", 422).line) {
        return true;
    }
    const auto previous = doof::array_at(this->tokens, (static_cast<int32_t>((this->tokens)->size()) - 1), "src/lexer", 423).kind;
    return (((((((((((((((((((((((((((((((((previous == TokenType::Equal) || (previous == TokenType::ColonEqual)) || (previous == TokenType::LeftParen)) || (previous == TokenType::LeftBracket)) || (previous == TokenType::LeftBrace)) || (previous == TokenType::Comma)) || (previous == TokenType::Colon)) || (previous == TokenType::Semicolon)) || (previous == TokenType::Return)) || (previous == TokenType::Yield)) || (previous == TokenType::Then)) || (previous == TokenType::Else)) || (previous == TokenType::Arrow)) || (previous == TokenType::RightArrow)) || (previous == TokenType::Plus)) || (previous == TokenType::Minus)) || (previous == TokenType::Star)) || (previous == TokenType::Slash)) || (previous == TokenType::Backslash)) || (previous == TokenType::Percent)) || (previous == TokenType::Ampersand)) || (previous == TokenType::Pipe)) || (previous == TokenType::Caret)) || (previous == TokenType::Bang)) || (previous == TokenType::EqualEqual)) || (previous == TokenType::BangEqual)) || (previous == TokenType::Less)) || (previous == TokenType::LessEqual)) || (previous == TokenType::Greater)) || (previous == TokenType::GreaterEqual)) || (previous == TokenType::QuestionQuestion)) || (previous == TokenType::AmpersandAmpersand)) || (previous == TokenType::PipePipe));
}
char32_t Lexer::peek(int32_t offset) {
    if ((this->pos + offset) >= static_cast<int32_t>(this->source.size())) {
        return U'\0';
    }
    return doof::string_at(this->source, (this->pos + offset), "src/lexer", 439);
}
char32_t Lexer::advance() {
    const auto ch = doof::string_at(this->source, this->pos, "src/lexer", 443);
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
    (static_cast<void>(this->tokens->push_back(Token{kind, tokenLength, valueOffset, valueLength, needsDecode, tokenLine, tokenColumn, tokenOffset})), std::monostate{});
}
void Lexer::diagnostic(const std::string& message, int32_t diagnosticLine, int32_t diagnosticColumn) {
    (static_cast<void>(this->diagnostics->push_back(LexerDiagnostic{std::string("error"), message, diagnosticLine, diagnosticColumn})), std::monostate{});
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
                (static_cast<void>(diagnostic(std::string("Unterminated block comment"), commentLine, commentColumn)), std::monostate{});
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
                (static_cast<void>(diagnostic(std::string("Numeric separators must appear between digits"), separatorLine, separatorColumn)), std::monostate{});
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
        (static_cast<void>(readDigits(16)), std::monostate{});
        (static_cast<void>(readNumericSuffix(start, this->pos, tokenLine, tokenColumn)), std::monostate{});
        return;
    }
    if ((peek(0) == U'\u0030') && ((peek(1) == U'\u0062') || (peek(1) == U'\u0042'))) {
        advance();
        advance();
        (static_cast<void>(readDigits(2)), std::monostate{});
        (static_cast<void>(readNumericSuffix(start, this->pos, tokenLine, tokenColumn)), std::monostate{});
        return;
    }
    (static_cast<void>(readDigits(10)), std::monostate{});
    if (((peek(0) == U'\u002E') && (peek(1) != U'\u002E')) && (peek(1) != U'\u003C')) {
        advance();
        (static_cast<void>(readDigits(10)), std::monostate{});
        const auto valueEnd = this->pos;
        if ((peek(0) == U'\u0066') || (peek(0) == U'\u0046')) {
            advance();
            (static_cast<void>(addToken(TokenType::FloatLiteral, start, (this->pos - start), start, (valueEnd - start), false, tokenLine, tokenColumn)), std::monostate{});
        } else {
            (static_cast<void>(addToken(TokenType::DoubleLiteral, start, (this->pos - start), start, (valueEnd - start), false, tokenLine, tokenColumn)), std::monostate{});
        }
        return;
    }
    (static_cast<void>(readNumericSuffix(start, this->pos, tokenLine, tokenColumn)), std::monostate{});
}
void Lexer::readNumericSuffix(int32_t valueStart, int32_t valueEnd, int32_t tokenLine, int32_t tokenColumn) {
    if ((peek(0) == U'\u004C') || (peek(0) == U'\u006C')) {
        advance();
        (static_cast<void>(addToken(TokenType::LongLiteral, valueStart, (this->pos - valueStart), valueStart, (valueEnd - valueStart), false, tokenLine, tokenColumn)), std::monostate{});
    } else if ((peek(0) == U'\u0066') || (peek(0) == U'\u0046')) {
        advance();
        (static_cast<void>(addToken(TokenType::FloatLiteral, valueStart, (this->pos - valueStart), valueStart, (valueEnd - valueStart), false, tokenLine, tokenColumn)), std::monostate{});
    } else {
        (static_cast<void>(addToken(TokenType::IntLiteral, valueStart, (this->pos - valueStart), valueStart, (valueEnd - valueStart), false, tokenLine, tokenColumn)), std::monostate{});
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
        (static_cast<void>(addToken(TokenType::Identifier, start, (this->pos - start), start, (this->pos - start), false, tokenLine, tokenColumn)), std::monostate{});
        return;
    }
    if (value == std::string("_")) {
        (static_cast<void>(addToken(TokenType::Underscore, start, (this->pos - start), start, (this->pos - start), false, tokenLine, tokenColumn)), std::monostate{});
    } else {
        (static_cast<void>(addToken(keywordType(value), start, (this->pos - start), start, (this->pos - start), false, tokenLine, tokenColumn)), std::monostate{});
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
            (static_cast<void>(addToken(TokenType::TemplateLiteralStart, start, (this->pos - start), contentStart, (this->pos - contentStart), needsDecode, tokenLine, tokenColumn)), std::monostate{});
            (static_cast<void>(this->interpolationLines->push_back(this->line)), std::monostate{});
            (static_cast<void>(this->interpolationColumns->push_back(this->column)), std::monostate{});
            advance();
            advance();
            (static_cast<void>(this->templateDelimiters->push_back(delimiter)), std::monostate{});
            (static_cast<void>(this->braceDepth->push_back(0)), std::monostate{});
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
        (static_cast<void>(diagnostic(std::string("Unterminated string literal"), tokenLine, tokenColumn)), std::monostate{});
    }
    auto valueEnd = this->pos;
    if (closed) {
        (valueEnd = (this->pos - 1));
    }
    (static_cast<void>(addToken(TokenType::StringLiteral, start, (this->pos - start), contentStart, (valueEnd - contentStart), needsDecode, tokenLine, tokenColumn)), std::monostate{});
}
void Lexer::readTemplateContinuation() {
    const auto start = this->pos;
    const auto tokenLine = this->line;
    const auto tokenColumn = this->column;
    const auto delimiter = doof::array_at(this->templateDelimiters, (static_cast<int32_t>((this->templateDelimiters)->size()) - 1), "src/lexer", 654);
    const auto contentStart = this->pos;
    auto needsDecode = false;
    auto closed = false;
    while ((this->pos < static_cast<int32_t>(this->source.size())) && (peek(0) != delimiter)) {
        if ((peek(0) == U'\u0024') && (peek(1) == U'\u007B')) {
            (static_cast<void>(addToken(TokenType::TemplateLiteralMiddle, start, (this->pos - start), contentStart, (this->pos - contentStart), needsDecode, tokenLine, tokenColumn)), std::monostate{});
            (static_cast<void>(this->interpolationLines->push_back(this->line)), std::monostate{});
            (static_cast<void>(this->interpolationColumns->push_back(this->column)), std::monostate{});
            advance();
            advance();
            (static_cast<void>(this->braceDepth->push_back(0)), std::monostate{});
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
        (static_cast<void>(diagnostic(std::string("Unterminated template literal"), tokenLine, tokenColumn)), std::monostate{});
    }
    auto valueEnd = this->pos;
    if (closed) {
        (valueEnd = (this->pos - 1));
    }
    const auto ignoredDelimiter = [&]() -> char32_t { auto _try_value = doof::array_pop(this->templateDelimiters); if (doof::is_failure(_try_value)) doof::panic_at("src/lexer", 685, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
    (static_cast<void>(addToken(TokenType::TemplateLiteralEnd, start, (this->pos - start), contentStart, (valueEnd - contentStart), needsDecode, tokenLine, tokenColumn)), std::monostate{});
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
        const auto width = utf8SequenceLength(peek(0));
        auto consumed = 0;
        while ((consumed < width) && (this->pos < static_cast<int32_t>(this->source.size()))) {
            advance();
            (consumed = (consumed + 1));
        }
    }
    const auto valueEnd = this->pos;
    if ((this->pos < static_cast<int32_t>(this->source.size())) && (peek(0) == U'\'')) {
        advance();
    }
    (static_cast<void>(addToken(TokenType::CharLiteral, start, (this->pos - start), valueStart, (valueEnd - valueStart), needsDecode, tokenLine, tokenColumn)), std::monostate{});
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
    (static_cast<void>(addToken(kind, start, count, start, count, false, tokenLine, tokenColumn)), std::monostate{});
}
void Lexer::readOperatorOrPunctuation() {
    const auto start = this->pos;
    const auto tokenLine = this->line;
    const auto tokenColumn = this->column;
    const auto ch = peek(0);
    if (ch == U'\u0028') {
        (static_cast<void>(emit(TokenType::LeftParen, tokenLine, tokenColumn, start, 1)), std::monostate{});
        return;
    }
    if (ch == U'\u0029') {
        (static_cast<void>(emit(TokenType::RightParen, tokenLine, tokenColumn, start, 1)), std::monostate{});
        return;
    }
    if (ch == U'\u007B') {
        advance();
        if (static_cast<int32_t>((this->braceDepth)->size()) > 0) {
            (doof::array_at(this->braceDepth, (static_cast<int32_t>((this->braceDepth)->size()) - 1), "src/lexer", 736) = (doof::array_at(this->braceDepth, (static_cast<int32_t>((this->braceDepth)->size()) - 1), "src/lexer", 736) + 1));
        }
        (static_cast<void>(addToken(TokenType::LeftBrace, start, 1, start, 1, false, tokenLine, tokenColumn)), std::monostate{});
        return;
    }
    if (ch == U'\u007D') {
        advance();
        if (static_cast<int32_t>((this->braceDepth)->size()) > 0) {
            (doof::array_at(this->braceDepth, (static_cast<int32_t>((this->braceDepth)->size()) - 1), "src/lexer", 742) = (doof::array_at(this->braceDepth, (static_cast<int32_t>((this->braceDepth)->size()) - 1), "src/lexer", 742) - 1));
        }
        (static_cast<void>(addToken(TokenType::RightBrace, start, 1, start, 1, false, tokenLine, tokenColumn)), std::monostate{});
        return;
    }
    if (ch == U'\u005B') {
        (static_cast<void>(emit(TokenType::LeftBracket, tokenLine, tokenColumn, start, 1)), std::monostate{});
        return;
    }
    if (ch == U'\u005D') {
        (static_cast<void>(emit(TokenType::RightBracket, tokenLine, tokenColumn, start, 1)), std::monostate{});
        return;
    }
    if (ch == U'\u002C') {
        (static_cast<void>(emit(TokenType::Comma, tokenLine, tokenColumn, start, 1)), std::monostate{});
        return;
    }
    if (ch == U'\u003B') {
        (static_cast<void>(emit(TokenType::Semicolon, tokenLine, tokenColumn, start, 1)), std::monostate{});
        return;
    }
    if (ch == U'\u007E') {
        (static_cast<void>(emit(TokenType::Tilde, tokenLine, tokenColumn, start, 1)), std::monostate{});
        return;
    }
    if (ch == U'\u002E') {
        if ((peek(1) == U'\u002E') && (peek(2) == U'\u002E')) {
            (static_cast<void>(emit(TokenType::Ellipsis, tokenLine, tokenColumn, start, 3)), std::monostate{});
        } else if ((peek(1) == U'\u002E') && (peek(2) == U'\u003C')) {
            (static_cast<void>(emit(TokenType::DotDotLess, tokenLine, tokenColumn, start, 3)), std::monostate{});
        } else if (peek(1) == U'\u002E') {
            (static_cast<void>(emit(TokenType::DotDot, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else {
            (static_cast<void>(emit(TokenType::Dot, tokenLine, tokenColumn, start, 1)), std::monostate{});
        }
        return;
    }
    if (ch == U'\u003A') {
        if (peek(1) == U'\u003A') {
            (static_cast<void>(emit(TokenType::DoubleColon, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else if (peek(1) == U'\u003D') {
            (static_cast<void>(emit(TokenType::ColonEqual, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else {
            (static_cast<void>(emit(TokenType::Colon, tokenLine, tokenColumn, start, 1)), std::monostate{});
        }
        return;
    }
    if (ch == U'\u003D') {
        if (peek(1) == U'\u003D') {
            (static_cast<void>(emit(TokenType::EqualEqual, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else if (peek(1) == U'\u003E') {
            (static_cast<void>(emit(TokenType::Arrow, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else {
            (static_cast<void>(emit(TokenType::Equal, tokenLine, tokenColumn, start, 1)), std::monostate{});
        }
        return;
    }
    if (ch == U'\u002B') {
        if (peek(1) == U'\u003D') {
            (static_cast<void>(emit(TokenType::PlusEqual, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else {
            (static_cast<void>(emit(TokenType::Plus, tokenLine, tokenColumn, start, 1)), std::monostate{});
        }
        return;
    }
    if (ch == U'\u002D') {
        if (peek(1) == U'\u003E') {
            (static_cast<void>(emit(TokenType::RightArrow, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else if (peek(1) == U'\u003D') {
            (static_cast<void>(emit(TokenType::MinusEqual, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else {
            (static_cast<void>(emit(TokenType::Minus, tokenLine, tokenColumn, start, 1)), std::monostate{});
        }
        return;
    }
    if (ch == U'\u002A') {
        if ((peek(1) == U'\u002A') && (peek(2) == U'\u003D')) {
            (static_cast<void>(emit(TokenType::StarStarEqual, tokenLine, tokenColumn, start, 3)), std::monostate{});
        } else if (peek(1) == U'\u002A') {
            (static_cast<void>(emit(TokenType::StarStar, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else if (peek(1) == U'\u003D') {
            (static_cast<void>(emit(TokenType::StarEqual, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else {
            (static_cast<void>(emit(TokenType::Star, tokenLine, tokenColumn, start, 1)), std::monostate{});
        }
        return;
    }
    if (ch == U'\u002F') {
        if (peek(1) == U'\u003D') {
            (static_cast<void>(emit(TokenType::SlashEqual, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else {
            (static_cast<void>(emit(TokenType::Slash, tokenLine, tokenColumn, start, 1)), std::monostate{});
        }
        return;
    }
    if (ch == U'\u0025') {
        if (peek(1) == U'\u003D') {
            (static_cast<void>(emit(TokenType::PercentEqual, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else {
            (static_cast<void>(emit(TokenType::Percent, tokenLine, tokenColumn, start, 1)), std::monostate{});
        }
        return;
    }
    if (ch == U'\\') {
        if (peek(1) == U'\u003D') {
            (static_cast<void>(emit(TokenType::BackslashEqual, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else {
            (static_cast<void>(emit(TokenType::Backslash, tokenLine, tokenColumn, start, 1)), std::monostate{});
        }
        return;
    }
    if (ch == U'\u0026') {
        if (peek(1) == U'\u0026') {
            (static_cast<void>(emit(TokenType::AmpersandAmpersand, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else if (peek(1) == U'\u003D') {
            (static_cast<void>(emit(TokenType::AmpersandEqual, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else {
            (static_cast<void>(emit(TokenType::Ampersand, tokenLine, tokenColumn, start, 1)), std::monostate{});
        }
        return;
    }
    if (ch == U'\u007C') {
        if (peek(1) == U'\u007C') {
            (static_cast<void>(emit(TokenType::PipePipe, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else if (peek(1) == U'\u003D') {
            (static_cast<void>(emit(TokenType::PipeEqual, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else {
            (static_cast<void>(emit(TokenType::Pipe, tokenLine, tokenColumn, start, 1)), std::monostate{});
        }
        return;
    }
    if (ch == U'\u005E') {
        if (peek(1) == U'\u003D') {
            (static_cast<void>(emit(TokenType::CaretEqual, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else {
            (static_cast<void>(emit(TokenType::Caret, tokenLine, tokenColumn, start, 1)), std::monostate{});
        }
        return;
    }
    if (ch == U'\u003C') {
        if ((peek(1) == U'\u003C') && (peek(2) == U'\u003D')) {
            (static_cast<void>(emit(TokenType::LessLessEqual, tokenLine, tokenColumn, start, 3)), std::monostate{});
        } else if (peek(1) == U'\u003C') {
            (static_cast<void>(emit(TokenType::LessLess, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else if (peek(1) == U'\u002D') {
            (static_cast<void>(emit(TokenType::LeftArrow, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else if (peek(1) == U'\u003D') {
            (static_cast<void>(emit(TokenType::LessEqual, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else {
            (static_cast<void>(emit(TokenType::Less, tokenLine, tokenColumn, start, 1)), std::monostate{});
        }
        return;
    }
    if (ch == U'\u003E') {
        if (((peek(1) == U'\u003E') && (peek(2) == U'\u003E')) && (peek(3) == U'\u003D')) {
            (static_cast<void>(emit(TokenType::GreaterGreaterEqual, tokenLine, tokenColumn, start, 4)), std::monostate{});
        } else if ((peek(1) == U'\u003E') && (peek(2) == U'\u003E')) {
            (static_cast<void>(emit(TokenType::GreaterGreaterGreater, tokenLine, tokenColumn, start, 3)), std::monostate{});
        } else if ((peek(1) == U'\u003E') && (peek(2) == U'\u003D')) {
            (static_cast<void>(emit(TokenType::GreaterGreaterEqual, tokenLine, tokenColumn, start, 3)), std::monostate{});
        } else if (peek(1) == U'\u003E') {
            (static_cast<void>(emit(TokenType::GreaterGreater, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else if (peek(1) == U'\u003D') {
            (static_cast<void>(emit(TokenType::GreaterEqual, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else {
            (static_cast<void>(emit(TokenType::Greater, tokenLine, tokenColumn, start, 1)), std::monostate{});
        }
        return;
    }
    if (ch == U'\u0021') {
        if (peek(1) == U'\u003D') {
            (static_cast<void>(emit(TokenType::BangEqual, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else if (peek(1) == U'\u002E') {
            (static_cast<void>(emit(TokenType::BangDot, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else {
            (static_cast<void>(emit(TokenType::Bang, tokenLine, tokenColumn, start, 1)), std::monostate{});
        }
        return;
    }
    if (ch == U'\u003F') {
        if ((peek(1) == U'\u003F') && (peek(2) == U'\u003D')) {
            (static_cast<void>(emit(TokenType::QuestionQuestionEqual, tokenLine, tokenColumn, start, 3)), std::monostate{});
        } else if (peek(1) == U'\u003F') {
            (static_cast<void>(emit(TokenType::QuestionQuestion, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else if (peek(1) == U'\u002E') {
            (static_cast<void>(emit(TokenType::QuestionDot, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else if (peek(1) == U'\u005B') {
            (static_cast<void>(emit(TokenType::QuestionBracket, tokenLine, tokenColumn, start, 2)), std::monostate{});
        } else {
            (static_cast<void>(emit(TokenType::Identifier, tokenLine, tokenColumn, start, 1)), std::monostate{});
        }
        return;
    }
    if ((((ch == U'\u0040') && ((this->pos + 7) <= static_cast<int32_t>(this->source.size()))) && (doof::string_substring(this->source, this->pos, (this->pos + 7)) == std::string("@caller"))) && !isIdentPart(peek(7))) {
        (static_cast<void>(emit(TokenType::CallerIntrinsic, tokenLine, tokenColumn, start, 7)), std::monostate{});
        return;
    }
    (static_cast<void>(diagnostic(((std::string("Unexpected character: '") + doof::to_string(ch)) + std::string("'")), this->line, this->column)), std::monostate{});
    advance();
}
}

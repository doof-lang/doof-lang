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
        return std::string("");
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
    this->tokens->reserve(((static_cast<int32_t>(this->source.size()) / 2) + 16));
    if (((static_cast<int32_t>(this->source.size()) >= 2) && (doof::string_at(this->source, 0, "src/lexer", 282) == U'\u0023')) && (doof::string_at(this->source, 1, "src/lexer", 282) == U'\u0021')) {
        while ((this->pos < static_cast<int32_t>(this->source.size())) && (peek(0) != U'\n')) {
            advance();
        }
    }
    while (this->pos < static_cast<int32_t>(this->source.size())) {
        if (this->tagMode == std::string("children")) {
            if ((peek(0) == U'\u003C') && (peek(1) == U'\u002F')) {
                emit(TokenType::Less, this->line, this->column, this->pos, 1);
                emit(TokenType::Slash, this->line, this->column, this->pos, 1);
                (this->tagMode = std::string("closing-tag"));
                continue;
            }
            if ((peek(0) == U'\u003C') && isIdentStart(peek(1))) {
                beginTag();
                continue;
            }
            if (peek(0) == U'\u007B') {
                beginTagExpression();
                continue;
            }
            readTagText();
            continue;
        }
        if ((this->tagMode == std::string("opening-tag")) || (this->tagMode == std::string("closing-tag"))) {
            skipWhitespaceAndComments();
            if (this->pos >= static_cast<int32_t>(this->source.size())) {
                break;
            }
            if ((this->tagMode == std::string("opening-tag")) && (peek(0) == U'\u007B')) {
                beginTagExpression();
                continue;
            }
            if ((this->tagMode == std::string("opening-tag")) && (peek(0) == U'\u003C')) {
                (this->tagGenericDepth = (this->tagGenericDepth + 1));
                emit(TokenType::Less, this->line, this->column, this->pos, 1);
                continue;
            }
            if ((peek(0) == U'\u003E') && (this->tagGenericDepth > 0)) {
                (this->tagGenericDepth = (this->tagGenericDepth - 1));
                emit(TokenType::Greater, this->line, this->column, this->pos, 1);
                continue;
            }
            if (peek(0) == U'\u003E') {
                emit(TokenType::Greater, this->line, this->column, this->pos, 1);
                if (this->tagMode == std::string("closing-tag")) {
                    (this->tagMode = [&]() -> std::string { auto _try_value = doof::array_pop(this->tagModeStack); if (doof::is_failure(_try_value)) doof::panic_at("src/lexer", 325, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
                } else if ((static_cast<int32_t>((this->tokens)->size()) >= 2) && (doof::array_at(this->tokens, (static_cast<int32_t>((this->tokens)->size()) - 2), "src/lexer", 326).kind == TokenType::Slash)) {
                    (this->tagMode = [&]() -> std::string { auto _try_value = doof::array_pop(this->tagModeStack); if (doof::is_failure(_try_value)) doof::panic_at("src/lexer", 327, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
                } else {
                    (this->tagMode = std::string("children"));
                }
                continue;
            }
        }
        skipWhitespaceAndComments();
        if (this->pos >= static_cast<int32_t>(this->source.size())) {
            break;
        }
        if (((((this->tagMode == std::string("code")) || (this->tagMode == std::string("tag-expression"))) && (peek(0) == U'\u003C')) && isIdentStart(peek(1))) && canStartTag()) {
            beginTag();
            continue;
        }
        if (((static_cast<int32_t>((this->templateDelimiters)->size()) > 0) && (peek(0) == U'\u007D')) && (doof::array_at(this->braceDepth, (static_cast<int32_t>((this->braceDepth)->size()) - 1), "src/lexer", 343) == 0)) {
            advance();
            const auto ignoredBrace = [&]() -> int32_t { auto _try_value = doof::array_pop(this->braceDepth); if (doof::is_failure(_try_value)) doof::panic_at("src/lexer", 345, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
            const auto ignoredLine = [&]() -> int32_t { auto _try_value = doof::array_pop(this->interpolationLines); if (doof::is_failure(_try_value)) doof::panic_at("src/lexer", 346, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
            const auto ignoredColumn = [&]() -> int32_t { auto _try_value = doof::array_pop(this->interpolationColumns); if (doof::is_failure(_try_value)) doof::panic_at("src/lexer", 347, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
            readTemplateContinuation();
            continue;
        }
        if ((this->tagMode == std::string("tag-expression")) && (peek(0) == U'\u007D')) {
            const auto index = (static_cast<int32_t>((this->tagExpressionDepths)->size()) - 1);
            if (doof::array_at(this->tagExpressionDepths, index, "src/lexer", 354) == 0) {
                emit(TokenType::RightBrace, this->line, this->column, this->pos, 1);
                const auto ignoredDepth = [&]() -> int32_t { auto _try_value = doof::array_pop(this->tagExpressionDepths); if (doof::is_failure(_try_value)) doof::panic_at("src/lexer", 356, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
                (this->tagMode = [&]() -> std::string { auto _try_value = doof::array_pop(this->tagModeStack); if (doof::is_failure(_try_value)) doof::panic_at("src/lexer", 357, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
                continue;
            }
            (doof::array_at(this->tagExpressionDepths, index, "src/lexer", 360) = (doof::array_at(this->tagExpressionDepths, index, "src/lexer", 360) - 1));
        } else if ((this->tagMode == std::string("tag-expression")) && (peek(0) == U'\u007B')) {
            const auto index = (static_cast<int32_t>((this->tagExpressionDepths)->size()) - 1);
            (doof::array_at(this->tagExpressionDepths, index, "src/lexer", 363) = (doof::array_at(this->tagExpressionDepths, index, "src/lexer", 363) + 1));
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
    if (static_cast<int32_t>((this->braceDepth)->size()) > 0) {
        diagnostic(std::string("Unterminated string interpolation"), doof::array_at(this->interpolationLines, (static_cast<int32_t>((this->interpolationLines)->size()) - 1), "src/lexer", 381), doof::array_at(this->interpolationColumns, (static_cast<int32_t>((this->interpolationColumns)->size()) - 1), "src/lexer", 381));
    }
    addToken(TokenType::EndOfFile, this->pos, 0, this->pos, 0, false, this->line, this->column);
    return this->tokens;
}
void Lexer::beginTag() {
    this->tagModeStack->push_back(this->tagMode);
    emit(TokenType::TagOpen, this->line, this->column, this->pos, 1);
    (this->tagMode = std::string("opening-tag"));
    (this->tagGenericDepth = 0);
}
void Lexer::beginTagExpression() {
    this->tagModeStack->push_back(this->tagMode);
    this->tagExpressionDepths->push_back(0);
    emit(TokenType::LeftBrace, this->line, this->column, this->pos, 1);
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
        addToken(TokenType::TagText, start, (this->pos - start), start, (this->pos - start), false, tokenLine, tokenColumn);
    }
}
bool Lexer::canStartTag() {
    if (static_cast<int32_t>((this->tokens)->size()) == 0) {
        return true;
    }
    if (this->line > doof::array_at(this->tokens, (static_cast<int32_t>((this->tokens)->size()) - 1), "src/lexer", 412).line) {
        return true;
    }
    const auto previous = doof::array_at(this->tokens, (static_cast<int32_t>((this->tokens)->size()) - 1), "src/lexer", 413).kind;
    return (((((((((((((((((((((((((((((((((previous == TokenType::Equal) || (previous == TokenType::ColonEqual)) || (previous == TokenType::LeftParen)) || (previous == TokenType::LeftBracket)) || (previous == TokenType::LeftBrace)) || (previous == TokenType::Comma)) || (previous == TokenType::Colon)) || (previous == TokenType::Semicolon)) || (previous == TokenType::Return)) || (previous == TokenType::Yield)) || (previous == TokenType::Then)) || (previous == TokenType::Else)) || (previous == TokenType::Arrow)) || (previous == TokenType::RightArrow)) || (previous == TokenType::Plus)) || (previous == TokenType::Minus)) || (previous == TokenType::Star)) || (previous == TokenType::Slash)) || (previous == TokenType::Backslash)) || (previous == TokenType::Percent)) || (previous == TokenType::Ampersand)) || (previous == TokenType::Pipe)) || (previous == TokenType::Caret)) || (previous == TokenType::Bang)) || (previous == TokenType::EqualEqual)) || (previous == TokenType::BangEqual)) || (previous == TokenType::Less)) || (previous == TokenType::LessEqual)) || (previous == TokenType::Greater)) || (previous == TokenType::GreaterEqual)) || (previous == TokenType::QuestionQuestion)) || (previous == TokenType::AmpersandAmpersand)) || (previous == TokenType::PipePipe));
}
char32_t Lexer::peek(int32_t offset) {
    if ((this->pos + offset) >= static_cast<int32_t>(this->source.size())) {
        return U'\0';
    }
    return doof::string_at(this->source, (this->pos + offset), "src/lexer", 429);
}
char32_t Lexer::advance() {
    const auto ch = doof::string_at(this->source, this->pos, "src/lexer", 433);
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
void Lexer::diagnostic(const std::string& message, int32_t diagnosticLine, int32_t diagnosticColumn) {
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
            this->interpolationLines->push_back(this->line);
            this->interpolationColumns->push_back(this->column);
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
    const auto delimiter = doof::array_at(this->templateDelimiters, (static_cast<int32_t>((this->templateDelimiters)->size()) - 1), "src/lexer", 644);
    const auto contentStart = this->pos;
    auto needsDecode = false;
    auto closed = false;
    while ((this->pos < static_cast<int32_t>(this->source.size())) && (peek(0) != delimiter)) {
        if ((peek(0) == U'\u0024') && (peek(1) == U'\u007B')) {
            addToken(TokenType::TemplateLiteralMiddle, start, (this->pos - start), contentStart, (this->pos - contentStart), needsDecode, tokenLine, tokenColumn);
            this->interpolationLines->push_back(this->line);
            this->interpolationColumns->push_back(this->column);
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
    const auto ignoredDelimiter = [&]() -> char32_t { auto _try_value = doof::array_pop(this->templateDelimiters); if (doof::is_failure(_try_value)) doof::panic_at("src/lexer", 675, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
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
            (doof::array_at(this->braceDepth, (static_cast<int32_t>((this->braceDepth)->size()) - 1), "src/lexer", 726) = (doof::array_at(this->braceDepth, (static_cast<int32_t>((this->braceDepth)->size()) - 1), "src/lexer", 726) + 1));
        }
        addToken(TokenType::LeftBrace, start, 1, start, 1, false, tokenLine, tokenColumn);
        return;
    }
    if (ch == U'\u007D') {
        advance();
        if (static_cast<int32_t>((this->braceDepth)->size()) > 0) {
            (doof::array_at(this->braceDepth, (static_cast<int32_t>((this->braceDepth)->size()) - 1), "src/lexer", 732) = (doof::array_at(this->braceDepth, (static_cast<int32_t>((this->braceDepth)->size()) - 1), "src/lexer", 732) - 1));
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
char32_t charFromUtf8(const std::string& value) {
    return ::doof::char_from_utf8(value);
}
}

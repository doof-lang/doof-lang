#include "src_lexer.hpp"

namespace app_src_lexer_ {


#line 148 "/src/lexer.do"
std::string decodeEscapeCharacter(char32_t escaped) {
#line 149 "/src/lexer.do"
    if (escaped == U'\u006E') {
#line 149 "/src/lexer.do"
        return std::string("\n");
    }
#line 150 "/src/lexer.do"
    if (escaped == U'\u0074') {
#line 150 "/src/lexer.do"
        return std::string("\t");
    }
#line 151 "/src/lexer.do"
    if (escaped == U'\u0072') {
#line 151 "/src/lexer.do"
        return std::string("\r");
    }
#line 152 "/src/lexer.do"
    if (escaped == U'\\') {
#line 152 "/src/lexer.do"
        return std::string("\\");
    }
#line 153 "/src/lexer.do"
    if (escaped == U'\u0022') {
#line 153 "/src/lexer.do"
        return std::string("\"");
    }
#line 154 "/src/lexer.do"
    if (escaped == U'\'') {
#line 154 "/src/lexer.do"
        return std::string("'");
    }
#line 155 "/src/lexer.do"
    if (escaped == U'\u0060') {
#line 155 "/src/lexer.do"
        return std::string("`");
    }
#line 156 "/src/lexer.do"
    if (escaped == U'\u0024') {
#line 156 "/src/lexer.do"
        return std::string("$");
    }
#line 157 "/src/lexer.do"
    if (escaped == U'\u0030') {
#line 157 "/src/lexer.do"
        return std::string("");
    }
#line 158 "/src/lexer.do"
    return doof::to_string(escaped);
}
#line 161 "/src/lexer.do"
std::string tokenValue(Token token, const std::string& source) {
#line 162 "/src/lexer.do"
    const auto raw = doof::string_substring(source, token.valueOffset, (token.valueOffset + token.valueLength));
#line 163 "/src/lexer.do"
    if ((((token.kind == TokenType::IntLiteral) || (token.kind == TokenType::LongLiteral)) || (token.kind == TokenType::FloatLiteral)) || (token.kind == TokenType::DoubleLiteral)) {
#line 167 "/src/lexer.do"
        if (doof::string_contains(raw, std::string("_"))) {
#line 167 "/src/lexer.do"
            return doof::string_replaceAll(raw, std::string("_"), std::string(""));
        }
#line 168 "/src/lexer.do"
        return raw;
    }
#line 170 "/src/lexer.do"
    if (!token.needsDecode) {
#line 170 "/src/lexer.do"
        return raw;
    }
#line 172 "/src/lexer.do"
    auto value = std::string("");
#line 173 "/src/lexer.do"
    auto index = 0;
#line 174 "/src/lexer.do"
    while (index < static_cast<int32_t>(raw.size())) {
#line 175 "/src/lexer.do"
        if ((doof::string_at(raw, index, "src/lexer", 175) == U'\\') && ((index + 1) < static_cast<int32_t>(raw.size()))) {
#line 176 "/src/lexer.do"
            (index = (index + 1));
#line 177 "/src/lexer.do"
            (value = (value + decodeEscapeCharacter(doof::string_at(raw, index, "src/lexer", 177))));
#line 178 "/src/lexer.do"
            (index = (index + 1));
        } else {
#line 180 "/src/lexer.do"
            const auto width = utf8SequenceLength(doof::string_at(raw, index, "src/lexer", 180));
#line 181 "/src/lexer.do"
            (value = (value + doof::string_substring(raw, index, (index + width))));
#line 182 "/src/lexer.do"
            (index = (index + width));
        }
    }
#line 185 "/src/lexer.do"
    return value;
}
#line 188 "/src/lexer.do"
int32_t utf8SequenceLength(char32_t first) {
#line 189 "/src/lexer.do"
    const auto value = static_cast<int32_t>(first);
#line 190 "/src/lexer.do"
    if (value < 128) {
#line 190 "/src/lexer.do"
        return 1;
    }
#line 191 "/src/lexer.do"
    if ((value >= 194) && (value <= 223)) {
#line 191 "/src/lexer.do"
        return 2;
    }
#line 192 "/src/lexer.do"
    if ((value >= 224) && (value <= 239)) {
#line 192 "/src/lexer.do"
        return 3;
    }
#line 193 "/src/lexer.do"
    if ((value >= 240) && (value <= 244)) {
#line 193 "/src/lexer.do"
        return 4;
    }
#line 194 "/src/lexer.do"
    return 1;
}
#line 197 "/src/lexer.do"
char32_t charTokenValue(Token token, const std::string& source) {
#line 198 "/src/lexer.do"
    const auto value = tokenValue(token, source);
#line 199 "/src/lexer.do"
    if (static_cast<int32_t>(value.size()) == 0) {
#line 199 "/src/lexer.do"
        return U'\0';
    }
#line 200 "/src/lexer.do"
    return ::doof::char_from_utf8(value);
}
#line 203 "/src/lexer.do"
TokenType keywordType(const std::string& word) {
#line 206 "/src/lexer.do"
    if (static_cast<int32_t>(word.size()) == 2) {
#line 207 "/src/lexer.do"
        if (word == std::string("if")) {
#line 207 "/src/lexer.do"
            return TokenType::If;
        }
#line 208 "/src/lexer.do"
        if (word == std::string("of")) {
#line 208 "/src/lexer.do"
            return TokenType::Of;
        }
#line 209 "/src/lexer.do"
        if (word == std::string("as")) {
#line 209 "/src/lexer.do"
            return TokenType::As;
        }
    } else if (static_cast<int32_t>(word.size()) == 3) {
#line 211 "/src/lexer.do"
        if (word == std::string("let")) {
#line 211 "/src/lexer.do"
            return TokenType::Let;
        }
#line 212 "/src/lexer.do"
        if (word == std::string("for")) {
#line 212 "/src/lexer.do"
            return TokenType::For;
        }
#line 213 "/src/lexer.do"
        if (word == std::string("try")) {
#line 213 "/src/lexer.do"
            return TokenType::Try;
        }
    } else if (static_cast<int32_t>(word.size()) == 4) {
#line 215 "/src/lexer.do"
        if (word == std::string("else")) {
#line 215 "/src/lexer.do"
            return TokenType::Else;
        }
#line 216 "/src/lexer.do"
        if (word == std::string("then")) {
#line 216 "/src/lexer.do"
            return TokenType::Then;
        }
#line 217 "/src/lexer.do"
        if (word == std::string("case")) {
#line 217 "/src/lexer.do"
            return TokenType::Case;
        }
#line 218 "/src/lexer.do"
        if (word == std::string("type")) {
#line 218 "/src/lexer.do"
            return TokenType::Type;
        }
#line 219 "/src/lexer.do"
        if (word == std::string("enum")) {
#line 219 "/src/lexer.do"
            return TokenType::Enum;
        }
#line 220 "/src/lexer.do"
        if (word == std::string("from")) {
#line 220 "/src/lexer.do"
            return TokenType::From;
        }
#line 221 "/src/lexer.do"
        if (word == std::string("true")) {
#line 221 "/src/lexer.do"
            return TokenType::True;
        }
#line 222 "/src/lexer.do"
        if (word == std::string("none")) {
#line 222 "/src/lexer.do"
            return TokenType::None;
        }
#line 223 "/src/lexer.do"
        if (word == std::string("null")) {
#line 223 "/src/lexer.do"
            return TokenType::Null;
        }
#line 224 "/src/lexer.do"
        if (word == std::string("void")) {
#line 224 "/src/lexer.do"
            return TokenType::Void;
        }
#line 225 "/src/lexer.do"
        if (word == std::string("this")) {
#line 225 "/src/lexer.do"
            return TokenType::This;
        }
#line 226 "/src/lexer.do"
        if (word == std::string("weak")) {
#line 226 "/src/lexer.do"
            return TokenType::Weak;
        }
#line 227 "/src/lexer.do"
        if (word == std::string("with")) {
#line 227 "/src/lexer.do"
            return TokenType::With;
        }
#line 228 "/src/lexer.do"
        if (word == std::string("mock")) {
#line 228 "/src/lexer.do"
            return TokenType::Mock;
        }
    } else if (static_cast<int32_t>(word.size()) == 5) {
#line 230 "/src/lexer.do"
        if (word == std::string("const")) {
#line 230 "/src/lexer.do"
            return TokenType::Const;
        }
#line 231 "/src/lexer.do"
        if (word == std::string("yield")) {
#line 231 "/src/lexer.do"
            return TokenType::Yield;
        }
#line 232 "/src/lexer.do"
        if (word == std::string("while")) {
#line 232 "/src/lexer.do"
            return TokenType::While;
        }
#line 233 "/src/lexer.do"
        if (word == std::string("break")) {
#line 233 "/src/lexer.do"
            return TokenType::Break;
        }
#line 234 "/src/lexer.do"
        if (word == std::string("class")) {
#line 234 "/src/lexer.do"
            return TokenType::Class;
        }
#line 235 "/src/lexer.do"
        if (word == std::string("false")) {
#line 235 "/src/lexer.do"
            return TokenType::False;
        }
#line 236 "/src/lexer.do"
        if (word == std::string("catch")) {
#line 236 "/src/lexer.do"
            return TokenType::Catch;
        }
#line 237 "/src/lexer.do"
        if (word == std::string("async")) {
#line 237 "/src/lexer.do"
            return TokenType::Async;
        }
    } else if (static_cast<int32_t>(word.size()) == 6) {
#line 239 "/src/lexer.do"
        if (word == std::string("return")) {
#line 239 "/src/lexer.do"
            return TokenType::Return;
        }
#line 240 "/src/lexer.do"
        if (word == std::string("struct")) {
#line 240 "/src/lexer.do"
            return TokenType::Struct;
        }
#line 241 "/src/lexer.do"
        if (word == std::string("import")) {
#line 241 "/src/lexer.do"
            return TokenType::Import;
        }
#line 242 "/src/lexer.do"
        if (word == std::string("export")) {
#line 242 "/src/lexer.do"
            return TokenType::Export;
        }
#line 243 "/src/lexer.do"
        if (word == std::string("static")) {
#line 243 "/src/lexer.do"
            return TokenType::Static;
        }
#line 244 "/src/lexer.do"
        if (word == std::string("retire")) {
#line 244 "/src/lexer.do"
            return TokenType::Retire;
        }
    } else if (static_cast<int32_t>(word.size()) == 7) {
#line 246 "/src/lexer.do"
        if (word == std::string("private")) {
#line 246 "/src/lexer.do"
            return TokenType::Private;
        }
    } else if (static_cast<int32_t>(word.size()) == 8) {
#line 248 "/src/lexer.do"
        if (word == std::string("readonly")) {
#line 248 "/src/lexer.do"
            return TokenType::Readonly;
        }
#line 249 "/src/lexer.do"
        if (word == std::string("function")) {
#line 249 "/src/lexer.do"
            return TokenType::Function;
        }
#line 250 "/src/lexer.do"
        if (word == std::string("continue")) {
#line 250 "/src/lexer.do"
            return TokenType::Continue;
        }
#line 251 "/src/lexer.do"
        if (word == std::string("isolated")) {
#line 251 "/src/lexer.do"
            return TokenType::Isolated;
        }
    } else if (static_cast<int32_t>(word.size()) == 9) {
#line 253 "/src/lexer.do"
        if (word == std::string("interface")) {
#line 253 "/src/lexer.do"
            return TokenType::Interface;
        }
    } else if (static_cast<int32_t>(word.size()) == 10) {
#line 255 "/src/lexer.do"
        if (word == std::string("implements")) {
#line 255 "/src/lexer.do"
            return TokenType::Implements;
        }
#line 256 "/src/lexer.do"
        if (word == std::string("destructor")) {
#line 256 "/src/lexer.do"
            return TokenType::Destructor;
        }
    }
#line 258 "/src/lexer.do"
    return TokenType::Identifier;
}

#line 277 "/src/lexer.do"
std::shared_ptr<std::vector<Token>> Lexer::tokenize() {
#line 281 "/src/lexer.do"
    this->tokens->reserve(((static_cast<int32_t>(this->source.size()) / 2) + 16));
#line 282 "/src/lexer.do"
    if (((static_cast<int32_t>(this->source.size()) >= 2) && (doof::string_at(this->source, 0, "src/lexer", 282) == U'\u0023')) && (doof::string_at(this->source, 1, "src/lexer", 282) == U'\u0021')) {
#line 283 "/src/lexer.do"
        while ((this->pos < static_cast<int32_t>(this->source.size())) && (peek(0) != U'\n')) {
#line 283 "/src/lexer.do"
            advance();
        }
    }
#line 285 "/src/lexer.do"
    while (this->pos < static_cast<int32_t>(this->source.size())) {
#line 286 "/src/lexer.do"
        if (this->tagMode == std::string("children")) {
#line 287 "/src/lexer.do"
            if ((peek(0) == U'\u003C') && (peek(1) == U'\u002F')) {
#line 288 "/src/lexer.do"
                emit(TokenType::Less, this->line, this->column, this->pos, 1);
#line 289 "/src/lexer.do"
                emit(TokenType::Slash, this->line, this->column, this->pos, 1);
#line 290 "/src/lexer.do"
                (this->tagMode = std::string("closing-tag"));
#line 291 "/src/lexer.do"
                continue;
            }
#line 293 "/src/lexer.do"
            if ((peek(0) == U'\u003C') && isIdentStart(peek(1))) {
#line 294 "/src/lexer.do"
                beginTag();
#line 295 "/src/lexer.do"
                continue;
            }
#line 297 "/src/lexer.do"
            if (peek(0) == U'\u007B') {
#line 298 "/src/lexer.do"
                beginTagExpression();
#line 299 "/src/lexer.do"
                continue;
            }
#line 301 "/src/lexer.do"
            readTagText();
#line 302 "/src/lexer.do"
            continue;
        }
#line 305 "/src/lexer.do"
        if ((this->tagMode == std::string("opening-tag")) || (this->tagMode == std::string("closing-tag"))) {
#line 306 "/src/lexer.do"
            skipWhitespaceAndComments();
#line 307 "/src/lexer.do"
            if (this->pos >= static_cast<int32_t>(this->source.size())) {
#line 307 "/src/lexer.do"
                break;
            }
#line 308 "/src/lexer.do"
            if ((this->tagMode == std::string("opening-tag")) && (peek(0) == U'\u007B')) {
#line 309 "/src/lexer.do"
                beginTagExpression();
#line 310 "/src/lexer.do"
                continue;
            }
#line 312 "/src/lexer.do"
            if ((this->tagMode == std::string("opening-tag")) && (peek(0) == U'\u003C')) {
#line 313 "/src/lexer.do"
                (this->tagGenericDepth = (this->tagGenericDepth + 1));
#line 314 "/src/lexer.do"
                emit(TokenType::Less, this->line, this->column, this->pos, 1);
#line 315 "/src/lexer.do"
                continue;
            }
#line 317 "/src/lexer.do"
            if ((peek(0) == U'\u003E') && (this->tagGenericDepth > 0)) {
#line 318 "/src/lexer.do"
                (this->tagGenericDepth = (this->tagGenericDepth - 1));
#line 319 "/src/lexer.do"
                emit(TokenType::Greater, this->line, this->column, this->pos, 1);
#line 320 "/src/lexer.do"
                continue;
            }
#line 322 "/src/lexer.do"
            if (peek(0) == U'\u003E') {
#line 323 "/src/lexer.do"
                emit(TokenType::Greater, this->line, this->column, this->pos, 1);
#line 324 "/src/lexer.do"
                if (this->tagMode == std::string("closing-tag")) {
#line 325 "/src/lexer.do"
                    (this->tagMode = [&]() -> std::string { auto _try_value = doof::array_pop(this->tagModeStack); if (doof::is_failure(_try_value)) doof::panic_at("src/lexer", 325, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
                } else if ((static_cast<int32_t>((this->tokens)->size()) >= 2) && (doof::array_at(this->tokens, (static_cast<int32_t>((this->tokens)->size()) - 2), "src/lexer", 326).kind == TokenType::Slash)) {
#line 327 "/src/lexer.do"
                    (this->tagMode = [&]() -> std::string { auto _try_value = doof::array_pop(this->tagModeStack); if (doof::is_failure(_try_value)) doof::panic_at("src/lexer", 327, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
                } else {
#line 329 "/src/lexer.do"
                    (this->tagMode = std::string("children"));
                }
#line 331 "/src/lexer.do"
                continue;
            }
        }
#line 335 "/src/lexer.do"
        skipWhitespaceAndComments();
#line 336 "/src/lexer.do"
        if (this->pos >= static_cast<int32_t>(this->source.size())) {
#line 336 "/src/lexer.do"
            break;
        }
#line 338 "/src/lexer.do"
        if (((((this->tagMode == std::string("code")) || (this->tagMode == std::string("tag-expression"))) && (peek(0) == U'\u003C')) && isIdentStart(peek(1))) && canStartTag()) {
#line 339 "/src/lexer.do"
            beginTag();
#line 340 "/src/lexer.do"
            continue;
        }
#line 343 "/src/lexer.do"
        if (((static_cast<int32_t>((this->templateDelimiters)->size()) > 0) && (peek(0) == U'\u007D')) && (doof::array_at(this->braceDepth, (static_cast<int32_t>((this->braceDepth)->size()) - 1), "src/lexer", 343) == 0)) {
#line 344 "/src/lexer.do"
            advance();
#line 345 "/src/lexer.do"
            const auto ignoredBrace = [&]() -> int32_t { auto _try_value = doof::array_pop(this->braceDepth); if (doof::is_failure(_try_value)) doof::panic_at("src/lexer", 345, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
#line 346 "/src/lexer.do"
            const auto ignoredLine = [&]() -> int32_t { auto _try_value = doof::array_pop(this->interpolationLines); if (doof::is_failure(_try_value)) doof::panic_at("src/lexer", 346, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
#line 347 "/src/lexer.do"
            const auto ignoredColumn = [&]() -> int32_t { auto _try_value = doof::array_pop(this->interpolationColumns); if (doof::is_failure(_try_value)) doof::panic_at("src/lexer", 347, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
#line 348 "/src/lexer.do"
            readTemplateContinuation();
#line 349 "/src/lexer.do"
            continue;
        }
#line 352 "/src/lexer.do"
        if ((this->tagMode == std::string("tag-expression")) && (peek(0) == U'\u007D')) {
#line 353 "/src/lexer.do"
            const auto index = (static_cast<int32_t>((this->tagExpressionDepths)->size()) - 1);
#line 354 "/src/lexer.do"
            if (doof::array_at(this->tagExpressionDepths, index, "src/lexer", 354) == 0) {
#line 355 "/src/lexer.do"
                emit(TokenType::RightBrace, this->line, this->column, this->pos, 1);
#line 356 "/src/lexer.do"
                const auto ignoredDepth = [&]() -> int32_t { auto _try_value = doof::array_pop(this->tagExpressionDepths); if (doof::is_failure(_try_value)) doof::panic_at("src/lexer", 356, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
#line 357 "/src/lexer.do"
                (this->tagMode = [&]() -> std::string { auto _try_value = doof::array_pop(this->tagModeStack); if (doof::is_failure(_try_value)) doof::panic_at("src/lexer", 357, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
#line 358 "/src/lexer.do"
                continue;
            }
#line 360 "/src/lexer.do"
            (doof::array_at(this->tagExpressionDepths, index, "src/lexer", 360) = (doof::array_at(this->tagExpressionDepths, index, "src/lexer", 360) - 1));
        } else if ((this->tagMode == std::string("tag-expression")) && (peek(0) == U'\u007B')) {
#line 362 "/src/lexer.do"
            const auto index = (static_cast<int32_t>((this->tagExpressionDepths)->size()) - 1);
#line 363 "/src/lexer.do"
            (doof::array_at(this->tagExpressionDepths, index, "src/lexer", 363) = (doof::array_at(this->tagExpressionDepths, index, "src/lexer", 363) + 1));
        }
#line 366 "/src/lexer.do"
        const auto ch = peek(0);
#line 367 "/src/lexer.do"
        if ((ch == U'\u0022') || (ch == U'\u0060')) {
#line 368 "/src/lexer.do"
            readQuoted(ch);
        } else if (ch == U'\'') {
#line 370 "/src/lexer.do"
            readChar();
        } else if (isDigit(ch)) {
#line 372 "/src/lexer.do"
            readNumber();
        } else if (isIdentStart(ch)) {
#line 374 "/src/lexer.do"
            readIdentifier();
        } else {
#line 376 "/src/lexer.do"
            readOperatorOrPunctuation();
        }
    }
#line 380 "/src/lexer.do"
    if (static_cast<int32_t>((this->braceDepth)->size()) > 0) {
#line 381 "/src/lexer.do"
        diagnostic(std::string("Unterminated string interpolation"), doof::array_at(this->interpolationLines, (static_cast<int32_t>((this->interpolationLines)->size()) - 1), "src/lexer", 381), doof::array_at(this->interpolationColumns, (static_cast<int32_t>((this->interpolationColumns)->size()) - 1), "src/lexer", 381));
    }
#line 384 "/src/lexer.do"
    addToken(TokenType::EndOfFile, this->pos, 0, this->pos, 0, false, this->line, this->column);
#line 385 "/src/lexer.do"
    return this->tokens;
}
#line 388 "/src/lexer.do"
void Lexer::beginTag() {
#line 389 "/src/lexer.do"
    this->tagModeStack->push_back(this->tagMode);
#line 390 "/src/lexer.do"
    emit(TokenType::TagOpen, this->line, this->column, this->pos, 1);
#line 391 "/src/lexer.do"
    (this->tagMode = std::string("opening-tag"));
#line 392 "/src/lexer.do"
    (this->tagGenericDepth = 0);
}
#line 395 "/src/lexer.do"
void Lexer::beginTagExpression() {
#line 396 "/src/lexer.do"
    this->tagModeStack->push_back(this->tagMode);
#line 397 "/src/lexer.do"
    this->tagExpressionDepths->push_back(0);
#line 398 "/src/lexer.do"
    emit(TokenType::LeftBrace, this->line, this->column, this->pos, 1);
#line 399 "/src/lexer.do"
    (this->tagMode = std::string("tag-expression"));
}
#line 402 "/src/lexer.do"
void Lexer::readTagText() {
#line 403 "/src/lexer.do"
    const auto start = this->pos;
#line 404 "/src/lexer.do"
    const auto tokenLine = this->line;
#line 405 "/src/lexer.do"
    const auto tokenColumn = this->column;
#line 406 "/src/lexer.do"
    while (((this->pos < static_cast<int32_t>(this->source.size())) && (peek(0) != U'\u003C')) && (peek(0) != U'\u007B')) {
#line 406 "/src/lexer.do"
        advance();
    }
#line 407 "/src/lexer.do"
    if (this->pos > start) {
#line 407 "/src/lexer.do"
        addToken(TokenType::TagText, start, (this->pos - start), start, (this->pos - start), false, tokenLine, tokenColumn);
    }
}
#line 410 "/src/lexer.do"
bool Lexer::canStartTag() {
#line 411 "/src/lexer.do"
    if (static_cast<int32_t>((this->tokens)->size()) == 0) {
#line 411 "/src/lexer.do"
        return true;
    }
#line 412 "/src/lexer.do"
    if (this->line > doof::array_at(this->tokens, (static_cast<int32_t>((this->tokens)->size()) - 1), "src/lexer", 412).line) {
#line 412 "/src/lexer.do"
        return true;
    }
#line 413 "/src/lexer.do"
    const auto previous = doof::array_at(this->tokens, (static_cast<int32_t>((this->tokens)->size()) - 1), "src/lexer", 413).kind;
#line 414 "/src/lexer.do"
    return (((((((((((((((((((((((((((((((((previous == TokenType::Equal) || (previous == TokenType::ColonEqual)) || (previous == TokenType::LeftParen)) || (previous == TokenType::LeftBracket)) || (previous == TokenType::LeftBrace)) || (previous == TokenType::Comma)) || (previous == TokenType::Colon)) || (previous == TokenType::Semicolon)) || (previous == TokenType::Return)) || (previous == TokenType::Yield)) || (previous == TokenType::Then)) || (previous == TokenType::Else)) || (previous == TokenType::Arrow)) || (previous == TokenType::RightArrow)) || (previous == TokenType::Plus)) || (previous == TokenType::Minus)) || (previous == TokenType::Star)) || (previous == TokenType::Slash)) || (previous == TokenType::Backslash)) || (previous == TokenType::Percent)) || (previous == TokenType::Ampersand)) || (previous == TokenType::Pipe)) || (previous == TokenType::Caret)) || (previous == TokenType::Bang)) || (previous == TokenType::EqualEqual)) || (previous == TokenType::BangEqual)) || (previous == TokenType::Less)) || (previous == TokenType::LessEqual)) || (previous == TokenType::Greater)) || (previous == TokenType::GreaterEqual)) || (previous == TokenType::QuestionQuestion)) || (previous == TokenType::AmpersandAmpersand)) || (previous == TokenType::PipePipe));
}
#line 427 "/src/lexer.do"
char32_t Lexer::peek(int32_t offset) {
#line 428 "/src/lexer.do"
    if ((this->pos + offset) >= static_cast<int32_t>(this->source.size())) {
#line 428 "/src/lexer.do"
        return U'\0';
    }
#line 429 "/src/lexer.do"
    return doof::string_at(this->source, (this->pos + offset), "src/lexer", 429);
}
#line 432 "/src/lexer.do"
char32_t Lexer::advance() {
#line 433 "/src/lexer.do"
    const auto ch = doof::string_at(this->source, this->pos, "src/lexer", 433);
#line 434 "/src/lexer.do"
    (this->pos = (this->pos + 1));
#line 435 "/src/lexer.do"
    if (ch == U'\n') {
#line 436 "/src/lexer.do"
        (this->line = (this->line + 1));
#line 437 "/src/lexer.do"
        (this->column = 1);
    } else {
#line 439 "/src/lexer.do"
        (this->column = (this->column + 1));
    }
#line 441 "/src/lexer.do"
    return ch;
}
#line 444 "/src/lexer.do"
void Lexer::addToken(TokenType kind, int32_t tokenOffset, int32_t tokenLength, int32_t valueOffset, int32_t valueLength, bool needsDecode, int32_t tokenLine, int32_t tokenColumn) {
#line 445 "/src/lexer.do"
    this->tokens->push_back(Token{kind, tokenLength, valueOffset, valueLength, needsDecode, tokenLine, tokenColumn, tokenOffset});
}
#line 448 "/src/lexer.do"
void Lexer::diagnostic(const std::string& message, int32_t diagnosticLine, int32_t diagnosticColumn) {
#line 449 "/src/lexer.do"
    this->diagnostics->push_back(LexerDiagnostic{std::string("error"), message, diagnosticLine, diagnosticColumn});
}
#line 457 "/src/lexer.do"
void Lexer::skipWhitespaceAndComments() {
#line 458 "/src/lexer.do"
    while (this->pos < static_cast<int32_t>(this->source.size())) {
#line 459 "/src/lexer.do"
        const auto ch = peek(0);
#line 460 "/src/lexer.do"
        if ((((ch == U'\u0020') || (ch == U'\t')) || (ch == U'\r')) || (ch == U'\n')) {
#line 461 "/src/lexer.do"
            advance();
        } else if ((ch == U'\u002F') && (peek(1) == U'\u002F')) {
#line 463 "/src/lexer.do"
            while ((this->pos < static_cast<int32_t>(this->source.size())) && (peek(0) != U'\n')) {
#line 463 "/src/lexer.do"
                advance();
            }
        } else if ((ch == U'\u002F') && (peek(1) == U'\u002A')) {
#line 465 "/src/lexer.do"
            const auto commentLine = this->line;
#line 466 "/src/lexer.do"
            const auto commentColumn = this->column;
#line 467 "/src/lexer.do"
            advance();
#line 468 "/src/lexer.do"
            advance();
#line 469 "/src/lexer.do"
            auto terminated = false;
#line 470 "/src/lexer.do"
            while (this->pos < static_cast<int32_t>(this->source.size())) {
#line 471 "/src/lexer.do"
                if ((peek(0) == U'\u002A') && (peek(1) == U'\u002F')) {
#line 472 "/src/lexer.do"
                    advance();
#line 473 "/src/lexer.do"
                    advance();
#line 474 "/src/lexer.do"
                    (terminated = true);
#line 475 "/src/lexer.do"
                    break;
                }
#line 477 "/src/lexer.do"
                advance();
            }
#line 479 "/src/lexer.do"
            if (!terminated) {
#line 480 "/src/lexer.do"
                diagnostic(std::string("Unterminated block comment"), commentLine, commentColumn);
            }
        } else {
#line 483 "/src/lexer.do"
            break;
        }
    }
}
#line 488 "/src/lexer.do"
bool Lexer::isDigit(char32_t ch) {
#line 489 "/src/lexer.do"
    return ((ch >= U'\u0030') && (ch <= U'\u0039'));
}
#line 492 "/src/lexer.do"
bool Lexer::isHexDigit(char32_t ch) {
#line 493 "/src/lexer.do"
    return ((((ch >= U'\u0030') && (ch <= U'\u0039')) || ((ch >= U'\u0061') && (ch <= U'\u0066'))) || ((ch >= U'\u0041') && (ch <= U'\u0046')));
}
#line 496 "/src/lexer.do"
bool Lexer::isBaseDigit(char32_t ch, int32_t base) {
#line 497 "/src/lexer.do"
    if (base == 10) {
#line 497 "/src/lexer.do"
        return isDigit(ch);
    }
#line 498 "/src/lexer.do"
    if (base == 16) {
#line 498 "/src/lexer.do"
        return isHexDigit(ch);
    }
#line 499 "/src/lexer.do"
    return ((ch == U'\u0030') || (ch == U'\u0031'));
}
#line 502 "/src/lexer.do"
bool Lexer::isIdentStart(char32_t ch) {
#line 503 "/src/lexer.do"
    return ((((ch >= U'\u0061') && (ch <= U'\u007A')) || ((ch >= U'\u0041') && (ch <= U'\u005A'))) || (ch == U'\u005F'));
}
#line 506 "/src/lexer.do"
bool Lexer::isIdentPart(char32_t ch) {
#line 507 "/src/lexer.do"
    return (isIdentStart(ch) || isDigit(ch));
}
#line 510 "/src/lexer.do"
void Lexer::readDigits(int32_t base) {
#line 511 "/src/lexer.do"
    auto sawDigit = false;
#line 513 "/src/lexer.do"
    while (this->pos < static_cast<int32_t>(this->source.size())) {
#line 514 "/src/lexer.do"
        const auto ch = peek(0);
#line 515 "/src/lexer.do"
        if (isBaseDigit(ch, base)) {
#line 516 "/src/lexer.do"
            advance();
#line 517 "/src/lexer.do"
            (sawDigit = true);
        } else if (ch == U'\u005F') {
#line 519 "/src/lexer.do"
            if (sawDigit && isBaseDigit(peek(1), base)) {
#line 520 "/src/lexer.do"
                advance();
            } else {
#line 522 "/src/lexer.do"
                const auto separatorLine = this->line;
#line 523 "/src/lexer.do"
                const auto separatorColumn = this->column;
#line 524 "/src/lexer.do"
                while (peek(0) == U'\u005F') {
#line 524 "/src/lexer.do"
                    advance();
                }
#line 525 "/src/lexer.do"
                diagnostic(std::string("Numeric separators must appear between digits"), separatorLine, separatorColumn);
            }
        } else {
#line 528 "/src/lexer.do"
            break;
        }
    }
}
#line 534 "/src/lexer.do"
void Lexer::readNumber() {
#line 535 "/src/lexer.do"
    const auto start = this->pos;
#line 536 "/src/lexer.do"
    const auto tokenLine = this->line;
#line 537 "/src/lexer.do"
    const auto tokenColumn = this->column;
#line 538 "/src/lexer.do"
    if ((peek(0) == U'\u0030') && ((peek(1) == U'\u0078') || (peek(1) == U'\u0058'))) {
#line 539 "/src/lexer.do"
        advance();
#line 540 "/src/lexer.do"
        advance();
#line 541 "/src/lexer.do"
        readDigits(16);
#line 542 "/src/lexer.do"
        readNumericSuffix(start, this->pos, tokenLine, tokenColumn);
#line 543 "/src/lexer.do"
        return;
    }
#line 545 "/src/lexer.do"
    if ((peek(0) == U'\u0030') && ((peek(1) == U'\u0062') || (peek(1) == U'\u0042'))) {
#line 546 "/src/lexer.do"
        advance();
#line 547 "/src/lexer.do"
        advance();
#line 548 "/src/lexer.do"
        readDigits(2);
#line 549 "/src/lexer.do"
        readNumericSuffix(start, this->pos, tokenLine, tokenColumn);
#line 550 "/src/lexer.do"
        return;
    }
#line 553 "/src/lexer.do"
    readDigits(10);
#line 554 "/src/lexer.do"
    if (((peek(0) == U'\u002E') && (peek(1) != U'\u002E')) && (peek(1) != U'\u003C')) {
#line 555 "/src/lexer.do"
        advance();
#line 556 "/src/lexer.do"
        readDigits(10);
#line 557 "/src/lexer.do"
        const auto valueEnd = this->pos;
#line 558 "/src/lexer.do"
        if ((peek(0) == U'\u0066') || (peek(0) == U'\u0046')) {
#line 559 "/src/lexer.do"
            advance();
#line 560 "/src/lexer.do"
            addToken(TokenType::FloatLiteral, start, (this->pos - start), start, (valueEnd - start), false, tokenLine, tokenColumn);
        } else {
#line 562 "/src/lexer.do"
            addToken(TokenType::DoubleLiteral, start, (this->pos - start), start, (valueEnd - start), false, tokenLine, tokenColumn);
        }
#line 564 "/src/lexer.do"
        return;
    }
#line 566 "/src/lexer.do"
    readNumericSuffix(start, this->pos, tokenLine, tokenColumn);
}
#line 569 "/src/lexer.do"
void Lexer::readNumericSuffix(int32_t valueStart, int32_t valueEnd, int32_t tokenLine, int32_t tokenColumn) {
#line 570 "/src/lexer.do"
    if ((peek(0) == U'\u004C') || (peek(0) == U'\u006C')) {
#line 571 "/src/lexer.do"
        advance();
#line 572 "/src/lexer.do"
        addToken(TokenType::LongLiteral, valueStart, (this->pos - valueStart), valueStart, (valueEnd - valueStart), false, tokenLine, tokenColumn);
    } else if ((peek(0) == U'\u0066') || (peek(0) == U'\u0046')) {
#line 574 "/src/lexer.do"
        advance();
#line 575 "/src/lexer.do"
        addToken(TokenType::FloatLiteral, valueStart, (this->pos - valueStart), valueStart, (valueEnd - valueStart), false, tokenLine, tokenColumn);
    } else {
#line 577 "/src/lexer.do"
        addToken(TokenType::IntLiteral, valueStart, (this->pos - valueStart), valueStart, (valueEnd - valueStart), false, tokenLine, tokenColumn);
    }
}
#line 581 "/src/lexer.do"
void Lexer::readIdentifier() {
#line 582 "/src/lexer.do"
    const auto start = this->pos;
#line 583 "/src/lexer.do"
    const auto tokenLine = this->line;
#line 584 "/src/lexer.do"
    const auto tokenColumn = this->column;
#line 585 "/src/lexer.do"
    while ((this->pos < static_cast<int32_t>(this->source.size())) && isIdentPart(peek(0))) {
#line 585 "/src/lexer.do"
        advance();
    }
#line 587 "/src/lexer.do"
    auto value = doof::string_substring(this->source, start, this->pos);
#line 588 "/src/lexer.do"
    if ((value == std::string("try")) && ((peek(0) == U'\u0021') || (peek(0) == U'\u003F'))) {
#line 589 "/src/lexer.do"
        advance();
#line 590 "/src/lexer.do"
        addToken(TokenType::Identifier, start, (this->pos - start), start, (this->pos - start), false, tokenLine, tokenColumn);
#line 591 "/src/lexer.do"
        return;
    }
#line 594 "/src/lexer.do"
    if (value == std::string("_")) {
#line 595 "/src/lexer.do"
        addToken(TokenType::Underscore, start, (this->pos - start), start, (this->pos - start), false, tokenLine, tokenColumn);
    } else {
#line 597 "/src/lexer.do"
        addToken(keywordType(value), start, (this->pos - start), start, (this->pos - start), false, tokenLine, tokenColumn);
    }
}
#line 601 "/src/lexer.do"
void Lexer::readQuoted(char32_t delimiter) {
#line 602 "/src/lexer.do"
    const auto start = this->pos;
#line 603 "/src/lexer.do"
    const auto tokenLine = this->line;
#line 604 "/src/lexer.do"
    const auto tokenColumn = this->column;
#line 605 "/src/lexer.do"
    advance();
#line 606 "/src/lexer.do"
    const auto contentStart = this->pos;
#line 607 "/src/lexer.do"
    auto needsDecode = false;
#line 608 "/src/lexer.do"
    auto closed = false;
#line 610 "/src/lexer.do"
    while ((this->pos < static_cast<int32_t>(this->source.size())) && (peek(0) != delimiter)) {
#line 611 "/src/lexer.do"
        if ((peek(0) == U'\u0024') && (peek(1) == U'\u007B')) {
#line 612 "/src/lexer.do"
            addToken(TokenType::TemplateLiteralStart, start, (this->pos - start), contentStart, (this->pos - contentStart), needsDecode, tokenLine, tokenColumn);
#line 613 "/src/lexer.do"
            this->interpolationLines->push_back(this->line);
#line 614 "/src/lexer.do"
            this->interpolationColumns->push_back(this->column);
#line 615 "/src/lexer.do"
            advance();
#line 616 "/src/lexer.do"
            advance();
#line 617 "/src/lexer.do"
            this->templateDelimiters->push_back(delimiter);
#line 618 "/src/lexer.do"
            this->braceDepth->push_back(0);
#line 619 "/src/lexer.do"
            return;
        }
#line 621 "/src/lexer.do"
        if (peek(0) == U'\\') {
#line 622 "/src/lexer.do"
            (needsDecode = true);
#line 623 "/src/lexer.do"
            advance();
#line 624 "/src/lexer.do"
            advance();
        } else {
#line 626 "/src/lexer.do"
            advance();
        }
    }
#line 630 "/src/lexer.do"
    if (this->pos < static_cast<int32_t>(this->source.size())) {
#line 631 "/src/lexer.do"
        advance();
#line 632 "/src/lexer.do"
        (closed = true);
    } else {
#line 634 "/src/lexer.do"
        diagnostic(std::string("Unterminated string literal"), tokenLine, tokenColumn);
    }
#line 635 "/src/lexer.do"
    auto valueEnd = this->pos;
#line 636 "/src/lexer.do"
    if (closed) {
#line 636 "/src/lexer.do"
        (valueEnd = (this->pos - 1));
    }
#line 637 "/src/lexer.do"
    addToken(TokenType::StringLiteral, start, (this->pos - start), contentStart, (valueEnd - contentStart), needsDecode, tokenLine, tokenColumn);
}
#line 640 "/src/lexer.do"
void Lexer::readTemplateContinuation() {
#line 641 "/src/lexer.do"
    const auto start = this->pos;
#line 642 "/src/lexer.do"
    const auto tokenLine = this->line;
#line 643 "/src/lexer.do"
    const auto tokenColumn = this->column;
#line 644 "/src/lexer.do"
    const auto delimiter = doof::array_at(this->templateDelimiters, (static_cast<int32_t>((this->templateDelimiters)->size()) - 1), "src/lexer", 644);
#line 645 "/src/lexer.do"
    const auto contentStart = this->pos;
#line 646 "/src/lexer.do"
    auto needsDecode = false;
#line 647 "/src/lexer.do"
    auto closed = false;
#line 649 "/src/lexer.do"
    while ((this->pos < static_cast<int32_t>(this->source.size())) && (peek(0) != delimiter)) {
#line 650 "/src/lexer.do"
        if ((peek(0) == U'\u0024') && (peek(1) == U'\u007B')) {
#line 651 "/src/lexer.do"
            addToken(TokenType::TemplateLiteralMiddle, start, (this->pos - start), contentStart, (this->pos - contentStart), needsDecode, tokenLine, tokenColumn);
#line 652 "/src/lexer.do"
            this->interpolationLines->push_back(this->line);
#line 653 "/src/lexer.do"
            this->interpolationColumns->push_back(this->column);
#line 654 "/src/lexer.do"
            advance();
#line 655 "/src/lexer.do"
            advance();
#line 656 "/src/lexer.do"
            this->braceDepth->push_back(0);
#line 657 "/src/lexer.do"
            return;
        }
#line 659 "/src/lexer.do"
        if (peek(0) == U'\\') {
#line 660 "/src/lexer.do"
            (needsDecode = true);
#line 661 "/src/lexer.do"
            advance();
#line 662 "/src/lexer.do"
            advance();
        } else {
#line 664 "/src/lexer.do"
            advance();
        }
    }
#line 668 "/src/lexer.do"
    if (this->pos < static_cast<int32_t>(this->source.size())) {
#line 669 "/src/lexer.do"
        advance();
#line 670 "/src/lexer.do"
        (closed = true);
    } else {
#line 672 "/src/lexer.do"
        diagnostic(std::string("Unterminated template literal"), tokenLine, tokenColumn);
    }
#line 673 "/src/lexer.do"
    auto valueEnd = this->pos;
#line 674 "/src/lexer.do"
    if (closed) {
#line 674 "/src/lexer.do"
        (valueEnd = (this->pos - 1));
    }
#line 675 "/src/lexer.do"
    const auto ignoredDelimiter = [&]() -> char32_t { auto _try_value = doof::array_pop(this->templateDelimiters); if (doof::is_failure(_try_value)) doof::panic_at("src/lexer", 675, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
#line 676 "/src/lexer.do"
    addToken(TokenType::TemplateLiteralEnd, start, (this->pos - start), contentStart, (valueEnd - contentStart), needsDecode, tokenLine, tokenColumn);
}
#line 679 "/src/lexer.do"
void Lexer::readChar() {
#line 680 "/src/lexer.do"
    const auto start = this->pos;
#line 681 "/src/lexer.do"
    const auto tokenLine = this->line;
#line 682 "/src/lexer.do"
    const auto tokenColumn = this->column;
#line 683 "/src/lexer.do"
    advance();
#line 684 "/src/lexer.do"
    const auto valueStart = this->pos;
#line 685 "/src/lexer.do"
    auto needsDecode = false;
#line 686 "/src/lexer.do"
    if (peek(0) == U'\\') {
#line 687 "/src/lexer.do"
        (needsDecode = true);
#line 688 "/src/lexer.do"
        advance();
#line 689 "/src/lexer.do"
        advance();
    } else if (this->pos < static_cast<int32_t>(this->source.size())) {
#line 691 "/src/lexer.do"
        const auto width = utf8SequenceLength(peek(0));
#line 692 "/src/lexer.do"
        auto consumed = 0;
#line 693 "/src/lexer.do"
        while ((consumed < width) && (this->pos < static_cast<int32_t>(this->source.size()))) {
#line 694 "/src/lexer.do"
            advance();
#line 695 "/src/lexer.do"
            (consumed = (consumed + 1));
        }
    }
#line 698 "/src/lexer.do"
    const auto valueEnd = this->pos;
#line 699 "/src/lexer.do"
    if ((this->pos < static_cast<int32_t>(this->source.size())) && (peek(0) == U'\'')) {
#line 699 "/src/lexer.do"
        advance();
    }
#line 700 "/src/lexer.do"
    addToken(TokenType::CharLiteral, start, (this->pos - start), valueStart, (valueEnd - valueStart), needsDecode, tokenLine, tokenColumn);
}
#line 703 "/src/lexer.do"
void Lexer::emit(TokenType kind, int32_t tokenLine, int32_t tokenColumn, int32_t start, int32_t count) {
#line 706 "/src/lexer.do"
    if (count > 0) {
#line 706 "/src/lexer.do"
        advance();
    }
#line 707 "/src/lexer.do"
    if (count > 1) {
#line 707 "/src/lexer.do"
        advance();
    }
#line 708 "/src/lexer.do"
    if (count > 2) {
#line 708 "/src/lexer.do"
        advance();
    }
#line 709 "/src/lexer.do"
    if (count > 3) {
#line 709 "/src/lexer.do"
        advance();
    }
#line 710 "/src/lexer.do"
    if (count > 4) {
#line 710 "/src/lexer.do"
        advance();
    }
#line 711 "/src/lexer.do"
    if (count > 5) {
#line 711 "/src/lexer.do"
        advance();
    }
#line 712 "/src/lexer.do"
    if (count > 6) {
#line 712 "/src/lexer.do"
        advance();
    }
#line 713 "/src/lexer.do"
    addToken(kind, start, count, start, count, false, tokenLine, tokenColumn);
}
#line 716 "/src/lexer.do"
void Lexer::readOperatorOrPunctuation() {
#line 717 "/src/lexer.do"
    const auto start = this->pos;
#line 718 "/src/lexer.do"
    const auto tokenLine = this->line;
#line 719 "/src/lexer.do"
    const auto tokenColumn = this->column;
#line 720 "/src/lexer.do"
    const auto ch = peek(0);
#line 722 "/src/lexer.do"
    if (ch == U'\u0028') {
#line 722 "/src/lexer.do"
        emit(TokenType::LeftParen, tokenLine, tokenColumn, start, 1);
#line 722 "/src/lexer.do"
        return;
    }
#line 723 "/src/lexer.do"
    if (ch == U'\u0029') {
#line 723 "/src/lexer.do"
        emit(TokenType::RightParen, tokenLine, tokenColumn, start, 1);
#line 723 "/src/lexer.do"
        return;
    }
#line 724 "/src/lexer.do"
    if (ch == U'\u007B') {
#line 725 "/src/lexer.do"
        advance();
#line 726 "/src/lexer.do"
        if (static_cast<int32_t>((this->braceDepth)->size()) > 0) {
#line 726 "/src/lexer.do"
            (doof::array_at(this->braceDepth, (static_cast<int32_t>((this->braceDepth)->size()) - 1), "src/lexer", 726) = (doof::array_at(this->braceDepth, (static_cast<int32_t>((this->braceDepth)->size()) - 1), "src/lexer", 726) + 1));
        }
#line 727 "/src/lexer.do"
        addToken(TokenType::LeftBrace, start, 1, start, 1, false, tokenLine, tokenColumn);
#line 728 "/src/lexer.do"
        return;
    }
#line 730 "/src/lexer.do"
    if (ch == U'\u007D') {
#line 731 "/src/lexer.do"
        advance();
#line 732 "/src/lexer.do"
        if (static_cast<int32_t>((this->braceDepth)->size()) > 0) {
#line 732 "/src/lexer.do"
            (doof::array_at(this->braceDepth, (static_cast<int32_t>((this->braceDepth)->size()) - 1), "src/lexer", 732) = (doof::array_at(this->braceDepth, (static_cast<int32_t>((this->braceDepth)->size()) - 1), "src/lexer", 732) - 1));
        }
#line 733 "/src/lexer.do"
        addToken(TokenType::RightBrace, start, 1, start, 1, false, tokenLine, tokenColumn);
#line 734 "/src/lexer.do"
        return;
    }
#line 736 "/src/lexer.do"
    if (ch == U'\u005B') {
#line 736 "/src/lexer.do"
        emit(TokenType::LeftBracket, tokenLine, tokenColumn, start, 1);
#line 736 "/src/lexer.do"
        return;
    }
#line 737 "/src/lexer.do"
    if (ch == U'\u005D') {
#line 737 "/src/lexer.do"
        emit(TokenType::RightBracket, tokenLine, tokenColumn, start, 1);
#line 737 "/src/lexer.do"
        return;
    }
#line 738 "/src/lexer.do"
    if (ch == U'\u002C') {
#line 738 "/src/lexer.do"
        emit(TokenType::Comma, tokenLine, tokenColumn, start, 1);
#line 738 "/src/lexer.do"
        return;
    }
#line 739 "/src/lexer.do"
    if (ch == U'\u003B') {
#line 739 "/src/lexer.do"
        emit(TokenType::Semicolon, tokenLine, tokenColumn, start, 1);
#line 739 "/src/lexer.do"
        return;
    }
#line 740 "/src/lexer.do"
    if (ch == U'\u007E') {
#line 740 "/src/lexer.do"
        emit(TokenType::Tilde, tokenLine, tokenColumn, start, 1);
#line 740 "/src/lexer.do"
        return;
    }
#line 742 "/src/lexer.do"
    if (ch == U'\u002E') {
#line 743 "/src/lexer.do"
        if ((peek(1) == U'\u002E') && (peek(2) == U'\u002E')) {
#line 743 "/src/lexer.do"
            emit(TokenType::Ellipsis, tokenLine, tokenColumn, start, 3);
        } else if ((peek(1) == U'\u002E') && (peek(2) == U'\u003C')) {
#line 744 "/src/lexer.do"
            emit(TokenType::DotDotLess, tokenLine, tokenColumn, start, 3);
        } else if (peek(1) == U'\u002E') {
#line 745 "/src/lexer.do"
            emit(TokenType::DotDot, tokenLine, tokenColumn, start, 2);
        } else {
#line 746 "/src/lexer.do"
            emit(TokenType::Dot, tokenLine, tokenColumn, start, 1);
        }
#line 747 "/src/lexer.do"
        return;
    }
#line 749 "/src/lexer.do"
    if (ch == U'\u003A') {
#line 750 "/src/lexer.do"
        if (peek(1) == U'\u003A') {
#line 750 "/src/lexer.do"
            emit(TokenType::DoubleColon, tokenLine, tokenColumn, start, 2);
        } else if (peek(1) == U'\u003D') {
#line 751 "/src/lexer.do"
            emit(TokenType::ColonEqual, tokenLine, tokenColumn, start, 2);
        } else {
#line 752 "/src/lexer.do"
            emit(TokenType::Colon, tokenLine, tokenColumn, start, 1);
        }
#line 753 "/src/lexer.do"
        return;
    }
#line 755 "/src/lexer.do"
    if (ch == U'\u003D') {
#line 756 "/src/lexer.do"
        if (peek(1) == U'\u003D') {
#line 756 "/src/lexer.do"
            emit(TokenType::EqualEqual, tokenLine, tokenColumn, start, 2);
        } else if (peek(1) == U'\u003E') {
#line 757 "/src/lexer.do"
            emit(TokenType::Arrow, tokenLine, tokenColumn, start, 2);
        } else {
#line 758 "/src/lexer.do"
            emit(TokenType::Equal, tokenLine, tokenColumn, start, 1);
        }
#line 759 "/src/lexer.do"
        return;
    }
#line 761 "/src/lexer.do"
    if (ch == U'\u002B') {
#line 762 "/src/lexer.do"
        if (peek(1) == U'\u003D') {
#line 762 "/src/lexer.do"
            emit(TokenType::PlusEqual, tokenLine, tokenColumn, start, 2);
        } else {
#line 763 "/src/lexer.do"
            emit(TokenType::Plus, tokenLine, tokenColumn, start, 1);
        }
#line 764 "/src/lexer.do"
        return;
    }
#line 766 "/src/lexer.do"
    if (ch == U'\u002D') {
#line 767 "/src/lexer.do"
        if (peek(1) == U'\u003E') {
#line 767 "/src/lexer.do"
            emit(TokenType::RightArrow, tokenLine, tokenColumn, start, 2);
        } else if (peek(1) == U'\u003D') {
#line 768 "/src/lexer.do"
            emit(TokenType::MinusEqual, tokenLine, tokenColumn, start, 2);
        } else {
#line 769 "/src/lexer.do"
            emit(TokenType::Minus, tokenLine, tokenColumn, start, 1);
        }
#line 770 "/src/lexer.do"
        return;
    }
#line 772 "/src/lexer.do"
    if (ch == U'\u002A') {
#line 773 "/src/lexer.do"
        if ((peek(1) == U'\u002A') && (peek(2) == U'\u003D')) {
#line 773 "/src/lexer.do"
            emit(TokenType::StarStarEqual, tokenLine, tokenColumn, start, 3);
        } else if (peek(1) == U'\u002A') {
#line 774 "/src/lexer.do"
            emit(TokenType::StarStar, tokenLine, tokenColumn, start, 2);
        } else if (peek(1) == U'\u003D') {
#line 775 "/src/lexer.do"
            emit(TokenType::StarEqual, tokenLine, tokenColumn, start, 2);
        } else {
#line 776 "/src/lexer.do"
            emit(TokenType::Star, tokenLine, tokenColumn, start, 1);
        }
#line 777 "/src/lexer.do"
        return;
    }
#line 779 "/src/lexer.do"
    if (ch == U'\u002F') {
#line 780 "/src/lexer.do"
        if (peek(1) == U'\u003D') {
#line 780 "/src/lexer.do"
            emit(TokenType::SlashEqual, tokenLine, tokenColumn, start, 2);
        } else {
#line 781 "/src/lexer.do"
            emit(TokenType::Slash, tokenLine, tokenColumn, start, 1);
        }
#line 782 "/src/lexer.do"
        return;
    }
#line 784 "/src/lexer.do"
    if (ch == U'\u0025') {
#line 785 "/src/lexer.do"
        if (peek(1) == U'\u003D') {
#line 785 "/src/lexer.do"
            emit(TokenType::PercentEqual, tokenLine, tokenColumn, start, 2);
        } else {
#line 786 "/src/lexer.do"
            emit(TokenType::Percent, tokenLine, tokenColumn, start, 1);
        }
#line 787 "/src/lexer.do"
        return;
    }
#line 789 "/src/lexer.do"
    if (ch == U'\\') {
#line 790 "/src/lexer.do"
        if (peek(1) == U'\u003D') {
#line 790 "/src/lexer.do"
            emit(TokenType::BackslashEqual, tokenLine, tokenColumn, start, 2);
        } else {
#line 791 "/src/lexer.do"
            emit(TokenType::Backslash, tokenLine, tokenColumn, start, 1);
        }
#line 792 "/src/lexer.do"
        return;
    }
#line 794 "/src/lexer.do"
    if (ch == U'\u0026') {
#line 795 "/src/lexer.do"
        if (peek(1) == U'\u0026') {
#line 795 "/src/lexer.do"
            emit(TokenType::AmpersandAmpersand, tokenLine, tokenColumn, start, 2);
        } else if (peek(1) == U'\u003D') {
#line 796 "/src/lexer.do"
            emit(TokenType::AmpersandEqual, tokenLine, tokenColumn, start, 2);
        } else {
#line 797 "/src/lexer.do"
            emit(TokenType::Ampersand, tokenLine, tokenColumn, start, 1);
        }
#line 798 "/src/lexer.do"
        return;
    }
#line 800 "/src/lexer.do"
    if (ch == U'\u007C') {
#line 801 "/src/lexer.do"
        if (peek(1) == U'\u007C') {
#line 801 "/src/lexer.do"
            emit(TokenType::PipePipe, tokenLine, tokenColumn, start, 2);
        } else if (peek(1) == U'\u003D') {
#line 802 "/src/lexer.do"
            emit(TokenType::PipeEqual, tokenLine, tokenColumn, start, 2);
        } else {
#line 803 "/src/lexer.do"
            emit(TokenType::Pipe, tokenLine, tokenColumn, start, 1);
        }
#line 804 "/src/lexer.do"
        return;
    }
#line 806 "/src/lexer.do"
    if (ch == U'\u005E') {
#line 807 "/src/lexer.do"
        if (peek(1) == U'\u003D') {
#line 807 "/src/lexer.do"
            emit(TokenType::CaretEqual, tokenLine, tokenColumn, start, 2);
        } else {
#line 808 "/src/lexer.do"
            emit(TokenType::Caret, tokenLine, tokenColumn, start, 1);
        }
#line 809 "/src/lexer.do"
        return;
    }
#line 811 "/src/lexer.do"
    if (ch == U'\u003C') {
#line 812 "/src/lexer.do"
        if ((peek(1) == U'\u003C') && (peek(2) == U'\u003D')) {
#line 812 "/src/lexer.do"
            emit(TokenType::LessLessEqual, tokenLine, tokenColumn, start, 3);
        } else if (peek(1) == U'\u003C') {
#line 813 "/src/lexer.do"
            emit(TokenType::LessLess, tokenLine, tokenColumn, start, 2);
        } else if (peek(1) == U'\u002D') {
#line 814 "/src/lexer.do"
            emit(TokenType::LeftArrow, tokenLine, tokenColumn, start, 2);
        } else if (peek(1) == U'\u003D') {
#line 815 "/src/lexer.do"
            emit(TokenType::LessEqual, tokenLine, tokenColumn, start, 2);
        } else {
#line 816 "/src/lexer.do"
            emit(TokenType::Less, tokenLine, tokenColumn, start, 1);
        }
#line 817 "/src/lexer.do"
        return;
    }
#line 819 "/src/lexer.do"
    if (ch == U'\u003E') {
#line 820 "/src/lexer.do"
        if (((peek(1) == U'\u003E') && (peek(2) == U'\u003E')) && (peek(3) == U'\u003D')) {
#line 820 "/src/lexer.do"
            emit(TokenType::GreaterGreaterEqual, tokenLine, tokenColumn, start, 4);
        } else if ((peek(1) == U'\u003E') && (peek(2) == U'\u003E')) {
#line 821 "/src/lexer.do"
            emit(TokenType::GreaterGreaterGreater, tokenLine, tokenColumn, start, 3);
        } else if ((peek(1) == U'\u003E') && (peek(2) == U'\u003D')) {
#line 822 "/src/lexer.do"
            emit(TokenType::GreaterGreaterEqual, tokenLine, tokenColumn, start, 3);
        } else if (peek(1) == U'\u003E') {
#line 823 "/src/lexer.do"
            emit(TokenType::GreaterGreater, tokenLine, tokenColumn, start, 2);
        } else if (peek(1) == U'\u003D') {
#line 824 "/src/lexer.do"
            emit(TokenType::GreaterEqual, tokenLine, tokenColumn, start, 2);
        } else {
#line 825 "/src/lexer.do"
            emit(TokenType::Greater, tokenLine, tokenColumn, start, 1);
        }
#line 826 "/src/lexer.do"
        return;
    }
#line 828 "/src/lexer.do"
    if (ch == U'\u0021') {
#line 829 "/src/lexer.do"
        if (peek(1) == U'\u003D') {
#line 829 "/src/lexer.do"
            emit(TokenType::BangEqual, tokenLine, tokenColumn, start, 2);
        } else if (peek(1) == U'\u002E') {
#line 830 "/src/lexer.do"
            emit(TokenType::BangDot, tokenLine, tokenColumn, start, 2);
        } else {
#line 831 "/src/lexer.do"
            emit(TokenType::Bang, tokenLine, tokenColumn, start, 1);
        }
#line 832 "/src/lexer.do"
        return;
    }
#line 834 "/src/lexer.do"
    if (ch == U'\u003F') {
#line 835 "/src/lexer.do"
        if ((peek(1) == U'\u003F') && (peek(2) == U'\u003D')) {
#line 835 "/src/lexer.do"
            emit(TokenType::QuestionQuestionEqual, tokenLine, tokenColumn, start, 3);
        } else if (peek(1) == U'\u003F') {
#line 836 "/src/lexer.do"
            emit(TokenType::QuestionQuestion, tokenLine, tokenColumn, start, 2);
        } else if (peek(1) == U'\u002E') {
#line 837 "/src/lexer.do"
            emit(TokenType::QuestionDot, tokenLine, tokenColumn, start, 2);
        } else if (peek(1) == U'\u005B') {
#line 838 "/src/lexer.do"
            emit(TokenType::QuestionBracket, tokenLine, tokenColumn, start, 2);
        } else {
#line 839 "/src/lexer.do"
            emit(TokenType::Identifier, tokenLine, tokenColumn, start, 1);
        }
#line 840 "/src/lexer.do"
        return;
    }
#line 842 "/src/lexer.do"
    if ((((ch == U'\u0040') && ((this->pos + 7) <= static_cast<int32_t>(this->source.size()))) && (doof::string_substring(this->source, this->pos, (this->pos + 7)) == std::string("@caller"))) && !isIdentPart(peek(7))) {
#line 843 "/src/lexer.do"
        emit(TokenType::CallerIntrinsic, tokenLine, tokenColumn, start, 7);
#line 844 "/src/lexer.do"
        return;
    }
#line 847 "/src/lexer.do"
    diagnostic(((std::string("Unexpected character: '") + doof::to_string(ch)) + std::string("'")), this->line, this->column);
#line 848 "/src/lexer.do"
    advance();
}
#line 1 "<doof-generated>"
char32_t charFromUtf8(const std::string& value) {
    return ::doof::char_from_utf8(value);
}
}

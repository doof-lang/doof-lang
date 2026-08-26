#include "std_url_index.hpp"

namespace std_::url::index {
using namespace ::std_::blob::index;


#line 25 "/std/url/index.do"
bool Path::isEmpty() {
    return (static_cast<int32_t>((this->segments)->size()) == 0);
}
#line 27 "/std/url/index.do"
int32_t Path::segmentCount() {
    return static_cast<int32_t>((this->segments)->size());
}
#line 29 "/std/url/index.do"
std::string Path::segment(int32_t index) {
    return doof::array_at(this->segments, index, "index", 29);
}

#line 37 "/std/url/index.do"
bool Authority::hasUserinfo() {
    return (!doof::is_null(this->userinfo));
}
#line 39 "/std/url/index.do"
bool Authority::hasPort() {
    return (!doof::is_null(this->port));
}

#line 46 "/std/url/index.do"
bool QueryParam::hasValue() {
    return (!doof::is_null(this->value));
}

#line 52 "/std/url/index.do"
bool QueryParams::isEmpty() {
    return (static_cast<int32_t>((this->entries)->size()) == 0);
}
#line 54 "/std/url/index.do"
int32_t QueryParams::size() {
    return static_cast<int32_t>((this->entries)->size());
}
#line 56 "/std/url/index.do"
bool QueryParams::has(const std::string& name) {
#line 57 "/std/url/index.do"
    const auto& _iterable_2 = this->entries;
    for (const auto& entry : *_iterable_2) {
#line 58 "/std/url/index.do"
        if (entry->name == name) {
#line 59 "/std/url/index.do"
            return true;
        }
    }
#line 62 "/std/url/index.do"
    return false;
}
#line 65 "/std/url/index.do"
std::shared_ptr<QueryParam> QueryParams::first(const std::string& name) {
#line 66 "/std/url/index.do"
    const auto& _iterable_4 = this->entries;
    for (const auto& entry : *_iterable_4) {
#line 67 "/std/url/index.do"
        if (entry->name == name) {
#line 68 "/std/url/index.do"
            return entry;
        }
    }
#line 71 "/std/url/index.do"
    return nullptr;
}
#line 74 "/std/url/index.do"
std::shared_ptr<std::vector<std::shared_ptr<QueryParam>>> QueryParams::all(const std::string& name) {
#line 75 "/std/url/index.do"
    const std::shared_ptr<std::vector<std::shared_ptr<QueryParam>>> matches = std::make_shared<std::vector<std::shared_ptr<QueryParam>>>(std::vector<std::shared_ptr<QueryParam>>{});
#line 76 "/std/url/index.do"
    const auto& _iterable_6 = this->entries;
    for (const auto& entry : *_iterable_6) {
#line 77 "/std/url/index.do"
        if (entry->name == name) {
#line 78 "/std/url/index.do"
            matches->push_back(entry);
        }
    }
#line 81 "/std/url/index.do"
    return doof::array_drainToReadonly(matches, "", 0);
}
#line 85 "/std/url/index.do"
doof::Result<std::shared_ptr<Path>, std::shared_ptr<UrlError>> parsePath(const std::string& text) {
#line 86 "/std/url/index.do"
    if (static_cast<int32_t>(text.size()) == 0) {
#line 87 "/std/url/index.do"
        return doof::Success<std::shared_ptr<Path>>{ std::make_shared<Path>(false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) };
    }
#line 95 "/std/url/index.do"
    const auto rawSegments = doof::string_split(text, std::string("/"));
#line 96 "/std/url/index.do"
    const std::shared_ptr<std::vector<std::string>> segments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 97 "/std/url/index.do"
    auto firstSegment = (doof::string_startsWith(text, std::string("/")) ? 1 : 0);
#line 99 "/std/url/index.do"
    for (int32_t index = firstSegment; index < static_cast<int32_t>((rawSegments)->size()); ++index) {
#line 100 "/std/url/index.do"
        const auto rawSegment = doof::array_at(rawSegments, index, "index", 100);
#line 101 "/std/url/index.do"
        auto _try_value_8 = decodeComponent(rawSegment, false);
        if (doof::is_failure(_try_value_8)) return doof::Failure<std::shared_ptr<UrlError>>{doof::variant_promote<std::shared_ptr<UrlError>>(doof::failure_error(_try_value_8))};
        const auto segment = doof::success_value(_try_value_8);
#line 102 "/std/url/index.do"
        segments->push_back(segment);
    }
#line 105 "/std/url/index.do"
    return doof::Success<std::shared_ptr<Path>>{ std::make_shared<Path>(doof::string_startsWith(text, std::string("/")), doof::array_drainToReadonly(segments, "", 0)) };
}
#line 113 "/std/url/index.do"
doof::Result<std::shared_ptr<Authority>, std::shared_ptr<UrlError>> parseAuthority(const std::string& text) {
#line 114 "/std/url/index.do"
    std::optional<std::string> userinfo = std::nullopt;
#line 115 "/std/url/index.do"
    auto hostPort = text;
#line 116 "/std/url/index.do"
    const auto atIndex = findLastChar(text, U'\u0040');
#line 118 "/std/url/index.do"
    if (atIndex >= 0) {
#line 119 "/std/url/index.do"
        auto _try_value_9 = decodeComponent(doof::string_substring(text, 0, atIndex), false);
        if (doof::is_failure(_try_value_9)) return doof::Failure<std::shared_ptr<UrlError>>{doof::variant_promote<std::shared_ptr<UrlError>>(doof::failure_error(_try_value_9))};
        const auto decodedUserinfo = doof::success_value(_try_value_9);
#line 120 "/std/url/index.do"
        (userinfo = decodedUserinfo);
#line 121 "/std/url/index.do"
        (hostPort = doof::string_slice(text, (atIndex + 1)));
    }
#line 124 "/std/url/index.do"
    auto hostText = hostPort;
#line 125 "/std/url/index.do"
    std::optional<std::string> port = std::nullopt;
#line 127 "/std/url/index.do"
    if (doof::string_startsWith(hostPort, std::string("["))) {
#line 128 "/std/url/index.do"
        const auto closeIndex = findChar(hostPort, U'\u005D');
#line 129 "/std/url/index.do"
        if (closeIndex < 0) {
#line 130 "/std/url/index.do"
            return invalidAuthority(0, std::string("Missing closing bracket in authority host"));
        }
#line 133 "/std/url/index.do"
        (hostText = doof::string_substring(hostPort, 0, (closeIndex + 1)));
#line 134 "/std/url/index.do"
        if ((closeIndex + 1) < static_cast<int32_t>(hostPort.size())) {
#line 135 "/std/url/index.do"
            if (doof::string_at(hostPort, (closeIndex + 1), "", 0) != U'\u003A') {
#line 136 "/std/url/index.do"
                return invalidAuthority((closeIndex + 1), std::string("Invalid bracketed authority host"));
            }
#line 138 "/std/url/index.do"
            (port = doof::string_slice(hostPort, (closeIndex + 2)));
        }
    } else {
#line 141 "/std/url/index.do"
        const auto portSeparator = findSingleChar(hostPort, U'\u003A');
#line 142 "/std/url/index.do"
        if (portSeparator >= 0) {
#line 143 "/std/url/index.do"
            (hostText = doof::string_substring(hostPort, 0, portSeparator));
#line 144 "/std/url/index.do"
            (port = doof::string_slice(hostPort, (portSeparator + 1)));
        }
    }
#line 148 "/std/url/index.do"
    auto _try_value_10 = decodeComponent(hostText, false);
    if (doof::is_failure(_try_value_10)) return doof::Failure<std::shared_ptr<UrlError>>{doof::variant_promote<std::shared_ptr<UrlError>>(doof::failure_error(_try_value_10))};
    const auto host = doof::success_value(_try_value_10);
#line 150 "/std/url/index.do"
    return doof::Success<std::shared_ptr<Authority>>{ std::make_shared<Authority>(userinfo, host, port) };
}
#line 159 "/std/url/index.do"
doof::Result<std::shared_ptr<QueryParams>, std::shared_ptr<UrlError>> parseQueryParams(const std::string& text) {
#line 160 "/std/url/index.do"
    if (static_cast<int32_t>(text.size()) == 0) {
#line 161 "/std/url/index.do"
        return doof::Success<std::shared_ptr<QueryParams>>{ std::make_shared<QueryParams>(std::make_shared<std::vector<std::shared_ptr<QueryParam>>>(std::vector<std::shared_ptr<QueryParam>>{})) };
    }
#line 168 "/std/url/index.do"
    const std::shared_ptr<std::vector<std::shared_ptr<QueryParam>>> entries = std::make_shared<std::vector<std::shared_ptr<QueryParam>>>(std::vector<std::shared_ptr<QueryParam>>{});
#line 169 "/std/url/index.do"
    const auto rawEntries = doof::string_split(text, std::string("&"));
#line 171 "/std/url/index.do"
    const auto& _iterable_12 = rawEntries;
    for (const auto& rawEntry : *_iterable_12) {
#line 172 "/std/url/index.do"
        if (static_cast<int32_t>(rawEntry.size()) == 0) {
#line 173 "/std/url/index.do"
            continue;
        }
#line 176 "/std/url/index.do"
        const auto separator = doof::string_indexOf(rawEntry, std::string("="));
#line 177 "/std/url/index.do"
        if (separator < 0) {
#line 178 "/std/url/index.do"
            auto _try_value_13 = decodeComponent(rawEntry, true);
            if (doof::is_failure(_try_value_13)) return doof::Failure<std::shared_ptr<UrlError>>{doof::variant_promote<std::shared_ptr<UrlError>>(doof::failure_error(_try_value_13))};
            const auto name = doof::success_value(_try_value_13);
#line 179 "/std/url/index.do"
            entries->push_back(std::make_shared<QueryParam>(name, std::nullopt));
#line 180 "/std/url/index.do"
            continue;
        }
#line 183 "/std/url/index.do"
        auto _try_value_14 = decodeComponent(doof::string_substring(rawEntry, 0, separator), true);
        if (doof::is_failure(_try_value_14)) return doof::Failure<std::shared_ptr<UrlError>>{doof::variant_promote<std::shared_ptr<UrlError>>(doof::failure_error(_try_value_14))};
        const auto name = doof::success_value(_try_value_14);
#line 184 "/std/url/index.do"
        auto _try_value_15 = decodeComponent(doof::string_slice(rawEntry, (separator + 1)), true);
        if (doof::is_failure(_try_value_15)) return doof::Failure<std::shared_ptr<UrlError>>{doof::variant_promote<std::shared_ptr<UrlError>>(doof::failure_error(_try_value_15))};
        const auto value = doof::success_value(_try_value_15);
#line 185 "/std/url/index.do"
        entries->push_back(std::make_shared<QueryParam>(name, value));
    }
#line 188 "/std/url/index.do"
    return doof::Success<std::shared_ptr<QueryParams>>{ std::make_shared<QueryParams>(doof::array_drainToReadonly(entries, "", 0)) };
}
#line 195 "/std/url/index.do"
doof::Result<std::string, std::shared_ptr<UrlError>> decodeComponent(const std::string& text, bool plusAsSpace) {
#line 196 "/std/url/index.do"
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian);
#line 197 "/std/url/index.do"
    auto rawStart = 0;
#line 198 "/std/url/index.do"
    auto index = 0;
#line 200 "/std/url/index.do"
    while (index < static_cast<int32_t>(text.size())) {
#line 201 "/std/url/index.do"
        const auto current = doof::string_at(text, index, "", 0);
#line 203 "/std/url/index.do"
        if (current == U'\u0025') {
#line 204 "/std/url/index.do"
            if (rawStart < index) {
#line 205 "/std/url/index.do"
                builder->writeString(doof::string_substring(text, rawStart, index));
            }
#line 208 "/std/url/index.do"
            if ((index + 2) >= static_cast<int32_t>(text.size())) {
#line 209 "/std/url/index.do"
                return invalidPercentEncoding(index);
            }
#line 212 "/std/url/index.do"
            const auto high = hexValue(doof::string_at(text, (index + 1), "", 0));
#line 213 "/std/url/index.do"
            const auto low = hexValue(doof::string_at(text, (index + 2), "", 0));
#line 214 "/std/url/index.do"
            if ((high < 0) || (low < 0)) {
#line 215 "/std/url/index.do"
                return invalidPercentEncoding(index);
            }
#line 218 "/std/url/index.do"
            builder->writeByte(static_cast<uint8_t>(((high * 16) + low)));
#line 219 "/std/url/index.do"
            (index += 3);
#line 220 "/std/url/index.do"
            (rawStart = index);
#line 221 "/std/url/index.do"
            continue;
        }
#line 224 "/std/url/index.do"
        if (plusAsSpace && (current == U'\u002B')) {
#line 225 "/std/url/index.do"
            if (rawStart < index) {
#line 226 "/std/url/index.do"
                builder->writeString(doof::string_substring(text, rawStart, index));
            }
#line 228 "/std/url/index.do"
            builder->writeString(std::string(" "));
#line 229 "/std/url/index.do"
            (index += 1);
#line 230 "/std/url/index.do"
            (rawStart = index);
#line 231 "/std/url/index.do"
            continue;
        }
#line 234 "/std/url/index.do"
        (index += 1);
    }
#line 237 "/std/url/index.do"
    if (rawStart < static_cast<int32_t>(text.size())) {
#line 238 "/std/url/index.do"
        builder->writeString(doof::string_substring(text, rawStart, static_cast<int32_t>(text.size())));
    }
#line 241 "/std/url/index.do"
    const auto bytes = builder->build();
#line 242 "/std/url/index.do"
    const auto reader = ::doof_blob::NativeBlobReader::constructor(bytes, ::std_::blob::types::Endian::LittleEndian);
#line 243 "/std/url/index.do"
    return doof::Success<std::string>{ reader->readString(reader->length()) };
}
#line 246 "/std/url/index.do"
int32_t findChar(const std::string& text, char32_t target) {
#line 247 "/std/url/index.do"
    auto index = 0;
#line 248 "/std/url/index.do"
    while (index < static_cast<int32_t>(text.size())) {
#line 249 "/std/url/index.do"
        if (doof::string_at(text, index, "", 0) == target) {
#line 250 "/std/url/index.do"
            return index;
        }
#line 252 "/std/url/index.do"
        (index += 1);
    }
#line 254 "/std/url/index.do"
    return -1;
}
#line 257 "/std/url/index.do"
int32_t findLastChar(const std::string& text, char32_t target) {
#line 258 "/std/url/index.do"
    auto found = -1;
#line 259 "/std/url/index.do"
    auto index = 0;
#line 260 "/std/url/index.do"
    while (index < static_cast<int32_t>(text.size())) {
#line 261 "/std/url/index.do"
        if (doof::string_at(text, index, "", 0) == target) {
#line 262 "/std/url/index.do"
            (found = index);
        }
#line 264 "/std/url/index.do"
        (index += 1);
    }
#line 266 "/std/url/index.do"
    return found;
}
#line 269 "/std/url/index.do"
int32_t findSingleChar(const std::string& text, char32_t target) {
#line 270 "/std/url/index.do"
    auto found = -1;
#line 271 "/std/url/index.do"
    auto index = 0;
#line 272 "/std/url/index.do"
    while (index < static_cast<int32_t>(text.size())) {
#line 273 "/std/url/index.do"
        if (doof::string_at(text, index, "", 0) == target) {
#line 274 "/std/url/index.do"
            if (found >= 0) {
#line 275 "/std/url/index.do"
                return -1;
            }
#line 277 "/std/url/index.do"
            (found = index);
        }
#line 279 "/std/url/index.do"
        (index += 1);
    }
#line 281 "/std/url/index.do"
    return found;
}
#line 284 "/std/url/index.do"
int32_t hexValue(char32_t value) {
#line 285 "/std/url/index.do"
    if ((value >= U'\u0030') && (value <= U'\u0039')) {
#line 286 "/std/url/index.do"
        return (static_cast<int32_t>(value) - static_cast<int32_t>(U'\u0030'));
    }
#line 288 "/std/url/index.do"
    if ((value >= U'\u0061') && (value <= U'\u0066')) {
#line 289 "/std/url/index.do"
        return ((10 + static_cast<int32_t>(value)) - static_cast<int32_t>(U'\u0061'));
    }
#line 291 "/std/url/index.do"
    if ((value >= U'\u0041') && (value <= U'\u0046')) {
#line 292 "/std/url/index.do"
        return ((10 + static_cast<int32_t>(value)) - static_cast<int32_t>(U'\u0041'));
    }
#line 294 "/std/url/index.do"
    return -1;
}
#line 297 "/std/url/index.do"
doof::Result<std::string, std::shared_ptr<UrlError>> invalidPercentEncoding(int32_t index) {
#line 298 "/std/url/index.do"
    return doof::Failure<std::shared_ptr<UrlError>>{ std::make_shared<UrlError>(std::string("invalid-percent-encoding"), index, ([&]() -> std::string { std::string _interpolation = "Invalid percent encoding at byte "; _interpolation += doof::to_string(index); _interpolation += ""; return _interpolation; }())) };
}
#line 307 "/std/url/index.do"
doof::Result<std::shared_ptr<Authority>, std::shared_ptr<UrlError>> invalidAuthority(int32_t index, const std::string& message) {
#line 308 "/std/url/index.do"
    return doof::Failure<std::shared_ptr<UrlError>>{ std::make_shared<UrlError>(std::string("invalid-authority"), index, message) };
}
#line 1 "<doof-generated>"
}

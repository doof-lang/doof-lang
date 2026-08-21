#include "std_url_index.hpp"

namespace std_::url::index {
using namespace ::std_::blob::index;


bool Path::isEmpty() {
    return (static_cast<int32_t>((this->segments)->size()) == 0);
}
int32_t Path::segmentCount() {
    return static_cast<int32_t>((this->segments)->size());
}
std::string Path::segment(int32_t index) {
    return doof::array_at(this->segments, index, "index", 29);
}

bool Authority::hasUserinfo() {
    return (!doof::is_null(this->userinfo));
}
bool Authority::hasPort() {
    return (!doof::is_null(this->port));
}

bool QueryParam::hasValue() {
    return (!doof::is_null(this->value));
}

bool QueryParams::isEmpty() {
    return (static_cast<int32_t>((this->entries)->size()) == 0);
}
int32_t QueryParams::size() {
    return static_cast<int32_t>((this->entries)->size());
}
bool QueryParams::has(const std::string& name) {
    const auto& _iterable_2 = this->entries;
    for (const auto& entry : *_iterable_2) {
        if (entry->name == name) {
            return true;
        }
    }
    return false;
}
std::shared_ptr<QueryParam> QueryParams::first(const std::string& name) {
    const auto& _iterable_4 = this->entries;
    for (const auto& entry : *_iterable_4) {
        if (entry->name == name) {
            return entry;
        }
    }
    return nullptr;
}
std::shared_ptr<std::vector<std::shared_ptr<QueryParam>>> QueryParams::all(const std::string& name) {
    const std::shared_ptr<std::vector<std::shared_ptr<QueryParam>>> matches = std::make_shared<std::vector<std::shared_ptr<QueryParam>>>(std::vector<std::shared_ptr<QueryParam>>{});
    const auto& _iterable_6 = this->entries;
    for (const auto& entry : *_iterable_6) {
        if (entry->name == name) {
            matches->push_back(entry);
        }
    }
    return doof::array_drainToReadonly(matches, "", 0);
}
doof::Result<std::shared_ptr<Path>, std::shared_ptr<UrlError>> parsePath(const std::string& text) {
    if (static_cast<int32_t>(text.size()) == 0) {
        return doof::Success<std::shared_ptr<Path>>{ std::make_shared<Path>(false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) };
    }
    const auto rawSegments = doof::string_split(text, std::string("/"));
    const std::shared_ptr<std::vector<std::string>> segments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    auto firstSegment = (doof::string_startsWith(text, std::string("/")) ? 1 : 0);
    for (int32_t index = firstSegment; index < static_cast<int32_t>((rawSegments)->size()); ++index) {
        const auto rawSegment = doof::array_at(rawSegments, index, "index", 100);
        auto _try_value_8 = decodeComponent(rawSegment, false);
        if (doof::is_failure(_try_value_8)) return doof::Failure<std::shared_ptr<UrlError>>{doof::variant_promote<std::shared_ptr<UrlError>>(doof::failure_error(_try_value_8))};
        const auto segment = doof::success_value(_try_value_8);
        segments->push_back(segment);
    }
    return doof::Success<std::shared_ptr<Path>>{ std::make_shared<Path>(doof::string_startsWith(text, std::string("/")), doof::array_drainToReadonly(segments, "", 0)) };
}
doof::Result<std::shared_ptr<Authority>, std::shared_ptr<UrlError>> parseAuthority(const std::string& text) {
    std::optional<std::string> userinfo = std::nullopt;
    auto hostPort = text;
    const auto atIndex = findLastChar(text, U'\u0040');
    if (atIndex >= 0) {
        auto _try_value_9 = decodeComponent(doof::string_substring(text, 0, atIndex), false);
        if (doof::is_failure(_try_value_9)) return doof::Failure<std::shared_ptr<UrlError>>{doof::variant_promote<std::shared_ptr<UrlError>>(doof::failure_error(_try_value_9))};
        const auto decodedUserinfo = doof::success_value(_try_value_9);
        (userinfo = decodedUserinfo);
        (hostPort = doof::string_slice(text, (atIndex + 1)));
    }
    auto hostText = hostPort;
    std::optional<std::string> port = std::nullopt;
    if (doof::string_startsWith(hostPort, std::string("["))) {
        const auto closeIndex = findChar(hostPort, U'\u005D');
        if (closeIndex < 0) {
            return invalidAuthority(0, std::string("Missing closing bracket in authority host"));
        }
        (hostText = doof::string_substring(hostPort, 0, (closeIndex + 1)));
        if ((closeIndex + 1) < static_cast<int32_t>(hostPort.size())) {
            if (doof::string_at(hostPort, (closeIndex + 1), "", 0) != U'\u003A') {
                return invalidAuthority((closeIndex + 1), std::string("Invalid bracketed authority host"));
            }
            (port = doof::string_slice(hostPort, (closeIndex + 2)));
        }
    } else {
        const auto portSeparator = findSingleChar(hostPort, U'\u003A');
        if (portSeparator >= 0) {
            (hostText = doof::string_substring(hostPort, 0, portSeparator));
            (port = doof::string_slice(hostPort, (portSeparator + 1)));
        }
    }
    auto _try_value_10 = decodeComponent(hostText, false);
    if (doof::is_failure(_try_value_10)) return doof::Failure<std::shared_ptr<UrlError>>{doof::variant_promote<std::shared_ptr<UrlError>>(doof::failure_error(_try_value_10))};
    const auto host = doof::success_value(_try_value_10);
    return doof::Success<std::shared_ptr<Authority>>{ std::make_shared<Authority>(userinfo, host, port) };
}
doof::Result<std::shared_ptr<QueryParams>, std::shared_ptr<UrlError>> parseQueryParams(const std::string& text) {
    if (static_cast<int32_t>(text.size()) == 0) {
        return doof::Success<std::shared_ptr<QueryParams>>{ std::make_shared<QueryParams>(std::make_shared<std::vector<std::shared_ptr<QueryParam>>>(std::vector<std::shared_ptr<QueryParam>>{})) };
    }
    const std::shared_ptr<std::vector<std::shared_ptr<QueryParam>>> entries = std::make_shared<std::vector<std::shared_ptr<QueryParam>>>(std::vector<std::shared_ptr<QueryParam>>{});
    const auto rawEntries = doof::string_split(text, std::string("&"));
    const auto& _iterable_12 = rawEntries;
    for (const auto& rawEntry : *_iterable_12) {
        if (static_cast<int32_t>(rawEntry.size()) == 0) {
            continue;
        }
        const auto separator = doof::string_indexOf(rawEntry, std::string("="));
        if (separator < 0) {
            auto _try_value_13 = decodeComponent(rawEntry, true);
            if (doof::is_failure(_try_value_13)) return doof::Failure<std::shared_ptr<UrlError>>{doof::variant_promote<std::shared_ptr<UrlError>>(doof::failure_error(_try_value_13))};
            const auto name = doof::success_value(_try_value_13);
            entries->push_back(std::make_shared<QueryParam>(name, std::nullopt));
            continue;
        }
        auto _try_value_14 = decodeComponent(doof::string_substring(rawEntry, 0, separator), true);
        if (doof::is_failure(_try_value_14)) return doof::Failure<std::shared_ptr<UrlError>>{doof::variant_promote<std::shared_ptr<UrlError>>(doof::failure_error(_try_value_14))};
        const auto name = doof::success_value(_try_value_14);
        auto _try_value_15 = decodeComponent(doof::string_slice(rawEntry, (separator + 1)), true);
        if (doof::is_failure(_try_value_15)) return doof::Failure<std::shared_ptr<UrlError>>{doof::variant_promote<std::shared_ptr<UrlError>>(doof::failure_error(_try_value_15))};
        const auto value = doof::success_value(_try_value_15);
        entries->push_back(std::make_shared<QueryParam>(name, value));
    }
    return doof::Success<std::shared_ptr<QueryParams>>{ std::make_shared<QueryParams>(doof::array_drainToReadonly(entries, "", 0)) };
}
doof::Result<std::string, std::shared_ptr<UrlError>> decodeComponent(const std::string& text, bool plusAsSpace) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian);
    auto rawStart = 0;
    auto index = 0;
    while (index < static_cast<int32_t>(text.size())) {
        const auto current = doof::string_at(text, index, "", 0);
        if (current == U'\u0025') {
            if (rawStart < index) {
                builder->writeString(doof::string_substring(text, rawStart, index));
            }
            if ((index + 2) >= static_cast<int32_t>(text.size())) {
                return invalidPercentEncoding(index);
            }
            const auto high = hexValue(doof::string_at(text, (index + 1), "", 0));
            const auto low = hexValue(doof::string_at(text, (index + 2), "", 0));
            if ((high < 0) || (low < 0)) {
                return invalidPercentEncoding(index);
            }
            builder->writeByte(static_cast<uint8_t>(((high * 16) + low)));
            (index += 3);
            (rawStart = index);
            continue;
        }
        if (plusAsSpace && (current == U'\u002B')) {
            if (rawStart < index) {
                builder->writeString(doof::string_substring(text, rawStart, index));
            }
            builder->writeString(std::string(" "));
            (index += 1);
            (rawStart = index);
            continue;
        }
        (index += 1);
    }
    if (rawStart < static_cast<int32_t>(text.size())) {
        builder->writeString(doof::string_substring(text, rawStart, static_cast<int32_t>(text.size())));
    }
    const auto bytes = builder->build();
    const auto reader = ::doof_blob::NativeBlobReader::constructor(bytes, ::std_::blob::types::Endian::LittleEndian);
    return doof::Success<std::string>{ reader->readString(reader->length()) };
}
int32_t findChar(const std::string& text, char32_t target) {
    auto index = 0;
    while (index < static_cast<int32_t>(text.size())) {
        if (doof::string_at(text, index, "", 0) == target) {
            return index;
        }
        (index += 1);
    }
    return -1;
}
int32_t findLastChar(const std::string& text, char32_t target) {
    auto found = -1;
    auto index = 0;
    while (index < static_cast<int32_t>(text.size())) {
        if (doof::string_at(text, index, "", 0) == target) {
            (found = index);
        }
        (index += 1);
    }
    return found;
}
int32_t findSingleChar(const std::string& text, char32_t target) {
    auto found = -1;
    auto index = 0;
    while (index < static_cast<int32_t>(text.size())) {
        if (doof::string_at(text, index, "", 0) == target) {
            if (found >= 0) {
                return -1;
            }
            (found = index);
        }
        (index += 1);
    }
    return found;
}
int32_t hexValue(char32_t value) {
    if ((value >= U'\u0030') && (value <= U'\u0039')) {
        return (static_cast<int32_t>(value) - static_cast<int32_t>(U'\u0030'));
    }
    if ((value >= U'\u0061') && (value <= U'\u0066')) {
        return ((10 + static_cast<int32_t>(value)) - static_cast<int32_t>(U'\u0061'));
    }
    if ((value >= U'\u0041') && (value <= U'\u0046')) {
        return ((10 + static_cast<int32_t>(value)) - static_cast<int32_t>(U'\u0041'));
    }
    return -1;
}
doof::Result<std::string, std::shared_ptr<UrlError>> invalidPercentEncoding(int32_t index) {
    return doof::Failure<std::shared_ptr<UrlError>>{ std::make_shared<UrlError>(std::string("invalid-percent-encoding"), index, ([&]() -> std::string { std::string _interpolation = "Invalid percent encoding at byte "; _interpolation += doof::to_string(index); _interpolation += ""; return _interpolation; }())) };
}
doof::Result<std::shared_ptr<Authority>, std::shared_ptr<UrlError>> invalidAuthority(int32_t index, const std::string& message) {
    return doof::Failure<std::shared_ptr<UrlError>>{ std::make_shared<UrlError>(std::string("invalid-authority"), index, message) };
}
}

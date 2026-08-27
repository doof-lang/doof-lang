#include "std_http_transport_url.hpp"

namespace std_::http::transport_url {
using namespace ::std_::http::types;
doof::Result<std::string, std::shared_ptr<::std_::http::types::HttpError>> prepareTransportUrl(const std::string& url) {
    const auto schemeEnd = doof::string_indexOf(url, std::string("://"));
    if (schemeEnd < 0) {
        return doof::Success<std::string>{ url };
    }
    const auto scheme = doof::string_toLowerCase(doof::string_substring(url, 0, schemeEnd));
    if ((((scheme != std::string("http")) && (scheme != std::string("https"))) && (scheme != std::string("ws"))) && (scheme != std::string("wss"))) {
        return doof::Success<std::string>{ url };
    }
    const auto authorityStart = (schemeEnd + 3);
    const auto authorityEnd = findAuthorityEnd(url, authorityStart);
    const auto lastAt = findLastByteInRange(url, static_cast<int32_t>(U'\u0040'), authorityStart, authorityEnd);
    const auto hostStart = ((lastAt >= 0) ? (lastAt + 1) : authorityStart);
    if (hostStart >= authorityEnd) {
        return doof::Success<std::string>{ url };
    }
    if (doof::string_at(url, hostStart, "", 0) == U'\u005B') {
        return doof::Success<std::string>{ url };
    }
    auto hostEnd = authorityEnd;
    auto colon = -1;
    auto colonCount = 0;
    auto index = hostStart;
    while (index < authorityEnd) {
        if (doof::string_at(url, index, "", 0) == U'\u003A') {
            (colon = index);
            (colonCount += 1);
        }
        (index += 1);
    }
    if (colonCount == 1) {
        (hostEnd = colon);
    } else if (colonCount > 1) {
        return doof::Success<std::string>{ url };
    }
    const auto host = doof::string_substring(url, hostStart, hostEnd);
    const auto asciiHost = ::std_::url::hostname::hostnameToAscii(host);
    {
        auto _case_subject = asciiHost;
        if (std::holds_alternative<doof::Success<std::string>>(_case_subject)) {
            const auto& s = std::get<doof::Success<std::string>>(_case_subject);
            return doof::Success<std::string>{ ((doof::string_substring(url, 0, hostStart) + s.value) + doof::string_slice(url, hostEnd)) };
    }
    else if (std::holds_alternative<doof::Failure<std::shared_ptr<::std_::url::punycode_error::PunycodeError>>>(_case_subject)) {
            const auto& f = std::get<doof::Failure<std::shared_ptr<::std_::url::punycode_error::PunycodeError>>>(_case_subject);
            return doof::Failure<std::shared_ptr<::std_::http::types::HttpError>>{ std::make_shared<::std_::http::types::HttpError>(std::string("invalid-url"), std::string("0"), ([&]() -> std::string { std::string _interpolation = "Invalid internationalized hostname at byte "; _interpolation += doof::to_string((hostStart + f.error->index)); _interpolation += ": "; _interpolation += doof::to_string(f.error->message); _interpolation += ""; return _interpolation; }())) };
    }
    }
    doof::unreachable();
}
int32_t findAuthorityEnd(const std::string& url, int32_t start) {
    auto index = start;
    while (index < static_cast<int32_t>(url.size())) {
        const auto value = doof::string_at(url, index, "", 0);
        if (((value == U'\u002F') || (value == U'\u003F')) || (value == U'\u0023')) {
            return index;
        }
        (index += 1);
    }
    return static_cast<int32_t>(url.size());
}
int32_t findLastByteInRange(const std::string& text, int32_t target, int32_t start, int32_t end) {
    auto found = -1;
    auto index = start;
    while (index < end) {
        if (static_cast<int32_t>(doof::string_at(text, index, "", 0)) == target) {
            (found = index);
        }
        (index += 1);
    }
    return found;
}
}

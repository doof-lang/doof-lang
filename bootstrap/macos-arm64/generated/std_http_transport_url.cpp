#include "std_http_transport_url.hpp"

namespace std_::http::transport_url {
using namespace ::std_::http::types;
#line 5 "/std/http/transport_url.do"
doof::Result<std::string, std::shared_ptr<::std_::http::types::HttpError>> prepareTransportUrl(const std::string& url) {
#line 6 "/std/http/transport_url.do"
    const auto schemeEnd = doof::string_indexOf(url, std::string("://"));
#line 7 "/std/http/transport_url.do"
    if (schemeEnd < 0) {
#line 8 "/std/http/transport_url.do"
        return doof::Success<std::string>{ url };
    }
#line 11 "/std/http/transport_url.do"
    const auto scheme = doof::string_toLowerCase(doof::string_substring(url, 0, schemeEnd));
#line 12 "/std/http/transport_url.do"
    if ((((scheme != std::string("http")) && (scheme != std::string("https"))) && (scheme != std::string("ws"))) && (scheme != std::string("wss"))) {
#line 13 "/std/http/transport_url.do"
        return doof::Success<std::string>{ url };
    }
#line 16 "/std/http/transport_url.do"
    const auto authorityStart = (schemeEnd + 3);
#line 17 "/std/http/transport_url.do"
    const auto authorityEnd = findAuthorityEnd(url, authorityStart);
#line 18 "/std/http/transport_url.do"
    const auto lastAt = findLastByteInRange(url, static_cast<int32_t>(U'\u0040'), authorityStart, authorityEnd);
#line 19 "/std/http/transport_url.do"
    const auto hostStart = ((lastAt >= 0) ? (lastAt + 1) : authorityStart);
#line 20 "/std/http/transport_url.do"
    if (hostStart >= authorityEnd) {
#line 21 "/std/http/transport_url.do"
        return doof::Success<std::string>{ url };
    }
#line 24 "/std/http/transport_url.do"
    if (doof::string_at(url, hostStart, "", 0) == U'\u005B') {
#line 25 "/std/http/transport_url.do"
        return doof::Success<std::string>{ url };
    }
#line 28 "/std/http/transport_url.do"
    auto hostEnd = authorityEnd;
#line 29 "/std/http/transport_url.do"
    auto colon = -1;
#line 30 "/std/http/transport_url.do"
    auto colonCount = 0;
#line 31 "/std/http/transport_url.do"
    auto index = hostStart;
#line 32 "/std/http/transport_url.do"
    while (index < authorityEnd) {
#line 33 "/std/http/transport_url.do"
        if (doof::string_at(url, index, "", 0) == U'\u003A') {
#line 34 "/std/http/transport_url.do"
            (colon = index);
#line 35 "/std/http/transport_url.do"
            (colonCount += 1);
        }
#line 37 "/std/http/transport_url.do"
        (index += 1);
    }
#line 39 "/std/http/transport_url.do"
    if (colonCount == 1) {
#line 40 "/std/http/transport_url.do"
        (hostEnd = colon);
    } else if (colonCount > 1) {
#line 42 "/std/http/transport_url.do"
        return doof::Success<std::string>{ url };
    }
#line 45 "/std/http/transport_url.do"
    const auto host = doof::string_substring(url, hostStart, hostEnd);
#line 46 "/std/http/transport_url.do"
    const auto asciiHost = ::std_::url::hostname::hostnameToAscii(host);
#line 47 "/std/http/transport_url.do"
    {
        auto _case_subject = asciiHost;
        if (std::holds_alternative<doof::Success<std::string>>(_case_subject)) {
            const auto& s = std::get<doof::Success<std::string>>(_case_subject);
#line 48 "/std/http/transport_url.do"
            return doof::Success<std::string>{ ((doof::string_substring(url, 0, hostStart) + s.value) + doof::string_slice(url, hostEnd)) };
    }
    else if (std::holds_alternative<doof::Failure<std::shared_ptr<::std_::url::punycode_error::PunycodeError>>>(_case_subject)) {
            const auto& f = std::get<doof::Failure<std::shared_ptr<::std_::url::punycode_error::PunycodeError>>>(_case_subject);
#line 51 "/std/http/transport_url.do"
            return doof::Failure<std::shared_ptr<::std_::http::types::HttpError>>{ std::make_shared<::std_::http::types::HttpError>(std::string("invalid-url"), std::string("0"), ([&]() -> std::string { std::string _interpolation = "Invalid internationalized hostname at byte "; _interpolation += doof::to_string((hostStart + f.error->index)); _interpolation += ": "; _interpolation += doof::to_string(f.error->message); _interpolation += ""; return _interpolation; }())) };
    }
    }
    doof::unreachable();
}
#line 61 "/std/http/transport_url.do"
int32_t findAuthorityEnd(const std::string& url, int32_t start) {
#line 62 "/std/http/transport_url.do"
    auto index = start;
#line 63 "/std/http/transport_url.do"
    while (index < static_cast<int32_t>(url.size())) {
#line 64 "/std/http/transport_url.do"
        const auto value = doof::string_at(url, index, "", 0);
#line 65 "/std/http/transport_url.do"
        if (((value == U'\u002F') || (value == U'\u003F')) || (value == U'\u0023')) {
#line 66 "/std/http/transport_url.do"
            return index;
        }
#line 68 "/std/http/transport_url.do"
        (index += 1);
    }
#line 70 "/std/http/transport_url.do"
    return static_cast<int32_t>(url.size());
}
#line 73 "/std/http/transport_url.do"
int32_t findLastByteInRange(const std::string& text, int32_t target, int32_t start, int32_t end) {
#line 74 "/std/http/transport_url.do"
    auto found = -1;
#line 75 "/std/http/transport_url.do"
    auto index = start;
#line 76 "/std/http/transport_url.do"
    while (index < end) {
#line 77 "/std/http/transport_url.do"
        if (static_cast<int32_t>(doof::string_at(text, index, "", 0)) == target) {
#line 78 "/std/http/transport_url.do"
            (found = index);
        }
#line 80 "/std/http/transport_url.do"
        (index += 1);
    }
#line 82 "/std/http/transport_url.do"
    return found;
}
#line 1 "<doof-generated>"
}

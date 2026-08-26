#include "std_url_hostname.hpp"

namespace std_::url::hostname {
using namespace ::std_::url::punycode;
using namespace ::std_::url::punycode_error;
#line 4 "/std/url/hostname.do"
doof::Result<std::string, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> hostnameToAscii(const std::string& hostname) {
#line 5 "/std/url/hostname.do"
    if (isBracketedHost(hostname)) {
#line 6 "/std/url/hostname.do"
        return doof::Success<std::string>{ hostname };
    }
#line 9 "/std/url/hostname.do"
    const auto labels = doof::string_split(hostname, std::string("."));
#line 10 "/std/url/hostname.do"
    auto result = std::string("");
#line 11 "/std/url/hostname.do"
    auto offset = 0;
#line 12 "/std/url/hostname.do"
    auto index = 0;
#line 13 "/std/url/hostname.do"
    while (index < static_cast<int32_t>((labels)->size())) {
#line 14 "/std/url/hostname.do"
        if (index > 0) {
#line 15 "/std/url/hostname.do"
            (result += std::string("."));
        }
#line 18 "/std/url/hostname.do"
        const auto label = doof::array_at(labels, index, "hostname", 18);
#line 19 "/std/url/hostname.do"
        if (containsNonAscii(label)) {
#line 20 "/std/url/hostname.do"
            const auto encoded = ::std_::url::punycode::encodePunycodeLabel(label);
#line 21 "/std/url/hostname.do"
            {
                auto _case_subject = encoded;
                if (std::holds_alternative<doof::Success<std::string>>(_case_subject)) {
                    const auto& s = std::get<doof::Success<std::string>>(_case_subject);
#line 22 "/std/url/hostname.do"
                    (result += ([&]() -> std::string { std::string _interpolation = "xn--"; _interpolation += doof::to_string(s.value); _interpolation += ""; return _interpolation; }()));
            }
            else if (std::holds_alternative<doof::Failure<std::shared_ptr<::std_::url::punycode_error::PunycodeError>>>(_case_subject)) {
                    const auto& f = std::get<doof::Failure<std::shared_ptr<::std_::url::punycode_error::PunycodeError>>>(_case_subject);
#line 23 "/std/url/hostname.do"
                    return doof::Failure<std::shared_ptr<::std_::url::punycode_error::PunycodeError>>{ offsetError(f.error, offset) };
            }
            }
        } else {
#line 26 "/std/url/hostname.do"
            (result += label);
        }
#line 29 "/std/url/hostname.do"
        (offset += (static_cast<int32_t>(label.size()) + 1));
#line 30 "/std/url/hostname.do"
        (index += 1);
    }
#line 32 "/std/url/hostname.do"
    return doof::Success<std::string>{ result };
}
#line 35 "/std/url/hostname.do"
doof::Result<std::string, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> hostnameToUnicode(const std::string& hostname) {
#line 36 "/std/url/hostname.do"
    if (isBracketedHost(hostname)) {
#line 37 "/std/url/hostname.do"
        return doof::Success<std::string>{ hostname };
    }
#line 40 "/std/url/hostname.do"
    const auto labels = doof::string_split(hostname, std::string("."));
#line 41 "/std/url/hostname.do"
    auto result = std::string("");
#line 42 "/std/url/hostname.do"
    auto offset = 0;
#line 43 "/std/url/hostname.do"
    auto index = 0;
#line 44 "/std/url/hostname.do"
    while (index < static_cast<int32_t>((labels)->size())) {
#line 45 "/std/url/hostname.do"
        if (index > 0) {
#line 46 "/std/url/hostname.do"
            (result += std::string("."));
        }
#line 49 "/std/url/hostname.do"
        const auto label = doof::array_at(labels, index, "hostname", 49);
#line 50 "/std/url/hostname.do"
        if (doof::string_startsWith(doof::string_toLowerCase(label), std::string("xn--"))) {
#line 51 "/std/url/hostname.do"
            const auto decoded = ::std_::url::punycode::decodePunycodeLabel(doof::string_slice(label, 4));
#line 52 "/std/url/hostname.do"
            {
                auto _case_subject = decoded;
                if (std::holds_alternative<doof::Success<std::string>>(_case_subject)) {
                    const auto& s = std::get<doof::Success<std::string>>(_case_subject);
#line 53 "/std/url/hostname.do"
                    (result += s.value);
            }
            else if (std::holds_alternative<doof::Failure<std::shared_ptr<::std_::url::punycode_error::PunycodeError>>>(_case_subject)) {
                    const auto& f = std::get<doof::Failure<std::shared_ptr<::std_::url::punycode_error::PunycodeError>>>(_case_subject);
#line 54 "/std/url/hostname.do"
                    return doof::Failure<std::shared_ptr<::std_::url::punycode_error::PunycodeError>>{ offsetError(f.error, (offset + 4)) };
            }
            }
        } else {
#line 57 "/std/url/hostname.do"
            (result += label);
        }
#line 60 "/std/url/hostname.do"
        (offset += (static_cast<int32_t>(label.size()) + 1));
#line 61 "/std/url/hostname.do"
        (index += 1);
    }
#line 63 "/std/url/hostname.do"
    return doof::Success<std::string>{ result };
}
#line 66 "/std/url/hostname.do"
bool containsNonAscii(const std::string& text) {
#line 67 "/std/url/hostname.do"
    auto index = 0;
#line 68 "/std/url/hostname.do"
    while (index < static_cast<int32_t>(text.size())) {
#line 69 "/std/url/hostname.do"
        if (static_cast<int32_t>(doof::string_at(text, index, "", 0)) >= 128) {
#line 70 "/std/url/hostname.do"
            return true;
        }
#line 72 "/std/url/hostname.do"
        (index += 1);
    }
#line 74 "/std/url/hostname.do"
    return false;
}
#line 77 "/std/url/hostname.do"
bool isBracketedHost(const std::string& hostname) {
#line 78 "/std/url/hostname.do"
    return (((static_cast<int32_t>(hostname.size()) >= 2) && doof::string_startsWith(hostname, std::string("["))) && doof::string_endsWith(hostname, std::string("]")));
}
#line 81 "/std/url/hostname.do"
std::shared_ptr<::std_::url::punycode_error::PunycodeError> offsetError(const std::shared_ptr<::std_::url::punycode_error::PunycodeError>& error, int32_t offset) {
#line 82 "/std/url/hostname.do"
    return std::make_shared<::std_::url::punycode_error::PunycodeError>(error->kind, (offset + error->index), error->message);
}
#line 1 "<doof-generated>"
}

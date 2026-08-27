#include "std_url_hostname.hpp"

namespace std_::url::hostname {
using namespace ::std_::url::punycode;
using namespace ::std_::url::punycode_error;
doof::Result<std::string, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> hostnameToAscii(const std::string& hostname) {
    if (isBracketedHost(hostname)) {
        return doof::Success<std::string>{ hostname };
    }
    const auto labels = doof::string_split(hostname, std::string("."));
    auto result = std::string("");
    auto offset = 0;
    auto index = 0;
    while (index < static_cast<int32_t>((labels)->size())) {
        if (index > 0) {
            (result += std::string("."));
        }
        const auto label = doof::array_at(labels, index, "hostname", 18);
        if (containsNonAscii(label)) {
            const auto encoded = ::std_::url::punycode::encodePunycodeLabel(label);
            {
                auto _case_subject = encoded;
                if (std::holds_alternative<doof::Success<std::string>>(_case_subject)) {
                    const auto& s = std::get<doof::Success<std::string>>(_case_subject);
                    (result += ([&]() -> std::string { std::string _interpolation = "xn--"; _interpolation += doof::to_string(s.value); _interpolation += ""; return _interpolation; }()));
            }
            else if (std::holds_alternative<doof::Failure<std::shared_ptr<::std_::url::punycode_error::PunycodeError>>>(_case_subject)) {
                    const auto& f = std::get<doof::Failure<std::shared_ptr<::std_::url::punycode_error::PunycodeError>>>(_case_subject);
                    return doof::Failure<std::shared_ptr<::std_::url::punycode_error::PunycodeError>>{ offsetError(f.error, offset) };
            }
            }
        } else {
            (result += label);
        }
        (offset += (static_cast<int32_t>(label.size()) + 1));
        (index += 1);
    }
    return doof::Success<std::string>{ result };
}
doof::Result<std::string, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> hostnameToUnicode(const std::string& hostname) {
    if (isBracketedHost(hostname)) {
        return doof::Success<std::string>{ hostname };
    }
    const auto labels = doof::string_split(hostname, std::string("."));
    auto result = std::string("");
    auto offset = 0;
    auto index = 0;
    while (index < static_cast<int32_t>((labels)->size())) {
        if (index > 0) {
            (result += std::string("."));
        }
        const auto label = doof::array_at(labels, index, "hostname", 49);
        if (doof::string_startsWith(doof::string_toLowerCase(label), std::string("xn--"))) {
            const auto decoded = ::std_::url::punycode::decodePunycodeLabel(doof::string_slice(label, 4));
            {
                auto _case_subject = decoded;
                if (std::holds_alternative<doof::Success<std::string>>(_case_subject)) {
                    const auto& s = std::get<doof::Success<std::string>>(_case_subject);
                    (result += s.value);
            }
            else if (std::holds_alternative<doof::Failure<std::shared_ptr<::std_::url::punycode_error::PunycodeError>>>(_case_subject)) {
                    const auto& f = std::get<doof::Failure<std::shared_ptr<::std_::url::punycode_error::PunycodeError>>>(_case_subject);
                    return doof::Failure<std::shared_ptr<::std_::url::punycode_error::PunycodeError>>{ offsetError(f.error, (offset + 4)) };
            }
            }
        } else {
            (result += label);
        }
        (offset += (static_cast<int32_t>(label.size()) + 1));
        (index += 1);
    }
    return doof::Success<std::string>{ result };
}
bool containsNonAscii(const std::string& text) {
    auto index = 0;
    while (index < static_cast<int32_t>(text.size())) {
        if (static_cast<int32_t>(doof::string_at(text, index, "", 0)) >= 128) {
            return true;
        }
        (index += 1);
    }
    return false;
}
bool isBracketedHost(const std::string& hostname) {
    return (((static_cast<int32_t>(hostname.size()) >= 2) && doof::string_startsWith(hostname, std::string("["))) && doof::string_endsWith(hostname, std::string("]")));
}
std::shared_ptr<::std_::url::punycode_error::PunycodeError> offsetError(const std::shared_ptr<::std_::url::punycode_error::PunycodeError>& error, int32_t offset) {
    return std::make_shared<::std_::url::punycode_error::PunycodeError>(error->kind, (offset + error->index), error->message);
}
}

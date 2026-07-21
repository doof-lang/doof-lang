#include "std_crypto_index.hpp"
#include <cmath>
#include "std_json_index.hpp"
#include "std_blob_index.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace std_::crypto::index {
using namespace ::std_::json::index;
using namespace ::std_::blob::index;
std::string sha1Hex(std::shared_ptr<std::vector<uint8_t>> data) {
    return ::doof_crypto::encode_hex(::doof_crypto::sha1_bytes(data));
}
std::string sha1HexString(std::string text) {
    return ::doof_crypto::encode_hex(::doof_crypto::sha1_utf8(text));
}
std::string sha256Hex(std::shared_ptr<std::vector<uint8_t>> data) {
    return ::doof_crypto::encode_hex(::doof_crypto::sha256_bytes(data));
}
std::string sha256HexString(std::string text) {
    return ::doof_crypto::encode_hex(::doof_crypto::sha256_utf8(text));
}
std::string hmacSha256Hex(std::shared_ptr<::doof_crypto::SecretBytes> key, std::shared_ptr<std::vector<uint8_t>> data) {
    return ::doof_crypto::encode_hex(::doof_crypto::hmac_sha256(key, data));
}
std::string hmacSha256Base64Url(std::shared_ptr<::doof_crypto::SecretBytes> key, std::shared_ptr<std::vector<uint8_t>> data) {
    return ::doof_crypto::encode_base64_url(::doof_crypto::hmac_sha256(key, data));
}
std::shared_ptr<::doof_crypto::SecretBytes> randomBytes(int32_t length) {
    return ::doof_crypto::SecretBytes::random(length);
}

doof::JsonObject Jwt::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["header"] = doof::json_value(this->header);
    (*_json)["claims"] = doof::json_value(this->claims);
    (*_json)["signedContent"] = doof::json_value(this->signedContent);
    (*_json)["signature"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->signature->size()); for (const auto& _element : *this->signature) { _array->push_back(doof::json_value(static_cast<int32_t>(_element))); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<Jwt>, std::string> Jwt::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_header = _object->find("header");
    if (_iterator_header == _object->end()) { return doof::Failure<std::string>{"Missing required field \"header\""}; }
    if (!(doof::json_is_object(_iterator_header->second))) { return doof::Failure<std::string>{"Field \"header\" expected object but got " + std::string(doof::json_type_name(_iterator_header->second))}; }
    auto _field_header = [&]() { const auto* _object_value = doof::json_as_object(_iterator_header->second); auto _values = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(); for (const auto& _entry : *_object_value) { (*_values)[_entry.first] = _entry.second; } return _values; }();
    auto _iterator_claims = _object->find("claims");
    if (_iterator_claims == _object->end()) { return doof::Failure<std::string>{"Missing required field \"claims\""}; }
    if (!(doof::json_is_object(_iterator_claims->second))) { return doof::Failure<std::string>{"Field \"claims\" expected object but got " + std::string(doof::json_type_name(_iterator_claims->second))}; }
    auto _field_claims = [&]() { const auto* _object_value = doof::json_as_object(_iterator_claims->second); auto _values = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(); for (const auto& _entry : *_object_value) { (*_values)[_entry.first] = _entry.second; } return _values; }();
    auto _iterator_signedContent = _object->find("signedContent");
    if (_iterator_signedContent == _object->end()) { return doof::Failure<std::string>{"Missing required field \"signedContent\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_signedContent->second) : doof::json_is_string(_iterator_signedContent->second)))) { return doof::Failure<std::string>{"Field \"signedContent\" expected string but got " + std::string(doof::json_type_name(_iterator_signedContent->second))}; }
    auto _field_signedContent = (_lenient ? doof::json_as_string_lenient(_iterator_signedContent->second) : doof::json_as_string(_iterator_signedContent->second));
    auto _iterator_signature = _object->find("signature");
    if (_iterator_signature == _object->end()) { return doof::Failure<std::string>{"Missing required field \"signature\""}; }
    if (!(doof::json_is_array(_iterator_signature->second))) { return doof::Failure<std::string>{"Field \"signature\" expected array but got " + std::string(doof::json_type_name(_iterator_signature->second))}; }
    auto _field_signature = [&]() { const auto* _array = doof::json_as_array(_iterator_signature->second); auto _values = std::make_shared<std::vector<uint8_t>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(static_cast<uint8_t>(_lenient ? doof::json_as_int_lenient(_element) : doof::json_as_int(_element))); } return _values; }();
    return doof::Success<std::shared_ptr<Jwt>>{std::make_shared<Jwt>(_field_header, _field_claims, _field_signedContent, _field_signature)};
}
doof::Result<std::string, std::string> decodeBase64UrlToString(std::string text) {
    auto _binding_value_1 = ::doof_crypto::decode_base64_url(text);
    if (doof::is_failure(_binding_value_1)) {
        const auto& blob = _binding_value_1;
        return doof::Failure<std::string>{ std::string("Invalid Base64Url string") };
    }
    const auto blob = doof::success_value(_binding_value_1);
    const auto reader = ::doof_blob::NativeBlobReader::constructor(blob, ::std_::blob::types::Endian::LittleEndian);
    return doof::Success<std::string>{ reader->readString(reader->length()) };
}
std::shared_ptr<std::vector<uint8_t>> stringToBytes(std::string text) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian);
    builder->writeString(text);
    return builder->build();
}
doof::Result<std::shared_ptr<Jwt>, JwtError> parseJwt(std::string token) {
    const auto parts = doof::string_split(token, std::string("."));
    if (static_cast<int32_t>((parts)->size()) != 3) {
        return doof::Failure<JwtError>{ JwtError::MalformedToken };
    }
    auto _binding_value_2 = decodeBase64UrlToString((*parts)[0]);
    if (doof::is_failure(_binding_value_2)) {
        const auto& headerJson = _binding_value_2;
        return doof::Failure<JwtError>{ JwtError::InvalidHeader };
    }
    const auto headerJson = doof::success_value(_binding_value_2);
    auto _binding_value_3 = decodeBase64UrlToString((*parts)[1]);
    if (doof::is_failure(_binding_value_3)) {
        const auto& claimsJson = _binding_value_3;
        return doof::Failure<JwtError>{ JwtError::InvalidPayload };
    }
    const auto claimsJson = doof::success_value(_binding_value_3);
    auto _binding_value_4 = ::doof_json::parse(headerJson);
    if (doof::is_failure(_binding_value_4)) {
        const auto& headerJsonValue = _binding_value_4;
        return doof::Failure<JwtError>{ JwtError::InvalidHeader };
    }
    const auto headerJsonValue = doof::success_value(_binding_value_4);
    auto _binding_value_5 = ::doof_json::parse(claimsJson);
    if (doof::is_failure(_binding_value_5)) {
        const auto& claimsJsonValue = _binding_value_5;
        return doof::Failure<JwtError>{ JwtError::InvalidPayload };
    }
    const auto claimsJsonValue = doof::success_value(_binding_value_5);
    auto _binding_value_6 = ::doof_crypto::decode_base64_url((*parts)[2]);
    if (doof::is_failure(_binding_value_6)) {
        const auto& signature = _binding_value_6;
        return doof::Failure<JwtError>{ JwtError::InvalidPayload };
    }
    const auto signature = doof::success_value(_binding_value_6);
    auto _binding_value_7 = [&]() -> doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> { auto _as_value = headerJsonValue; if (doof::json_is_object(_as_value)) return doof::Success<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>>{doof::json_object(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_7)) {
        const auto& header = _binding_value_7;
        return doof::Failure<JwtError>{ JwtError::InvalidHeader };
    }
    const auto header = doof::success_value(_binding_value_7);
    auto _binding_value_8 = [&]() -> doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> { auto _as_value = claimsJsonValue; if (doof::json_is_object(_as_value)) return doof::Success<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>>{doof::json_object(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_8)) {
        const auto& claims = _binding_value_8;
        return doof::Failure<JwtError>{ JwtError::InvalidPayload };
    }
    const auto claims = doof::success_value(_binding_value_8);
    return doof::Success<std::shared_ptr<Jwt>>{ std::make_shared<Jwt>(header, claims, (((*parts)[0] + std::string(".")) + (*parts)[1]), signature) };
}
doof::Result<std::shared_ptr<Jwt>, JwtError> verifyJwtHs256(std::string token, std::shared_ptr<::doof_crypto::SecretBytes> key) {
    auto _binding_value_9 = parseJwt(token);
    if (doof::is_failure(_binding_value_9)) {
        const auto& jwt = _binding_value_9;
        return doof::Failure<JwtError>{ doof::failure_error(jwt) };
    }
    const auto jwt = doof::success_value(_binding_value_9);
    auto _binding_value_10 = [&]() -> doof::Result<std::string, std::string> { auto _as_source = doof::map_get(jwt->header, std::string("alg"), "", 0); if (doof::is_failure(_as_source)) return doof::Failure<std::string>{doof::failure_error(_as_source)}; return [&]() -> doof::Result<std::string, std::string> { auto _as_value = doof::success_value(_as_source); if (doof::json_is_string(_as_value)) return doof::Success<std::string>{doof::json_as_string(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }(); }();
    if (doof::is_failure(_binding_value_10)) {
        const auto& alg = _binding_value_10;
        return doof::Failure<JwtError>{ JwtError::AlgorithmMismatch };
    }
    const auto alg = doof::success_value(_binding_value_10);
    if (alg != std::string("HS256")) {
        return doof::Failure<JwtError>{ JwtError::AlgorithmMismatch };
    }
    const auto expectedSignature = ::doof_crypto::hmac_sha256(key, stringToBytes(jwt->signedContent));
    if (!::doof_crypto::timing_safe_equal(jwt->signature, expectedSignature)) {
        return doof::Failure<JwtError>{ JwtError::SignatureInvalid };
    }
    return doof::Success<std::shared_ptr<Jwt>>{ jwt };
}
std::shared_ptr<std::vector<uint8_t>> sha1(std::shared_ptr<std::vector<uint8_t>> data) {
    return ::doof_crypto::sha1_bytes(data);
}
std::string encodeHex(std::shared_ptr<std::vector<uint8_t>> data) {
    return ::doof_crypto::encode_hex(data);
}
std::shared_ptr<std::vector<uint8_t>> sha1String(std::string text) {
    return ::doof_crypto::sha1_utf8(text);
}
std::shared_ptr<std::vector<uint8_t>> sha256(std::shared_ptr<std::vector<uint8_t>> data) {
    return ::doof_crypto::sha256_bytes(data);
}
std::shared_ptr<std::vector<uint8_t>> sha256String(std::string text) {
    return ::doof_crypto::sha256_utf8(text);
}
std::shared_ptr<std::vector<uint8_t>> hmacSha256(std::shared_ptr<::doof_crypto::SecretBytes> key, std::shared_ptr<std::vector<uint8_t>> data) {
    return ::doof_crypto::hmac_sha256(key, data);
}
std::string encodeBase64Url(std::shared_ptr<std::vector<uint8_t>> data) {
    return ::doof_crypto::encode_base64_url(data);
}
doof::Result<std::shared_ptr<std::vector<uint8_t>>, std::string> decodeBase64Url(std::string text) {
    return ::doof_crypto::decode_base64_url(text);
}
bool timingSafeEqual(std::shared_ptr<std::vector<uint8_t>> a, std::shared_ptr<std::vector<uint8_t>> b) {
    return ::doof_crypto::timing_safe_equal(a, b);
}
doof::Result<std::shared_ptr<std::vector<uint8_t>>, std::string> decodeBase64(std::string text) {
    return ::doof_crypto::decode_base64(text);
}
}

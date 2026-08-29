#include "std_crypto_index.hpp"

namespace std_::crypto::index {
using namespace ::std_::json::index;
using namespace ::std_::blob::index;
std::string sha1Hex(const std::shared_ptr<std::vector<uint8_t>>& data) {
    return ::doof_crypto::encode_hex(::doof_crypto::sha1_bytes(data));
}
std::string sha1HexString(const std::string& text) {
    return ::doof_crypto::encode_hex(::doof_crypto::sha1_utf8(text));
}
std::string sha256Hex(const std::shared_ptr<std::vector<uint8_t>>& data) {
    return ::doof_crypto::encode_hex(::doof_crypto::sha256_bytes(data));
}
std::string sha256HexString(const std::string& text) {
    return ::doof_crypto::encode_hex(::doof_crypto::sha256_utf8(text));
}
std::string sha256Base64(const std::shared_ptr<std::vector<uint8_t>>& data) {
    return ::doof_crypto::encode_base64(::doof_crypto::sha256_bytes(data));
}
std::string sha256Base64String(const std::string& text) {
    return ::doof_crypto::encode_base64(::doof_crypto::sha256_utf8(text));
}
std::string sha256Base64Url(const std::shared_ptr<std::vector<uint8_t>>& data) {
    return ::doof_crypto::encode_base64_url(::doof_crypto::sha256_bytes(data));
}
std::string sha256Base64UrlString(const std::string& text) {
    return ::doof_crypto::encode_base64_url(::doof_crypto::sha256_utf8(text));
}
std::string hmacSha256Hex(const std::shared_ptr<::doof_crypto::SecretBytes>& key, const std::shared_ptr<std::vector<uint8_t>>& data) {
    return ::doof_crypto::encode_hex(::doof_crypto::hmac_sha256(key, data));
}
std::string hmacSha256Base64(const std::shared_ptr<::doof_crypto::SecretBytes>& key, const std::shared_ptr<std::vector<uint8_t>>& data) {
    return ::doof_crypto::encode_base64(::doof_crypto::hmac_sha256(key, data));
}
std::string hmacSha256Base64Url(const std::shared_ptr<::doof_crypto::SecretBytes>& key, const std::shared_ptr<std::vector<uint8_t>>& data) {
    return ::doof_crypto::encode_base64_url(::doof_crypto::hmac_sha256(key, data));
}
std::shared_ptr<std::vector<uint8_t>> hmacSha256String(const std::shared_ptr<::doof_crypto::SecretBytes>& key, const std::string& text) {
    return ::doof_crypto::hmac_sha256(key, stringToBytes(text));
}
std::string hmacSha256HexString(const std::shared_ptr<::doof_crypto::SecretBytes>& key, const std::string& text) {
    return ::doof_crypto::encode_hex(hmacSha256String(key, text));
}
std::string hmacSha256Base64String(const std::shared_ptr<::doof_crypto::SecretBytes>& key, const std::string& text) {
    return ::doof_crypto::encode_base64(hmacSha256String(key, text));
}
std::string hmacSha256Base64UrlString(const std::shared_ptr<::doof_crypto::SecretBytes>& key, const std::string& text) {
    return ::doof_crypto::encode_base64_url(hmacSha256String(key, text));
}
std::shared_ptr<::doof_crypto::SecretBytes> randomBytes(int32_t length) {
    return ::doof_crypto::SecretBytes::random(length);
}
std::string randomToken(int32_t byteLength) {
    return ::doof_crypto::encode_base64_url(randomBytes(byteLength)->bytes());
}

doof::Result<std::string, std::string> decodeBase64UrlToString(const std::string& text) {
    auto _binding_value_1 = ::doof_crypto::decode_base64_url(text);
    if (doof::is_failure(_binding_value_1)) {
        const auto& blob = _binding_value_1;
        return doof::Failure<std::string>{ std::string("Invalid Base64Url string") };
    }
    const auto blob = doof::success_value(_binding_value_1);
    const auto reader = ::doof_blob::NativeBlobReader::constructor(blob, ::std_::blob::types::Endian::LittleEndian);
    return doof::Success<std::string>{ reader->readString(reader->length()) };
}
std::shared_ptr<std::vector<uint8_t>> stringToBytes(const std::string& text) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian);
    builder->writeString(text);
    return builder->build();
}
doof::Result<std::shared_ptr<Jwt>, JwtError> parseJwt(const std::string& token) {
    const auto parts = doof::string_split(token, std::string("."));
    if (static_cast<int32_t>((parts)->size()) != 3) {
        return doof::Failure<JwtError>{ JwtError::MalformedToken };
    }
    auto _binding_value_2 = decodeBase64UrlToString(doof::array_at(parts, 0, "index", 89));
    if (doof::is_failure(_binding_value_2)) {
        const auto& headerJson = _binding_value_2;
        return doof::Failure<JwtError>{ JwtError::InvalidHeader };
    }
    const auto headerJson = doof::success_value(_binding_value_2);
    auto _binding_value_3 = decodeBase64UrlToString(doof::array_at(parts, 1, "index", 93));
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
    auto _binding_value_6 = ::doof_crypto::decode_base64_url(doof::array_at(parts, 2, "index", 104));
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
    return doof::Success<std::shared_ptr<Jwt>>{ std::make_shared<Jwt>(header, claims, ((doof::array_at(parts, 0, "index", 120) + std::string(".")) + doof::array_at(parts, 1, "index", 120)), signature) };
}
doof::Result<std::shared_ptr<Jwt>, JwtError> verifyJwtHs256(const std::string& token, const std::shared_ptr<::doof_crypto::SecretBytes>& key) {
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
}

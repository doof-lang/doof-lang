#include "std_crypto_index.hpp"

namespace std_::crypto::index {
using namespace ::std_::json::index;
using namespace ::std_::blob::index;
#line 14 "/std/crypto/index.do"
std::string sha1Hex(const std::shared_ptr<std::vector<uint8_t>>& data) {
    return ::doof_crypto::encode_hex(::doof_crypto::sha1_bytes(data));
}
#line 15 "/std/crypto/index.do"
std::string sha1HexString(const std::string& text) {
    return ::doof_crypto::encode_hex(::doof_crypto::sha1_utf8(text));
}
#line 19 "/std/crypto/index.do"
std::string sha256Hex(const std::shared_ptr<std::vector<uint8_t>>& data) {
    return ::doof_crypto::encode_hex(::doof_crypto::sha256_bytes(data));
}
#line 20 "/std/crypto/index.do"
std::string sha256HexString(const std::string& text) {
    return ::doof_crypto::encode_hex(::doof_crypto::sha256_utf8(text));
}
#line 21 "/std/crypto/index.do"
std::string sha256Base64(const std::shared_ptr<std::vector<uint8_t>>& data) {
    return ::doof_crypto::encode_base64(::doof_crypto::sha256_bytes(data));
}
#line 22 "/std/crypto/index.do"
std::string sha256Base64String(const std::string& text) {
    return ::doof_crypto::encode_base64(::doof_crypto::sha256_utf8(text));
}
#line 23 "/std/crypto/index.do"
std::string sha256Base64Url(const std::shared_ptr<std::vector<uint8_t>>& data) {
    return ::doof_crypto::encode_base64_url(::doof_crypto::sha256_bytes(data));
}
#line 24 "/std/crypto/index.do"
std::string sha256Base64UrlString(const std::string& text) {
    return ::doof_crypto::encode_base64_url(::doof_crypto::sha256_utf8(text));
}
#line 34 "/std/crypto/index.do"
std::string hmacSha256Hex(const std::shared_ptr<::doof_crypto::SecretBytes>& key, const std::shared_ptr<std::vector<uint8_t>>& data) {
    return ::doof_crypto::encode_hex(::doof_crypto::hmac_sha256(key, data));
}
#line 35 "/std/crypto/index.do"
std::string hmacSha256Base64(const std::shared_ptr<::doof_crypto::SecretBytes>& key, const std::shared_ptr<std::vector<uint8_t>>& data) {
    return ::doof_crypto::encode_base64(::doof_crypto::hmac_sha256(key, data));
}
#line 36 "/std/crypto/index.do"
std::string hmacSha256Base64Url(const std::shared_ptr<::doof_crypto::SecretBytes>& key, const std::shared_ptr<std::vector<uint8_t>>& data) {
    return ::doof_crypto::encode_base64_url(::doof_crypto::hmac_sha256(key, data));
}
#line 37 "/std/crypto/index.do"
std::shared_ptr<std::vector<uint8_t>> hmacSha256String(const std::shared_ptr<::doof_crypto::SecretBytes>& key, const std::string& text) {
    return ::doof_crypto::hmac_sha256(key, stringToBytes(text));
}
#line 38 "/std/crypto/index.do"
std::string hmacSha256HexString(const std::shared_ptr<::doof_crypto::SecretBytes>& key, const std::string& text) {
    return ::doof_crypto::encode_hex(hmacSha256String(key, text));
}
#line 39 "/std/crypto/index.do"
std::string hmacSha256Base64String(const std::shared_ptr<::doof_crypto::SecretBytes>& key, const std::string& text) {
    return ::doof_crypto::encode_base64(hmacSha256String(key, text));
}
#line 40 "/std/crypto/index.do"
std::string hmacSha256Base64UrlString(const std::shared_ptr<::doof_crypto::SecretBytes>& key, const std::string& text) {
    return ::doof_crypto::encode_base64_url(hmacSha256String(key, text));
}
#line 50 "/std/crypto/index.do"
std::shared_ptr<::doof_crypto::SecretBytes> randomBytes(int32_t length) {
    return ::doof_crypto::SecretBytes::random(length);
}
#line 51 "/std/crypto/index.do"
std::string randomToken(int32_t byteLength) {
    return ::doof_crypto::encode_base64_url(randomBytes(byteLength)->bytes());
}

#line 69 "/std/crypto/index.do"
doof::Result<std::string, std::string> decodeBase64UrlToString(const std::string& text) {
#line 70 "/std/crypto/index.do"
    auto _binding_value_1 = ::doof_crypto::decode_base64_url(text);
    if (doof::is_failure(_binding_value_1)) {
        const auto& blob = _binding_value_1;
#line 71 "/std/crypto/index.do"
        return doof::Failure<std::string>{ std::string("Invalid Base64Url string") };
    }
    const auto blob = doof::success_value(_binding_value_1);
#line 73 "/std/crypto/index.do"
    const auto reader = ::doof_blob::NativeBlobReader::constructor(blob, ::std_::blob::types::Endian::LittleEndian);
#line 74 "/std/crypto/index.do"
    return doof::Success<std::string>{ reader->readString(reader->length()) };
}
#line 77 "/std/crypto/index.do"
std::shared_ptr<std::vector<uint8_t>> stringToBytes(const std::string& text) {
#line 78 "/std/crypto/index.do"
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian);
#line 79 "/std/crypto/index.do"
    builder->writeString(text);
#line 80 "/std/crypto/index.do"
    return builder->build();
}
#line 83 "/std/crypto/index.do"
doof::Result<std::shared_ptr<Jwt>, JwtError> parseJwt(const std::string& token) {
#line 84 "/std/crypto/index.do"
    const auto parts = doof::string_split(token, std::string("."));
#line 85 "/std/crypto/index.do"
    if (static_cast<int32_t>((parts)->size()) != 3) {
#line 86 "/std/crypto/index.do"
        return doof::Failure<JwtError>{ JwtError::MalformedToken };
    }
#line 89 "/std/crypto/index.do"
    auto _binding_value_2 = decodeBase64UrlToString(doof::array_at(parts, 0, "index", 89));
    if (doof::is_failure(_binding_value_2)) {
        const auto& headerJson = _binding_value_2;
#line 90 "/std/crypto/index.do"
        return doof::Failure<JwtError>{ JwtError::InvalidHeader };
    }
    const auto headerJson = doof::success_value(_binding_value_2);
#line 93 "/std/crypto/index.do"
    auto _binding_value_3 = decodeBase64UrlToString(doof::array_at(parts, 1, "index", 93));
    if (doof::is_failure(_binding_value_3)) {
        const auto& claimsJson = _binding_value_3;
#line 94 "/std/crypto/index.do"
        return doof::Failure<JwtError>{ JwtError::InvalidPayload };
    }
    const auto claimsJson = doof::success_value(_binding_value_3);
#line 97 "/std/crypto/index.do"
    auto _binding_value_4 = ::doof_json::parse(headerJson);
    if (doof::is_failure(_binding_value_4)) {
        const auto& headerJsonValue = _binding_value_4;
#line 98 "/std/crypto/index.do"
        return doof::Failure<JwtError>{ JwtError::InvalidHeader };
    }
    const auto headerJsonValue = doof::success_value(_binding_value_4);
#line 101 "/std/crypto/index.do"
    auto _binding_value_5 = ::doof_json::parse(claimsJson);
    if (doof::is_failure(_binding_value_5)) {
        const auto& claimsJsonValue = _binding_value_5;
#line 102 "/std/crypto/index.do"
        return doof::Failure<JwtError>{ JwtError::InvalidPayload };
    }
    const auto claimsJsonValue = doof::success_value(_binding_value_5);
#line 104 "/std/crypto/index.do"
    auto _binding_value_6 = ::doof_crypto::decode_base64_url(doof::array_at(parts, 2, "index", 104));
    if (doof::is_failure(_binding_value_6)) {
        const auto& signature = _binding_value_6;
#line 105 "/std/crypto/index.do"
        return doof::Failure<JwtError>{ JwtError::InvalidPayload };
    }
    const auto signature = doof::success_value(_binding_value_6);
#line 108 "/std/crypto/index.do"
    auto _binding_value_7 = [&]() -> doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> { auto _as_value = headerJsonValue; if (doof::json_is_object(_as_value)) return doof::Success<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>>{doof::json_object(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_7)) {
        const auto& header = _binding_value_7;
#line 109 "/std/crypto/index.do"
        return doof::Failure<JwtError>{ JwtError::InvalidHeader };
    }
    const auto header = doof::success_value(_binding_value_7);
#line 112 "/std/crypto/index.do"
    auto _binding_value_8 = [&]() -> doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> { auto _as_value = claimsJsonValue; if (doof::json_is_object(_as_value)) return doof::Success<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>>{doof::json_object(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_8)) {
        const auto& claims = _binding_value_8;
#line 113 "/std/crypto/index.do"
        return doof::Failure<JwtError>{ JwtError::InvalidPayload };
    }
    const auto claims = doof::success_value(_binding_value_8);
#line 116 "/std/crypto/index.do"
    return doof::Success<std::shared_ptr<Jwt>>{ std::make_shared<Jwt>(header, claims, ((doof::array_at(parts, 0, "index", 120) + std::string(".")) + doof::array_at(parts, 1, "index", 120)), signature) };
}
#line 127 "/std/crypto/index.do"
doof::Result<std::shared_ptr<Jwt>, JwtError> verifyJwtHs256(const std::string& token, const std::shared_ptr<::doof_crypto::SecretBytes>& key) {
#line 128 "/std/crypto/index.do"
    auto _binding_value_9 = parseJwt(token);
    if (doof::is_failure(_binding_value_9)) {
        const auto& jwt = _binding_value_9;
#line 129 "/std/crypto/index.do"
        return doof::Failure<JwtError>{ doof::failure_error(jwt) };
    }
    const auto jwt = doof::success_value(_binding_value_9);
#line 132 "/std/crypto/index.do"
    auto _binding_value_10 = [&]() -> doof::Result<std::string, std::string> { auto _as_source = doof::map_get(jwt->header, std::string("alg"), "", 0); if (doof::is_failure(_as_source)) return doof::Failure<std::string>{doof::failure_error(_as_source)}; return [&]() -> doof::Result<std::string, std::string> { auto _as_value = doof::success_value(_as_source); if (doof::json_is_string(_as_value)) return doof::Success<std::string>{doof::json_as_string(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }(); }();
    if (doof::is_failure(_binding_value_10)) {
        const auto& alg = _binding_value_10;
#line 133 "/std/crypto/index.do"
        return doof::Failure<JwtError>{ JwtError::AlgorithmMismatch };
    }
    const auto alg = doof::success_value(_binding_value_10);
#line 135 "/std/crypto/index.do"
    if (alg != std::string("HS256")) {
#line 136 "/std/crypto/index.do"
        return doof::Failure<JwtError>{ JwtError::AlgorithmMismatch };
    }
#line 139 "/std/crypto/index.do"
    const auto expectedSignature = ::doof_crypto::hmac_sha256(key, stringToBytes(jwt->signedContent));
#line 140 "/std/crypto/index.do"
    if (!::doof_crypto::timing_safe_equal(jwt->signature, expectedSignature)) {
#line 141 "/std/crypto/index.do"
        return doof::Failure<JwtError>{ JwtError::SignatureInvalid };
    }
#line 144 "/std/crypto/index.do"
    return doof::Success<std::shared_ptr<Jwt>>{ jwt };
}
#line 1 "<doof-generated>"
std::shared_ptr<std::vector<uint8_t>> sha1(const std::shared_ptr<std::vector<uint8_t>>& data) {
    return ::doof_crypto::sha1_bytes(data);
}
std::string encodeHex(const std::shared_ptr<std::vector<uint8_t>>& data) {
    return ::doof_crypto::encode_hex(data);
}
std::shared_ptr<std::vector<uint8_t>> sha1String(const std::string& text) {
    return ::doof_crypto::sha1_utf8(text);
}
std::shared_ptr<std::vector<uint8_t>> sha256(const std::shared_ptr<std::vector<uint8_t>>& data) {
    return ::doof_crypto::sha256_bytes(data);
}
std::shared_ptr<std::vector<uint8_t>> sha256String(const std::string& text) {
    return ::doof_crypto::sha256_utf8(text);
}
std::string encodeBase64(const std::shared_ptr<std::vector<uint8_t>>& data) {
    return ::doof_crypto::encode_base64(data);
}
std::string encodeBase64Url(const std::shared_ptr<std::vector<uint8_t>>& data) {
    return ::doof_crypto::encode_base64_url(data);
}
std::shared_ptr<std::vector<uint8_t>> hmacSha256(const std::shared_ptr<::doof_crypto::SecretBytes>& key, const std::shared_ptr<std::vector<uint8_t>>& data) {
    return ::doof_crypto::hmac_sha256(key, data);
}
doof::Result<std::shared_ptr<std::vector<uint8_t>>, std::string> decodeBase64Url(const std::string& text) {
    return ::doof_crypto::decode_base64_url(text);
}
bool timingSafeEqual(const std::shared_ptr<std::vector<uint8_t>>& a, const std::shared_ptr<std::vector<uint8_t>>& b) {
    return ::doof_crypto::timing_safe_equal(a, b);
}
doof::Result<std::shared_ptr<std::vector<uint8_t>>, std::string> decodeBase64(const std::string& text) {
    return ::doof_crypto::decode_base64(text);
}
}

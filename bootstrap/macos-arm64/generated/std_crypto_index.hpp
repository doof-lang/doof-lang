#pragma once
#include "doof_runtime.hpp"
#include <cstdint>
#include <cmath>
#include <functional>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <variant>
#include <vector>
namespace std_::blob::index { struct BlobBuilder; }
namespace std_::blob::index { struct BlobReader; }
namespace std_::blob::types { enum class EncodingError; }
namespace std_::blob::types { enum class Endian; }
namespace std_::blob::types { enum class TextEncoding; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace std_::crypto::index {
    struct Jwt;
}

#include "std_json_index.hpp"
#include "std_blob_index.hpp"

namespace doof_crypto { using ::doof_json::parse; }
namespace doof_crypto { using EncodingError = ::std_::blob::types::EncodingError; }
namespace doof_crypto { using Endian = ::std_::blob::types::Endian; }
namespace doof_crypto { using TextEncoding = ::std_::blob::types::TextEncoding; }
#include "doof_crypto.hpp"

namespace std_::crypto::index {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    enum class JwtError {
    MalformedToken,
    InvalidHeader,
    InvalidPayload,
    AlgorithmMismatch,
    SignatureInvalid
};
inline const char* JwtError_name(JwtError value) {
  switch (value) {
    case JwtError::MalformedToken: return "MalformedToken";
    case JwtError::InvalidHeader: return "InvalidHeader";
    case JwtError::InvalidPayload: return "InvalidPayload";
    case JwtError::AlgorithmMismatch: return "AlgorithmMismatch";
    case JwtError::SignatureInvalid: return "SignatureInvalid";
  }
  return "";
}
inline std::optional<JwtError> JwtError_fromName(std::string_view value) {
  if (value == "MalformedToken") return JwtError::MalformedToken;
  if (value == "InvalidHeader") return JwtError::InvalidHeader;
  if (value == "InvalidPayload") return JwtError::InvalidPayload;
  if (value == "AlgorithmMismatch") return JwtError::AlgorithmMismatch;
  if (value == "SignatureInvalid") return JwtError::SignatureInvalid;
  return std::nullopt;
}
inline std::optional<JwtError> JwtError_fromValue(int32_t value) {
  switch (static_cast<JwtError>(value)) {
    case JwtError::MalformedToken: return JwtError::MalformedToken;
    case JwtError::InvalidHeader: return JwtError::InvalidHeader;
    case JwtError::InvalidPayload: return JwtError::InvalidPayload;
    case JwtError::AlgorithmMismatch: return JwtError::AlgorithmMismatch;
    case JwtError::SignatureInvalid: return JwtError::SignatureInvalid;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, JwtError value) { return output << JwtError_name(value); }
    std::shared_ptr<std::vector<uint8_t>> sha1(std::shared_ptr<std::vector<uint8_t>> data);
    std::string encodeHex(std::shared_ptr<std::vector<uint8_t>> data);
    std::shared_ptr<std::vector<uint8_t>> sha1String(std::string text);
    std::shared_ptr<std::vector<uint8_t>> sha256(std::shared_ptr<std::vector<uint8_t>> data);
    std::shared_ptr<std::vector<uint8_t>> sha256String(std::string text);
    std::shared_ptr<std::vector<uint8_t>> hmacSha256(std::shared_ptr<::doof_crypto::SecretBytes> key, std::shared_ptr<std::vector<uint8_t>> data);
    std::string encodeBase64Url(std::shared_ptr<std::vector<uint8_t>> data);
    doof::Result<std::shared_ptr<std::vector<uint8_t>>, std::string> decodeBase64Url(std::string text);
    bool timingSafeEqual(std::shared_ptr<std::vector<uint8_t>> a, std::shared_ptr<std::vector<uint8_t>> b);
    doof::Result<std::shared_ptr<std::vector<uint8_t>>, std::string> decodeBase64(std::string text);
    struct Jwt : public std::enable_shared_from_this<Jwt> {
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> header;
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> claims;
    std::string signedContent;
    std::shared_ptr<std::vector<uint8_t>> signature;
    Jwt(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> header, std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> claims, std::string signedContent, std::shared_ptr<std::vector<uint8_t>> signature) : header(header), claims(claims), signedContent(signedContent), signature(signature) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<Jwt>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::string sha1Hex(std::shared_ptr<std::vector<uint8_t>> data);
    std::string sha1HexString(std::string text);
    std::string sha256Hex(std::shared_ptr<std::vector<uint8_t>> data);
    std::string sha256HexString(std::string text);
    std::string hmacSha256Hex(std::shared_ptr<::doof_crypto::SecretBytes> key, std::shared_ptr<std::vector<uint8_t>> data);
    std::string hmacSha256Base64Url(std::shared_ptr<::doof_crypto::SecretBytes> key, std::shared_ptr<std::vector<uint8_t>> data);
    std::shared_ptr<::doof_crypto::SecretBytes> randomBytes(int32_t length);
    doof::Result<std::string, std::string> decodeBase64UrlToString(std::string text);
    std::shared_ptr<std::vector<uint8_t>> stringToBytes(std::string text);
    doof::Result<std::shared_ptr<Jwt>, JwtError> parseJwt(std::string token);
    doof::Result<std::shared_ptr<Jwt>, JwtError> verifyJwtHs256(std::string token, std::shared_ptr<::doof_crypto::SecretBytes> key);
}

namespace std_::crypto::index {
}

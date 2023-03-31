#include "rz_crypt.h"

namespace rz_crypt {
std::string test() { return ("crypt: Hello World"); }

/**
 * @brief sha256(const std::string str)
 *
 *  @details encrypt the given string with SHA2-256Bit
 *
 * @param str
 * e.g.: It's nice 2 be a price, but it's higher 2 be a bayer?
 *
 * @return str
 * e.g.: 2b9f6eaf2bea188d6cdd2267b9da7ed7f4451b9e6e5ec62560078d870adbbf34
 */
std::string sha256(const std::string str) {
  unsigned char hash[SHA256_DIGEST_LENGTH];

  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, str.c_str(), str.size());
  SHA256_Final(hash, &sha256);

  std::stringstream ss;

  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    ss << std::hex << std::setw(2) << std::setfill('0')
       << static_cast<int>(hash[i]);
  }
  return ss.str();
}

} // namespace rz_crypt

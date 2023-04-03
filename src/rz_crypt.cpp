#include "rz_crypt.h"

namespace rz_crypt {
std::string test() { return ("crypt: Hello World"); }

std::string to_hex(unsigned char s) {
  std::stringstream ss;
  ss << std::hex << (int)s;
  return ss.str();
}

std::string sha256(std::string line) {
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, line.c_str(), line.length());
  SHA256_Final(hash, &sha256);

  std::string output = "";
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    output += to_hex(hash[i]);
  }
  return output;
}

} // namespace rz_crypt

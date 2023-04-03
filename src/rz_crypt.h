#pragma once

#include <filesystem>
#include <string>

#include <sstream>

/* MacOS
#include "/opt/homebrew/opt/openssl@3.1/include/openssl/sha.h"
*/

/* Linux */
#include <openssl/evp.h>
#include <openssl/sha.h>

#include <iomanip>
#include <sstream>

namespace rz_crypt {
namespace fs = std::filesystem;
std::string test();
std::string sha256(const std::string str);
} // namespace rz_crypt

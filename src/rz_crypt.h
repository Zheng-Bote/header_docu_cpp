#pragma once

#include <string>
#include <filesystem>

#include <iomanip>
#include <sstream>
#include "/opt/homebrew/opt/openssl@3.1/include/openssl/sha.h"

namespace rz_crypt {
    namespace fs = std::filesystem;
    std::string test();
    std::string sha256(const std::string str);
}



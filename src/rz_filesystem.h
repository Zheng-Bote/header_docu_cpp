#pragma once

#include <ctime>
#include <filesystem>
#include <iostream>
#include <string>

namespace rz_filesystem {
std::string test();
std::string makeDir(std::string targetDir);
std::string makeDir(std::string mainDir, std::string childDir);
bool existDir(std::string dir);
std::string dirTree(std::string dir);
std::string listDirContent(std::string dir);
} // namespace rz_filesystem

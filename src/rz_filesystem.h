#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <ctime>

namespace rz_filesystem {
    std::string test();
    std::string makeDir(std::string mainDir, std::string childDir);
    bool existDir(std::string dir);
    std::string dirTree(std::string dir);
    std::string listDirContent(std::string dir);
}

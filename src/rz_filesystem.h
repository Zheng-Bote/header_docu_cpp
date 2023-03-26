#pragma once

#include <string>
#include <filesystem>
#include <ctime>

namespace rz_filesystem {
    std::string test();
    std::string makeDir(std::string mainDir, std::string childDir);
    bool existDir(std::string dir);
    std::string filePerm(std::string pathToFile);
    std::string lastWriteTime(std::string pathToFile);
    std::string dirTree(std::string dir);
    std::string fileSize(std::string pathToFile);
    std::string fileExt(std::string pathToFile);
}



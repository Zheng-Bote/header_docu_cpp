#include "rz_filesystem.h"

namespace rz_filesystem{
namespace fs = std::filesystem;

std::string test() {
    return ("rz_filesystem: Hello World");
}

/**
 * @brief makeDir
 *
 * @details create a directory
 *
 * @param mainDir
 * base path where to create the new directory
 * mainDir  (e.g.: /Volumes/500G/DEV/Header_Docu)
 *
 * @param childDir
 * directory to create
 * childDir (e.g.: Temp)
 *
 * @return std::string
 * returns std::string:
 *
 * std::string   (e.g.: /Volumes/500G/DEV/Header_Docu/Temp allready exists)
 * directory allready exists
 *
 * std::string   (e.g.: /Volumes/500G/DEV/Header_Docu/Temp)
 * directory successfully created
 *
 * std::string   (e.g.: Permission denied)
 * system error message
 */
std::string makeDir(std::string mainDir, std::string childDir) {
    std::string targetDir {mainDir};
    targetDir.append("/" + childDir);

    if(! fs::create_directory(targetDir)) {
        return(targetDir + " allready exist");
    }
    try {
         targetDir = fs::canonical(targetDir);
    }
    catch (const std::exception& e) {
        return(e.what());
    }

    return(targetDir);
}

/**
 * @brief checks if a directory exists
 *
 * @param dir
 * dir  (e.g.: /Volumes/500G/DEV/Header_Docu/Temp)
 *
 * @return true
 * directory exists
 *
 * @return false
 * directory doesn't exists
 */
bool existDir(std::string dir) {
    if(! fs::exists(dir)) {
        return false;
    }
    else {
        return true;
    }
}

/**
 * @brief list directory and subs as tree
 *
 * @param dir
 * std::string dir  (e.g.: /Volumes/500G/DEV/Header_Docu/Temp)
 *
 * @return std::string
 *
 * /Users/zb_bamboo/Downloads/cxxopts-3.1.1
 * |-- packaging
 * |  |-- pkgconfig.pc.in
 * |  |-- cxxopts-config.cmake.in
 * |-- cxxopts-config-version.cmake
 */
std::string dirTree(std::string dir) {
    std::string dirTree = dir + "\n";
    std::filesystem::path start(dir);
    std::filesystem::recursive_directory_iterator di(start), end;

    while(di != end) {
        for(int i = 0; i < di.depth(); ++i) {
            dirTree.append(" | ");
        }
        dirTree.append(" |-- " + di->path().filename().string() + "\n");
        ++di;
    }
    return(dirTree);
}

/**
 * @brief listDirContent(std::string verz)
 *
 * @details list directories and content
 *
 * @param verz
 *
 * @return std::string
 */
std::string listDirContent(std::string dir) {
    std::string dirTree = dir + "\n";
    std::string temp {};

    try {
        fs::path pfad(dir);
        fs::directory_iterator di(pfad), ende;
        while(di != ende) {
            auto p = di->path();
            temp = p.filename();
            dirTree.append(temp + "\t");
            if(fs::is_directory(p)) {
                dirTree.append(" (Directory)\n");
            }
            else {
                temp = std::to_string(fs::file_size(p));
                dirTree.append(temp + " Bytes\t");
                temp = p.extension();
                dirTree.append("\tExtension: " + temp + "\n");
                temp = fs::canonical(p);
                dirTree.append("\tPath: " + temp + "\n");
            }
            ++di;
        }
    }
    catch (const std::exception& e) {
        dirTree.append("Display Dir " + dir + " failed:\n" + e.what() + "\n");
    }
    return(dirTree);
}


/* the end*/
}

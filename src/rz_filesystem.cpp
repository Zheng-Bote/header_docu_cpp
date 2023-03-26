#include "rz_filesystem.h"

namespace rz_filesystem{
namespace fs = std::filesystem;

std::string test() {
    return ("rz_filesystem: Hello World");
}

/**
 * @brief create a directory
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

std::string filePerms(std::filesystem::perms pathToFile)
{
    using std::filesystem::perms;
    std::string ergeb;
    auto show = [=](char op, perms perm)
    {
        char erg = (perms::none == (perm & pathToFile) ? '-' : op);
        return erg;
    };
    ergeb = show('r', perms::owner_read);
    ergeb += show('w', perms::owner_write);
    ergeb += show('x', perms::owner_exec);
    ergeb += " ";
    ergeb += show('r', perms::group_read);
    ergeb += show('w', perms::group_write);
    ergeb += show('x', perms::group_exec);
    ergeb += " ";
    ergeb += show('r', perms::others_read);
    ergeb += show('w', perms::others_write);
    ergeb += show('x', perms::others_exec);
    
    return(ergeb);
}
/**
 * @brief get the folder|file permissions
 * 
 * @param pathToFile 
 * @param pathToFolder
 * pathToFile   (e.g.: /Volumes/500G/DEV/Header_Docu/Temp/test.txt)
 * pathToFolder (e.g.: /Volumes/500G/DEV/Header_Docu/Temp)
 * 
 * @return std::string
 * std::string  (e.g.: rwx r-x r-x) 
 */
std::string filePerm(std::string pathToFile) {
    return(filePerms(fs::status(pathToFile).permissions()));
}

const std::string wDateTime(std::time_t fileTime) {
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&fileTime);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

    return buf;
}
/**
 * @brief last modification time
 * 
 * @param pathToFile
 * @param pathToFolder 
 * pathToFile   (e.g.: /Volumes/500G/DEV/Header_Docu/Temp/test.txt)
 * pathToFolder (e.g.: /Volumes/500G/DEV/Header_Docu/Temp)
 * 
 * @return std::string 
 * std::string  (e.g.: 2023-03-24 18:18:45)
 */
std::string lastWriteTime(std::string pathToFile) {
    const auto fileTime = std::filesystem::last_write_time(pathToFile);
    std::time_t cftime = decltype(fileTime)::clock::to_time_t(fileTime); 
    return(wDateTime(cftime));
}

/**
 * @brief file size in Bytes
 * 
 * @param pathToFile
 * pathToFile   (e.g.: /Volumes/500G/DEV/Header_Docu/Temp/test.txt)
 * 
 * @return std::string 
 * std::string bytes    (e.g.: 2996)
 */
std::string fileSize(std::string pathToFile) {
    const auto fileSize = fs::file_size(pathToFile);
    return(std::to_string(fileSize));
}

/**
 * @brief file extension
 * 
 * @param pathToFile
 * pathToFile   (e.g.: /Volumes/500G/DEV/Header_Docu/Temp/test.txt)
 * 
 * @return std::string 
 * std::string  (e.g.: .txt)
 */
std::string fileExt(std::string pathToFile) {
    return(fs::path(pathToFile).extension());
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

}

#pragma once

#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>

#include <regex>
#include <map>
#include <algorithm>

namespace rz_files {
    namespace fs = std::filesystem;
    std::string test();
    std::string fileSize(std::string pathToFile);
    std::string fileExt(std::string pathToFile);
    std::string filePerm(std::string pathToFile);
    std::string lastWriteTime(std::string pathToFile);
    std::string readFile(std::string pathToFile);

    std::string& ltrim(std::string &s);
    std::string& rtrim(std::string &s);
    std::string& trim(std::string &s);
    char* rz_strToChar(std::string str);
    void displayText(std::map<std::string,std::string> &mapKeys);
    void displayText(std::map<std::string,std::string> &mapKeys);
    void displayJson(std::map<std::string,std::string> &mapKeys);
    void writeJson(std::map<std::string,std::string> &mapKeys);
    void writeCsv(std::map<std::string,std::string> &mapKeys);
    void writeAsciiDoc(std::map<std::string,std::string> &mapKeys);
    void writeGithubMd(std::map<std::string,std::string> &mapKeys);
}

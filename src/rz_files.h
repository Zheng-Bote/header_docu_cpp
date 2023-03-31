#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include <algorithm>
#include <map>
#include <regex>

#include "rz_crypt.h"
#include "rz_datetime.h"

namespace rz_files {
namespace fs = std::filesystem;
std::string test();
std::string fileSize(std::string pathToFile);
std::string fileExt(std::string pathToFile);
std::string filePerm(std::string pathToFile);
std::string lastWriteTime(std::string pathToFile);
std::string *readFile(std::string pathToFile);
void clearMapVals(std::map<std::string, std::string> &mapKeys);
void parseFileToMapKey(std::map<std::string, std::string> &mapKeys,
                       std::string pathToFile);

std::string &ltrim(std::string &s);
std::string &rtrim(std::string &s);
std::string &trim(std::string &s);
std::string rmLastNewline(std::string s);
char *rz_strToChar(std::string str);

void displayText(std::map<std::string, std::string> &mapKeys);
void displayJson(std::map<std::string, std::string> &mapKeys);
void writeJson(std::map<std::string, std::string> &mapKeys,
               std::string &pathToFile);
void writeCsv(std::map<std::string, std::string> &mapKeys,
              std::string &pathToFile);
void writeAsciiDocTable(std::map<std::string, std::string> &mapKeys,
                        std::string &pathToFile);
void writeAsciiDoc(std::map<std::string, std::string> &mapKeys,
                   std::string &pathToFile);
void writeGithubMd(std::map<std::string, std::string> &mapKeys,
                   std::string &pathToFile);
void writeHtmlHeader(std::string &pathToFile);
void writeHtmlCss(std::string &pathToFile);
void writeHtml(std::map<std::string, std::string> &mapKeys,
               std::string &pathToFile);
void writeHtmlEnd(std::string &pathToFile);
int parseDirContent(std::map<std::string, std::string> &mapKeys,
                    std::string searchDir, std::string searchFileExt,
                    std::string outFile, std::string outFormat,
                    std::map<std::string, int> &mapExt);
int parseDirRek(std::map<std::string, std::string> &mapKeys,
                std::string searchDir, std::string searchFileExt,
                std::string outFile, std::string outFormat,
                std::map<std::string, int> &mapExt, std::string outputDir);
} // namespace rz_files

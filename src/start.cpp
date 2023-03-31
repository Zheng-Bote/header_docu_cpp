/*
TITLE:
    start.cpp
BRIEF:
    header_docu_cpp (main.cpp)
VERSION:
    1.3.0
DESC:
    header_docu_cpp is a small nafty C++ commandline tool to read the first
comment block of a textfile and outputs it as HTML5- or markdown- snippet
    DEPENDENCIES:
        cxxopts
        a lightweight C++ option parser library, supporting the standard GNU
style syntax for options. https://github.com/jarro2783/cxxopts License: gpl2
Author:
    ZHENG Robert
COPYRIGHT:
    ZHENG Robert
SOURCE:
    https://github.com/Zheng-Bote/header_docu
Comment:
    keinen
SYNTAX:
    header_docu -h | header_docu --help

    -d, --dir arg     parse directory (default: .)
    -e, --ext arg     file extension (default: .h)
    -f, --file arg    1 single textfile: path/file
    -o, --out arg     output type: md | html | json | csv | adoc(default: html)
    -t, --target arg  target output dir (default: ./header_docu_cpp/)
    -h, --help        Print usage
    -v, --version     Version
EXAMPLES:
    /usr/local/bin/header_docu --dir . --ext h --out md // read/parse all *.h
files in the current directory /usr/local/bin/header_docu --file
~/DEV/CPP/header_docu/main.cpp --out html // read/parse single file and output
as HTML5 snippet
RETURN:
output.md | output.html void

HISTORY:
Version | Date      | Developer        | Comments
--------|-----------|------------------|---------------------------------------------------------------
0.3.0   |2023-03-24 | RZheng           | created
*/

/*******************************************************/

#include <cxxopts.hpp>
#include <iostream>

#include "rz_crypt.h"
#include "rz_datetime.h"
#include "rz_files.h"
#include "rz_filesystem.h"

const std::string VERSION = "0.3.0";

int main(int argc, char *argv[]) {

  cxxopts::Options options("header_parser", "parse header and output as docu");

  options.add_options()("d,dir", "parse directory",
                        cxxopts::value<std::string>()->default_value("."))(
      "e,ext", "file extension",
      cxxopts::value<std::string>()->default_value(".h"))(
      "f,file", "1 single textfile: path/file", cxxopts::value<std::string>())(
      "o,out", "output type: md | html | json | csv | adoc",
      cxxopts::value<std::string>()->default_value("html"))(
      "s,single", "single output files: yes | no",
      cxxopts::value<std::string>()->default_value("yes"))(
      "t,target", "target output dir",
      cxxopts::value<std::string>()->default_value("./header_docu_cpp/"))(
      "h,help", "Print usage")("v,version", "Version");

  auto result = options.parse(argc, argv);

  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    exit(0);
  }
  if (result.count("version")) {
    std::cout << argv[0] << "-" << VERSION << std::endl;
    exit(0);
  }

  std::string targetDir{"."}, searchForExt{".h"}, singleFile{},
      outputDir{"./header_docu_cpp"}, outFile{"header_docu_cpp"},
      outFormat{"html"}, dtString{};

  bool singleFiles = true;
  int countedFiles{0};

  /*
      std::string newDir = rz_filesystem::makeDir(".", "_SBOM_");
      std::cout << "newDir: " << newDir << "\n";

      if(rz_filesystem::existDir(newDir)) {
          std::cout << newDir << " exist\n";
      }
      else {
          std::cout << newDir << " doesn't exist\n";
      }

      std::string erg =
     rz_files::filePerm("/Users/zb_bamboo/Downloads/cxxopts-3.1.1"); std::cout
     << "Perm: " << erg << "\n";

      erg = rz_files::lastWriteTime("/Users/zb_bamboo/Downloads/cxxopts-3.1.1");
      std::cout << "LastWriteTime: " << erg << "\n";

      std::string erg =
     rz_filesystem::dirTree("/Users/zb_bamboo/Downloads/cxxopts-3.1.1");
      std::cout << erg << "\n";

      std::string erg =
     rz_file::fileSize("/Users/zb_bamboo/Downloads/cxxopts-3.1.1/CMakeLists.txt");
      std::cout << erg << "\n";

      std::string erg =
     rz_files::fileExt("/Users/zb_bamboo/Downloads/cxxopts-3.1.1/CMakeLists.txt");
      std::cout << erg << "\n";

  std::cout << "filecontent: " << rz_files::readFile("./bin/start") << "\n";
  std::cout << "SHA256: "
            << rz_crypt::sha256(
                   "/Users/zb_bamboo/Downloads/cxxopts-3.1.1/CMakeLists.txt")
            << std::endl;
  std::cout << "SHA256:\n"
            << rz_crypt::sha256(rz_files::readFile("./Makefile")) << "\n";

  std::cout << "listdir:\n\n" << rz_filesystem::listDirContent(".") << "\n";

  std::string *erg = rz_files::readFile("./bin/start");
  std::cout << "pointer content:\n" << *erg << "\n";

  std::map<std::string, std::string> mapKeys = {
      {"DESC", ""},    {"TITLE", ""},     {"AUTHOR", ""}, {"LICENSE", ""},
      {"VERSION", ""}, {"COPYRIGHT", ""}, {"SOURCE", ""}, {"COMMENT", ""}};
  std::string inFile = "/Volumes/500GB/Dev/Header_Docu01/main.cpp";
  std::string outFile = "./out.html";
  rz_files::parseFileToMapKey(mapKeys, inFile);
  mapKeys["SHA256"] = rz_crypt::sha256(inFile);
  mapKeys["SIZE"] = rz_files::fileSize(inFile);
  mapKeys["LModified"] = rz_files::lastWriteTime(inFile);

  rz_files::writeHtmlHeader(outFile);
  rz_files::writeHtmlCss(outFile);
  rz_files::writeHtml(mapKeys, outFile);
  rz_files::writeHtmlEnd(outFile);
*/

  std::map<std::string, std::string> mapKeys = {
      {"DESC", ""},    {"TITLE", ""},     {"AUTHOR", ""},       {"LICENSE", ""},
      {"VERSION", ""}, {"COPYRIGHT", ""}, {"SOURCE", ""},       {"COMMENT", ""},
      {"SYNTAX", ""},  {"HISTORY", ""},   {"DEPENDENCIES", ""}, {"BRIEF", ""}};

  std::map<std::string, int> mapExt = {
      {"gmd", 1}, {"html", 2}, {"json", 3}, {"csv", 4}, {"adoc", 5}};

  if (result.count("dir")) {
    targetDir = result["dir"].as<std::string>();
  }
  if (result.count("ext")) {
    searchForExt = result["ext"].as<std::string>();
  }
  if (result.count("file")) {
    singleFile = result["file"].as<std::string>();
    std::cout << "file: " << singleFile << "\n";
    rz_files::parseFileToMapKey(mapKeys, singleFile);
    std::string temp = mapKeys["TITLE"];
    std::cout << "single: " << temp << "\n";
    mapKeys["SHA256"] = rz_crypt::sha256(singleFile);
    mapKeys["SIZE"] = rz_files::fileSize(singleFile);
    mapKeys["LAST_MODIFIED"] = rz_files::lastWriteTime(singleFile);
    countedFiles = 1;
  }
  if (result.count("out")) {
    outFormat = result["out"].as<std::string>();
  }
  if (result.count("target")) {
    outputDir = result["target"].as<std::string>();
  }
  if (result["single"].as<std::string>().compare("yes") == 0) {
    singleFiles = true;
  } else {
    singleFiles = false;
  }

  if (!rz_filesystem::existDir(outputDir)) {
    rz_filesystem::makeDir(outputDir);
  }
  if (!rz_filesystem::existDir(outputDir)) {
    std::cout << rz_filesystem::makeDir(outputDir) << "\n";
    exit(1);
  }
  dtString = rz_datetime::currentDateTime("");
  outFile = outputDir + "/" + dtString + "_" + outFile + "." + outFormat;

  if (result.count("file")) {
    switch (mapExt[outFormat]) {
    case 1: {
      rz_files::writeGithubMd(mapKeys, outFile);
      break;
    }
    case 2: {
      rz_files::writeHtmlHeader(outFile);
      rz_files::writeHtmlCss(outFile);
      rz_files::writeHtml(mapKeys, outFile);
      rz_files::writeHtmlEnd(outFile);
      break;
    }
    case 3: {
      rz_files::writeJson(mapKeys, outFile);
      break;
    }
    case 4: {
      rz_files::writeCsv(mapKeys, outFile);
      break;
    }
    case 5: {
      rz_files::writeAsciiDoc(mapKeys, outFile);
      break;
    }

    default:
      break;
    }
  } else if (singleFiles == false) {
    switch (mapExt[outFormat]) {
    case 2: {
      rz_files::writeHtmlHeader(outFile);
      rz_files::writeHtmlCss(outFile);
      countedFiles = rz_files::parseDirContent(mapKeys, targetDir, searchForExt,
                                               outFile, outFormat, mapExt);
      rz_files::writeHtmlEnd(outFile);
      break;
    }

    default: {
      countedFiles = rz_files::parseDirContent(mapKeys, targetDir, searchForExt,
                                               outFile, outFormat, mapExt);
    } break;
    }
  } else if (singleFiles) {
    countedFiles = rz_files::parseDirRek(mapKeys, targetDir, searchForExt,
                                         outFile, outFormat, mapExt, outputDir);
    outFile = outputDir;
  }

  std::cout << "\nFiles parsed: " << countedFiles << "\n";
  std::cout << "output:\n" << outFile << "\n";
  /*#################*/
  exit(0);
}

#include "rz_files.h"

namespace rz_files {
namespace fs = std::filesystem;
using namespace std::chrono_literals;

std::string test() { return ("files: Hello World"); }

std::string filePerms(std::filesystem::perms pathToFile) {
  using std::filesystem::perms;
  std::string ergeb;
  auto show = [=](char op, perms perm) {
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

  return (ergeb);
}
/**
 * @brief filePerm(std::string pathToFile)
 *
 * @details get the folder|file permissions
 *
 * @param pathToFile
 * or
 * @param pathToFolder
 * e.g.: /Volumes/500G/DEV/Header_Docu/Temp/test.txt
 * e.g.: /Volumes/500G/DEV/Header_Docu/Temp
 *
 * @return std::string
 * e.g.: rwx r-x r-x
 */
std::string filePerm(std::string pathToFile) {
  return (filePerms(fs::status(pathToFile).permissions()));
}

const std::string wDateTime(std::time_t fileTime) {
  struct tm tstruct;
  char buf[80];
  tstruct = *localtime(&fileTime);
  // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
  // for more information about date/time format
  strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

  return buf;
}
/**
 * @brief lastWriteTime(std::string pathToFile)
 *
 * @details last modification time
 *
 * @param pathToFile
 * @param pathToFolder
 * e.g.: /Volumes/500G/DEV/Header_Docu/Temp/test.txt
 * e.g.: /Volumes/500G/DEV/Header_Docu/Temp
 *
 * @return std::string
 * e.g.: 2023-03-24 18:18:45
 */
std::string lastWriteTime(std::string pathToFile) {
  auto ftime = fs::last_write_time(pathToFile);
  auto cftime = std::chrono::system_clock::to_time_t(
      std::chrono::file_clock::to_sys(ftime));

  return (wDateTime(cftime));
}

/**
 * @brief fileSize(std::string pathToFile)
 *
 * @details filesize in Bytes
 *
 * @param pathToFile
 * e.g.: /Volumes/500G/DEV/Header_Docu/Temp/test.txt
 *
 * @return std::string
 * e.g.: 2996
 */
std::string fileSize(std::string pathToFile) {
  const auto fileSize = fs::file_size(pathToFile);
  return (std::to_string(fileSize));
}

/**
 * @brief fileExt(std::string pathToFile)
 *
 * @details file extension
 *
 * @param pathToFile
 * e.g.: /Volumes/500G/DEV/Header_Docu/Temp/test.txt
 *
 * @return std::string
 * e.g.: .txt
 */
std::string fileExt(std::string pathToFile) {
  return (fs::path(pathToFile).extension());
}

/**
 * @brief std::string *readFile(std::string pathToFile)
 *
 * @details reads a file
 *
 * @param pathToFile
 *
 * @return *string
 */
std::string *readFile(std::string pathToFile) {
  std::ifstream ifs;
  std::string fileLine{};
  static std::string fileContent{};

  ifs.open(pathToFile, std::ios::in);

  if (ifs.is_open()) {
    while (!ifs.eof()) {
      ifs >> fileLine;
      fileContent.append(fileLine);
    }
    ifs.close();
  } else {
    // std:: cout << "Unable to open file to read" << std::endl;
  }
  return (&fileContent);
}

void parseFileToMapKey(std::map<std::string, std::string> &mapKeys,
                       std::string pathToFile) {
  std::ifstream ifs;
  std::string str;
  bool commentStart = true;
  std::string key;

  ifs.open(pathToFile, std::ios::in);

  if (ifs) {
    while (!ifs.eof()) {
      std::getline(ifs, str);
      if (std::regex_match(str, std::regex("\\/\\*")) && commentStart == true) {
        commentStart = false;
      }

      char *line = rz_strToChar(str);
      std::regex re("([A-Z]+):([ A-Z]*)", std::regex::icase);
      std::cmatch m;

      if (std::regex_match(line, m, re)) {
        str = m[1];
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        key.clear();
        key.append(trim(str));
        continue;
      }
      if (!std::regex_match(line, m, re)) {
        if (mapKeys.contains(key)) {
          mapKeys[key].append(trim(str));
          mapKeys[key].append("\n");
        }
      }

      if (std::regex_match(str, std::regex("\\*\\/"))) {
        break;
      }
    }
    ifs.close();
  } else {
    std::cout << "Unable to open file to read" << std::endl;
  }
}

/*####################################################*/

/**
 * @brief rmLastNewline(std::string s)
 *
 * @details remove Carriage Return / Line Feed
 *
 * @param s
 *
 * @return String
 */
std::string rmLastNewline(std::string s) {
  s = std::regex_replace(s, std::regex("\\r\\n|\\r|\\n"), "");
  return s;
}

/**
 * @brief ltrim(std::string &s)
 *
 * @details trims left site of a given string
 *
 * @param s
 * @return std::string&
 */
std::string &ltrim(std::string &s) {
  auto it = std::find_if(s.begin(), s.end(), [](char c) {
    return !std::isspace<char>(c, std::locale::classic());
  });
  s.erase(s.begin(), it);
  return s;
}

/**
 * @brief rtrim(std::string &s)
 *
 * @details trims the right site of a given string
 *
 * @param s
 * @return std::string&
 */
std::string &rtrim(std::string &s) {
  auto it = std::find_if(s.rbegin(), s.rend(), [](char c) {
    return !std::isspace<char>(c, std::locale::classic());
  });
  s.erase(it.base(), s.end());
  return s;
}

/**
 * @brief trim(std::string &s)
 *
 * @details trims right and left site of a given string
 *
 * @param s
 * @return std::string&
 */
std::string &trim(std::string &s) { return ltrim(rtrim(s)); }

/**
 * @brief rz_strToChar(std::string str)
 *
 * @details convert string to char
 *
 * @param str
 * @return char
 */
char *rz_strToChar(std::string str) {
  int len = str.length() + 1;
  char *buf = new char[len];
  strcpy(buf, str.c_str());
  return buf;
}

/**
 * @brief displayText(std::map<std::string,std::string> &mapKeys)
 *
 * @details prints text
 *
 * @param mapKeys
 */
void displayText(std::map<std::string, std::string> &mapKeys) {
  for (auto const &[key, val] : mapKeys) {
    if (val.length() > 0) {
      std::cout << key << ":" << val << std::endl;
    }
  }
}

/**
 * @brief displayJson(std::map<std::string,std::string> &mapKeys)
 *
 * @details prints JSon
 *
 * @param mapKeys
 */
void displayJson(std::map<std::string, std::string> &mapKeys) {
  int counter = 0;
  int mapSize = mapKeys.size();
  std::cout << "{" << std::endl;
  for (auto const &[key, val] : mapKeys) {
    counter++;
    std::cout << "\"" << key << "\": \"" << val << "\"";
    if (counter < mapSize) {
      std::cout << "," << std::endl;
    } else {
      std::cout << "\n";
    }
  }
  std::cout << "}" << std::endl;
}

/**
 * @brief writeJson(std::map<std::string,std::string> &mapKeys,std::string
 * &pathToFile)
 *
 * @details write JSon to file
 *
 * @param mapKeys, pathToFile
 */
void writeJson(std::map<std::string, std::string> &mapKeys,
               std::string &pathToFile) {
  int counter = 0;
  std::string s{};
  int mapSize = mapKeys.size();
  std::ofstream ofs;

  ofs.open(pathToFile, std::ios::app);

  if (ofs) {
    ofs << "{";
    for (auto const &[key, val] : mapKeys) {
      counter++;
      s = rz_files::rmLastNewline(val);
      ofs << "\"" << key << "\": \"" << s << "\"";
      if (counter < mapSize) {
        ofs << ",";
      }
    }
    ofs << "}";
    ofs.close();
  }
}

/**
 * @brief clearMapVals(std::map<std::string, std::string> &mapKeys)
 *
 * @details clears all map values″
 *
 * @param mapKeys
 */
void clearMapVals(std::map<std::string, std::string> &mapKeys) {
  for (auto const &[key, val] : mapKeys) {
    mapKeys[key] = "";
  }
  mapKeys = {{"DESC", ""},     {"TITLE", ""},        {"AUTHOR", ""},
             {"LICENSE", ""},  {"VERSION", ""},      {"COPYRIGHT", ""},
             {"SOURCE", ""},   {"COMMENT", ""},      {"SYNTAX", ""},
             {"HISTORY", ""},  {"DEPENDENCIES", ""}, {"BRIEF", ""},
             {"FILE_PERM", ""}};
}

/**
 * @brief writeCsv(std::map<std::string,std::string> &mapKeys,std::string
 * &pathToFile)
 *
 * @details write text to csv
 *
 * @param mapKeys, pathToFile
 */
void writeCsv(std::map<std::string, std::string> &mapKeys,
              std::string &pathToFile) {
  int counter = 0;
  int mapSize = mapKeys.size();
  std::ofstream ofs;
  std::string s{};

  ofs.open(pathToFile, std::ios::app);

  if (ofs) {
    for (auto const &[key, val] : mapKeys) {
      counter++;
      ofs << key;
      if (counter < mapSize) {
        ofs << ";";
      }
    }
    ofs << "\n";
    counter = 0;
    for (auto const &[key, val] : mapKeys) {
      counter++;
      s = rz_files::rmLastNewline(val);
      ofs << s;
      if (counter < mapSize) {
        ofs << ";";
      }
    }
    ofs << "\n";
    ofs.close();
  }
}

/**
 * @brief writeAsciiDoc(std::map<std::string,std::string> &mapKeys,
              std::string &pathToFile)
 *
 * @details write text as table to ASCIIdoc
 *
 * @param mapKeys, pathToFile
 */
void writeAsciiDocTable(std::map<std::string, std::string> &mapKeys,
                        std::string &pathToFile) {
  int counter = 0;
  int mapSize = mapKeys.size();
  std::ofstream ofs;

  ofs.open(pathToFile, std::ios::app);

  if (ofs) {
    ofs << "[%autowidth]\n|===\n|";
    for (auto const &[key, val] : mapKeys) {
      counter++;
      ofs << key;
      if (counter < mapSize) {
        ofs << "|";
      }
    }
    ofs << "\n\n";
    counter = 0;
    for (auto const &[key, val] : mapKeys) {
      counter++;
      ofs << "|" << val;
      if (counter < mapSize) {
        ofs << "\n";
      }
    }
    ofs << "\n|===\n";
    ofs.close();
  }
}

/**
 * @brief writeAsciiDoc(std::map<std::string, std::string> &mapKeys,std::string
 * &pathToFile)
 *
 * @param mapKeys
 * @param pathToFile
 */
void writeAsciiDoc(std::map<std::string, std::string> &mapKeys,
                   std::string &pathToFile) {
  int counter = 0;
  std::ofstream ofs;

  ofs.open(pathToFile, std::ios::app);

  if (ofs) {
    ofs << "= " + mapKeys["TITLE"] + "\n\n";
    counter = 0;
    for (auto const &[key, val] : mapKeys) {
      counter++;
      ofs << "*" << key << "* : " << val << "\n\n";
    }
    ofs << "\n\n\n";
    ofs.close();
  }
}

/**
 * @brief writeGithubMd(std::map<std::string,std::string> &mapKeys,
              std::string &pathToFile)
 *
 * @details write text to Github markdown
 *
 * @param mapKeys, pathToFile
 */
void writeGithubMd(std::map<std::string, std::string> &mapKeys,
                   std::string &pathToFile) {
  std::ofstream ofs;

  ofs.open(pathToFile, std::ios::app);

  if (ofs) {
    ofs << "- - -"
        << "\n";
    ofs << "## TITLE: " << mapKeys["TITLE"] << "\n";
    if (!mapKeys["VERSION"].empty()) {
      ofs << "### VERSION: " << mapKeys["VERSION"] << "\n";
    }

    for (auto const &[key, val] : mapKeys) {
      if (!mapKeys[key].empty()) {
        ofs << "### " << key << ":\n" << val << "\n";
      }
    }
    ofs << "\n";
    ofs.close();
  }
}

void writeHtmlHeader(std::string &pathToFile) {
  std::string html{};
  std::ofstream ofs;

  ofs.open(pathToFile, std::ios::out);

  if (ofs) {

    html = R"(<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="author" content="header_docu_cpp">
    <title>header_docu_cpp</title>)";
    ofs << html << "\n";
    ofs.close();
  }
}

void writeHtmlEnd(std::string &pathToFile) {
  std::ofstream ofs;

  ofs.open(pathToFile, std::ios::app);

  if (ofs) {
    ofs << "</article>\n</body>\n</html>";
  }
}

void writeHtmlCss(std::string &pathToFile) {
  std::string html{};
  std::ofstream ofs;

  ofs.open(pathToFile, std::ios::app);

  if (ofs) {

    html = R"(
    <style>
*, *:before, *:after {
    box-sizing: border-box;
    margin: 0;
    padding: 0;
}

html {
  font-family: 'Inter', -apple-system, BlinkMacSystemFont, Roboto, Ubuntu, 'Segeo UI', 'Helvetica Neue', Arial, sans-serif;
	font-size: 16px;
  color: rgba(9, 19, 60, 1);
}

body {
  }
section {
    margin: 5px;
    border: 1px solid lightgrey;
    border-radius: 5px;
    padding: 5px;
    /* width: 100%;*/
}
h1 {}
h1, .title, .head {
    background-color: grey;
    color: white;
}
.content {
    background-color: lightgrey;
}
h1, .head, .content {
    padding: 5px;
}
table {
    width: 100%
}

    </style>
</head>
<body id="body">
  <article>)";

    ofs << html << "\n";
    ofs.close();
  }
}
/**
 * @brief writeHtml(std::map<std::string, std::string> &mapKeys, std::string *
 * &pathToFile) {
 *
 * @param mapKeys
 * @param pathToFile
 */
void writeHtml(std::map<std::string, std::string> &mapKeys,
               std::string &pathToFile) {
  std::string html{};
  std::ofstream ofs;

  ofs.open(pathToFile, std::ios::app);

  if (ofs) {
    ofs << "<section>\n<h1>" << mapKeys["TITLE"] << "</h1>\n";
    ofs << "<table>"
        << "\n";
    for (auto const &[key, val] : mapKeys) {
      ofs << "<tr><td class=\"head\">" << key << "</td><td class=\"content\">"
          << val << "</td></tr>\n";
    }
    ofs << "</table>\n</section>\n<p align=\"right\">(<a href=\"#body\">back "
           "to "
           "top</a>)</p>\n";
    ofs.close();
  }
}

/**
 * @brief parseDirContent(std::map<std::string, std::string> &mapKeys,
                    std::string searchDir, std::string searchFileExt,
                    std::string outFile, std::string outFormat,
                    std::map<std::string, int> &mapExt)
 *
 * @details parse all files with specific extension in a given dir and save the
 parsed header in one file
 *
 * @param mapKeys
 * @param searchDir
 * @param searchFileExt
 * @param outFile
 * @param outFormat
 * @param mapExt
 * @return amount of parsed files
 */
int parseDirContent(std::map<std::string, std::string> &mapKeys,
                    std::string searchDir, std::string searchFileExt,
                    std::string outFile, std::string outFormat,
                    std::map<std::string, int> &mapExt) {
  int count{0};
  try {
    fs::path pfad(searchDir);
    fs::directory_iterator di(pfad), ende;
    while (di != ende) {
      auto p = di->path();
      if (!fs::is_directory(p)) {
        if (searchFileExt.compare(p.extension()) == 0) {

          count++;
          clearMapVals(mapKeys);
          // std::cout << count << " found " << p.extension() << "\n";
          std::string pathFile = fs::canonical(p);
          parseFileToMapKey(mapKeys, pathFile);
          mapKeys["SHA256"] = rz_crypt::sha256(pathFile);
          mapKeys["SIZE"] = fileSize(pathFile);
          mapKeys["LAST_MODIFIED"] = lastWriteTime(pathFile);
          mapKeys["FILE_PERM"] = filePerm(pathFile);
          if (mapKeys["TITLE"].empty()) {
            mapKeys["TITLE"] = p.filename();
          }
          if (mapKeys["AUTHOR"].empty()) {
            mapKeys["AUTHOR"] = "ZHENG Robert";
          }
          switch (mapExt[outFormat]) {
          case 1: {
            rz_files::writeGithubMd(mapKeys, outFile);
            break;
          }
          case 2: {
            rz_files::writeHtml(mapKeys, outFile);
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
        }
      }
      ++di;
    }
  } catch (const std::exception &e) {
    std::cout << "Display Dir " + searchDir + " failed:\n" + e.what() + "\n";
  }
  return (count);
}

/**
 * @brief parseDirRek(std::map<std::string, std::string> &mapKeys,
                std::string searchDir, std::string searchFileExt,
                std::string outFile, std::string outFormat,
                std::map<std::string, int> &mapExt, std::string outputDir)
 *
 * @details parse all files with specific extension in a given dir and save the
 parsed header in separated files
 *
 * @param mapKeys
 * @param searchDir
 * @param searchFileExt
 * @param outFile
 * @param outFormat
 * @param mapExt
 * @param outputDir
 * @return amount of parsed files
 */
int parseDirRek(std::map<std::string, std::string> &mapKeys,
                std::string searchDir, std::string searchFileExt,
                std::string outFile, std::string outFormat,
                std::map<std::string, int> &mapExt, std::string outputDir) {
  int count{0};

  try {
    fs::path pfad(searchDir);
    fs::directory_iterator di(pfad), ende;
    while (di != ende) {
      auto p = di->path();
      std::string currentDir{};
      if (fs::is_directory(p)) {
        // std::cout << "\n##### Directory: " << p.filename() << " #####\n";
      }
      if (!fs::is_directory(p)) {
        if (searchFileExt.compare(p.extension()) == 0) {

          std::string dtString = rz_datetime::currentDateTime("");
          std::string outFile = p.filename();
          outFile =
              outputDir + "/" + dtString + "__" + outFile + "__." + outFormat;

          count++;
          clearMapVals(mapKeys);
          std::string pathFile = fs::canonical(p);
          parseFileToMapKey(mapKeys, pathFile);
          mapKeys["SHA256"] = rz_crypt::sha256(pathFile);
          mapKeys["SIZE"] = fileSize(pathFile);
          mapKeys["LAST_MODIFIED"] = lastWriteTime(pathFile);
          mapKeys["FILE_PERM"] = filePerm(pathFile);
          if (mapKeys["TITLE"].empty()) {
            mapKeys["TITLE"] = p.filename();
          }
          if (mapKeys["AUTHOR"].empty()) {
            mapKeys["AUTHOR"] = "ZHENG Robert";
          }
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
        }
      }
      ++di;
    }
  } catch (const std::exception &e) {
    std::cout << "Display Dir " + searchDir + " failed:\n" + e.what() + "\n";
  }
  return (count);
}

/*####################################################*/

} // namespace rz_files

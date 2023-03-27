#include "rz_files.h"


namespace rz_files{
std::string test() {
    return ("files: Hello World");
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
    const auto fileTime = std::filesystem::last_write_time(pathToFile);
    std::time_t cftime = decltype(fileTime)::clock::to_time_t(fileTime);
    return(wDateTime(cftime));
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
    return(std::to_string(fileSize));
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
    return(fs::path(pathToFile).extension());
}

std::string readFile(std::string pathToFile) {
    std::ifstream ifs;
    std::string fileLine {};
    std::string fileContent {};

    ifs.open( pathToFile, std::ios::in );

    if(ifs.is_open())
    {
        while ( !ifs.eof() ) {
            ifs >> fileLine;
            fileContent.append(fileLine);
        }
        ifs.close();
    }
    else {
        //std:: cout << "Unable to open file to read" << std::endl;
    }
    return(fileContent);
}

/*####################################################*/

/**
 * @brief ltrim(std::string &s)
 *
 * @details trims left site of a given string
 *
 * @param s
 * @return std::string&
 */
std::string& ltrim(std::string &s)
{
    auto it = std::find_if(s.begin(), s.end(),
                    [](char c) {
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
std::string& rtrim(std::string &s)
{
    auto it = std::find_if(s.rbegin(), s.rend(),
                    [](char c) {
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
std::string& trim(std::string &s) {
    return ltrim(rtrim(s));
}

/**
 * @brief rz_strToChar(std::string str)
 *
 * @details convert string to char
 *
 * @param str
 * @return char
 */
char* rz_strToChar(std::string str)
{
  int len = str.length() + 1;
  char* buf = new char[len];
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
void displayText(std::map<std::string,std::string> &mapKeys) {
    for (auto const& [key, val] : mapKeys) {
        if(val.length() > 0) {
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
void displayJson(std::map<std::string,std::string> &mapKeys) {
    int counter = 0;
    int mapSize = mapKeys.size();
    std::cout << "{" << std::endl;
    for(auto const& [key, val] : mapKeys) {
        counter++;
        std::cout << "\"" << key << "\": \"" << val << "\"";
        if(counter < mapSize) {
            std::cout << "," << std::endl;
        }
        else {
            std::cout << "\n";
        }
    }
    std::cout << "}" << std::endl;
}

/**
 * @brief writeJson(std::map<std::string,std::string> &mapKeys)
 *
 * @details write JSon to file
 *
 * @param mapKeys
 */
void writeJson(std::map<std::string,std::string> &mapKeys) {
    int counter = 0;
    int mapSize = mapKeys.size();
    std::ofstream ofs;

    ofs.open( "./my_stream_test.json", std::ios::out );

    if(ofs)
    {
        ofs << "{";
        for(auto const& [key, val] : mapKeys) {
            counter++;
            ofs << "\"" << key << "\": \"" << val << "\"";
            if(counter < mapSize) {
                ofs << ",";
            }
        }
        ofs << "}";
        ofs.close();
    }
}

/**
 * @brief writeCsv(std::map<std::string,std::string> &mapKeys)
 *
 * @details write text to csv
 *
 * @param mapKeys
 */
void writeCsv(std::map<std::string,std::string> &mapKeys) {
    int counter = 0;
    int mapSize = mapKeys.size();
    std::ofstream ofs;

    ofs.open( "./my_stream_test.csv", std::ios::out );

    if(ofs)
    {
        for(auto const& [key, val] : mapKeys) {
            counter++;
            ofs << key;
            if(counter < mapSize) {
                ofs << ";";
            }
        }
        ofs << "\n";
        counter = 0;
        for(auto const& [key, val] : mapKeys) {
            counter++;
            ofs << val;
            if(counter < mapSize) {
                ofs << ";";
            }
        }
        ofs.close();
    }
}

/**
 * @brief writeAsciiDoc(std::map<std::string,std::string> &mapKeys)
 *
 * @details write text to ASCIIdoc
 *
 * @param mapKeys
 */
void writeAsciiDoc(std::map<std::string,std::string> &mapKeys) {
    int counter = 0;
    int mapSize = mapKeys.size();
    std::ofstream ofs;

    ofs.open( "./my_stream_test.adoc", std::ios::out );

    if(ofs)
    {
        ofs << "[%autowidth]\n|===\n|";
        for(auto const& [key, val] : mapKeys) {
            counter++;
            ofs << key;
            if(counter < mapSize) {
                ofs << "|";
            }
        }
        ofs << "\n\n";
        counter = 0;
        for(auto const& [key, val] : mapKeys) {
            counter++;
            ofs << "|" << val;
            if(counter < mapSize) {
                ofs << "\n";
            }
        }
        ofs << "\n|===\n";
        ofs.close();
    }
}

/**
 * @brief writeGithubMd(std::map<std::string,std::string> &mapKeys)
 *
 * @details write text to Github markdown
 *
 * @param mapKeys
 */
void writeGithubMd(std::map<std::string,std::string> &mapKeys) {
    int counter = 0;
    int mapSize = mapKeys.size();
    std::ofstream ofs;

    ofs.open( "./my_stream_test.md", std::ios::out );

    if(ofs)
    {
        ofs << "## TITLE: " << mapKeys["TITLE"] << "\n";
        ofs << "### VERSION: " << mapKeys["VERSION"] << "\n";

        for(auto const& [key, val] : mapKeys) {
            if(key.compare("TITLE") != 0 || key.compare("VERSION") != 0) {
                if(key.compare("DESC") == 0 || key.compare("BRIEF") == 0 || key.compare("SOURCE") == 0) {
                    ofs << "### " << key << ":\n" << val << "\n";
                }
                else {
                    ofs << "### " << key << ": " << val << "\n";
                }
            }
        }
        ofs << "\n";
        ofs.close();
    }
}
/*####################################################*/

}

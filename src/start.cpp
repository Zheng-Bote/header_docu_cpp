#include <iostream>

#include "rz_files.h"
#include "rz_datetime.h"
#include "rz_filesystem.h"
#include "rz_crypt.h"

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout << "call: " << argv[0] << " dirname\n";
        std::cout << rz_files::test() << "\n";
        std::cout << rz_datetime::test() << "\n";
        std::cout << rz_filesystem::test() << "\n";
        std::cout << rz_crypt::test() << "\n";
        exit(0);
    }

/*
    std::string newDir = rz_filesystem::makeDir(".", "_SBOM_");
    std::cout << "newDir: " << newDir << "\n";

    if(rz_filesystem::existDir(newDir)) {
        std::cout << newDir << " exist\n";
    }
    else {
        std::cout << newDir << " doesn't exist\n";
    }

    std::string erg = rz_files::filePerm("/Users/zb_bamboo/Downloads/cxxopts-3.1.1");
    std::cout << "Perm: " << erg << "\n";

    erg = rz_files::lastWriteTime("/Users/zb_bamboo/Downloads/cxxopts-3.1.1");
    std::cout << "LastWriteTime: " << erg << "\n";

    std::string erg = rz_filesystem::dirTree("/Users/zb_bamboo/Downloads/cxxopts-3.1.1");
    std::cout << erg << "\n";

    std::string erg = rz_file::fileSize("/Users/zb_bamboo/Downloads/cxxopts-3.1.1/CMakeLists.txt");
    std::cout << erg << "\n";

    std::string erg = rz_files::fileExt("/Users/zb_bamboo/Downloads/cxxopts-3.1.1/CMakeLists.txt");
    std::cout << erg << "\n";

    std::cout << "filecontent: " << rz_files::readFile("./bin/start") << "\n";
    std::cout << "SHA256: " << rz_crypt::sha256("/Users/zb_bamboo/Downloads/cxxopts-3.1.1/CMakeLists.txt") << std::endl;
    std::cout << "SHA256:\n" << rz_crypt::sha256(rz_files::readFile("./Makefile")) << "\n";
*/

    std::cout << "listdir:\n\n" << rz_filesystem::listDirContent(".") << "\n";

    exit(0);
}

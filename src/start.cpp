#include <iostream>

#include "rz_dirfiles.h"
#include "rz_datetime.h"
#include "rz_filesystem.h"

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout << "call: " << argv[0] << " dirname\n";
        std::cout << dirfiles::test() << "\n";
        std::cout << rz_datetime::test() << "\n";
        std::cout << rz_filesystem::test() << "\n";
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

    std::string erg = rz_filesystem::filePerm("/Users/zb_bamboo/Downloads/cxxopts-3.1.1");
    std::cout << "Perm: " << erg << "\n";

    erg = rz_filesystem::lastWriteTime("/Users/zb_bamboo/Downloads/cxxopts-3.1.1");
    std::cout << "LastWriteTime: " << erg << "\n";

    std::string erg = rz_filesystem::dirTree("/Users/zb_bamboo/Downloads/cxxopts-3.1.1");
    std::cout << erg << "\n";

    std::string erg = rz_filesystem::fileSize("/Users/zb_bamboo/Downloads/cxxopts-3.1.1/CMakeLists.txt");
    std::cout << erg << "\n";
*/
    std::string erg = rz_filesystem::fileExt("/Users/zb_bamboo/Downloads/cxxopts-3.1.1/CMakeLists.txt");
    std::cout << erg << "\n";

    exit(0);
}

<div id="top"></div>
<br />
<div align="center">
<h3 align="center">header_docu_cpp</h3>

  <p align="center">
      Create documentation from file header
      <br/>
      (focussed on older libraries which didn't use the docs-as-code approach)
    <br />
    <br />
    <a href="https://github.com/Zheng-Bote/header_docu_cpp/issues">Report Bug</a>
    ·
    <a href="https://github.com/Zheng-Bote/header_docu_cpp/issues">Request Feature</a>
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->

### Create documentation from file header (e.g. \*.c[pp], \*.h[pp], ...)

With great respect to Doxygen, JSDoc or DoxDox, but they all reading / parsing the complete textfile.

**For me I just need parsing the first comment block of a single textfile or every textfile with a defined file-extension in a folder, doesn't matter if \*.js, \*.h, \*.hpp or whatever**

_scanned / collected Meta data:_

-   TITLE
-   BRIEF
-   DESC
-   AUTHOR
-   LICENSE
-   VERSION
-   COPYRIGHT
-   SOURCE
-   COMMENT
-   SYNTAX
-   HISTORY
-   DEPENDENCIES
-   FILE_PERM       (file permssions)
-   LAST_MODIFIED   (file last modified)
-   SIZE            (file size in bytes)
-   SHA256          (SHA2-256 filehash)

So, this tool is focussed on older libraries which doesn't use the docs-as-code approach.

### built with

This is yet another version of the commandline tool, written in plain C++20.

There's another version, written in QT5 with C++17 : <a href="https://github.com/Zheng-Bote/header_docu" alt="header_docu QT" title="https://github.com/Zheng-Bote/header_docu">header_docu QT5 C++17</a>

### docs-as-code approach:

see:

-   <a href="https://docs-as-co.de/" alt="docs-as-code" title="https://docs-as-co.de/">docs-as-code</a>
-   <a href="https://doctoolchain.org/docToolchain" alt="docToolchain" title="https://doctoolchain.org/docToolchain">docToolchain (user site)</a>
-   <a href="https://github.com/doctoolchain/doctoolchain/" alt="docToolchain dev" title="https://github.com/doctoolchain/doctoolchain/">docToolchain (Github)</a>

<!-- GETTING STARTED -->

## Getting Started

### Prerequisites

-   PC or Laptop with Windows, MacOS or Linux \*\_^
-   installed C++ compiler like g++ or clang++ with C++20 support
-   developer tools with make

#### DEPENDENCIES:

_cxxopts_

a lightweight C++ option parser library, supporting the standard GNU style syntax for options.
https://github.com/jarro2783/cxxopts

_OpenSSL_

OpenSSL (Library tested: OpenSSL 3.0.2 15 Mar 2022; Linux: openssl-dev) is needed for creating SHA2-256Bit Hashes for strings and files.

### Installation

1. Clone the repo
    ```sh
    git clone https://github.com/Zheng-Bote/header_docu_cpp/.git
    ```
2. install
    - not yet implemented

<p align="right">(<a href="#top">back to top</a>)</p>

### configuration and build

#### MacOS

1. rename Makefile_macos to Makefile
2. rename src/rz_files.h_macos to src/rz_files.h
3. rename src/rz_files.cpp_macos to src/rz_files.cpp
4. rename src/rz_crypto.h_macos to src/rz_crypto.h
5. rename src/rz_crypto.cpp_macos to src/rz_crypto.cpp

#### Linux

1. due to main target, nothing special


### all OS

4. configure the Makefile to your environment
    - g++ or clang++
    - configure the Makefile var FLAGS to DEBUG_FLAGS or RELEASE_FLAGS
5. build
    - within the main dir of the project, execute on the commandline `make`

*hint:*

In case of linker error, check the syntaxt and change in-/output file _BEFORE_ the Include (-I) and Lib (-L).

_Example with g++_

`g++ -std=c++20 -o bin/start obj/start.o obj/rz_files.o obj/rz_datetime.o obj/rz_filesystem.o obj/rz_crypt.o -I/usr/include/openssl/ -L/usr/lib/ssl -lcrypto -g3 -O0 -Wall -Wextra -Wpedantic -Wshadow -Wconversion
`

_see also:_ ```do_build.sh``` (for Linux g++) 


<p align="right">(<a href="#top">back to top</a>)</p>

## Usage

### SYNTAX:

```
header_docu_cpp -h | header_docu_cpp --help

    -d, --dir arg     parse directory (default: .)

    -e, --ext arg     file extension (default: .h)

    -f, --file arg    1 single textfile: path/file

    -o, --out arg     output type: md | html | json | csv | adoc (default: 
                    html)

    -s, --single arg  single output files: yes | no (default: yes)

    -t, --target arg  target output dir (default: ./header_docu_cpp/)

    -h, --help        Print usage

    -v, --version     Version
```

#### EXAMPLES:

```
/usr/local/bin/header_docu_cpp --dir /volume2/Dev/Cpp/header_docu --ext .h --out md --single yes --target /volume2/Dev/Cpp/header_docu/wiki

bin/header_docu_cpp -d /volume2/Dev/Cpp/header_docu -e .h -o md -s yes -t /volume2/Dev/Cpp/header_docu/wiki

// read/parse all \*.h files in the given directory and store the results in one Github markdown file in the wiki-subfolder
```

```
/usr/local/bin/header_docu_cpp --file ~/DEV/CPP/header_docu/main.cpp --out html
// read/parse single file and output as HTML5
```

*default:*
```
/usr/local/bin/header_docu_cpp -d . -e .h -o json -s yes -t ./header_docu_cpp
```

### RETURN:

     2023-04-03 18:22:57 : 5 .cpp Files in folder ./src found. Output stored with format md in folder ./header_docu_cpp
     
     exit(0)

### HISTORY:

> | Version | Date       | Developer | Comments                           |
> | ------- | ---------- | --------- | ---------------------------------- |
> | 0.1.0   | 2023-03-25 | RZheng    | created                            |
> | 0.2.0   | 2023-03-31 | RZheng    | file permission added              |
> | 0.2.0   | 2023-03-31 | RZheng    | SHA2-256 filehash added            |
> | 0.3.0   | 2023-04-02 | RZheng    | separated to MacOS                 |
> | 0.4.0   | 2023-04-02 | RZheng    | Linux threads added to multiple file output |
> | 0.5.0   | 2023-04-06 | RZheng    | Linux threads removed (SBOM topic) |

<!-- ROADMAP -->

## Roadmap:

-   [x] quick and dirty commandline parser (see QT5 C++17)

-   [x] migrate QT commandline to vanilla cxx (this one, C++20 ongoing)

-   [x] create optional md file[s]

-   [x] create optional Github md file[s]

-   [x] create optional ASCIIdoc (adoc) file[s]

-   [x] create optional JSON file[s]

-   [x] create optional csv file[s]

-   [x] create optional HTML5 file[s]

-   [x] get SHA2-256 filehash

-   [x] file last modified time

-   [x] file permissions

-   [x] save output results in separared file[s] or in one file

-   [ ] performance improvements for single outfiles (threaded)

-   [ ] create optional SBOM (spdx) json file[s]

-   [ ] upload optional SBOM (spdx) json to RDBMS

-   [ ] build Linux and Windows desktop app with QT

-   [ ] build Windows desktop app with C#

-   [ ] make support for installation

-   [ ] CMake support for compilation and installation

Maybe a Kanban board will be established (soon)

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- CONTRIBUTING -->

## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- LICENSE -->

## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- CONTACT -->

## Contact

ZHENG Robert Zhèng Bó Tè 郑 伯特

Project Link: [https://github.com/Zheng-Bote/https://github.com/Zheng-Bote/header_docu_cpp/](https://github.com/Zheng-Bote/header_docu_cpp/)

:vulcan_salute:

<p align="right">(<a href="#top">back to top</a>)</p>

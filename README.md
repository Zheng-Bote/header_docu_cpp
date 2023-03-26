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

## About The Project

### Create documentation from file header (e.g. \*.c[pp], \*.h[pp], ...)

With great respect to Doxygen, JSDoc or DoxDox, but they all reading / parsing the complete textfile.

**For me I just need parsing the first comment block of a single textfile or every textfile with a defined file-extension in a folder, doesn't matter if \*.js, \*.h, \*.hpp or whatever**

_scanned / collected Meta data:_

-   TITLE
-   VERSION
-   AUTHOR
-   LICENSE
-   BRIEF
-   DESC
-   Last Modified
-   SHA256 filehash

So, this tool is focussed on older libraries which doesn't use the docs-as-code approach.

### docs-as-code approach:

see:

-   <a href="https://docs-as-co.de/" alt="docs-as-code" title="https://docs-as-co.de/">docs-as-code</a>
-   <a href="https://doctoolchain.org/docToolchain" alt="docToolchain" title="https://doctoolchain.org/docToolchain">docToolchain (user site)</a>
-   <a href="https://github.com/doctoolchain/doctoolchain/" alt="docToolchain dev" title="https://github.com/doctoolchain/doctoolchain/">docToolchain (Github)</a>

**Comment**

This is yet another version of the commandline tool, written in plain C++20
There's another version, written in QT5 with C++17 : <a href="https://github.com/Zheng-Bote/header_docu" alt="header_docu QT" title="https://github.com/Zheng-Bote/header_docu">header_docu QT5 C++17</a>

<!-- GETTING STARTED -->

## Getting Started

### Prerequisites

-   PC or Laptop with Windows, MacOS or Linux \*\_^
-   installed C++ compiler like gnu++ or clang++ with C++20 support
-   developer tools with make

_DEPENDENCIES:_
cxxopts
a lightweight C++ option parser library, supporting the standard GNU style syntax for options.
https://github.com/jarro2783/cxxopts

### Installation

1. Clone the repo
    ```sh
    git clone https://github.com/Zheng-Bote/https://github.com/Zheng-Bote/header_docu_cpp/.git
    ```
2. install
    - not yet implemented

<p align="right">(<a href="#top">back to top</a>)</p>

### configuration

1. configure the Makefile to your environment
    - gnu++ or clang++
    - configure the Makefile var FLAGS to DEBUG_FLAGS or RELEASE_FLAGS
2. build
    - within the main dir of the project, execute on the commandline `make`

the recommended way to use the libraries would be to install the additional <a href="https://github.com/Zheng-Bote/ESP32_libs" alt="ESP32_libs" title="https://github.com/Zheng-Bote/ESP32_libs">ESP32_libs</a>

and replace

old:

```
#include "myESP32lib.h"
```

new:

```
#include <ESP32_libs/myESP32lib.h>
```

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- ROADMAP -->

## Roadmap:

-   [x] quick and dirty commandline parser (see QT5 C++17)

-   [x] migrate QT commandline to vanilla cxx (this one, C++20 ongoing)

-   [ ] create optional md file[s]

-   [ ] create optional HTML5 file[s]

-   [ ] create optional SBOM (spdx) json file[s]

-   [ ] upload optional SBOM (spdx) json to RDBMS

-   [ ] build Linux and Windows desktop app with QT

-   [ ] build Windows desktop app with C#

-   [x] make support for compilation and installation

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

Project Link: [https://github.com/Zheng-Bote/https://github.com/Zheng-Bote/header_docu_cpp/](https://github.com/Zheng-Bote/https://github.com/Zheng-Bote/header_docu_cpp/)

<p align="right">(<a href="#top">back to top</a>)</p>

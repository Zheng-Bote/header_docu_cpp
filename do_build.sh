#!/usr/bin/bash

mkdir -p obj bin

g++ -std=c++20 -c src/header_docu_cpp.cpp -o obj/header_docu_cpp.o -I/usr/include/openssl/ -L/usr/lib/ssl -lcrypto -g3 -O0 -Wall -Wextra -Wpedantic -Wshadow -Wconversion

g++ -std=c++20 -c src/rz_files.cpp -o obj/rz_files.o -I/usr/include/openssl/ -L/usr/lib/ssl -lcrypto -g3 -O0 -Wall -Wextra -Wpedantic -Wshadow -Wconversion

g++ -std=c++20 -c src/rz_datetime.cpp -o obj/rz_datetime.o -I/usr/include/openssl/ -L/usr/lib/ssl -lcrypto -g3 -O0 -Wall -Wextra -Wpedantic -Wshadow -Wconversion

g++ -std=c++20 -c src/rz_filesystem.cpp -o obj/rz_filesystem.o -I/usr/include/openssl/ -L/usr/lib/ssl -lcrypto -g3 -O0 -Wall -Wextra -Wpedantic -Wshadow -Wconversion

g++ -std=c++20  -c src/rz_crypt.cpp -o obj/rz_crypt.o -I/usr/include/openssl/ -L/usr/lib/ssl -lcrypto -g3 -O0 -Wall -Wextra -Wpedantic -Wshadow -Wconversion

g++ -std=c++20 -o bin/header_docu_cpp obj/header_docu_cpp.o obj/rz_files.o obj/rz_datetime.o obj/rz_filesystem.o obj/rz_crypt.o -I/usr/include/openssl/ -L/usr/lib/ssl -lcrypto -g3 -O0 -Wall -Wextra -Wpedantic -Wshadow -Wconversion

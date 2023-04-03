#!/usr/bin/bash

g++ -std=c++20 -o bin/start obj/start.o obj/rz_files.o obj/rz_datetime.o obj/rz_filesystem.o obj/rz_crypt.o -I/usr/include/openssl/ -L/usr/lib/ssl -lcrypto -g3 -O0 -Wall -Wextra -Wpedantic -Wshadow -Wconversion

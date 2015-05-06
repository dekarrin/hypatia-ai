#/bin/sh

make clean
./autogen.sh &&
./configure CPPFLAGS=-DDEBUG CFLAGS="-g -O0" "$@" &&
make

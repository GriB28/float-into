FLAGS = -std=c++17

all:
	echo "you have to use one of these names: binary, ..."

binary:
	g++ scripts/binary.cpp -O2 -o bin/binary
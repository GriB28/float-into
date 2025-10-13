FLAGS = -std=c++17

all:
	echo "you have to use one of these names: binary, ..."

binary:
	g++ scripts/binary.cpp lib/utils.cpp -O2 -o bin/binary

overflow:
	g++ scripts/overflow.cpp lib/utils.cpp -O2 -o bin/overflow
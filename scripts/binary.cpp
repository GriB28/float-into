#include <iostream>
#include <fstream>
#include <string>

#include "../lib/coloring.h"

using namespace color;
using std::cout;
using std::fstream;
using std::string;


string uint2bin(unsigned number) {
    string answer;
    while (number) {
        const unsigned before = number;
        number = (number >> 1) << 1;
        if (before == number) answer = '0' + answer;
        else answer = '1' + answer;
        number >>= 1;
    }
    return answer;
}

union float_mirroring {
    float f;
    unsigned u;
} mirror;


int main() {
    cout << FAINT << LIGHTBLUE << "> reading config...\n" << RESET;
    fstream data("data/binary_input.csv", std::ios::in);

    char type;
    data >> type;

    if (type == 'f') data >> mirror.f;
    else data >> mirror.u;

    cout << FAINT << LIGHTBLUE << "> configuring is over.\n" << RESET;

    const string answer = uint2bin(mirror.u);

    cout << YELLOW;
    if (type == 'f')
        for (unsigned short i = 0; i < answer.length(); i++) {
            if (i == 1 || i == 9) cout << ' ';
            cout << answer[i];
        }
    else cout << answer;
    cout << FAINT << LIGHTBLUE << "> finished\n\n" << RESET;
    return 0;
}
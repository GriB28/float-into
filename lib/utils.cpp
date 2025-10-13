#include <iostream>
#include "lib.h"
using std::cout;


string utils::uint2bin(unsigned number) {
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

string utils::float2bin(const float &number) {
    float_mirroring mirror;
    mirror.f = number;
    return uint2bin(mirror.u);
}

void utils::print_float_binary_line(const string &bin_line) {
    for (unsigned short i = 0; i < bin_line.length(); i++) {
        if (i == 1 || i == 9) cout << ' ';
        cout << bin_line[i];
    }
}

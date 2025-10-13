#include <iostream>
#include <fstream>
#include <string>

#include "../lib/lib.h"

using namespace color;
using std::cout;
using std::fstream;
using std::string;


int main() {
    cout << FAINT << LIGHTBLUE << "> reading config...\n" << RESET;
    fstream data("data/binary_input.csv", std::ios::in);

    char type;
    string result;
    data >> type;

    if (type == 'f') {
        float value;
        data >> value;
        result = utils::float2bin(value);
    }
    else {
        unsigned value;
        data >> value;
        result = utils::uint2bin(value);
    }

    cout << FAINT << LIGHTBLUE << "> configuring is over.\n" << RESET << YELLOW;
    if (type == 'f') utils::print_float_binary_line(result);
    else cout << result;
    cout << '\n' << FAINT << LIGHTBLUE << "> finished\n\n" << RESET;
    return 0;
}
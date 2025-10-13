#include <iostream>
#include <string>

#include "../lib/lib.h"

using namespace color;
using std::cout;


void print(const unsigned &pow, const string &current) {
    cout << YELLOW << "10^" << pow << RESET << "\t:\t" << YELLOW;
    utils::print_float_binary_line(current);
    cout << RESET << '\n';
}


int main() {
    cout << std::fixed;
    cout.precision(2);
    cout << YELLOW;
    float number = 1.0;
    unsigned power = 0;
    string current_bin = utils::float2bin(number), previous_bin;

    print(power, current_bin);

    while (current_bin != previous_bin) {
        number *= 10;
        power++;
        previous_bin = current_bin;
        current_bin = utils::float2bin(number);

        print(power, current_bin);
    }

    cout << "infinite cycle from this point...\n";
    cout << '\n' << FAINT << LIGHTBLUE << "> finished\n\n" << RESET;
    return 0;
}
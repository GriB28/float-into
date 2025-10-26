#include <iostream>

#include "../lib/lib.h"

using namespace color;
using std::cout;


int main() {
    cout << std::fixed;
    cout.precision(2);

    float counter = 16777210, previous = 0;

    while (counter < 1e8 && previous != counter) {
        previous = counter;
        counter += 1;
        cout << YELLOW << counter << RESET << '\n';
    }

    cout << "infinite cycle from this point...\n";
    cout << '\n' << FAINT << LIGHTBLUE << "> finished\n\n" << RESET;
    return 0;
}
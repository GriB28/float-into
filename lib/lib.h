#ifndef FLOAT_INTO_LIB_H
#define FLOAT_INTO_LIB_H
#include <string>
using std::string;
namespace color {
    static const string LIGHTBLUE = "\x1b[36m";
    static const string YELLOW = "\x1b[33m";

    static const string FAINT = "\x1b[2m";
    static const string RESET = "\x1b[0m";
}

namespace utils {
    union float_mirroring {
        float f;
        unsigned u;
    };

    string uint2bin(unsigned number);
    string float2bin(const float &number);
    void print_float_binary_line(const string &bin_line);
}
#endif
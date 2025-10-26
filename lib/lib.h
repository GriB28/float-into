#ifndef FLOAT_INTO_LIB_H
#define FLOAT_INTO_LIB_H
#include <string>
#include <fstream>
using std::string;
using std::fstream;
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

    static fstream *stream_link = nullptr;
    void prepare_result_file(fstream *&filestream, const string &graph_name, const string &x_axis_name, const string &y_axis_name);
    void add_result_d(const double &x, const double &y);
    void add_result_f(const float &x, const float &y);
    void add_result_ud(const unsigned &x, const double &y);
    void add_result_uf(const unsigned &x, const float &y);
}
#endif
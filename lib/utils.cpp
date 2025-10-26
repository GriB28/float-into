#include <iostream>
#include <fstream>
#include "lib.h"
using std::cout;
using std::fstream;


string utils::uint2bin(unsigned number) {
    string answer;
    while (number) {
        const unsigned before = number;
        number = (number >> 1) << 1;
        if (before == number) answer = '0' + answer;
        else answer = '1' + answer;
        number >>= 1;
    }
    while (answer.length() < 32) answer = '0' + answer;
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


void utils::prepare_result_file(fstream *&filestream, const string &graph_name, const string &x_axis_name, const string &y_axis_name) {
    stream_link = filestream;
    *stream_link << '#' << graph_name << '\t' << x_axis_name << '\t' << y_axis_name << '\n';
}

void utils::add_result_d(const double &x, const double &y) { *stream_link << x << ',' << y << '\n'; }
void utils::add_result_f(const float &x, const float &y) { *stream_link << x << ',' << y << '\n'; }
void utils::add_result_ud(const unsigned &x, const double &y) { *stream_link << x << ',' << y << '\n'; }
void utils::add_result_uf(const unsigned &x, const float &y) { *stream_link << x << ',' << y << '\n'; }

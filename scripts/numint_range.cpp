#include <iostream>
#include <fstream>
#include <string>

#include "../lib/lib.h"

using namespace color;
using std::cout;
using std::fstream;
using std::string;


float f_float(float x) { return x * x; }
double f_double(double x) { return x * x; }


int main() {
    cout << FAINT << LIGHTBLUE << "> reading config...\n" << RESET;
    fstream data("data/numint_range_input.csv", std::ios::in);

    unsigned N_max, N_min, dN;
    double x_0, x_1;
    char type;
    string output_file, graph_name, Ox, Oy;
    data >> N_min >> N_max >> dN >> x_0 >> x_1 >> type;
    data >> output_file >> graph_name >> Ox >> Oy;

    auto *result = new fstream("data/" + output_file + ".csv", std::ios::out);
    utils::prepare_result_file(result, graph_name, Ox, Oy);

    cout << FAINT << LIGHTBLUE << "> configuring is over.\nstarting calculating...\n" << RESET << LIGHTBLUE;
    for (unsigned N = N_min; N <= N_max; N += dN) {
        double sum_d = 0;
        float sum_f = 0;
        const float step_f = (float)(x_1 - x_0) / N;
        const double step_d = (x_1 - x_0) / N;
        for (unsigned delta = 0; delta < N; delta++) {
            const long percent = 1000 * delta / N;
            cout << "\r\b> progress (" << N << " / " << N_max << "): " << delta << " / " << N << " (" << percent / 10 << '.' << percent % 10 << "%)    ";
            if (type == 'f')
                sum_f += f_float((float)x_0 + delta * step_f);
            else if (type == 'd')
                sum_d += f_double(x_0 + delta * step_d);
        }
        sum_f *= step_f;
        sum_d *= step_d;
        if (type == 'f') utils::add_result_uf(N, sum_f);
        else if (type == 'd') utils::add_result_ud(N, sum_d);
    }

    cout << RESET << LIGHTBLUE << "\r\b> finished\n\n" << RESET;
    delete result;
    return 0;
}
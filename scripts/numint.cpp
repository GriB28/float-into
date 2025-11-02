#include <iostream>
#include <fstream>
#include <string>

#include "../lib/lib.h"

using namespace color;
using std::cout;
using std::fstream;
using std::string;


float f_float(float x) { return 10 * x * x + .1 * x; }
double f_double(double x) { return 10 * x * x + .1 * x; }


int main() {
    cout << FAINT << LIGHTBLUE << "> reading config...\n" << RESET;
    fstream data("data/numint_input.csv", std::ios::in);

    unsigned long long N;
    double x_0, x_1;
    char type;
    string output_file, graph_name, Ox, Oy;
    data >> N >> x_0 >> x_1 >> type;
    data >> output_file >> graph_name >> Ox >> Oy;

    auto *result = new fstream("data/" + output_file + ".csv", std::ios::out);
    utils::prepare_result_file(result, graph_name, Ox, Oy);

    cout << FAINT << LIGHTBLUE << "> configuring is over.\nstarting calculating...\n" << RESET << LIGHTBLUE;
    double sum_d = 0;
    float sum_f = 0;
    const float step_f = (float)(x_1 - x_0) / N;
    const double step_d = (x_1 - x_0) / N;
    for (unsigned long long delta = 0; delta < N; delta++) {
        const long percent = 1000 * delta / N;
        cout << "\r\b> progress: " << delta << " / " << N << " (" << percent / 10 << '.' << percent % 10 << "%)";
        if (type == 'f') {
            float local_x = (float)x_0 + delta * step_f;
            sum_f += f_float(local_x);
            utils::add_result_f(local_x, sum_f);
        }
        else if (type == 'd') {
            double local_x = x_0 + delta * step_d;
            sum_d += f_double(local_x);
            utils::add_result_d(local_x, sum_d);
        }
    }

    cout << RESET << LIGHTBLUE << "\r\b> finished\n\n" << RESET;
    delete result;
    return 0;
}
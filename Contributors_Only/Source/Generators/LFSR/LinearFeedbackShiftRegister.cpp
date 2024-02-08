#include <iostream>
#include <chrono>
#include <fstream>
#include <cstdint>
#include <map>
#include "lfsr.hpp"
int main() {
    std::ofstream output_file("output.txt");
    std::ofstream gnu_plot("gnuplot.txt");
    DiceForge::LFSR<u_int64_t> rng(1);
    std::map<const unsigned long long int, long long int> freq;
    // output_file.precision(17);

    for (int i = 0; i < 1000000; i++) {
        auto rand_num = rng.random();
        output_file << rand_num << '\n';
        freq[rand_num]++;
    }

    for (auto &i : freq) {
        gnu_plot << i.first << " " << i.second << '\n';
    }

    gnu_plot.close();
    output_file.close();
}
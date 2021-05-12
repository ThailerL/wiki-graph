#include "util.h"

#include <fstream>
#include <iostream>

namespace wikigraph {
namespace util {

void log(std::string s, bool colored) {
    if (colored)
        std::cout << "\x1B[32m" << s << "\033[0m\t\t\n";
    else
        std::cout << s << "\n";
}

void err(std::string s) { std::cout << "\x1B[31m" << s << "\033[0m\t\t\n"; }

bool file_exists(const std::string& fileName) {
    std::ifstream infile(fileName);
    return infile.good();
}

bool isValid(int lower, int upper, int value) {
    return value >= lower && value <= upper;
}

// Adopted from https://stackoverflow.com/a/20016865/11129331
RNG::RNG(double low, double high)
    : r(std::bind(std::uniform_real_distribution<>(low, high),
                  std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()))) {}

double RNG::operator()() {
    return r();
}

} // namespace util
} // namespace wikigraph

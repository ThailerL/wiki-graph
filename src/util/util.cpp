#include "util.h"

void log(std::string s, bool colored) {
    if (colored)
        std::cout << "\x1B[32m" << s << "\033[0m\t\t\n";
    else
        std::cout << s << "\n";
}

void err(std::string s) { std::cout << "\x1B[31m" << s << "\033[0m\t\t\n"; }

bool file_exists(const char *fileName) {
    std::ifstream infile(fileName);
    return infile.good();
}

bool isValid(int lower, int upper, int value) {
    return value >= lower && value <= upper;
}

#pragma once

#include <functional>
#include <random>
#include <string>

namespace wikigraph {
namespace util {

void log(std::string s, bool colored);
void err(std::string s);
bool file_exists(const std::string& fileName);
bool isValid(int lower, int upper, int value);

/**
 * Helper class that generates a random double between supplied bounds.
 */
class RNG {
public:
    RNG(double low, double high);
    double operator()();

private:
    std::function<double()> r;
};

}
}

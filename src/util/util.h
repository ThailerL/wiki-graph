#pragma once

#include <string>

namespace wikigraph {
namespace util {

void log(std::string s, bool colored);
void err(std::string s);
bool file_exists(const std::string &fileName);
bool isValid(int lower, int upper, int value);

}
}

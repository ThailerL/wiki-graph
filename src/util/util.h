#pragma once

namespace wikigraph {

    void log(std::string s, bool colored);
    void err(std::string s);
    bool file_exists(const string &fileName);
    bool isValid(int lower, int upper, int value);

}

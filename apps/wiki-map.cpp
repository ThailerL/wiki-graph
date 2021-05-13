#include "../src/util/util.h"
#include <fstream>
#include <iostream>
#include <sstream>

using std::string;
using std::stringstream;
using namespace wikigraph::util;
using std::cout;

int main(int argc, char* argv[]) {
    log(string("[-] Wiki title mapper [-]"), true);

    // Number of Expected arguments
    int NUM_ARGS = 2;
    if (argc != NUM_ARGS + 1) {
        err(string("Incorrect syntax, Use ./prep-data map_file.txt node_id"));
        return 1;
    }

    if (!file_exists(argv[1])) {
        err(string("Map file not found :("));
        return 1;
    }
    std::ifstream dataFile(argv[1]);
    if (!dataFile.is_open()) {
        err(string("Map file could not be opened :("));
        return 1;
    }

    stringstream node_str(argv[2]);
    int node_id;
    node_str >> node_id;

    int counter = -1;
    string line;
    while (getline(dataFile, line)) {
        if(counter++ == node_id) {
            break;
        }
    }
    size_t size = line.size();
    line = line.substr(line.find("\""), size);
    log(line, true);
    return 0;
}

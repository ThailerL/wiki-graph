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
    if (argc < NUM_ARGS + 1) {
        err(string("Incorrect syntax, Use ./wiki-map map_file.txt node_id1 [node_id2 node_id3 ...]"));
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

    for(int i = 1; i<argc-1; i++) {
        stringstream node_str(argv[i+1]);
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
        line = std::to_string(node_id) + " : " + line.substr(line.find("\""), size);
        log(line, true);
    }
    return 0;
}

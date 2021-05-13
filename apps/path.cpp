#include "../src/core/graph.h"
#include "../src/util/util.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::stringstream;
using namespace wikigraph::core;
using namespace wikigraph::util;

int main(int argc, char* argv[]) {
    log(string("[-] Graph path finder [-]"), true);

    // Number of Expected arguments
    int NUM_ARGS = 3;
    if (argc < NUM_ARGS + 1) {
        err(string("Incorrect syntax, Use ./path graph_file from_node to_node [type]"));
        return 1;
    }

    Graph graph(argv[1]);

    // Parse bounds
    stringstream from_str(argv[2]);
    stringstream to_str(argv[3]);
    size_t from, to;
    from_str >> from;
    to_str >> to;

    std::vector<size_t> path;
    if (argc >= 5 && (std::string(argv[4]) == "b" || std::string(argv[4]) == "bfs")) {
        path = graph.shortestPath(from, to);
    } else {
        path = graph.getDijkstraPath(from, to);
    }

    if (path.empty()) {
        cout << "No path exists\n";
    } else {
        cout << "Path of length " << path.size() - 1 << " found: ";
        for (size_t i : path) {
            cout << i << " ";
        }
        cout << std::endl;
    }

    return 0;
}

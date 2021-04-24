#include <iostream>
#include <algorithm>
#include <fstream>
#include "graph.h"
#include <boost/algorithm/string.hpp>
#include "../util/util.h"

using std::stringstream;
using std::getline;
using std::ifstream;
using namespace wikigraph::util;

namespace wikigraph {
namespace core {

Graph::Graph(const string &filename) {
    // validate file
    if (!file_exists(filename))
        throw std::invalid_argument("File " + filename + " does not exist");

    ifstream ifs(filename);
    string line;

    getline(ifs, line);
    vector<string> split;
    boost::split(split, line, boost::is_any_of(" "));
    _lowerIndex = stoi(split[0]);
    _higherIndex = stoi(split[1]);

    
    // initialize with empty nodes
    for (size_t i = _lowerIndex; i <= _higherIndex; i++)
        nodes.emplace_back(i);

    // iterate over file
    while (getline(ifs, line)) {
        // split line
        vector<string> split;
        boost::split(split, line, boost::is_any_of(" "));
        size_t from = stoi(split[0]);
        size_t to = stoi(split[1]);

        addEdge(from, to);
    }
}

void Graph::addEdge(size_t from, size_t to) {
    // validate node indices
    if (!isValid(_lowerIndex, _higherIndex, from) || !isValid(_lowerIndex, _higherIndex, to))
        throw std::invalid_argument("Received node index out of range");
    from -= _lowerIndex;
    to -= _lowerIndex;
    nodes[from].neighbors.push_back(to);
}

vector<size_t> Graph::shortestPath(size_t from, size_t to) {
    return vector<size_t>();
}

}
}

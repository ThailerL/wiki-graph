#include <iostream>
#include <algorithm>
#include "graph.h"
#include <boost/algorithm/string.hpp>
#include "../util/util.h"

using std::stringstream;
using std::getline;
using std::ifstream;
using namespace wikigraph::util;

namespace wikigraph {
namespace core {

Graph::Graph(size_t lowerIndex, size_t higherIndex, const string &filename)
    : _lowerIndex(lowerIndex), _higherIndex(higherIndex) {
    // initialize with empty nodes
    for (size_t i = lowerIndex; i < higherIndex; i++)
        nodes.push_back(Node(i));

    // validate file
    if (!file_exists(filename))
        throw std::invalid_argument("File " + filename + " does not exist");
    ifstream ifs(filename);
    string line;

    // iterate over file
    while (getline(ifs, line)) {
        // split line
        vector<string> split;
        boost::split(split, line, " ");
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

}
}

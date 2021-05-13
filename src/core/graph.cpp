#include "graph.h"
#include "../util/util.h"
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>

using std::getline;
using std::ifstream;
using std::priority_queue;
using std::stringstream;
using namespace wikigraph::util;

namespace wikigraph {
namespace core {

Graph::Graph(const string& filename) {
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
    if (!isValid(_lowerIndex, _higherIndex, from) ||
        !isValid(_lowerIndex, _higherIndex, to))
        throw std::invalid_argument("Received node index out of range");
    from -= _lowerIndex;
    to -= _lowerIndex;
    nodes[from].neighbors.push_back(to);
    nodes[to].indegree++;
}

vector<size_t> Graph::shortestPath(size_t from, size_t to) {
    from = from - _lowerIndex;
    to = to - _lowerIndex;
    // maps from a node to its predecessor to backtrack
    std::unordered_map<size_t, size_t> predecessors;
    std::queue<size_t> work;

    predecessors[from] = from;
    work.push(from);

    while (!work.empty()) {
        size_t idx = work.front();
        work.pop();

        if (idx == to) {
            vector<size_t> path = {idx};
            while (path.back() != from) {
                path.push_back(predecessors[path.back()]);
            }
            std::reverse(path.begin(), path.end());
            for (size_t& node : path) {
                node += _lowerIndex;
            }
            return path;
        }

        for (size_t newIdx : nodes[idx].neighbors) {
            bool isNew = predecessors.insert({newIdx, idx}).second;
            if (isNew) {
                work.push(newIdx);
            }
        }
    }

    return vector<size_t>();
}

std::vector<size_t> Graph::getDjikstraPath(size_t from, size_t to) {
    // Create min heap using stl priority queue
    priority_queue<size_t, vector<size_t>, std::greater<size_t>> minHeap;
    // Initialize all distances to infinity beforehand
    std::vector<size_t> distances(nodes.size(), INT16_MAX);
    std::vector<int> predecessors;

    from -= _lowerIndex;
    to -= _lowerIndex;

    for (size_t i = 0; i < nodes.size(); i++)
        predecessors.push_back(-1);

    minHeap.push(from);

    while (!minHeap.empty()) {
        size_t current_node = minHeap.top();
        minHeap.pop();
        if (current_node == to)
            break;
        for (const size_t neighbor : nodes[current_node].neighbors) {
            size_t new_dist =
                distances[current_node] + nodes[neighbor].indegree;
            if (distances[neighbor] == INT16_MAX) {
                distances[neighbor] = new_dist;
                minHeap.push(neighbor);
                predecessors[neighbor] = current_node;
            } else if (distances[neighbor] >= new_dist) {
                distances[neighbor] = new_dist;
                predecessors[neighbor] = current_node;
                minHeap.push(neighbor);
            }
        }
    }

    vector<size_t> path;
    size_t index = to;
    if (predecessors[index] == static_cast<int>(from)) {
        return std::vector<size_t>{from + _lowerIndex, to + _lowerIndex};
    }
    while (index != from) {
        if (predecessors[index] == -1)
            return std::vector<size_t>();
        path.push_back(index + _lowerIndex);
        index = predecessors[index];
    }
    path.push_back(from + _lowerIndex);
    std::reverse(path.begin(), path.end());
    return path;
}

size_t Graph::getLowerIndex() const {
    return _lowerIndex;
}

} // namespace core
} // namespace wikigraph

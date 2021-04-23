#pragma once

#include <vector>
#include <string>

using std::vector;
using std::string;

namespace wikigraph {
namespace core {

class Graph {
public:
    /**
     * Node struct which stores an integer index and a vector of neighbors.
     */
    struct Node {
        Node(size_t index) : index(index) {}
        size_t index;
        vector<size_t> neighbors;
    };
    /**
     * Constructor for a Graph object.
     *
     * @param lowerIndex the lowest node index
     * @param higherIndex the highest node index
     * @param filename path to output of prep-data
    */
    Graph(size_t lowerIndex, size_t higherIndex, const string &filename);

    vector<Node> nodes;
private:
    /**
     * Helper method to insert edge into the graph.
     * @param from index of the node the edge is going from
     * @param to index of the node the edge is going to
     */
    void addEdge(size_t from, size_t to);
    size_t _lowerIndex;
    size_t _higherIndex;
};

}
}

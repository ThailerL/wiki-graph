#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

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
        size_t indegree = 0;
        vector<size_t> neighbors;
    };

    /**
     * Constructor for a Graph object.
     *
     * @param lowerIndex the lowest node index
     * @param higherIndex the highest node index
     * @param filename path to output of prep-data
    */
    Graph(const string& filename);

    /**
     * Finds the shortest path from one node to another with breadth first search.
     *
     * @param from the starting node index
     * @param to the ending node index
     * @return a vector of node indices of nodes that make up the shortest path in order (empty if no path)
    */
    vector<size_t> shortestPath(size_t from, size_t to);

    vector<size_t> getDijkstraPath(size_t from, size_t to);

    size_t getLowerIndex() const;

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

} // namespace core
} // namespace wikigraph

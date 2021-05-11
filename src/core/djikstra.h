#pragma once

#include "graph.h"
#include <

using wikigraph::core::Graph;
namespace wikigraph {
namespace core {

// Encapsulates Djikstra's shortest path algorithm
class Djikstra {
    Graph graph_;
    public:
    // Creates a Djikstra instance from the given graph
    Djikstra(Graph graph) : graph_(graph) {};
    /**
     * @brief Returns a list of vertices in the shortest path from the given node to another node 
     * 
     * @param from starting node index
     * @param to destination node index
     * @return std::vector<int> containing indices of nodes, or {-1} if no path exists
     */
    std::vector<int> getPath(size_t from, size_t to);
};

} // namespace wikigraph
} // namespace core
#include "renderer.h"

namespace wikigraph {
namespace core {

/**
 * Helper method to get a vector of masses from a graph.
 * @param graph a Graph object
 * @return ordered vector of doubles
 */
vector<double> getMassVector(const Graph& graph) {
    vector<double> masses;
    for (const Graph::Node& node : graph.nodes) {
        masses.push_back(node.indegree);
    }
    return masses;
}

Renderer::Renderer(const Graph& graph, const RendererConfig& cfg)
    : _cfg(cfg), _simulation(getMassVector(graph), cfg.simulationWidth, cfg.simulationHeight) {
    // add repulsive forces between nodes
    for (size_t i = 0; i < graph.nodes.size(); i++) {
        for (size_t j = i + 1; j < graph.nodes.size(); j++) {
            // k must be negative to get repulsion not attraction
            _simulation.addForceBetween(i, j, coulombicForce(-cfg.nodeRepulsion));
        }
    }
    // add attractive forces between adjacent nodes
    // once per edge, so bidirectional edges will lead to twice the attraction
    for (const Graph::Node& node : graph.nodes) {
        for (size_t neighbor : node.neighbors) {
            _simulation.addForceBetween(node.index, neighbor, elasticForce(cfg.neighborAttraction));
        }
    }
}

PNG Renderer::render(size_t imageWidth, size_t imageHeight) {
    _simulation.run(_cfg.iterations, _cfg.dt);
    return PNG(imageWidth, imageHeight);
}

}
}

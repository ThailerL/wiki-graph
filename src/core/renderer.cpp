#include "renderer.h"

namespace wikigraph {
namespace core {

/**
 * Helper method to get a vector of masses from a graph.
 * @param graph a Graph object
 * @return ordered vector of doubles
 */
vector<double> getMassVector(const Graph& graph) {
    vector<double> masses(graph.nodes.size());
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
    PNG image(imageWidth, imageHeight);
    HSLAPixel color(0, 1, .5, 1);

    double xScale = imageWidth / _cfg.simulationWidth;
    double yScale = imageHeight / _cfg.simulationHeight;
    for (const auto& pair : _simulation.getParticleInfo()) {
        const QVector2D& position = pair.first;
        double mass = pair.second;
        size_t pixelX = xScale * (position.x() + _cfg.simulationWidth / 2);
        size_t pixelY = yScale * (position.y() + _cfg.simulationHeight / 2);
        drawCircle(image, pixelX, pixelY, static_cast<size_t>(mass), color);
    }

    return image;
}

void Renderer::drawCircle(PNG& image, size_t x, size_t y, size_t radius, const HSLAPixel& color) {
    for (size_t currentX = x - radius; currentX < x + radius; ++currentX) {
        image.getPixel(currentX, y) = color;
    }

    // start at middle of circle and reduce deltaX while going down each row
    size_t maxDeltaX = radius;

    for (size_t deltaY = 1; deltaY <= radius; ++deltaY) {
        for (size_t deltaX = maxDeltaX; deltaX <= maxDeltaX; --deltaX) {
            if (deltaX * deltaX + deltaY * deltaY > radius * radius) {
                continue;
            }

            for (size_t currentX = x - deltaX; currentX <= x + deltaX; ++currentX) {
                image.getPixel(currentX, y + deltaY) = color;
                image.getPixel(currentX, y - deltaY) = color;
            }

            maxDeltaX = deltaX;
            break;
        }
    }
}

} // namespace core
} // namespace wikigraph

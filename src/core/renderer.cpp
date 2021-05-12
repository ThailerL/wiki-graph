#include "renderer.h"
#include <math.h>

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
        masses.push_back(node.indegree + 1);
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

        // add attractive forces between adjacent nodes
        // once per edge, so bidirectional edges will lead to twice the attraction
        for (size_t neighbor : graph.nodes[i].neighbors) {
            _simulation.addForceBetween(i, neighbor, elasticForce(cfg.neighborAttraction));
            if (i < neighbor)
                _edges.insert({i, neighbor});
            else
                _edges.insert({neighbor, i});
        }
    }
}

PNG Renderer::render(size_t imageWidth, size_t imageHeight) {
    _simulation.run(_cfg.iterations, _cfg.dt);
    PNG image(imageWidth, imageHeight);
    HSLAPixel lineColor(0, 0, 0, 1);
    HSLAPixel nodeColor(0, 1, .5, 1);

    double xScale = 0.9 * imageWidth / _cfg.simulationWidth;
    double yScale = 0.9 * imageHeight / _cfg.simulationHeight;
    const auto& particles = _simulation.getParticleInfo();

    // first draw lines
    for (const auto& edge : _edges) {
        auto p1pos = particles[edge.first].first;
        auto p2pos = particles[edge.second].first;
        double p1x = 0.05 * imageWidth + xScale * (p1pos.x() + _cfg.simulationWidth / 2);
        double p1y = 0.05 * imageHeight + yScale * (p1pos.y() + _cfg.simulationHeight / 2);
        double p2x = 0.05 * imageWidth + xScale * (p2pos.x() + _cfg.simulationWidth / 2);
        double p2y = 0.05 * imageHeight + yScale * (p2pos.y() + _cfg.simulationHeight / 2);
        drawLine(image, p1x, p1y, p2x, p2y, lineColor);
    }

    for (const auto& pair : _simulation.getParticleInfo()) {
        const QVector2D& position = pair.first;
        double mass = pair.second;
        size_t pixelX = 0.05 * imageWidth + xScale * (position.x() + _cfg.simulationWidth / 2);
        size_t pixelY = 0.05 * imageHeight + yScale * (position.y() + _cfg.simulationHeight / 2);
        drawCircle(image, pixelX, pixelY, static_cast<size_t>(3 + 4 * log(mass)), nodeColor);
    }

    return image;
}

void Renderer::drawLine(PNG& image, double x0, double y0, double x1, double y1, const HSLAPixel& color) {
    double x = x1 - x0;
    double y = y1 - y0;
    const double max = std::max(abs(x), abs(y));
    x /= max;
    y /= max;
    for (double n = 0; n < max; ++n) {
        image.getPixel(x0, y0) = color;
        x0 += x;
        y0 += y;
    }
}

void Renderer::drawCircle(PNG& image, size_t x, size_t y, size_t radius, const HSLAPixel& color) {
    for (size_t currentX = x - radius; currentX <= x + radius; ++currentX) {
        if (currentX < image.width() && y < image.height())
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
                if (currentX < image.width() && y + deltaY < image.height())
                    image.getPixel(currentX, y + deltaY) = color;
                if (currentX < image.width() && y - deltaY < image.height())
                    image.getPixel(currentX, y - deltaY) = color;
            }

            maxDeltaX = deltaX;
            break;
        }
    }
}

} // namespace core
} // namespace wikigraph

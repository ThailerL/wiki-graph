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
    : _cfg(cfg), _simulation(getMassVector(graph), cfg.simulationWidth, cfg.simulationHeight), _lowerIndex(graph.getLowerIndex()) {
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
    HSLAPixel lineColor(185, 0.5, 0.5);
    HSLAPixel nodeColor(216, 0.5, 0.5);

    double xScale = 0.9 * imageWidth / _cfg.simulationWidth;
    double yScale = 0.9 * imageHeight / _cfg.simulationHeight;
    const auto& particles = _simulation.getParticleInfo();

    for (const auto& pair : _simulation.getParticleInfo()) {
        const QVector2D& position = pair.first;
        double mass = pair.second;
        size_t x = 0.05 * imageWidth + xScale * (position.x() + _cfg.simulationWidth / 2);
        size_t y = 0.05 * imageHeight + yScale * (position.y() + _cfg.simulationHeight / 2);
        _nodeDrawInfo.emplace_back(x, y, static_cast<size_t>(3 + 4 * log(mass)));
    }

    // first draw lines
    for (const auto& edge : _edges) {
        const auto& p1 = _nodeDrawInfo[edge.first];
        const auto& p2 = _nodeDrawInfo[edge.second];
        drawLine(image, p1.x, p1.y, p2.x, p2.y, lineColor);
    }

    for (const auto& node : _nodeDrawInfo) {
        drawCircle(image, node.x, node.y, node.radius, nodeColor);
    }

    return image;
}

PNG Renderer::renderWithPathHighlighted(size_t imageWidth, size_t imageHeight, vector<size_t> path) {
    HSLAPixel endPointColor(0, 1, 0.5);
    HSLAPixel pathColor(0, 0, 0);
    PNG image = render(imageWidth, imageHeight);

    for (size_t i = 0; i < path.size(); ++i) {
        const auto& node = _nodeDrawInfo[path[i] - _lowerIndex];
        if (path.size() > 1 && i != path.size() - 1) {
            const auto& nextNode = _nodeDrawInfo[path[i + 1] - _lowerIndex];
            drawLine(image, node.x, node.y, nextNode.x, nextNode.y, pathColor);
            drawCircle(image, node.x, node.y, node.radius, pathColor);
        }
        if (i == 0 || i == path.size() - 1) {
            drawCircle(image, node.x, node.y, node.radius, endPointColor);
        }
    }

    return image;
}

void Renderer::drawLine(PNG& image, double x0, double y0, double x1, double y1, const HSLAPixel& color) const {
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

void Renderer::drawCircle(PNG& image, size_t x, size_t y, size_t radius, const HSLAPixel& color) const {
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

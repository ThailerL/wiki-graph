#pragma once

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "force.h"
#include "graph.h"
#include "simulation.h"
#include <set>
#include <vector>

using cs225::HSLAPixel;
using cs225::PNG;

namespace wikigraph {
namespace core {

/**
 Force-based renderer for a graph.
 */
class Renderer {
public:
    /**
     * Options for force-based rendering.
     *
     * @param simulationWidth width of the simulation
     * @param simulationHeight height of the simulation
     * @param nodeRepulsion coloumbic multiplier for how strong nodes repel each other (should be positive)
     * @param neighborAttraction elastic multiplier for how strong adjacent nodes attract each other
     * @param iterations number of iterations to run the simulation for
     * @param dt timestep per iteration
     */
    struct RendererConfig {
        double simulationWidth;
        double simulationHeight;
        double nodeRepulsion;
        double neighborAttraction;
        double maxRepulsionRadius;
        size_t iterations;
        double dt;
    };

    Renderer(const Graph& graph, const RendererConfig& cfg);

    /**
     * Renders the graph.
     * @return a PNG object with the drawn graph.
     */
    PNG render(size_t imageWidth, size_t imageHeight);

    /**
     * Renders the graph with a path highlighted in a different color.
     * @return a PNG object with the drawn graph.
     */
    PNG renderWithPathHighlighted(size_t imageWidth, size_t imageHeight, vector<size_t> path);

private:
    // Stores information of a node needed for drawing. Units are pixels.
    struct NodeInfo {
        NodeInfo(size_t x, size_t y, size_t r) : x(x), y(y), radius(r) {}
        size_t x;
        size_t y;
        size_t radius;
    };

    RendererConfig _cfg;
    Simulation _simulation;
    size_t _lowerIndex;
    // set of undirected edges to draw later
    std::set<std::pair<size_t, size_t>> _edges;
    // the information needed to draw all nodes
    vector<NodeInfo> _nodeDrawInfo;

    /**
     * Draws a straight 1-pixel thick line on the image from one point to another in the specified color.
     */
    void drawLine(PNG& image, double x0, double y0, double x1, double y1, const HSLAPixel& color) const;

    /**
     * Draws a filled circle with center (x, y) on the image with a specified radius and color.
     */
    void drawCircle(PNG& image, size_t x, size_t y, size_t radius, const HSLAPixel& color) const;
};

} // namespace core
} // namespace wikigraph
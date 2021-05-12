#pragma once

#include <vector>

#include "graph.h"
#include "simulation.h"
#include "force.h"
#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"

using cs225::PNG;
using cs225::HSLAPixel;

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
        size_t iterations;
        double dt;
    };

    Renderer(const Graph& graph, const RendererConfig& cfg);

    /**
     * Renders the graph.
     * @return a PNG object with the drawn graph.
     */
    PNG render(size_t imageWidth, size_t imageHeight);

private:
    RendererConfig _cfg;
    Simulation _simulation;

    void drawCircle(PNG& image, size_t x, size_t y, size_t radius, const HSLAPixel& color);
};

}
}
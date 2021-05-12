#include "../src/core/graph.h"
#include "../src/core/renderer.h"
#include <iostream>

using namespace wikigraph::core;
using std::cout;

int main(int argc, char* argv[]) {
    Graph graph(argv[1]);
    cout << "Created graph\n";
    Renderer::RendererConfig cfg;
    cfg.simulationWidth = 1000;
    cfg.simulationHeight = 1000;
    cfg.nodeRepulsion = 1;
    cfg.neighborAttraction = 2;
    cfg.iterations = 1000;
    cfg.dt = 0.01;

    auto path = graph.shortestPath(1421, 1329);
    cout << "Shortest path found " << path.size() << "\n";

    Renderer renderer(graph, cfg);
    cout << "Created renderer\n";
    PNG image = renderer.renderWithPathHighlighted(2000, 2000, path);
    cout << "Created image\n";
    image.writeToFile("graph.png");
}
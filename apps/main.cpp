#include "../src/core/graph.h"
#include "../src/core/renderer.h"
#include <iostream>

using namespace wikigraph::core;
using std::cout;

int main(int argc, char* argv[]) {
    Graph graph(argv[1]);
    cout << "Created graph\n";
    Renderer::RendererConfig cfg;
    cfg.simulationWidth = 10000;
    cfg.simulationHeight = 10000;
    cfg.nodeRepulsion = 1;
    cfg.neighborAttraction = 1;
    cfg.iterations = 1000;
    cfg.dt = 1;

    Renderer renderer(graph, cfg);
    cout << "Created renderer\n";

    PNG image = renderer.render(1000, 1000);
    cout << "Created image\n";

    image.writeToFile("graph.png");
}
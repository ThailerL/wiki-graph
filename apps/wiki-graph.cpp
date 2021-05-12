#include "../src/core/graph.h"
#include "../src/core/renderer.h"
#include <iostream>
#include <math.h>
#include <sstream>

using namespace wikigraph::core;
using std::cout;

int main(int argc, char* argv[]) {
    if (argc < 3 || argc == 4) {
        std::cerr << "Insufficient arguments. Use ./wiki-graph data_path output_path [from_node to_node]\n";
        return 1;
    }
    Graph graph(argv[1]);
    cout << "Created graph\n";
    Renderer::RendererConfig cfg;
    cfg.simulationWidth = sqrt(graph.nodes.size()) * 30;
    cfg.simulationHeight = cfg.simulationWidth;
    cfg.nodeRepulsion = .5;
    cfg.neighborAttraction = 1;
    cfg.iterations = cfg.simulationWidth;
    cfg.dt = 0.01;
    vector<size_t> path;

    if (argc > 4) {
        std::istringstream fromStream(argv[3]), toStream(argv[4]);
        size_t from, to;
        if (!(fromStream >> from)) {
            std::cerr << "Invalid from " << argv[3] << '\n';
            return 1;
        }
        if (!(toStream >> to)) {
            std::cerr << "Invalid to " << argv[4] << '\n';
            return 1;
        }
        if (from < graph.getLowerIndex() || from >= graph.getLowerIndex() + graph.nodes.size()) {
            std::cerr << "From node " << argv[3] << " is out of range\n";
            return 1;
        }
        if (to < graph.getLowerIndex() || to >= graph.getLowerIndex() + graph.nodes.size()) {
            std::cerr << "To node " << argv[4] << " is out of range\n";
            return 1;
        }

        path = graph.shortestPath(from, to);
        if (path.empty()) {
            cout << "No path from " << from << " to " << to << " found\n";
        } else {
            cout << "Shortest path found of length " << path.size() - 1 << '\n';
        }
    }

    Renderer renderer(graph, cfg);
    cout << "Running force simulation...\n";
    PNG image = renderer.renderWithPathHighlighted(cfg.simulationWidth * 2, cfg.simulationHeight * 2, path);
    image.writeToFile(argv[2]);
    cout << "Wrote image to " << argv[2] << '\n';
}
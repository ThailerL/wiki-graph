#include "../src/cs225/catch/catch.hpp"
#include "../src/core/graph.h"

#include <vector>
#include <stdlib.h>

using namespace wikigraph::core;

const std::string test_file =  "/home/tslietz2/tslietz2-sohamk2-ttz2/tests/simple_graph.txt";

TEST_CASE("Simple constructor tests") {
    SECTION("Graph loaded in correctly") {
        std::vector<Graph::Node> expected = {1, 2, 3, 4};
        expected[0].neighbors = {2, 3};
        expected[2].neighbors = {0};
        expected[3].neighbors = {2};

        Graph graph(test_file);

         REQUIRE(graph.nodes.size() == expected.size());

        for (size_t i = 0; i < graph.nodes.size(); ++i) {
            REQUIRE(graph.nodes[i].index == expected[i].index);
            REQUIRE(graph.nodes[i].neighbors == expected[i].neighbors);
        }   
    } 

    SECTION("No file found throws exception") {
        std::string file_name = "does_not_exist.txt";
        REQUIRE_THROWS_WITH(Graph(file_name), "File " + file_name + " does not exist");
    }
}

TEST_CASE("Simple shortestPath tests") {
    Graph graph(test_file);

    SECTION("Shortest path found when a longer path exists") {
        REQUIRE(graph.shortestPath(1, 3) == vector<size_t>{1, 3});
    }

    SECTION("Returns empty vector when no path exists") {
        REQUIRE(graph.shortestPath(1, 2) == vector<size_t>{});
    }

    SECTION("Shortest path from a node to itself is itself") {
        REQUIRE(graph.shortestPath(1, 1) == vector<size_t>{1});
    }
}

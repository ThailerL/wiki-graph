#include "../src/core/graph.h"
#include "../src/cs225/catch/catch.hpp"
#include <stdlib.h>
#include <vector>

using namespace wikigraph::core;

const std::string test_file = "./tests/simple_graph.txt";

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

    SECTION("Indegrees are accurate") {
        Graph graph(test_file);
        std::vector<Graph::Node> expected = {1, 2, 3, 4};
        expected[0].indegree = 1;
        expected[1].indegree = 0;
        expected[2].indegree = 2;
        expected[3].indegree = 1;

        for (size_t i = 0; i < graph.nodes.size(); ++i) {
            REQUIRE(graph.nodes[i].index == expected[i].index);
            REQUIRE(graph.nodes[i].indegree == expected[i].indegree);
        }
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

TEST_CASE("Djikstra shortestPath tests") {
    Graph graph(test_file);

    // SECTION("Shortest path found when a longer path exists") {
    //     REQUIRE(graph.getDjikstraPath(1, 3) == vector<size_t>{1, 3});
    // }

    // SECTION("Returns empty vector when no path exists") {
    //     REQUIRE(graph.getDjikstraPath(1, 2) == vector<size_t>{});
    // }

    // SECTION("Shortest path from a node to itself is itself") {
    //     REQUIRE(graph.getDjikstraPath(1, 1) == vector<size_t>{1});
    // }

    graph = Graph("./tests/djikstra_graph.txt");

    SECTION("Shortest path avoids node with high indegree") {
        REQUIRE(graph.getDjikstraPath(5, 3) == vector<size_t>{5, 2, 3});
    }
}
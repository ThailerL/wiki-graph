#include "../src/cs225/catch/catch.hpp"
#include "../src/core/graph.h"

#include <vector>

using namespace wikigraph::core;

TEST_CASE("Graph loaded in correctly") {
    std::vector<Graph::Node> expected = {1, 2, 3, 4};
    expected[0].neighbors = {2, 3};
    expected[2].neighbors = {0};
    expected[3].neighbors = {2};

    Graph graph(1, 4, "wikidata_example.txt");

    REQUIRE(graph.nodes.size() == expected.size());

    for (size_t i = 0; i < graph.nodes.size(); ++i) {
        REQUIRE(graph.nodes[i].index == expected[i].index);
        REQUIRE(graph.nodes[i].neighbors == expected[i].neighbors);
    }
}

TEST_CASE("No file found throws exception") {
    std::string file_name = "does_not_exist.txt";
    REQUIRE_THROWS_WITH(Graph(1, 4, file_name), "File " + file_name + "does not exist");
}

TEST_CASE("Index out of range throws expection") {
    REQUIRE_THROWS_WITH(Graph(1, 6, "wikidata_example.txt"), "Received node index out of range");
}
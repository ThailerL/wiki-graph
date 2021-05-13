# Development Log

## Weeks 0 - 1

We decided to use Stanford's SNAP! Dataset, which provides directed edges between articles. Our project and development structure was also planned - we decided to use separate execuables (build targets) for data sanitizing, testing and for running our graph algorithms. 

## Weeks 1 - 2

This week, we started by writing a script to morph our large dataset into a smaller subset of it based on some tolerances. 
Alongside this, the project subdirectory structure and Makefiles were also set up.
Furthermore, we implemented our graph data structure in C++ with the ability to load data, and set up the interface with some preliminary tests for the shortestPath algorithm.

## Weeks 2 - 3

In this time frame, we began the implementation of two major components of this project: Physics simulation for Force based visualization and implementation for the shortest path algorithm. We plan to use a unique approach for making the graph weighted, by making the weight of edges inversely proportional to the indegree of a particular node. We anticipate this to result in a graph with normalized influence of popular nodes, making the relationship between articles much more meaningful. Tests were also added to check the functionality of the project during the development process.

## Weeks 3 - 4 

During the final stretch, we were able to implement our goals and touch up on finer details. We implemented the Djikstra's shortest path algorithm to find meaningful relationships between articles. In addition, we finished the force based visualization with support for highlighting certain paths. Finally, we added executables such as `wiki-graph`, `wiki-map` and `path` for a better user end experience.

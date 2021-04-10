# Project Proposal

Having used Wikipedia as a consistently reliable and powerful source of knowledge and references throughout school and college, we are curious about how the wiki articles we know and love are related. We would like to find out how graph theory is embedded within information schemas such as Wikipedia by using the wiki hyperlinks dataset for our analysis.
## Leading Question
How could we visualize the relationship between articles on Wikipedia? To do this, we will combine Dijkstra’s algorithm and force-based visualization. We use Dijkstra’s algorithm to find the shortest path between two articles by clicking on hyperlinks and we use force-based visualization to create an aesthetic image of a graph represented by a set of articles. Combining these two algorithms, we can draw a set of articles and highlight the shortest path between two specific articles within that set.
## Data Set Acquisition and Processing
To serve our purposes, we will be working with wikipedia dumps. More specifically, we are using a subset of this data and isolating our perspective to hyperlinks. We chanced upon the work of one very helpful individual in the development community, who has morphed the tedious gigabytes of SQL data (Over 35 GB!!) into a clean, elegant adjacency list in text format (647 MB Compressed).

We will make some additional changes to our data, such as eliminating nodes with no outgoing edges and no incoming edges. This will make our data much more well connected and cohesive. Also, in order to not crash EWS or our own computers, we may decide to randomly eliminate a portion of the articles to further reduce the size of our dataset. To summarize, our data consists of an adjacency list of connected wikipedia articles, and the hyperlinks referenced in each article.

This will be stored as a main vector with each element being a node stored as a pair. The first component of each pair is the URL of the webpage as a string, and the second is a vector of pointers to elements in the main vector that the webpage has links to. This has a space complexity of `O(V+E)`, where `V` is the number of nodes and `E` is the number of edges.
## Graph Algorithms
While deliberating for weeks on which graph algorithms to implement, our team considered an ensemble of applications such as PageRank, Pathfinding, Spectral Clustering, Graph Drawing and many more. However, we have decided to spend our 3 weeks on the following algorithms:

### Dijkstra’s Algorithm
We will implement Dijkstra’s algorithm to find the shortest path between two Wikipedia articles by clicking hyperlinks. As a part of this, we will also be implementing a breadth-first search of the graph that traverses from the starting page until it reaches the ending page, while keeping track of tentative distances of the traversal. We estimate that this algorithm will run in `O(ElogV)`.

Input: The adjacency list representing the graph, the index of the starting page, and the index of the ending page.
Output: A vector of pointers to nodes representing the shortest path from the starting page to the ending page.
### Force-Based Visualization
We will do a simple force-based visualization of our Wikipedia graph. Force-based visualization works by treating nodes as entities with mass and assigning forces to them. Nodes that are connected will have attractive coulombic forces that pull them together, while nodes in general will exhibit repulsive forces towards each other. Since we plan on performing O(n) iterations, a naive implementation would run in `O(n^3)`, since for each iteration, we would have to loop through every node and check it’s position relative to all other nodes in the graph. However, we plan on using a 2-d tree to partition the image so that only nearby nodes repulse each other, so that we can perform each iteration in `O(nlogn)` and the algorithm as a whole will run in `O(n^2logn)`. The output of our algorithm will be a visualization of our Wikipedia graph such as [this](https://en.wikipedia.org/wiki/Force-directed_graph_drawing#/media/File:Visualization_of_wiki_structure_using_prefuse_visualization_package.png).

Input: The adjacency list representing the graph.
Output: A `cs225::PNG` object.
## Timeline
### Week 1
- Clean up and pre-process dataset to reduce size and discard irrelevant information that is uninteresting
- Parsing of the SQL dataset into an adjacency list graph representation

### Week 2
- Infrastructure for force based drawing—class for entity with mass with methods for adding/updating forces, updating position, etc.
- Test cases for Dijkstra’s algorithm
- Implement Dijkstra’s algorithm to find shortest path between two given hyperlinks

### Week 3
- Test cases for simple force-based simulation
- Implement backend for force-based drawing using naive method in `O(n^3)`
- Display output of force-based simulation as a PNG

### Week 4
- Implement non-naive force-based drawing in O(nlogn) using 2-d tree
- Color graph output of force-based drawing based on shortest paths between nodes
- Clean up and refactor code base as needed


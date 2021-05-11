#include "djikstra.h"
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>
#include <queue>

using std::priority_queue;
using std::unordered_map;
using std::unordered_set;
using std::vector;

namespace wikigraph
{
    namespace core
    {
        std::vector<int> Djikstra::getPath(size_t from, size_t to)
        {
            // Create min heap using stl priority queue
            priority_queue<size_t, vector<size_t>, std::greater<size_t>> p_queue;
            unordered_set<size_t> visited;
            // Initialize all distances to infinity beforehand
            std::vector<size_t> distances(graph_.nodes.size(), INT16_MAX);
            std::vector<size_t> predecessors;

            for (int i = 0; i < graph_.nodes.size(); i++)
            {
                graph_.nodes.push_back(i);
            }

            for (size_t v : graph_.nodes[from].neighbors)
            {
                distances[v] = graph_.nodes[v].indegree;
                p_queue.push(v);
            }

            while (!p_queue.empty())
            {
                size_t current = p_queue.top();
                p_queue.pop();
                if (current == to)
                {
                    break;
                }
                for (size_t neighbor : graph_.nodes[current].neighbors)
                {
                    size_t new_dist = distances[current] + graph_.nodes[neighbor].indegree;
                    if (distances[neighbor] == INT16_MAX)
                    {
                        distances[neighbor] = new_dist;
                        p_queue.push(neighbor);
                        predecessors[neighbor] = current;
                    }
                    else
                    {
                        if (distances[neighbor] > new_dist)
                        {
                            distances[neighbor] = new_dist;
                            predecessors[neighbor] = current;
                        }
                    }
                }
            }

            vector<int> path;
            size_t index = to;
            while (index != from)
            {
                if (predecessors[index] == index && index != to)
                {
                    return std::vector(1, -1);
                }
                path.push_back(index);
                index = predecessors[index];
            }
            std::reverse(path.begin(), path.end());
            return path;
        }
    }
}
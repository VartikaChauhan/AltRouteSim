#include "Graph.hpp"
#include <fstream>
#include <sstream>
#include <queue>
#include <limits>
#include <algorithm>
#include <iostream>

void Graph::loadFromCSV(const std::string& nodeFile, const std::string& edgeFile) {
    std::ifstream nf(nodeFile), ef(edgeFile);
    std::string line;

    if (!nf.is_open() || !ef.is_open()) {
        std::cerr << "Error: Could not open node or edge CSV file.\n";
        return;
    }

    // Load nodes
    getline(nf, line); // skip header
    while (getline(nf, line)) {
        std::istringstream ss(line);
        int id;
        float x, y;
        char comma;
        ss >> id >> comma >> x >> comma >> y;
        nodes[id] = {id, x, y};
    }

    // Load edges
    getline(ef, line); // skip header
    while (getline(ef, line)) {
        std::istringstream ss(line);
        int from, to;
        double weight;
        char comma;
        ss >> from >> comma >> to >> comma >> weight;
        adj[from].push_back({to, weight});
    }

    std::cout << "Graph loaded: " << nodes.size() << " nodes, " << adj.size() << " adjacency lists.\n";
}

std::vector<int> Graph::dijkstra(int src, int dst) {
    std::unordered_map<int, double> dist;
    std::unordered_map<int, int> prev;

    for (const auto& [id, _] : nodes)
        dist[id] = std::numeric_limits<double>::infinity();
    dist[src] = 0.0;

    using P = std::pair<double, int>;  // (distance, node)
    std::priority_queue<P, std::vector<P>, std::greater<>> pq;
    pq.push({0.0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (u == dst) break;

        for (auto& e : adj[u]) {
            if (dist[e.to] > dist[u] + e.weight) {
                dist[e.to] = dist[u] + e.weight;
                prev[e.to] = u;
                pq.push({dist[e.to], e.to});
            }
        }
    }

    // Check if destination is reachable
    if (dist.find(dst) == dist.end() || dist[dst] == std::numeric_limits<double>::infinity()) {
        std::cerr << "Warning: No path found from " << src << " to " << dst << "\n";
        return {};
    }

    // Reconstruct path
    std::vector<int> path;
    for (int at = dst; at != src; ) {
        if (prev.find(at) == prev.end()) {
            std::cerr << "Error: Incomplete path. Missing previous node for " << at << "\n";
            return {};
        }
        path.push_back(at);
        at = prev[at];
    }
    path.push_back(src);
    std::reverse(path.begin(), path.end());

    std::cout << "Path found from " << src << " to " << dst << ": ";
    for (int node : path) std::cout << node << " ";
    std::cout << "\n";

    return path;
}


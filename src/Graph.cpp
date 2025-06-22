#include "Graph.hpp"
#include <fstream>
#include <sstream>
#include <queue>
#include <limits>
#include <iostream>
#include <algorithm>

void Graph::loadFromCSV(const std::string& nf, const std::string& ef) {
    std::ifstream nfs(nf), efs(ef);
    std::string line;

    
    // Load nodes
    while (getline(nfs, line)) {
        if (line.empty() || line.find(',') == std::string::npos) continue;
        std::stringstream ss(line);
        std::string id_str, x_str, y_str;
        getline(ss, id_str, ',');
        getline(ss, x_str, ',');
        getline(ss, y_str, ',');

        try {
            long long id = std::stoll(id_str);
            float x = std::stof(x_str);
            float y = std::stof(y_str);
            nodes[id] = {id, x, y};
        } catch (...) {
            std::cerr << "[Node CSV] Malformed line: " << line << "\n";
        }
    }

    // Load edges
    while (getline(efs, line)) {
        if (line.empty() || line.find(',') == std::string::npos) continue;
        std::stringstream ss(line);
        std::string u_str, v_str, len_str, speed_str;
        getline(ss, u_str, ',');
        getline(ss, v_str, ',');
        getline(ss, len_str, ',');
        getline(ss, speed_str, ',');

        try {
            long long u = std::stoll(u_str);
            long long v = std::stoll(v_str);
            float len = std::stof(len_str);
            float speed = speed_str.empty() ? 1.0 : std::stof(speed_str);
            edges.push_back({u, v, len, speed});
            adjList[u].emplace_back(v, len);
        } catch (...) {
            std::cerr << "[Edge CSV] Malformed line: " << line << "\n";
        }
    }
}

std::vector<long long> Graph::dijkstra(long long start, long long end) {
    std::map<long long, float> dist;
    std::map<long long, long long> prev;
    for (auto& n : nodes) dist[n.first] = std::numeric_limits<float>::max();
    dist[start] = 0;

    using P = std::pair<float, long long>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (u == end) break;

        for (auto& [v, w] : adjList[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    std::vector<long long> path;
    if (prev.find(end) == prev.end() && start != end) return path;
    for (long long at = end; at != start; at = prev[at]) path.push_back(at);
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}


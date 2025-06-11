#pragma once
#include <vector>
#include <unordered_map>
#include <mutex>
#include <string>
#include <iostream>

struct Node { int id; float x, y; };

struct Edge { int to; double weight; };

class Graph {
public:
    std::unordered_map<int, Node> nodes;
    std::unordered_map<int, std::vector<Edge>> adj;
    std::unordered_map<int, std::unordered_map<int, std::mutex>> edgeLocks;

    void loadFromCSV(const std::string& nodeFile, const std::string& edgeFile);
    std::vector<int> dijkstra(int src, int dst);

void printNodes() const {
        for (const auto& [id, node] : nodes)
            std::cout << "Node " << id << ": (" << node.x << ", " << node.y << ")\n";
    }

    void printEdges() const {
        for (const auto& [from, edges] : adj) {
            for (const auto& edge : edges)
                std::cout << "Edge " << from << " -> " << edge.to << " (weight " << edge.weight << ")\n";
        }
    }
};

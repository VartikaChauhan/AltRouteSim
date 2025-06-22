#pragma once
#include <map>
#include <vector>
#include <string>

struct Node {
    long long id;
    float x, y;
};

struct Edge {
    long long from, to;
    float length, speed;
};

class Graph {
public:
    std::map<long long, Node> nodes;
    std::vector<Edge> edges;
    std::map<long long, std::vector<std::pair<long long, float>>> adjList;
    
    void loadFromCSV(const std::string& nodeFile, const std::string& edgeFile);
    std::vector<long long> dijkstra(long long start, long long end);
};


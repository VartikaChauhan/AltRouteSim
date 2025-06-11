#pragma once
#include "Graph.hpp"
#include "Vehicle.hpp"
#include <thread>
#include <vector>

class Simulator {
public:
    Graph* graph;
    std::vector<Vehicle> vehicles;

    Simulator(Graph* g): graph(g) {}
    void spawnVehicle(int src, int dst);
    void simulate();
};

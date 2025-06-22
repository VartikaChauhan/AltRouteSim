#include "Simulator.hpp"
#include "Graph.hpp"
#include <thread>
#include <mutex>
#include <iostream>
#include <ctime>
#include <GLFW/glfw3.h>
#include <chrono>

Graph g;
std::mutex edgeMutex;

void Simulator::run() {
    log_file.open("log.txt");
    g.loadFromCSV("data/nodes.csv", "data/edges.csv");
    MLPredictor predictor;

    renderer.init();
    srand(static_cast<unsigned>(time(nullptr)));
    
    std::vector<long long> node_ids;
    for (auto& [id, _] : g.nodes) node_ids.push_back(id);

    for (int i = 0; i < 5; ++i) {
        long long src = node_ids[rand() % node_ids.size()];
        long long dst = node_ids[rand() % node_ids.size()];
        while (dst == src) dst = node_ids[rand() % node_ids.size()];
        
        auto path = g.dijkstra(src, dst);
        if (path.empty()) continue;

        Vehicle v;
        v.id = i + 1;
        v.path = path;
        v.pathIndex = 0;
        v.arrived = false;
        v.predictedClass = 0;
        v.entry_tick = current_tick;
        
        vehicles.push_back(v);
        
        std::cout << "Vehicle " << v.id << " path: ";
        for (long long node : v.path) std::cout << node << " ";
        std::cout << std::endl;
    }

    while (!glfwWindowShouldClose(renderer.getWindow())) {

        for (auto& v : vehicles) {
   if (v.arrived || v.pathIndex >= v.path.size() - 1) continue;

            long long from = v.path[v.pathIndex];
            long long to = v.path[v.pathIndex + 1];
            int pred=0;

            {
                std::lock_guard<std::mutex> lock(edgeMutex);
                pred = predictor.predict(10 + current_tick * 2, 50 - current_tick * 2);
            }

             v.predictedClass = pred;
             
            v.x = g.nodes[to].x;
            v.y = g.nodes[to].y;

            v.pathIndex++;

            if (v.pathIndex == v.path.size() - 1) {
                v.arrived = true;
                v.exit_tick = current_tick;
                log_file << "Vehicle " << v.id
                         << " ETA: " << (v.exit_tick - v.entry_tick) << " ticks\n";
          // Append to CSV
    static bool header_written = false;
    std::ofstream csv("log.csv", std::ios::app);
    if (!header_written && csv.tellp() == 0) {
    csv << "VehicleID,StartNode,EndNode,Path,EntryTick,ExitTick,PredictedClass\n";
    header_written = true;
}
    csv << v.id << "," << v.path.front() << "," << v.path.back() << ",\"";
    for (size_t j = 0; j < v.path.size(); ++j) {
    csv << v.path[j];
    if (j != v.path.size() - 1) csv << " ";
}
csv << "\"," << v.entry_tick << "," << v.exit_tick << "," << v.predictedClass << "\n";
csv.close();
          }
        }
        
        renderer.draw(vehicles);
        glfwWaitEventsTimeout(0.05);  // Keeps window responsive
        current_tick++;
    }


    log_file.close();
    renderer.cleanup();
}


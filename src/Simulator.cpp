#include "Simulator.hpp"
#include <fstream>
#include <chrono>
#include <thread>
#include <ctime>
#include <cmath>
#include "MLPredictor.hpp"


void Simulator::spawnVehicle(int src, int dst) {
    vehicles.push_back({graph->dijkstra(src, dst)});
}

void Simulator::simulate() {
    for (auto& v : vehicles) {
        for (int i = 1; i < v.path.size(); ++i) {
            int u = v.path[i - 1], w = v.path[i];

            double dx = graph->nodes[u].x - graph->nodes[w].x;
            double dy = graph->nodes[u].y - graph->nodes[w].y;
            double dist = sqrt(dx*dx + dy*dy);

            time_t now = time(nullptr);
            struct tm* ltm = localtime(&now);
            int hour = ltm->tm_hour;
            double delay = predictDelay(dist, hour);

            {
                std::lock_guard<std::mutex> lock(graph->edgeLocks[u][w]);
                for (int step = 0; step < 100; ++step) {
                    v.t = step / 100.0f;
                    v.currentIndex = i;
                    std::this_thread::sleep_for(std::chrono::milliseconds((int)(delay * 10)));
                }
            }

            std::ofstream log("travel_log.csv", std::ios::app);
            log << u << "," << w << "," << dist << "," << delay << "," << hour << "\n";
        }
        v.finished = true;
    }
}

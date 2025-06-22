#pragma once
#include <vector>


struct Vehicle {
    int id;                         // vehicle ID
    long long from = -1;                  // current from-node ID
    long long to = -1;                    // current to-node ID
    float fromX = 0, fromY = 0;     // for rendering edge lines
    float toX = 0, toY = 0;
    float x = 0, y = 0;             // interpolated position on edge
    int predictedClass = 0;         // ML-based class

    std::vector<long long> path;          // complete path
    int pathIndex = 0;              // index into path vector

    bool arrived = false;
    int entry_tick = 0;
    int exit_tick = 0;
};



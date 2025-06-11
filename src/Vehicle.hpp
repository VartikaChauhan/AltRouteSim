#pragma once
#include <vector>
#include <chrono>
#include <string>

struct Vehicle {
    std::vector<int> path;     // Node indices
    int currentIndex = 0;      // Index of current segment in path
    float t = 0.0f;            // Interpolation factor between current and next node
    bool finished = false;     // Flag to indicate journey completion

    // Optional metadata
    std::chrono::steady_clock::time_point startTime; // For performance logging
    std::string id = "";       // Unique identifier (if needed)
    
    // Constructor (optional)
    Vehicle(const std::vector<int>& path_, const std::string& id_ = "")
        : path(path_), id(id_) {
        startTime = std::chrono::steady_clock::now();
    }

    // Get current node
    int currentNode() const {
        return (currentIndex < path.size()) ? path[currentIndex] : -1;
    }

    // Get next node
    int nextNode() const {
        return (currentIndex + 1 < path.size()) ? path[currentIndex + 1] : -1;
    }
};


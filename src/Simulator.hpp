#pragma once
#include <vector>
#include <fstream>
#include "Vehicle.hpp"
#include "MLPredictor.hpp"
#include "Render.hpp"
class Simulator {
public:
    void run();
private:
    std::vector<Vehicle> vehicles;
    int current_tick = 0;
    Render renderer;
    std::ofstream log_file;
};

#pragma once
#include <vector>
#include "Vehicle.hpp"
#include <GLFW/glfw3.h>
#include "MLPredictor.hpp"

class Render {
public:
    void init();  // initialize GLFW once
    void draw(const std::vector<Vehicle>& vehicles);
    void cleanup();
    GLFWwindow* getWindow() const { return window; }
private:
    bool initialized = false;
    struct GLFWwindow* window = nullptr;
};


#include "Graph.hpp"
#include "Simulator.hpp"
#include "Render.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>

int main() {
    Graph g;
    try {
        g.loadFromCSV("data/nodes.csv", "data/edges.csv");
    } catch (const std::exception& e) {
        std::cerr << "Error loading graph data: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    Simulator s(&g);
    s.spawnVehicle(0, 5);
    s.spawnVehicle(1, 6);

    std::thread simThread(&Simulator::simulate, &s);

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW." << std::endl;
        return EXIT_FAILURE;
    }

    GLFWwindow* win = glfwCreateWindow(600, 600, "AltRouteSim", nullptr, nullptr);
    if (!win) {
        std::cerr << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(win);
    glOrtho(0, 500, 500, 0, -1, 1);  // Set up 2D projection matrix

    while (!glfwWindowShouldClose(win)) {
        glClear(GL_COLOR_BUFFER_BIT);
        Render::drawGraph(&g, &s);
        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    simThread.join();
    glfwDestroyWindow(win);
    glfwTerminate();

    return 0;
}


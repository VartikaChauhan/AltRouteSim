#include "Render.hpp"
#include "Graph.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_easy_font.h"

extern Graph g;

void Render::init() {
    if (initialized) return;
    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW\n";
        exit(1);
    }
    window = glfwCreateWindow(800, 600, "AltRouteSim Visualization", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        std::cerr << "Failed to create GLFW window\n";
        exit(1);
    }
    glfwMakeContextCurrent(window);
    
    // Set coordinate system to normalized (0 to 1)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1.0, 0, 1.0, -1.0, 1.0);  // 2D projection
    glMatrixMode(GL_MODELVIEW);
    
    initialized = true;
    std::cout << "GLFW window created successfully\n";
}

void drawText(float x, float y, const std::string& text) {
    char buffer[99999];
    int quads = stb_easy_font_print(x, y, (char*)text.c_str(), nullptr, buffer, sizeof(buffer));
    glColor3f(1, 1, 1);  // white text
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 16, buffer);
    glDrawArrays(GL_QUADS, 0, quads * 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void Render::draw(const std::vector<Vehicle>& vehicles) {
    if (!initialized || !window) return;

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    // Normalize coordinates using bounding box of graph
    float minX = 1e9, minY = 1e9, maxX = -1e9, maxY = -1e9;
    for (const auto& [id, node] : g.nodes) {
        if (node.x < minX) minX = node.x;
        if (node.y < minY) minY = node.y;
        if (node.x > maxX) maxX = node.x;
        if (node.y > maxY) maxY = node.y;
    }

    float dx = maxX - minX + 1e-5;  // avoid divide by zero
    float dy = maxY - minY + 1e-5;
    
    //draw edges(roads)
    glBegin(GL_LINES);
   glColor3f(0.7f, 0.7f, 0.7f); // grey roads
    for (const auto& [id, node] : g.nodes) {
         for (const auto& [neighbor, weight] : g.adjList.at(id)) {
            float x1 = (g.nodes[id].x - minX) / dx;
            float y1 = (g.nodes[id].y - minY) / dy;
            float x2 = (g.nodes[neighbor].x - minX) / dx;
            float y2 = (g.nodes[neighbor].y - minY) / dy;
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
        }
    }
    glEnd();

//draw vehicles
    glPointSize(8.0);
    glBegin(GL_POINTS);
    for (const auto& v : vehicles) {
       float normX = (v.x - minX) / dx;
        float normY = (v.y - minY) / dy;

        if (v.predictedClass == 0) glColor3f(0.0f, 1.0f, 0.0f);       // Green
        else if (v.predictedClass == 1) glColor3f(1.0f, 1.0f, 0.0f);  // Yellow
        else glColor3f(1.0f, 0.0f, 0.0f);                             // Red
        
        glVertex2f(normX, normY);
        char label[64];
snprintf(label, sizeof(label), "V%d ETA:%d", v.id, v.arrived ? (v.exit_tick - v.entry_tick) : -1);
drawText(normX + 0.005f, normY + 0.005f, label);

    }
    glEnd();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Render::cleanup() {
    if (window) glfwDestroyWindow(window);
    glfwTerminate();
    initialized = false;
}

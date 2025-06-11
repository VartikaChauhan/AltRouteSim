#include "Render.hpp"
#include <GLFW/glfw3.h>
#include <cmath>

void Render::drawGraph(Graph* g, Simulator* s) {
    for (auto& [u, node] : g->nodes) {
        for (auto& e : g->adj[u]) {
            auto& n2 = g->nodes[e.to];
            glBegin(GL_LINES);
            glColor3f(0.6f, 0.6, 0.6f);
            glVertex2f(node.x, node.y);
            glVertex2f(n2.x, n2.y);
            glEnd();
        }
    }

    // Draw nodes
    for (auto& [_, node] : g->nodes)
        drawCircle(node.x, node.y, 8);

    // Draw vehicles
    for (auto& v : s->vehicles) {
        if (v.finished || v.path.size() < 2 || v.currentIndex <= 0 || v.currentIndex >= v.path.size())
            continue;

        int u = v.path[v.currentIndex - 1], w = v.path[v.currentIndex];
        float x = (1 - v.t) * g->nodes[u].x + v.t * g->nodes[w].x;
        float y = (1 - v.t) * g->nodes[u].y + v.t * g->nodes[w].y;
        drawCircle(x, y, 5);
    }
}

void Render::drawCircle(float cx, float cy, float r) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.0, 0.0f);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 20; i++) {
        float theta = i * 2.0f * M_PI / 20;
        glVertex2f(cx + cos(theta) * r, cy + sin(theta) * r);
    }
    glEnd();
}

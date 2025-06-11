#pragma once
#include "Graph.hpp"
#include "Simulator.hpp"

class Render {
public:
    static void drawGraph(Graph* g, Simulator* s);
    static void drawCircle(float cx, float cy, float r);
};

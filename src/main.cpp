#include <pybind11/embed.h>
#include "Simulator.hpp"

namespace py = pybind11;

int main() {
    py::scoped_interpreter guard{};  // Initializes Python interpreter

    Simulator sim;
    sim.run();

    return 0;
}


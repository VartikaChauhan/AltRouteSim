#include "MLPredictor.hpp"
#include <pybind11/embed.h>

namespace py = pybind11;

MLPredictor::MLPredictor() {
    py::module_::import("sys").attr("path").attr("insert")(0, "ml");
}

int MLPredictor::predict(float f1, float f2) {
    py::gil_scoped_acquire acquire;
    py::object mod = py::module_::import("inference_wrapper");
    return mod.attr("predict_class")(f1, f2).cast<int>();
}

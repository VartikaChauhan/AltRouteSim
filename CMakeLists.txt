cmake_minimum_required(VERSION 3.10)
project(AltRouteSim)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)

# OpenGL, GLEW, and GLFW
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(
    ${Python3_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    src
)

file(GLOB_RECURSE SRC src/*.cpp)

add_executable(AltRouteSim ${SRC})

# Link libraries
target_link_libraries(AltRouteSim
    pybind11::embed
    ${Python3_LIBRARIES}
    ${OPENGL_LIBRARIES}
    GLEW::GLEW
    glfw
    GL
)



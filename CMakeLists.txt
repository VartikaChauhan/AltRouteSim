cmake_minimum_required(VERSION 3.10)
project(AltRouteSim)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(src)

add_executable(AltRouteSim
    src/main.cpp
    src/Graph.cpp
    src/Simulator.cpp
    src/Render.cpp
    src/MLPredictor.cpp 
)

target_link_libraries(AltRouteSim
    ${OPENGL_gl_LIBRARY}
    glfw
    GLEW::GLEW
)

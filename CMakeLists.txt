cmake_minimum_required(VERSION 3.1...3.25)

project(
    TestProject
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)

# Enable testing
enable_testing()

add_subdirectory(Sources)
add_subdirectory(External/GLFW)
add_subdirectory(External/GLM)
add_subdirectory(External/GoogleTest)
add_subdirectory(Tests)




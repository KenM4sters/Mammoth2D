cmake_minimum_required(VERSION 3.1...3.25)

project(
    mammoth
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)

# Enable testing
enable_testing()

add_subdirectory(src)
add_subdirectory(external/GLFW)
add_subdirectory(external/Glad)
add_subdirectory(external/GLM)
add_subdirectory(external/GoogleTest)
add_subdirectory(testbed)




add_executable(Tutorial1 main.cpp)

# Include directories for tests
target_include_directories(
    Tutorial1 
    PUBLIC ${CMAKE_SOURCE_DIR}/Sources/
    PUBLIC ${CMAKE_SOURCE_DIR}/Tests/Tutorial1/
    PUBLIC ${CMAKE_SOURCE_DIR}/External/GLFW/include/
    PUBLIC ${CMAKE_SOURCE_DIR}/External/GLM/glm/
    PUBLIC ${CMAKE_SOURCE_DIR}/External/GoogleTest/googletest/include/
)

target_link_libraries(
    Tutorial1 
    Vulkan2D
    DeltaLib 
    glfw 
    glm 
)
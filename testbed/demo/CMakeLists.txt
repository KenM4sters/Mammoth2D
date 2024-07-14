add_executable(Demo main.cpp)

# Include directories for tests
target_include_directories(
    Demo 
    PUBLIC ${CMAKE_SOURCE_DIR}/Sources/
    PUBLIC ${CMAKE_SOURCE_DIR}/Tests/Demo/
    PUBLIC ${CMAKE_SOURCE_DIR}/External/GLFW/include/
    PUBLIC ${CMAKE_SOURCE_DIR}/External/GLM/glm/
    PUBLIC ${CMAKE_SOURCE_DIR}/External/GoogleTest/googletest/include/
)

target_link_libraries(
    Demo 
    mammoth
    glad
    glfw 
    glm 
)
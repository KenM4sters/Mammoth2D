# Add test executable
add_executable(ExampleTest ExampleTest.cpp)


# Include directories for tests
target_include_directories(
    ExampleTest PUBLIC
    PUBLIC ../../Engine/
    PUBLIC ../../External/GLFW/include/
    PUBLIC ../../External/GLM/glm/
    PUBLIC ../../External/GoogleTest/googletest/include/
)

# Link test executable against gtest and your project library
target_link_libraries(
    ExampleTest 
    Vulkan2D 
    glfw 
    glm 
    gtest
    gtest_main
)

add_test(
    NAME ExampleTest
    COMMAND ExampleTest
)

# Discover tests
include(GoogleTest)
gtest_discover_tests(ExampleTest)

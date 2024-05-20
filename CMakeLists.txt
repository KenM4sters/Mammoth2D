include(./.env.cmake OPTIONAL RESULT_VARIABLE LOCAL_ENV)
cmake_minimum_required(VERSION 3.1...3.25)
project(
	Vulkan2D
	VERSION 0.1.0
	LANGUAGES CXX C
)

# Window.
add_subdirectory(External/glfw)

# Maths.
add_subdirectory(External/glm)

# Vulkan.
include_directories("/usr/local/macOS/include")

add_executable(${PROJECT_NAME}
	main.cpp
  Sources/Program.cpp
  Sources/Window.cpp
  Sources/Device.cpp
  Sources/Camera.cpp
  Sources/Input.cpp
  Sources/Graphics/Renderer/SwapChain.cpp
  Sources/Graphics/Renderer/Renderer.cpp
  Sources/Graphics/Renderer/Sprite2DSystem.cpp
  Sources/Graphics/Pipelines/Pipeline.cpp
  Sources/Graphics/Pipelines/Shader.cpp
  Sources/Graphics/Pipelines/VertexInput.cpp
  Sources/Graphics/Buffers/Buffer.cpp
  Sources/Graphics/Buffers/BufferLayout.cpp
  Sources/Scene/Scene.cpp
  Sources/Physics/Physics.cpp
  Sources/Physics/Collision.cpp
  Sources/Physics/SpatialGrid.cpp
)

if (DEFINED VULKAN_SDK_PATH)
  set(Vulkan_INCLUDE_DIRS "${VULKAN_SDK_PATH}/include") # 1.1 Make sure this include path is correct.
  set(Vulkan_LIBRARIES "${VULKAN_SDK_PATH}/lib") # 1.2 Make sure lib path is correct.
  set(Vulkan_FOUND "True")
else()
  find_package(Vulkan REQUIRED) # throws an error if the Vulkan SDK could not be found.
  message(STATUS "Found Vulkan: $ENV{VULKAN_SDK}")
endif()
if (NOT Vulkan_FOUND)
    message(FATAL_ERROR "Could not find Vulkan library!")
else()
    message(STATUS "Using vulkan lib at: ${Vulkan_LIBRARIES}")
    message(STATUS "Using vulkan include at: ${Vulkan_INCLUDE_DIRS}")
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)


message(STATUS "CREATING BUILD FOR UNIX")
target_include_directories(${PROJECT_NAME} PUBLIC
  ${PROJECT_SOURCE_DIR}/Sources
  ${Vulkan_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME} glfw glm ${Vulkan_LIBRARIES})

############## Build SHADERS #######################

# Finds all vertex and fragment sources within the Shaders directory.
# Taken from VBlancos vulkan tutorial.
# https://github.com/vblanco20-1/vulkan-guide/blob/all-chapters/CMakeLists.txt
find_program(GLSL_VALIDATOR glslangValidator HINTS
  ${Vulkan_GLSLANG_VALIDATOR_EXECUTABLE}
  ${VULKAN_SDK_PATH}/bin
)

# Get all .vert and .frag files in shaders directory.s
file(GLOB_RECURSE GLSL_SOURCE_FILES
  "${PROJECT_SOURCE_DIR}/Shaders/*.frag"
  "${PROJECT_SOURCE_DIR}/Shaders/*.vert"
)

foreach(GLSL ${GLSL_SOURCE_FILES})
  get_filename_component(FILE_NAME ${GLSL} NAME)
  message(STATUS "Found shader file at ${FILE_NAME}")
  set(SPIRV "${PROJECT_SOURCE_DIR}/Shaders/${FILE_NAME}.spv")
  add_custom_command( 
    OUTPUT ${SPIRV}
    COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
    DEPENDS ${GLSL})
  list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
    Shaders
    DEPENDS ${SPIRV_BINARY_FILES}
)


# Enable AddressSanitizer and UndefinedBehaviorSanitizer.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined")
# Link with sanitizer runtime libraries.
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address,undefined")
# Set optimization and debugging flags.
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
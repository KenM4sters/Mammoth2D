include(../.env.cmake OPTIONAL RESULT_VARIABLE LOCAL_ENV)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)

add_library(${PROJECT_NAME} ${SOURCES})


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

target_include_directories(
  ${PROJECT_NAME} 
  PUBLIC ${PROJECT_SOURCE_DIR}/include/
  PUBLIC ${CMAKE_SOURCE_DIR}/src/
  PUBLIC ${CMAKE_SOURCE_DIR}/external/
  PUBLIC ${CMAKE_SOURCE_DIR}/external/Glad/include/
  PUBLIC ${Vulkan_INCLUDE_DIRS}
)

target_link_libraries(
  ${PROJECT_NAME}
  glfw 
  glad
  glm 
  ${Vulkan_LIBRARIES}
)


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
  "${PROJECT_SOURCE_DIR}/resources/*.frag"
  "${PROJECT_SOURCE_DIR}/resources/*.vert"
)

foreach(GLSL ${GLSL_SOURCE_FILES})
  get_filename_component(FILE_NAME ${GLSL} NAME)
  message(STATUS "Found shader file at ${FILE_NAME}")
  set(SPIRV "${PROJECT_SOURCE_DIR}/resources/${FILE_NAME}.spv")
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
# Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined")
# Link with sanitizer runtime libraries.
# Set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address,undefined")
# Set optimization and debugging flags.
# Set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")


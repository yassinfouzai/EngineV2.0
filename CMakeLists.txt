cmake_minimum_required(VERSION 3.15)
project(EngineV2.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Source files
set(SRC_FILES
    src/main.cpp
    src/glad.c
    Engine/Core/Timer.cpp
    Engine/Platform/Window.cpp
    Engine/Core/Input.cpp
)

# Executable target
add_executable(EngineV2 ${SRC_FILES})

# Rename output to EngineV2.0
set_target_properties(EngineV2 PROPERTIES
    OUTPUT_NAME "EngineV2.0"
)

# Include paths for engine headers, GLAD, GLFW
target_include_directories(EngineV2 PRIVATE
    ${CMAKE_SOURCE_DIR}                        # so Engine/Core/Logger.h works
    ${CMAKE_SOURCE_DIR}/ThirdParty/glad/include
    ${CMAKE_SOURCE_DIR}/ThirdParty/glfw/include
)

# Prevent GLFW from including system GL headers
target_compile_definitions(EngineV2 PRIVATE GLFW_INCLUDE_NONE)

# Build GLFW
add_subdirectory(ThirdParty/glfw)

# Link libraries
target_link_libraries(EngineV2
    PRIVATE
      glfw
      dl
      pthread
)


cmake_minimum_required(VERSION 3.15)
project(EngineV2.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include third-party GLAD & GLFW
add_subdirectory(ThirdParty/glfw)

# Source files
set(SRC_FILES
    src/main.cpp
    src/glad.c

    Engine/Core/Timer.cpp
    Engine/Core/Input.cpp
    Engine/Platform/Window.cpp
    Engine/Renderer/Renderer.cpp
    Engine/Renderer/Shader.cpp
)

# Executable target
add_executable(EngineV2 ${SRC_FILES})

# Set output binary name
set_target_properties(EngineV2 PROPERTIES OUTPUT_NAME "EngineV2.0")

# Include directories
target_include_directories(EngineV2 PRIVATE
    ${CMAKE_SOURCE_DIR} 
    ${CMAKE_SOURCE_DIR}/ThirdParty/glad/include
    ${CMAKE_SOURCE_DIR}/ThirdParty/glfw/include
)

# Prevent GLFW from including system GL headers
target_compile_definitions(EngineV2 PRIVATE GLFW_INCLUDE_NONE)

# Link required libraries
target_link_libraries(EngineV2
    PRIVATE
        glfw
        dl
        pthread
)

# Copy shaders into the bin directory after build
add_custom_command(TARGET EngineV2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Shaders ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Shaders
)

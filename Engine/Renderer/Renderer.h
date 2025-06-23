#pragma once

#include <GLFW/glfw3.h>

namespace Renderer {
    void Init();
    void Draw();
    void Shutdown();
    void framebuffer_size_callback(GLFWwindow* win, int w, int h);
}


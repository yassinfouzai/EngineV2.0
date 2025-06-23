#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
    bool Init(int width, int height, const char* title);
    void PollEvents();
    void SwapBuffers();
    bool ShouldClose();
    void Shutdown();
    GLFWwindow* GetNativeWindow();
private:
    GLFWwindow* window = nullptr;
};

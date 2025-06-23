#include "Engine/Core/Input.h"

GLFWwindow* Input::s_Window = nullptr;
float Input::s_ScrollX = 0.0f;
float Input::s_ScrollY = 0.0f;

void Input::Init(GLFWwindow* window) {
    s_Window = window;
    glfwSetScrollCallback(window, ScrollCallback);
}

bool Input::IsKeyPressed(int key) {
    return glfwGetKey(s_Window, key) == GLFW_PRESS;
}

bool Input::IsMouseButtonPressed(int button) {
    return glfwGetMouseButton(s_Window, button) == GLFW_PRESS;
}

void Input::GetMousePosition(double& x, double& y) {
    glfwGetCursorPos(s_Window, &x, &y);
}

double Input::GetMouseX() {
    double x, y;
    glfwGetCursorPos(s_Window, &x, &y);
    return x;
}

double Input::GetMouseY() {
    double x, y;
    glfwGetCursorPos(s_Window, &x, &y);
    return y;
}

void Input::DisableCursor() {
    glfwSetInputMode(s_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Input::EnableCursor() {
    glfwSetInputMode(s_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Input::SetCursorMode(int mode) {
    glfwSetInputMode(s_Window, GLFW_CURSOR, mode);
}

float Input::GetScrollX() {
    return s_ScrollX;
}

float Input::GetScrollY() {
    return s_ScrollY;
}

void Input::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    s_ScrollX = static_cast<float>(xoffset);
    s_ScrollY = static_cast<float>(yoffset);
}

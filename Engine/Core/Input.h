#pragma once
#include <GLFW/glfw3.h>

class Input {
public:
    static void Init(GLFWwindow* window);

    static bool IsKeyPressed(int key);
    static bool IsMouseButtonPressed(int button);
    static void GetMousePosition(double& x, double& y);
    static double GetMouseX();
    static double GetMouseY();

    static void DisableCursor();
    static void EnableCursor();

    static float GetScrollX();
    static float GetScrollY();

    static void SetCursorMode(int mode);

private:
    static GLFWwindow* s_Window;
    static float s_ScrollX, s_ScrollY;

    static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};

#include "Engine/Core/Logger.h"
#include "Engine/Core/Timer.h"
#include "Engine/Platform/Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>  // Needed for input constants like GLFW_KEY_ESCAPE

int main() {
    Window window;

    if (!window.Init(800, 600, "Engine Core")) {
        LOG_ERROR("Failed to initialize window");
        return -1;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERROR("Failed to initialize GLAD");
        return -1;
    }

    LOG_INFO("Window and OpenGL initialized");
    LOG_INFO("OpenGL version: " << glGetString(GL_VERSION));

    Timer timer;

    while (!window.ShouldClose()) {
        float deltaTime = timer.GetDeltaTime();

        if (glfwGetKey(window.GetNativeWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            break;
        }

        // Render
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        window.SwapBuffers();
        window.PollEvents();
    }

    window.Shutdown();
    return 0;
}


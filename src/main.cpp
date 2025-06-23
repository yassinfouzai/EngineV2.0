#include "Engine/Core/Logger.h"
#include "Engine/Core/Timer.h"
#include "Engine/Platform/Window.h"
#include "Engine/Core/Input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

    // Initialize Input system with the window
    Input::Init(window.GetNativeWindow());

    LOG_INFO("Window and OpenGL initialized");
    LOG_INFO("OpenGL version: {}" << reinterpret_cast<const char*>(glGetString(GL_VERSION)));

    Timer timer;

    while (!window.ShouldClose()) {
        float deltaTime = timer.GetDeltaTime();

        // Input Handling
        if (Input::IsKeyPressed(GLFW_KEY_TAB)) {
            Input::DisableCursor();
        }

        if (Input::IsKeyPressed(GLFW_KEY_ENTER)) {
            Input::EnableCursor();
        }

        if (Input::IsKeyPressed(GLFW_KEY_ESCAPE)) {
            break;
        }

        if (Input::GetScrollY() != 0.0f) {
            LOG_INFO("Scroll Y: {}" << Input::GetScrollY());
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


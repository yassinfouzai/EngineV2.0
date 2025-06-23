#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Core/Logger.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Internal state
static unsigned int VAO = 0, VBO = 0;
static Shader* shader = nullptr;

static void SetupGL();
static void LoadShaders();
static void SetupTriangle();

void Renderer::Init() {
    LOG_INFO("Initializing Renderer");
    SetupGL();
    LoadShaders();
    SetupTriangle();
    LOG_INFO("Renderer initialized");
}

void Renderer::Draw() {
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void Renderer::Shutdown() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    delete shader;

    LOG_INFO("Renderer shutdown");
}

void Renderer::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // Adjust the OpenGL viewport when the window size changes
    glViewport(0, 0, width, height);
}

// ------------------ Internal functions ------------------

static void SetupGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

static void LoadShaders() {
    shader = new Shader("/home/neo/GitHub/EngineV2.0/Shaders/basic.vs","/home/neo/GitHub/EngineV2.0/Shaders/basic.fs");
}

static void SetupTriangle() {
    float vertices[] = {
         0.0f,  0.5f, 0.0f,  // top
        -0.5f, -0.5f, 0.0f,  // left
         0.5f, -0.5f, 0.0f   // right
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}


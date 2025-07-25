#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <glad/glad.h>
#include <glfw3.h>
#include "glm/glm.hpp"
#include "Game.hpp"
#include "Shader.hpp"
#include "utils.h"
#include "nmath.h"
#include <vector>
#include <stdint.h>

typedef unsigned int uint;
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;
typedef float real32;

// FUNCTIONALITY LIST
// COLLISION
// MEMORY LAYOUT
// AUDIO
// HEX ADJACENCY
// UI
// MATH LIBRARY

#define Assert(Expression) if(!(Expression)) {*(int *)0 = 0;}

Game Breakout;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }

    Breakout.SetKey(key, action);
}

int main(void)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Learn OpenGL", NULL, NULL);
    if(!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float deltaTime = 0.f;
    float lastFrame = 0.f;
    float currentFrame = 0.f;

    Breakout.Init(SCREEN_WIDTH, SCREEN_HEIGHT);

    while(!glfwWindowShouldClose(window))
    {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();
        Breakout.ProcessInput(deltaTime);

        Breakout.Update(deltaTime);
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        Breakout.Render(deltaTime);
        glfwSwapBuffers(window);

        lastFrame = currentFrame;
    }

    glfwTerminate();
    return 0;
}

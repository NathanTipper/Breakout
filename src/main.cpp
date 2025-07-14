#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <glad/glad.h>
#include <glfw3.h>
#include "Game.hpp"
#include "Texture2D.h"
#include "assimp/material.h"
#include "glm/detail/qualifier.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/geometric.hpp"
#include "glm/matrix.hpp"
#include "glm/trigonometric.hpp"
#include "shader.h"


#include "utils.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "nmath.h"

// Model loading using assimp
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <vector>
#include <stdint.h>
#include "sprite.h"

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
typedef bool (check_state_func)();

check_state_func IsComplete;
#define LEVEL_COMPLETE_FUNC(lvl_name) bool lvl_name

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
    if(key >= 0 && key < 1024)
    {
        Breakout.keys[key] = action;
    }
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

    game_initialize(&Breakout, SCREEN_WIDTH, SCREEN_HEIGHT);

    ShaderProgram sprite_sp;
    shader_init(&sprite_sp);
    shader_set_source(&sprite_sp, SHADERTYPE_VERTEX, (char*)"..\\shaders\\shader.vert");
    shader_set_source(&sprite_sp, SHADERTYPE_FRAGMENT, (char*)"..\\shaders\\shader.frag");
    shader_load(&sprite_sp);
    if(!shader_link(&sprite_sp))
    {
        return 0;
    }
    shader_use(&sprite_sp);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glm::mat4 projection = glm::ortho(0.f, 800.f, 600.f, 0.f, -1.f, 1.f);
    shader_set_int(&sprite_sp, (char*)"image", 0);
    shader_set_matrix(&sprite_sp, (char*)"projection", glm::value_ptr(projection));

    game_set_sprite_shader(&Breakout, &sprite_sp);
    game_add_sprite(&Breakout, "face", glm::vec2(200.f, 200.f), glm::vec2(300.f, 400.f), glm::vec3(0.f, 1.f, 0.f), 45.f);
    float deltaTime = 0.f;
    float lastFrame = 0.f;
    float currentFrame = 0.f;

    while(!glfwWindowShouldClose(window))
    {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        game_process_input(&Breakout, deltaTime);

        game_update(&Breakout, deltaTime);

        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        game_render(&Breakout);
        glfwSwapBuffers(window);

        lastFrame = currentFrame;
    }

    glfwTerminate();
    return 0;
}

// TODO: Keeping this code in case I want to re-visit math stuff in OpenGL
    // TESTS
#if TESTS_ENABLED
    printf("\n***** TESTS *****\n");
    Vector2D testVector = {3, 4};
    float test_length = Length(testVector);
    printf("\nLength of vector { %.2f, %.2f } = %.2f\n", testVector.x, testVector.y, test_length);

    Vector2D testVectorB = { 4.f, 8.f };
    float test_dot = Dot_2D(testVector, testVectorB);
    printf("\n{ %.2f, %.2f } dot { %.2f, %.2f } = %.2f\n", 
           testVector.x, testVector.y, 
           testVectorB.x, testVectorB.y,
           test_dot);

    Vector2D testVectorC = testVector - testVectorB;
    printf("\nResult of vector { %.2f, %.2f } - { %.2f, %.2f } = { %.2f, %.2f }\n", 
           testVector.x, testVector.y, 
           testVectorB.x, testVectorB.y,
           testVectorC.x, testVectorC.y) ;

    testVectorC = testVector + testVectorB;
    printf("\nResult of vector { %.2f, %.2f } + { %.2f, %.2f } = { %.2f, %.2f }\n", 
           testVector.x, testVector.y, 
           testVectorB.x, testVectorB.y,
           testVectorC.x, testVectorC.y) ;

    Vector2D testVectorD = { 1.f, 0.f };
    Vector2D testVectorE = { 0.70710f, 0.70710f };
    printf("\ncos of vectors { %.2f, %.2f } & { %.2f, %.2f } = %.2f\n",
           testVectorD.x, testVectorD.y, 
           testVectorE.x, testVectorE.y,
           ncos(testVectorD, testVectorE)) ;

    printf("\n**** END TESTS *****\n");
    Vector2D pos = { -3, 4 };
    Vector2D forward = { 5, -2 };

    float points[] = {
        0.f, 0.f, 0.f,
        1.f, 6.f, 0.f,
        -6.f, 0.f, 0.f,
        -4.f, 7.f, 0.f,
        5.f, 5.f, 0.f,
        -3.f, 0.f, 0.f,
        -6.f, -3.5f, 0.f
    };

#define NUMBER_OF_VECTORS 7
    float posToPointVectors[NUMBER_OF_VECTORS * 2];
    for(int i = 0; i < NUMBER_OF_VECTORS; ++i)
    {
        Vector2D currentPoint = { points[i * 3], points[(i * 3) + 1] };
        Vector2D posToPointVec = currentPoint - pos;
        posToPointVectors[i * 3] = posToPointVec.x / 800.f;
        posToPointVectors[i * 3 + 1] = posToPointVec.y / 600.f;
        posToPointVectors[i * 3 + 2] = 0.f;
        points[i * 3] = points[i * 3] / 800.f;
        points[i * 3 + 1] = points[i * 3 + 1] / 600.f;
    }

    int is_in_front[NUMBER_OF_VECTORS];
    for(int i = 0; i < NUMBER_OF_VECTORS; ++i)
    {
        is_in_front[i] = Dot_2D(forward, { posToPointVectors[i * 3], posToPointVectors[i * 3 + 1] }) > 0.f;
    }

    uint PointsArray, PointsBuffer;
    glGenVertexArrays(1, &PointsArray);
    glGenBuffers(1, &PointsBuffer);

    glBindVertexArray(PointsArray);
    glBindBuffer(GL_ARRAY_BUFFER, PointsBuffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    uint VectorArray, VectorBuffer;
    glGenVertexArrays(1, &VectorArray);
    glGenBuffers(1, &VectorBuffer);

    glBindVertexArray(VectorArray);
    glBindBuffer(GL_ARRAY_BUFFER, VectorBuffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(posToPointVectors), posToPointVectors, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
#endif

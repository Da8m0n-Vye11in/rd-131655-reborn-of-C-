// Main program: initializes GLFW/GLAD, creates level and renderer, runs main loop
#include "com_mojang/rubydung/Main.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    (void)argc; (void)argv;

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1024, 768, "rd_reborn_c", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create window\n");
        glfwTerminate();
        return 2;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return 3;
    }

    // Simple GL setup similar to original
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.5f, 0.8f, 1.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // Create level and renderer
    Level* level = Level_new(256, 256, 64);
    if (!level) {
        fprintf(stderr, "Failed to create level\n");
        return 4;
    }

    LevelRenderer* lr = LevelRenderer_new(level);
    if (!lr) {
        fprintf(stderr, "Failed to create level renderer\n");
        return 5;
    }

    Player* player = Player_new(level);

    // Load texture
    char texturePath[512];
    snprintf(texturePath, sizeof(texturePath), "%s/resources/terrain.png", glfwGetExecutablePath ? "." : ".");
    Textures_init();
    int tex = Textures_loadTexture("resources/terrain.png", GL_NEAREST);
    (void)tex;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Simple input handling
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;

        LevelRenderer_render(lr, 0);
        LevelRenderer_render(lr, 1);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    Player_free(player);
    LevelRenderer_free(lr);
    Level_free(level);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

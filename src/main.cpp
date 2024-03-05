#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ShaderClass.hpp"
#include "Entity.hpp"

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stb_image.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//CFG???
Entity player{-0.9f, 0.0f, 0.05f, 0.6f};
Entity enemy{0.9f, 0.0f, 0.05f, 0.6f};
Entity ball = Entity(0.0f, 0.0f, 0.1f, 0.17f);
float platformMs = 0.015f;
float ballMs = 0.01;

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Fuck me", NULL, NULL);
    if (!window) {
        std::cout << "Failed to initialize GLFW\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Callback funcs
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {

        processInput(window);
        
        glClearColor(0.2, 0.3, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        player.draw();
        enemy.draw();
        ball.draw();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void playerMovement(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && player.y + player.height/2 <= 1.0) {
        player.y += platformMs;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && player.y - player.height/2 >= -1.0) {
        player.y -= platformMs;
    }
}

void hacks(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        player.height += platformMs;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && player.height >= 0.6) {
        player.height -= platformMs;
    }
}

void ballMovement() { 
    bool start;
}

void enemyMovement() {
    if (enemy.y < ball.y) {
        enemy.y += platformMs;
    }
    if (enemy.y > ball.y) {
        enemy.y -= platformMs;
    }
}

void processInput(GLFWwindow* window) { 
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    playerMovement(window);
    hacks(window);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
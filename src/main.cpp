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

#define M_PI 3.14159265358979323846

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//CFG???
float platformMs = 0.015f;
float ballMsX = -0.01;
float ballMsY = 0.01;

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

    Shader myShader{"shaders/vert.vs", "shaders/frag.fs"};
    Entity player{-0.9f, 0.0f, 0.05f, 0.6f, myShader};
    Entity enemy{0.9f, 0.0f, 0.05f, 0.6f, myShader};
    Entity ball{0.0f, 0.0f, 0.1f, 0.17f, myShader};

    while (!glfwWindowShouldClose(window)) {
        
        glClearColor(0.2, 0.3, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        //Enemy update
        if (enemy.y < ball.y) {
            enemy.y += platformMs;
        }
        if (enemy.y > ball.y) {
            enemy.y -= platformMs;
        }
        myShader.setV2("Move", glm::vec2(0.0f, enemy.y));
        enemy.draw();

        // Ball update
        // Ball vars
        ball.x += ballMsX;
        ball.y += ballMsY;
        bool hit = false;

        if (ball.y-ball.height <= -1.1f or ball.y+ball.height >= 1.1f) {
            ballMsY *= -1;
        }

        if (ball.x < -0.99f or ball.x > 0.99f) {
            float platformMs = 0.015f;
            ballMsX = -0.01;
            ballMsY = 0.01;
            ball.x = 0.0f;
            ball.y = 0.0f;
        }

        float diffX, diffY;
        diffX = abs(ball.x - enemy.x);
        diffY = abs(ball.y - enemy.y);

        if (diffX <= enemy.width / 2 + ball.width / 2 && diffY <= enemy.height / 2) {
            std::cout << "SEX\n";
            ballMsX *= -1;
        } else if (diffY <= enemy.height / 2 + ball.height / 2 && diffX <= enemy.width / 2) {
            ballMsY *= -1;
        } else if (pow(diffX - enemy.width / 2, 2) + pow(diffY - enemy.height / 2, 2) <= ball.height/3) {
            ballMsX *= -1;
            ballMsY *= -1;
        }

        diffX = abs(ball.x - player.x);
        diffY = abs(ball.y - player.y);

        if (diffX <= player.width/2 + ball.width/2 && diffY <= player.height/2) {
            ballMsX *= -1;
        } else if (diffY <= player.height/2 + ball.height/2 && diffX <= player.width/2) {
            ballMsY *= -1;
        } else if (pow(diffX - player.width / 2, 2) + pow(diffY - player.height/2, 2) <= ball.height/3) {
            ballMsX *= -1;
            ballMsY *= -1;
        }

        myShader.setV2("Move", glm::vec2(ball.x, ball.y));
        ball.draw();

        // Player update
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS &&
            player.y + player.height / 2 <= 1.0) {
            player.y += platformMs;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS &&
            player.y - player.height / 2 >= -1.0) {
            player.y -= platformMs;
        }
        myShader.setV2("Move", glm::vec2(0.0f, player.y));
        player.draw();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            float platformMs = 0.015f;
            ballMsX = -0.01;
            ballMsY = 0.01;
            ball.x = 0.0f;
            ball.y = 0.0f;
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
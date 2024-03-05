#pragma once
#include "ShaderClass.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stb_image.h>

class Entity {
   public:
    float x;
    float y;
    float width; //Normalized
    float height; //Normalized
    unsigned int VAO;
    Shader shader;
    float vertex[];

    Entity(float xCoord, float yCoord, float width, float height, Shader shader)
        : x{xCoord}, y{yCoord}, width{width}, height{height}, shader{shader}
    {
        float vertex[] = {
            x - (width) / 2, y + (height) / 2,
            x - (width) / 2, y - (height) / 2,
            x + (width) / 2, y - (height) / 2,
            x + (width) / 2, y - (height) / 2,
            x + (width) / 2, y + (height) / 2,
            x - (width) / 2, y + (height) / 2,
        };

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

        // Attributes
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);
    }

    void draw() {
        shader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
};
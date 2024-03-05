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
    

    Entity(float xCoord, float yCoord, float width, float height)
        : x{xCoord},
          y{yCoord},
          width{width},
          height{height} {
        float vertex[] = {
            x - (width) / 2, y + (height) / 2, 0.0,
            x - (width) / 2, y - (height) / 2, 0.0,
            x + (width) / 2, y - (height) / 2, 0.0,
            x + (width) / 2, y - (height) / 2, 0.0,
            x + (width) / 2, y + (height) / 2, 0.0,
            x - (width) / 2, y + (height) / 2, 0.0,
        };

        glGenBuffers(1, &VAO);

        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

        // Attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    void draw() {
        Shader shader = Shader("shaders/vert.vs", "shaders/frag.fs");
        shader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
};
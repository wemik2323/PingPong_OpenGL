#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 Color;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    Color = vec3(1.0f, 0.7f, 0.0f);
}

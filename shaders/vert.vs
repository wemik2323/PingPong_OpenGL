#version 330 core
layout (location = 0) in vec2 aPos;

out vec3 Color;

uniform vec2 Move;

void main()
{
    gl_Position = vec4(aPos + Move, 0.0, 1.0);
    Color = vec3(1.0f, 0.7f, 0.0f);
}

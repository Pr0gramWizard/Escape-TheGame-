#version 330 core

in vec3 out_Color;

out vec4 color;

void main()
{
    color = vec4(out_Color, 1.0);
}
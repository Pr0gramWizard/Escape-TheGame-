#version 330 core

in vec3 position;

out vec3 out_Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    out_Color = vec3(0.66f , 0.66f, 0.66f);
}
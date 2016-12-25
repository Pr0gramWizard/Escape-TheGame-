#version 330 core

in vec3 position;

out vec3 out_Color;

uniform mat4 transformationMatrix;
//uniform mat4 projectionMatrix;

void main()
{
    gl_Position = transformationMatrix * vec4(position, 1.0f);
    out_Color = vec3(position.x +0.5 , 1.0, position.y + 0.5);
}
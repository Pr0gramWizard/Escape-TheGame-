#version 330 core

in vec2 TexCoords;
in vec3 viewPos;
in vec3 fragPos;

out vec4 color;

uniform sampler2D texture;


void main()
{    

    color = texture2D(texture, TexCoords);
}
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
out vec3 out_Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
	float test = position.y;
	test /= 20.0;
	test += 1.0;
	test /= 2.0;
    out_Color = vec3(0.8 , test , 0.2);
}
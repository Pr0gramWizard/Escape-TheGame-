#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec2 TexCoords;
out float visibility;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

const float density = 0.01;
const float gradient = 1.5;

void main()
{
	vec4 worldPosition = vec4(position, 1.0f);
    gl_Position = projection * view * worldPosition;
    TexCoords = texCoords;

	float distance = length((view * worldPosition).xyz);
	visibility = exp(-pow((distance * density), gradient));
	visibility = clamp(visibility, 0.0, 1.0);
}
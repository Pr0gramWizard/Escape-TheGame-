#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec2 TexCoords;
out float visibility;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float fogDensity;
uniform float fogGradient;

void main()
{
	vec4 worldPosition = vec4(position, 1.0f);
    gl_Position = projection * view * worldPosition;
    TexCoords = texCoords;

	float distance = length((view * worldPosition).xyz);
	visibility = exp(-pow((distance * fogDensity), fogGradient));
	visibility = clamp(visibility, 0.0, 1.0);
}
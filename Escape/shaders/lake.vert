#version 330 core
layout (location = 0) in vec3 position;

out vec4 clipSpace;
out vec3 toCameraVector;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 worldPosition = vec4(position, 1.0f);
	clipSpace = projection * view * model * worldPosition;
	toCameraVector = (inverse(view) * vec4(0.0,0.0,0.0,1.0)).xyz - worldPosition.xyz;
    gl_Position = clipSpace;
}
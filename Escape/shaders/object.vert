#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec2 TexCoords;
out vec3 viewPos;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 worldPosition = vec4(position, 1.0f);
    gl_Position = projection * view * worldPosition;
    TexCoords = texCoords;

	viewPos = (inverse(view) * vec4(0.0,0.0,0.0,1.0)).xyz;
    fragPos = vec3(worldPosition);
}
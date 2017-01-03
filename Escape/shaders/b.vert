#version 330 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec4 plane;

void main()
{
	vec4 worldPosition = model * vec4(position, 1.0f);

	gl_ClipDistance[0] = dot(worldPosition, plane);

    gl_Position = projection * view * worldPosition;
    TexCoord = texCoord;
}
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 surfaceNormal;
out vec3 toLightVector[6];
out vec3 toCameraVector;

out vec3 viewPos;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec4 plane;

void main()
{
	vec4 worldPosition = model * vec4(position,1.0);
	gl_ClipDistance[0] = dot(worldPosition, plane);

    gl_Position = projection * view * worldPosition;
	
	surfaceNormal = mat3(transpose(inverse(model))) * normal;
	viewPos = (inverse(view) * vec4(0.0,0.0,0.0,1.0)).xyz;

    fragPos = vec3(worldPosition);
	
}
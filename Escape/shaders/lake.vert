#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec4 clipSpace;
out vec3 toCameraVector;
out vec3 fromLightVector;

out vec3 lakeNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

const vec3 lightPosition = vec3(0.0, 2.0, 0.0);

void main()
{
	vec4 worldPosition = vec4(position, 1.0f);
	clipSpace = projection * view * model * worldPosition;
	toCameraVector = (inverse(view) * vec4(0.0,0.0,0.0,1.0)).xyz - worldPosition.xyz;
	fromLightVector =  worldPosition.xyz - lightPosition;
	lakeNormal = mat3(transpose(inverse(model))) * normal;
    gl_Position = clipSpace;
}
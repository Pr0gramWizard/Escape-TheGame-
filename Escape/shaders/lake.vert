#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec4 clipSpace;
out vec3 toCameraVector;
out vec3 fromLightVector[6];
out vec3 lakeNormal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPosition[6];

void main()
{
	vec4 worldPosition = vec4(position, 1.0f);
	clipSpace = projection * view * model * worldPosition;
	fragPos = vec3(worldPosition);
	toCameraVector = (inverse(view) * vec4(0.0,0.0,0.0,1.0)).xyz - worldPosition.xyz;
	for(int i = 0; i < 6; i++){
		fromLightVector[i] =  worldPosition.xyz - lightPosition[i];
	}
	lakeNormal = mat3(transpose(inverse(model))) * normal;
    gl_Position = clipSpace;
}
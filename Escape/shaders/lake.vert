#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec4 clipSpace;
out vec2 textureCoords;
out vec3 fromLightVector[4];
out vec3 lakeNormal;
out vec3 fragPos;
out vec3 viewPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPosition[4];
uniform float fogDensity;
uniform float fogGradient;

const float dudvTiling = 60.0;

void main()
{
	vec4 worldPosition = model * vec4(position, 1.0f);
	clipSpace = projection * view * worldPosition;
	fragPos = vec3(worldPosition);
	viewPos = (inverse(view) * vec4(0.0,0.0,0.0,1.0)).xyz;
	for(int i = 0; i < 4; i++){
		fromLightVector[i] =  worldPosition.xyz - lightPosition[i];
	}
	lakeNormal = mat3(transpose(inverse(model))) * normal;

	textureCoords = texCoords * dudvTiling;

    gl_Position = clipSpace;
}
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec2 textureCoords;
out vec3 fromLightVector[4];
out vec3 lavaNormal;
out vec3 fragPos;
out vec3 viewPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPosition[4];

const float dudvTiling = 5.0;

void main()
{
	vec3 newPosition = position;
	newPosition.y -= 0.25f;
	vec4 worldPosition = model * vec4(newPosition, 1.0f);
	fragPos = vec3(worldPosition);
	viewPos = (inverse(view) * vec4(0.0,0.0,0.0,1.0)).xyz;
	for(int i = 0; i < 4; i++){
		fromLightVector[i] =  worldPosition.xyz - lightPosition[i];
	}
	lavaNormal = mat3(transpose(inverse(model))) * normal;

	textureCoords = texCoords * dudvTiling;

    gl_Position = projection * view * worldPosition;
}
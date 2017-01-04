#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 surfaceNormal;
out vec3 toLightVector[6];
out vec3 toCameraVector;

out vec3 viewPos;
out vec3 FragPos;
//out vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec4 plane;

// 6 is MAX_LIGHTS
uniform vec3 lightPosition[6];

//uniform vec3 lightColor[6];
//uniform vec3 lightAttenuation[6];

void main()
{
	vec4 worldPosition = model * vec4(position,1.0);
	gl_ClipDistance[0] = dot(worldPosition, plane);

    gl_Position = projection * view * worldPosition;
	
	surfaceNormal = mat3(transpose(inverse(model))) * normal;
	viewPos = (inverse(view) * vec4(0.0,0.0,0.0,1.0)).xyz;

    FragPos = vec3(model * vec4(position, 1.0f));
	
}
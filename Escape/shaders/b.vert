#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out vec2 TexCoord;
out vec3 surfaceNormal;
out vec3 viewPos;
out vec3 fragPos;
out float visibility;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 plane;
uniform float fogDensity;
uniform float fogGradient;

void main()
{
	vec4 worldPosition = model * vec4(position, 1.0f);
	gl_ClipDistance[0] = dot(worldPosition, plane);

    TexCoord = texCoord;
	surfaceNormal = mat3(transpose(inverse(model))) * normal;
	viewPos = (inverse(view) * vec4(0.0,0.0,0.0,1.0)).xyz;
    fragPos = vec3(worldPosition);

	float distance = length((view * worldPosition).xyz);
	visibility = exp(-pow((distance * fogDensity), fogGradient));
	visibility = clamp(visibility, 0.0, 1.0);

	gl_Position = projection * view * worldPosition;
}
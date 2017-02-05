#version 330 core

layout (location = 0) in vec3 position;

out vec4 ParticleColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 worldPosition = model * vec4(position,1.0);
	gl_Position = projection * view * worldPosition;

	ParticleColor = vec4(1.0f,0.0f,0.0f,1.0f);
	
}
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out float AttenuationFactor;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 lightAttenuation;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
	//float test = position.y;
	//test /= 20.0;
	//test += 1.0;
	//test /= 2.0;
	//float distance = length(position - lightPosition);
	//float attenuationFactor = lightAttenuation.x + (lightAttenuation.y * distance) + (lightAttenuation.z * distance * distance);
	//out_Color = vec3(0.8 , test , 0.2) + lightColor;
    //out_Color = lightColor / attenuationFactor;
	//out_Color = normal;

	float distance = length(position - lightPosition);
	AttenuationFactor = lightAttenuation.x + (lightAttenuation.y * distance) + (lightAttenuation.z * distance * distance);
	FragPos = vec3(model * vec4(position, 1.0f));
    Normal = mat3(transpose(inverse(model))) * normal;
}
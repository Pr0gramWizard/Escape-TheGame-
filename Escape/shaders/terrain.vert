#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPosition;
//uniform vec3 lightColor;

void main()
{
	vec4 worldPosition = model * vec4(position,1.0);
    gl_Position = projection * view * worldPosition;
	
	//pass_textureCoordinates = textureCoordinates * 10.0;
	
	surfaceNormal = mat3(transpose(inverse(model))) * normal;
	toLightVector = lightPosition - worldPosition.xyz;
	toCameraVector = (inverse(view) * vec4(0.0,0.0,0.0,1.0)).xyz - worldPosition.xyz;
}

    //float test = position.y;
	//test /= 20.0;
	//test += 1.0;
	//test /= 2.0;
	//float distance = length(position - lightPosition);
	//float attenuationFactor = lightAttenuation.x + (lightAttenuation.y * distance) + (lightAttenuation.z * distance * distance);
	//out_Color = vec3(0.8 , test , 0.2) + lightColor;
    //out_Color = lightColor / attenuationFactor;
	//out_Color = normal;

	//FragPos = vec3(model * vec4(position, 1.0f));
    //Normal = mat3(transpose(inverse(model))) * normal;
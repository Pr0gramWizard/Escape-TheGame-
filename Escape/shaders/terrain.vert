#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 surfaceNormal;
out vec3 toLightVector[6];
out vec3 toCameraVector;

//out vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// 6 is MAX_LIGHTS
uniform vec3 lightPosition[6];

//uniform vec3 lightColor[6];
//uniform vec3 lightAttenuation[6];

void main()
{
	vec4 worldPosition = model * vec4(position,1.0);
    gl_Position = projection * view * worldPosition;
	
	//pass_textureCoordinates = textureCoordinates * 10.0;
	
	surfaceNormal = mat3(transpose(inverse(model))) * normal;
	for(int i = 0; i < 6; i++){
		toLightVector[i] = lightPosition[i] - worldPosition.xyz;
	}
	toCameraVector = (inverse(view) * vec4(0.0,0.0,0.0,1.0)).xyz - worldPosition.xyz;
	
	//works
	//float distance = length(mat3(model) * position - lightPosition[0]);
	//float attenuationFactor = lightAttenuation[0].x + (lightAttenuation[0].y * distance) + (lightAttenuation[0].z * distance * distance);
    //color = lightColor[0] / attenuationFactor;
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
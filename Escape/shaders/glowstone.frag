#version 330 core

in vec2 TexCoords;
in vec3 viewPos;
in vec3 fragPos;
in vec3 surfaceNormal;

layout (location = 0) out vec4 color;
layout (location = 1) out vec4 BrightColor;

uniform sampler2D texture;

uniform vec3 lightPosition[6]; 
uniform vec3 lightColor[6];
uniform vec3 lightAttenuation[6];

uniform float fogDensity;
uniform float fogGradient;
uniform vec3 backgroundColor;


void main()
{    

	// Ambient
    float ambientStrength = 0.1f;
	vec3 result = vec3(0,0,0);

	for(int i = 0; i < 6; i++){
		if(lightPosition[i].x == 0 && lightPosition[i].y == 0 && lightPosition[i].z == 0)
		{
			continue;
		}
		vec3 ambient = ambientStrength * lightColor[i];
  	
		// Diffuse 
		vec3 norm = normalize(surfaceNormal);
		vec3 lightDir = normalize(lightPosition[i] - fragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * lightColor[i];
	
		// Specular
		float specularStrength = 0.5f;
		vec3 viewDir = normalize(viewPos - fragPos);
		vec3 reflectDir = reflect(-lightDir, norm);  
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		vec3 specular = specularStrength * spec * lightColor[i];  

		float distance = length(fragPos - lightPosition[i]);
		float attenuationFactor = lightAttenuation[i].x + (lightAttenuation[i].y * distance) + (lightAttenuation[i].z * distance * distance);
		
		result += (ambient + diffuse + specular)/(attenuationFactor);
    }

	float distance = length(viewPos - fragPos);
	float visibility = exp(-pow((distance * fogDensity), fogGradient));
	visibility = clamp(visibility, 0.0, 1.0);

    color = vec4(result, 1.0) * texture2D(texture, TexCoords);

	color = mix(vec4(backgroundColor, 1.0) , color, visibility);

	float brightness = dot(color.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        BrightColor = vec4(color.rgb, 1.0);
}
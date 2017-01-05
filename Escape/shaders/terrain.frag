#version 330 core

out vec4 out_Color;

in vec3 surfaceNormal;
in vec3 toLightVector[6];
in vec3 toCameraVector;

in vec3 viewPos;
in vec3 FragPos;
smooth in vec2 vTexCoord;

//in vec3 color;
  
uniform vec3 lightPosition[6]; 
uniform vec3 lightColor[6];
uniform vec3 lightAttenuation[6];
uniform sampler2D gSampler[2];

void main()
{
	// Ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor[0];
  	
    // Diffuse 
    vec3 norm = normalize(surfaceNormal);
    vec3 lightDir = normalize(lightPosition[0] - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor[0];
    
    // Specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor[0];  

	float distance = length(FragPos - lightPosition[0]);
	float attenuationFactor = lightAttenuation[0].x + (lightAttenuation[0].y * distance) + (lightAttenuation[0].z * distance * distance);
        
    vec3 result = (ambient + (diffuse + specular)/attenuationFactor) * vec3(1,1,0);
    out_Color = vec4(result, 1.0f);
}
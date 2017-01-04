#version 330 core

out vec4 out_Color;

in vec3 surfaceNormal;
in vec3 toLightVector[6];
in vec3 toCameraVector;

in vec3 viewPos;
in vec3 fragPos;

//in vec3 color;
  
uniform vec3 lightPosition[6]; 
uniform vec3 lightColor[6];
uniform vec3 lightAttenuation[6];

const vec3 terrainColor = vec3(1,1,0);

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
		
		result += (ambient + diffuse + specular)/attenuationFactor;
    }

    out_Color = vec4(result * terrainColor, 1.0f);
}
#version 330 core

in vec2 TexCoord;
in vec3 surfaceNormal;
in vec3 viewPos;
in vec3 fragPos;

out vec4 out_Color;
  
uniform vec3 lightPosition[6]; 
uniform vec3 lightColor[6];
uniform vec3 lightAttenuation[6];
uniform float fogDensity;
uniform float fogGradient;
uniform vec3 backgroundColor;

uniform sampler2D ourTexture;

void main()
{
     vec4 textureColor = texture(ourTexture, TexCoord);

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

	float distance = length(viewPos - fragPos);
	float visibility = exp(-pow((distance * fogDensity), fogGradient));
	visibility = clamp(visibility, 0.0, 1.0);

    out_Color = vec4(result * vec3(textureColor), 1.0f);
	out_Color = mix(vec4(backgroundColor, 1.0) , out_Color, visibility);
}
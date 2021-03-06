#version 330 core

in vec3 surfaceNormal;
in vec3 viewPos;
in vec3 fragPos;
in vec2 TexCoord;

out vec4 out_Color;
  
uniform vec3 lightPosition[4]; 
uniform vec3 lightColor[4];
uniform vec3 lightAttenuation[4];
uniform vec3 backgroundColor;
uniform bool playerBelowLake;

uniform sampler2D grass;
uniform sampler2D stone;
uniform sampler2D flower;
uniform sampler2D mud;
uniform sampler2D blendMap;

void main()
{

	vec4 blendMapColor = texture(blendMap,TexCoord);

	float backTextureAmount = 1 - (blendMapColor.r + blendMapColor.g + blendMapColor.b);
	vec2 tiledCoords = TexCoord * 50;
	vec4 backgroundTextureColor = texture(grass, tiledCoords) * backTextureAmount;
	vec4 rTextureColor = texture(mud, tiledCoords) * blendMapColor.r;
	vec4 gTextureColor = texture(flower, tiledCoords) * blendMapColor.g;
	vec4 bTextureColor = texture(stone, tiledCoords) * blendMapColor.b;

	vec4 totalColor = backgroundTextureColor + rTextureColor + gTextureColor + bTextureColor;
		
	// Ambient
    float ambientStrength = 0.1f;
	vec3 result = vec3(0,0,0);

	for(int i = 0; i < 4; i++){
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

    out_Color = vec4(result,1.0) * totalColor;
	out_Color = mix(vec4(backgroundColor, 1.0) , out_Color, 1.0);

}
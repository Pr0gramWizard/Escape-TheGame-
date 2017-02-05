#version 330 core

in vec3 surfaceNormal;
in vec3 viewPos;
in vec3 fragPos;
in vec2 TexCoord;

layout (location = 0) out vec4 out_Color;
layout (location = 1) out vec4 BrightColor;
  
uniform vec3 lightPosition[4]; 
uniform vec3 lightColor[4];
uniform vec3 lightAttenuation[4];
uniform float fogDensity;
uniform float fogGradient;
uniform vec3 backgroundColor;
uniform bool playerBelowLake;

uniform sampler2D BlueTex;
uniform samplerCube depthCubemap0;

const float far_plane = 25.0f;

// array of offset direction for sampling
vec3 gridSamplingDisk[20] = vec3[]
(
   vec3(1, 1, 1), vec3(1, -1, 1), vec3(-1, -1, 1), vec3(-1, 1, 1), 
   vec3(1, 1, -1), vec3(1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1, 0), vec3(1, -1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
   vec3(1, 0, 1), vec3(-1, 0, 1), vec3(1, 0, -1), vec3(-1, 0, -1),
   vec3(0, 1, 1), vec3(0, -1, 1), vec3(0, -1, -1), vec3(0, 1, -1)
);

float ShadowCalculation(vec3 fragToLight)
{
    // Get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);
    // Test for shadows with PCF
    float shadow = 0.0;
    float bias = 0.15;
    int samples = 20;
    float viewDistance = length(viewPos - fragPos);
    float diskRadius = (1.0 + (viewDistance / far_plane)) / 25.0;
    for(int i = 0; i < samples; ++i)
    {
        float closestDepth = texture(depthCubemap0, fragToLight + gridSamplingDisk[i] * diskRadius).r;
        closestDepth *= far_plane;   // Undo mapping [0;1]
        if(currentDepth - bias > closestDepth)
            shadow += 1.0;
    }
    shadow /= float(samples);
        
    // Display closestDepth as debug (to visualize depth cubemap)
    // FragColor = vec4(vec3(closestDepth / far_plane), 1.0);    
        
    // return shadow;
    return shadow;
}

void main()
{
		
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
		
		result += (1.0-ShadowCalculation(fragPos - lightPosition[i])) * (ambient + diffuse + specular)/attenuationFactor;
    }

	float distance = length(viewPos - fragPos);
	float visibility = exp(-pow((distance * fogDensity), fogGradient));
	visibility = clamp(visibility, 0.0, 1.0);

    // out_Color = vec4(result,1.0) * totalColor;
	// out_Color = mix(vec4(backgroundColor, 1.0) , out_Color, visibility);
	out_Color = vec4(result, 1.0) * texture2D(BlueTex, TexCoord);

	if(playerBelowLake){
		out_Color = mix(out_Color, vec4(0.0, 0.0, 1.0, 1.0), 0.2);
	}

	

	float brightness = dot(out_Color.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0){
		BrightColor = vec4(out_Color.rgb, 1.0);
	}
}
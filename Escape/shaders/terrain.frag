#version 330 core

out vec4 out_Color;

in vec3 surfaceNormal;
in vec3 toLightVector[6];
in vec3 toCameraVector;
  
//uniform vec3 lightPosition; 
uniform vec3 lightColor[6];
uniform vec3 lightAttenuation[6];

void main()
{
	float shineDamper = 1;
	float reflectivity = 0.1;
	vec3 terrainColor = vec3(1,1,1);

	// units
    vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitVectorToCamera = normalize(toCameraVector);

	// ambient
    //vec3 ambient = terrainColor * 0.02; //  to damp the ambient color

	vec3 totalDiffuse = vec3(0,0,0);
	vec3 totalSpec = vec3(0,0,0);

	for(int i = 0; i < 6; i++){
		vec3 unitLightVector = normalize(toLightVector[i]);

		// diffuse
		float nL = dot(unitNormal,unitLightVector);
		float brightness = max(nL,0.0);
		vec3 diffuse = brightness * lightColor[i];
	
		// specular
		vec3 lightDir = -unitLightVector;
		vec3 reflectedLightDir = reflect(lightDir,unitNormal);
		float specularFactor = dot(reflectedLightDir , unitVectorToCamera);
		specularFactor = max(specularFactor,0.0);
		float dampedFactor = pow(specularFactor,shineDamper);
		vec3 specular = dampedFactor * reflectivity * lightColor[i];

		float distance = length(toLightVector[i]);
		float attenuationFactor = lightAttenuation[i].x + (lightAttenuation[i].y * distance) + (lightAttenuation[i].z * distance * distance);
	
		totalDiffuse = totalDiffuse + diffuse/attenuationFactor;
		totalSpec = totalSpec + specular/attenuationFactor;
	}
	totalDiffuse = max(totalDiffuse, 0.3);
	
	out_Color =  vec4(totalDiffuse,1.0) * vec4(terrainColor,1.0) + vec4(totalSpec,1.0);
}
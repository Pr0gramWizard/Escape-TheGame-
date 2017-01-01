#version 330 core

out vec4 out_Color;

in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;
  
//uniform vec3 lightPosition; 
uniform vec3 lightColor;
uniform vec3 lightAttenuation;

void main()
{
	float shineDamper = 0.8;
	float reflectivity = 0.1;
	vec3 terrainColor = vec3(1,1,0);

	// units
    vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);
	
	// ambient
    vec3 ambient = terrainColor * 0.02; //  to damp the ambient color

	// diffuse
	float nL = dot(unitNormal,unitLightVector);
	float brightness = max(nL,0.1); // to prevent completely dark spots
	vec3 diffuse = brightness * lightColor;
	
	// specular
	vec3 unitVectorToCamera = normalize(toCameraVector);
	vec3 lightDir = -unitLightVector;
	vec3 reflectedLightDir = reflect(lightDir,unitNormal);
	
	float specularFactor = dot(reflectedLightDir , unitVectorToCamera);
	specularFactor = max(specularFactor,0.0);
	float dampedFactor = pow(specularFactor,shineDamper);
	vec3 specular = dampedFactor * reflectivity * lightColor;
	

	out_Color =  vec4(ambient,1.0) + vec4(diffuse,1.0) * vec4(terrainColor,0) + vec4(specular,1.0);
}
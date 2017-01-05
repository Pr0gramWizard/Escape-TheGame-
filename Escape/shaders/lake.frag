#version 330 core

in vec4 clipSpace;
in vec3 toCameraVector;
in vec3 fromLightVector[6];
in vec3 lakeNormal;
in vec3 fragPos;

out vec4 color;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D depthMap;
uniform vec3 lightColor[6];
uniform vec3 lightAttenuation[6];

const float refactiveExponent = 2.0;

const float shineDamper = 20.0;
const float reflectivity = 0.6;

void main()
{
	// normalized device coordinates
	vec2 ndc = (clipSpace.xy/clipSpace.w)/2.0 + 0.5;
	// texCoords
	vec2 reflectionTexCoords = vec2(ndc.x, -ndc.y);
	vec2 refractionTexCoords = vec2(ndc.x, ndc.y);

	// load as uniform!
	float near = 0.1;
	float far = 1000.0;

	float depth = texture(depthMap, refractionTexCoords).r;
	float floorDistance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));

	depth = gl_FragCoord.z;
	float lakeDistance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));
	float lakeDepth = floorDistance - lakeDistance;

	vec4 reflectColor = texture(reflectionTexture, reflectionTexCoords);
    vec4 refractColor = texture(refractionTexture, refractionTexCoords);

	vec3 viewVector = normalize(toCameraVector);
	float refractiveFactor = clamp(pow(dot(viewVector, lakeNormal), refactiveExponent), 0.0, 1.0);

	// specular highlights
	vec3 specularHighlights;
	for(int i = 0; i < 6; i++){
		// attenuation
		float distance = length(fromLightVector[i]);
		float attenuationFactor = lightAttenuation[i].x + (lightAttenuation[i].y * distance) + (lightAttenuation[i].z * distance * distance);
		
		vec3 reflectedLight = reflect(normalize(fromLightVector[i]), lakeNormal);
		float specular = max(dot(reflectedLight, viewVector), 0.0);
		specular = pow(specular, shineDamper);
		specularHighlights = specularHighlights + (lightColor[i] * specular * reflectivity * clamp(lakeDepth/2.0, 0.0, 1.0))/attenuationFactor;
	}

	color = mix(reflectColor, refractColor, refractiveFactor);
	color = mix(color, vec4(0,0,1,0), 0.2) + vec4(specularHighlights, 0.0);
	color.a = clamp(lakeDepth/2.0, 0.0, 1.0);
}
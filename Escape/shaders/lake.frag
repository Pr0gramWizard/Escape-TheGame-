#version 330 core

in vec4 clipSpace;
in vec2 textureCoords;
in vec3 fromLightVector[4];
in vec3 lakeNormal;
in vec3 fragPos;
in vec3 viewPos;

out vec4 color;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D depthMap;
uniform sampler2D dudvMap;
uniform sampler2D normalMap;
uniform float waterMoveFactor;
uniform vec3 lightColor[4];
uniform vec3 lightAttenuation[4];
uniform float fogDensity;
uniform float fogGradient;
uniform vec3 backgroundColor;
uniform float near;
uniform float far;

const float refactiveExponent = 2.0;
const float shineDamper = 20.0;
const float reflectivity = 0.6;
const float waveStrength = 0.02;

const float activateNormalMapping = 0.0;

void main()
{
	vec3 toCameraVector = viewPos - fragPos;
	// normalized device coordinates
	vec2 ndc = (clipSpace.xy/clipSpace.w)/2.0 + 0.5;
	// texCoords
	vec2 reflectionTexCoords = vec2(ndc.x, -ndc.y);
	vec2 refractionTexCoords = vec2(ndc.x, ndc.y);

	float depth = texture(depthMap, refractionTexCoords).r;
	float floorDistance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));

	depth = gl_FragCoord.z;
	float lakeDistance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));
	float lakeDepth = floorDistance - lakeDistance;

	vec2 distortedTexCoords = texture(dudvMap, vec2(textureCoords.x + waterMoveFactor, textureCoords.y)).rg*0.1;
	distortedTexCoords = textureCoords + vec2(distortedTexCoords.x, distortedTexCoords.y + waterMoveFactor);
	vec2 totalDistortion = (texture(dudvMap, distortedTexCoords).rg * 2.0 - 1.0) * waveStrength * clamp(lakeDepth/8.0, 0.0, 1.0);

	reflectionTexCoords += totalDistortion;
	reflectionTexCoords.x = clamp(reflectionTexCoords.x, 0.01, 0.999);
	reflectionTexCoords.y = clamp(reflectionTexCoords.y, -0.999, -0.01);

	refractionTexCoords += totalDistortion;
	refractionTexCoords = clamp(refractionTexCoords, 0.01, 0.999);

	vec4 reflectColor = texture(reflectionTexture, reflectionTexCoords);
    vec4 refractColor = texture(refractionTexture, refractionTexCoords);

	// calculate normal
	vec3 usedLakeNormal = lakeNormal;
	if(activateNormalMapping != 0.0 && lakeNormal.y >= 0.95){
		vec4 normalColor = texture(normalMap, distortedTexCoords);
		usedLakeNormal = vec3(normalColor.r * 2.0 - 1.0, normalColor.b, normalColor.g * 2.0 - 1.0);
	}

	vec3 viewVector = normalize(toCameraVector);
	float refractiveFactor = clamp(pow(dot(viewVector, usedLakeNormal), refactiveExponent), 0.0, 1.0);

	// specular highlights
	vec3 specularHighlights;

	for(int i = 0; i < 4; i++){
		// attenuation
		float distance = length(fromLightVector[i]);
		float attenuationFactor = lightAttenuation[i].x + (lightAttenuation[i].y * distance) + (lightAttenuation[i].z * distance * distance);

		//specular highlights
		vec3 reflectedLight = reflect(normalize(fromLightVector[i]), usedLakeNormal);
		float specular = max(dot(reflectedLight, viewVector), 0.0);
		specular = pow(specular, shineDamper);
		specularHighlights = specularHighlights + (lightColor[i] * specular * reflectivity * clamp(lakeDepth/8.0, 0.0, 1.0))/attenuationFactor;
	
	}

	float distance = length(toCameraVector);
	float visibility = exp(-pow((distance * fogDensity), fogGradient));
	visibility = clamp(visibility, 0.0, 1.0);

	color = mix(reflectColor, refractColor, refractiveFactor);
	color =  mix(color, vec4(0,0,1,0), 0.2) + vec4(specularHighlights, 0.0);
	color = mix(vec4(backgroundColor, 1.0) , color, visibility);
	color.a = clamp(lakeDepth/8.0, 0.0, 1.0);

	//color = vec4(1,0,0, 1);
}
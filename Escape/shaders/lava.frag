#version 330 core

in vec2 textureCoords;
in vec3 fromLightVector[6];
in vec3 lavaNormal;
in vec3 fragPos;
in vec3 viewPos;

layout (location = 0) out vec4 color;
layout (location = 1) out vec4 BrightColor;

uniform sampler2D lavaTexture;
uniform sampler2D dudvMap;
uniform float lavaMoveFactor;
uniform vec3 lightColor[6];
uniform vec3 lightAttenuation[6];
uniform float fogDensity;
uniform float fogGradient;
uniform vec3 backgroundColor;
uniform float near;
uniform float far;

const float refactiveExponent = 2.0;
const float shineDamper = 20.0;
const float reflectivity = 0.6;
const float waveStrength = 0.02;

void main()
{
	vec3 toCameraVector = viewPos - fragPos;

	vec2 distortedTexCoords = texture(dudvMap, vec2(textureCoords.x + lavaMoveFactor + 0.5, textureCoords.y)).rg*0.1;
	distortedTexCoords = textureCoords + vec2(distortedTexCoords.x, distortedTexCoords.y + lavaMoveFactor - 0.5);
	vec2 totalDistortion = (texture(dudvMap, distortedTexCoords).rg * 2.0 - 1.0) * waveStrength;

	vec3 viewVector = normalize(toCameraVector);

	// specular highlights
	vec3 specularHighlights;

	for(int i = 0; i < 6; i++){
		// attenuation
		float distance = length(fromLightVector[i]);
		float attenuationFactor = lightAttenuation[i].x + (lightAttenuation[i].y * distance) + (lightAttenuation[i].z * distance * distance);

		//specular highlights
		vec3 reflectedLight = reflect(normalize(fromLightVector[i]), lavaNormal);
		float specular = max(dot(reflectedLight, viewVector), 0.0);
		specular = pow(specular, shineDamper);
		specularHighlights = specularHighlights + (lightColor[i] * specular * reflectivity)/attenuationFactor;
	}

	float distance = length(toCameraVector);
	float visibility = exp(-pow((distance * fogDensity), fogGradient));
	visibility = clamp(visibility, 0.0, 1.0);

	//color = mix(reflectColor, refractColor, refractiveFactor);
	color =  texture(lavaTexture, totalDistortion) + vec4(specularHighlights, 0.0);
	color = mix(vec4(backgroundColor, 1.0) , color, visibility);

	float brightness = dot(color.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0){
		BrightColor = vec4(color.rgb, 1.0);
	}
}
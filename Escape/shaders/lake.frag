#version 330 core

in vec4 clipSpace;
in vec3 toCameraVector;
in vec3 fromLightVector;

out vec4 color;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;

const vec3 lakeNormal = vec3(0.0, 1.0, 0.0);
const float refactiveExponent = 2.0;

const vec3 lightColor = vec3(1.0,1.0,0.0);
const float shineDamper = 20.0;
const float reflectivity = 0.6;

void main()
{
	// normalized device coordinates
	vec2 ndc = (clipSpace.xy/clipSpace.w)/2.0 + 0.5;
	// texCoords
	vec2 reflectionTexCoords = vec2(ndc.x, -ndc.y);
	vec2 refractionTexCoords = vec2(ndc.x, ndc.y);

	vec4 reflectColor = texture(reflectionTexture, reflectionTexCoords);
    vec4 refractColor = texture(refractionTexture, refractionTexCoords);

	vec3 viewVector = normalize(toCameraVector);
	float refractiveFactor = pow(dot(viewVector, lakeNormal), refactiveExponent);

	// specular highlights
	vec3 reflectedLight = reflect(normalize(fromLightVector), lakeNormal);
	float specular = max(dot(reflectedLight, viewVector), 0.0);
	specular = pow(specular, shineDamper);
	vec3 specularHighlights = lightColor * specular * reflectivity;

	color = mix(reflectColor, refractColor, refractiveFactor);
	color = mix(color, vec4(0,0,1,0), 0.3) + vec4(specularHighlights, 0.0);
}
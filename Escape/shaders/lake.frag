#version 330 core

in vec4 clipSpace;
in vec3 toCameraVector;
in vec3 fromLightVector;

in vec3 lakeNormal;

out vec4 color;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D depthMap;

const float refactiveExponent = 2.0;

const vec3 lightColor = vec3(1.0,1.0,1.0);
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
	float refractiveFactor = pow(dot(viewVector, lakeNormal), refactiveExponent);

	// specular highlights
	vec3 reflectedLight = reflect(normalize(fromLightVector), lakeNormal);
	float specular = max(dot(reflectedLight, viewVector), 0.0);
	specular = pow(specular, shineDamper);
	vec3 specularHighlights = lightColor * specular * reflectivity * clamp(lakeDepth/2.0, 0.0, 1.0);

	color = mix(reflectColor, refractColor, refractiveFactor);
	color = mix(color, vec4(0,0,1,0), 0.2) + vec4(specularHighlights, 0.0);
	color.a = clamp(lakeDepth/2.0, 0.0, 1.0);
}
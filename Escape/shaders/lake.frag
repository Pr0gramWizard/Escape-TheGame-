#version 330 core

in vec4 clipSpace;
in vec3 toCameraVector;

out vec4 color;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;

const float refactiveExponent = 2.0;

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
	float refractiveFactor = pow(dot(viewVector, vec3(0.0, 1.0, 0.0)), refactiveExponent);

	color = mix(reflectColor, refractColor, refractiveFactor);
	color = mix(color, vec4(0,0,1,0), 0.3);
}
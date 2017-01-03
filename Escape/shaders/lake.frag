#version 330 core

in vec4 clipSpace;

out vec4 color;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;

void main()
{
	// normalized device coordinates
	vec2 ndc = (clipSpace.xy/clipSpace.w)/2.0 + 0.5;
	// texCoords
	vec2 reflectionTexCoords = vec2(ndc.x, -ndc.y);
	vec2 refractionTexCoords = vec2(ndc.x, ndc.y);

	vec4 reflectColor = texture(reflectionTexture, reflectionTexCoords);
    vec4 refractColor = texture(refractionTexture, refractionTexCoords);

	color = mix(reflectColor, refractColor, 0.5);
}
#version 330 core

in vec2 TexCoords;
in float visibility;

out vec4 color;

uniform sampler2D texture_diffuse1;

const vec3 skyColor = vec3(0.2f, 0.3f, 0.3f);

void main()
{    
    color = vec4(texture(texture_diffuse1, TexCoords));
	color = mix(vec4(skyColor, 1.0) , color, visibility);
}
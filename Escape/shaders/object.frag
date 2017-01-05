#version 330 core

in vec2 TexCoords;
in float visibility;

out vec4 color;

uniform sampler2D texture_diffuse1;
uniform vec3 backgroundColor;

void main()
{    
    color = vec4(texture(texture_diffuse1, TexCoords));
	color = mix(vec4(backgroundColor, 1.0) , color, visibility);
}
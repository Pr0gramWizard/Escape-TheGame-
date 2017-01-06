#version 330 core

in vec2 TexCoords;
in vec3 viewPos;
in vec3 fragPos;

out vec4 color;

uniform sampler2D texture_diffuse1;
uniform float fogDensity;
uniform float fogGradient;
uniform vec3 backgroundColor;

void main()
{    
	float distance = length(viewPos - fragPos);
	float visibility = exp(-pow((distance * fogDensity), fogGradient));
	visibility = clamp(visibility, 0.0, 1.0);
	
    color = vec4(texture(texture_diffuse1, TexCoords));
	color = mix(vec4(backgroundColor, 1.0) , color, visibility);
}
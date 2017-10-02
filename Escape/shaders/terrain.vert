#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 surfaceNormal;
out vec3 viewPos;
out vec3 fragPos;
out vec2 TexCoord;
out float rgbColor;

out VS_OUT {
    vec3 normal;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 plane;

void main()
{
	vec4 worldPosition = model * vec4(position.x,0.0,position.z,1.0);

	rgbColor = position.y;
	// gl_ClipDistance[0] = dot(worldPosition, plane);

	
	surfaceNormal = mat3(transpose(inverse(model))) * normal;
	
	vs_out.normal = normalize(vec3(projection * vec4(surfaceNormal * normal, 1.0)));

	viewPos = (inverse(view) * vec4(0.0,0.0,0.0,1.0)).xyz;
    fragPos = vec3(worldPosition);
	TexCoord = texCoords;
	gl_Position = projection * view * worldPosition;
	
}
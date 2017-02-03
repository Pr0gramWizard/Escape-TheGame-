#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec2 TexCoords;
out vec3 viewPos;
out vec3 fragPos;
out vec3 surfaceNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 plane;

void main()
{
	TexCoords = texCoords;
	vec4 worldPosition = model * vec4(position,1.0);
	gl_ClipDistance[0] = dot(worldPosition, plane);
    gl_Position = projection * view * worldPosition;

	// use inverted normal because light is inside ? -> not all objects
	surfaceNormal = mat3(transpose(inverse(model))) * (-normal);

	viewPos = (inverse(view) * vec4(0.0,0.0,0.0,1.0)).xyz;
    fragPos = vec3(worldPosition);
}
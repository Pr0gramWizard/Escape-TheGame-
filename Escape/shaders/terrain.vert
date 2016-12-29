#version 330 core

in vec3 position;

out vec3 out_Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
	float test = position.y;
	test /= 20.0;
	test += 1.0;
	test /= 2.0;
    out_Color = vec3(0.8 , test, 0.2);
}
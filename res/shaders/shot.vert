#version 330 core
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec2 vTexcoord;

out vec3 color;
out vec2 texcoord;

uniform vec4 time;
uniform mat4 transform;

void main()
{
	color = vColor;
	texcoord = vTexcoord;
	gl_Position = transform * vec4(vPos, 1.0);
};
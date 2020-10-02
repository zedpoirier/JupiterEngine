#version 330 core

layout(location = 0) in vec3 pos;

void main()
{
	vec3 pos.y += 0.5;
	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
};


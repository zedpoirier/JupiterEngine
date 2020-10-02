#version 330 core
layout(location = 0) in vec3 vPos;
out vec4 color;
uniform vec4 time;

void main()
{
	vec3 pos = vPos;
	//pos.x += sin(time.x) * 0.5;
	//pos.y += cos(time.x) * 0.5;
	gl_Position = vec4(pos, 1.0);
	color = vec4(pos, 1.0);
};
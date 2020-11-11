#version 330 core
in vec3 color;
in vec2 texcoord;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform int frame;
uniform vec4 time;
uniform vec4 reso;

void main()
{
    vec2 p = texcoord;
	vec4 color = mix(texture(texture0, p), texture(texture1, p), 0.2);

	FragColor = vec4(color);
};


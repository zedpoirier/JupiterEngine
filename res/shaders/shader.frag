#version 330 core
in vec3 color;
in vec2 texcoord;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform vec4 time;
uniform vec4 reso;

void main()
{
    // these twovars seem like equivalent ways to access the texcoord
    vec2 uv = texcoord;
	vec4 st = gl_FragCoord / reso;
	FragColor = mix(texture(texture0, uv), texture(texture1, uv), 0.2) * vec4(color, 1.0);
};
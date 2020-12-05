#version 330 core
in vec3 color;
in vec2 texcoord;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float time;
uniform int frame;
uniform vec2 reso;

float box(vec2 st, vec2 size)
{
    size = vec2(0.5) - size*0.5;
    vec2 p = smoothstep(size, size+vec2(0.001), st);
    p *= smoothstep(size, size+vec2(0.001), vec2(1.0)-st);
    return p.x*p.y;
}

void main()
{
	vec2 uv = texcoord;
	vec2 p = vec2(uv.x, uv.y - frame / 60.0);
	vec4 color = vec4(box(fract(p), vec2(0.05, 0.2)));
	vec2 offset1 = vec2(0.2, 0.4);
	color += vec4(box(fract(p + offset1), vec2(0.05, 0.2)));
	vec2 offset2 = vec2(-0.3, -0.2);
	color += vec4(box(fract(p + offset2), vec2(0.05, 0.2)));
	vec2 offset3 = vec2(0.6, -0.5);
	color += vec4(box(fract(p + offset3), vec2(0.05, 0.2)));
	//vec2 offset4 = vec2(-0.8, 0.1);
	//color += vec4(box(fract(p + offset4), vec2(0.02, 0.2)));
	if (color.a < 0.1) discard;
	FragColor = color; //* vec4(1.0, 0.0, 1.0, 1.0);
};


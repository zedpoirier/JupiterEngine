#version 330 core
in vec3 color;
in vec2 texcoord;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform vec4 time;
uniform vec4 reso;

float box(vec2 st, vec2 size)
{
    size = vec2(0.5) - size*0.5;
    vec2 uv = smoothstep(size, size+vec2(0.001), st);
    uv *= smoothstep(size, size+vec2(0.001), vec2(1.0)-st);
    return uv.x*uv.y;
}

float sdfBox(vec3 space, vec3 size)
{
	vec3 q = abs(space) - size;
	float dist = length(max(q, 0.0));
	return dist;
}

float sdfSphere(vec3 p, float radius)
{
	vec3 q = abs(p) - radius;
	float dist = length(p) - radius;
	return dist;
}

vec4 lasers()
{
	vec4 final = vec4(1.0, 1.0, 0.0, 1.0);
	// create single long box

	return final;
}

void main()
{
    vec2 uv = texcoord;
	FragColor = vec4(step(sdfSphere(vec3(uv.xy - 0.5, abs(sin(time.x)) * 0.5 ), 0.3), 0.0));
};


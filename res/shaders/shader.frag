#version 330 core
in vec3 color;
in vec2 texcoord;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform vec4 time;
uniform vec4 reso;

float sdfCircle(vec2 p, float radius)
{
	vec2 q = abs(p) - radius;
	float dist = length(p) - radius;
	return dist;
}

float ringDots(vec2 p, float count, float radius, float size)
{
	float angle = 6.283185 / count;
	float sector = round(atan(p.x, p.y) / angle);
	float an = sector * angle;

	p *= mat2(cos(an), -sin(an),
			  sin(an),  cos(an));

	p -= vec2(0.0, radius); // translate
	return sdfCircle(p, size);
}

void main()
{
    vec2 p = texcoord - 0.5; // center
	vec2 q = p;

	p *= mat2(cos(time.x), -sin(time.x),
			  sin(time.x),  cos(time.x));

	q *= mat2(cos(-time.x), -sin(-time.x),
			  sin(-time.x),  cos(-time.x));

    
	float d6 = ringDots(p, 256.0, 0.5, 0.01);
	float d5 = ringDots(q, 128.0, 0.4, 0.01);
	float d4 = ringDots(p, 64.0, 0.4, 0.01);
	float d3 = ringDots(q, 32.0, 0.3, 0.01);
	float d2 = ringDots(p, 16.0, 0.2, 0.01);
	float d1 = ringDots(q, 8.0, 0.1, 0.01);
	float d = min(min(min(min(min(d1, d2), d3), d4), d5), d6);
	FragColor = vec4(vec3(step(d, 0.0)), 1.0);
};


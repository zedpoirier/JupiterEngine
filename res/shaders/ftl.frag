#version 330 core
#line 3 // sets the next line's starting number
in vec3 color;
in vec2 texcoord;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform int frame;
uniform float time;
uniform vec2 reso;
uniform vec3 col1;
uniform vec3 col2;
uniform vec3 col3;

// repuires noise.glsl to function!!!!

float rings(vec2 p)
{
	float d = abs(circle(p, 0.1)) - 0.01;

	return d;
}

float ftlThread(vec2 m)
{
	vec2 q = m * 30.0;
	q.y -= 6.0;
	q.x += sin(q.y + time) * 0.2;
	q.x += cos(q.y * 3.0) * 0.2;

	vec2 l1 = q;
	l1.x += sin(l1.y + 4.71);
	float b = box(l1, vec2(0.05, 20.0));

	vec2 l2 = q;
	l2.x += sin(l2.y + 3.14);
	b = combine(b, box(l2, vec2(0.05, 20.0)));
	
	vec2 l3 = q;
	l3.x += sin(l3.y + 1.57);
	b = combine(b, box(l3, vec2(0.05, 20.0)));
	
	vec2 l4 = q;
	l4.x += sin(l4.y + 0.00);
	b = combine(b, box(l4, vec2(0.05, 20.0)));
	
	
	return b;
}

void main()
{
	// spinUp FTL sketch
    vec2 uv = texcoord - 0.5;
	vec2 p = uv / (2.5 + 0.2 * sin(time));
	float an = 20.0 * length(p) - (time * 0.5);
	p *= mat2(cos(an), -sin(an), sin(an), cos(an));
	vec2 w1 = vec2( fractalNoise(p + vec2(0.2, -0.6), 3),
					fractalNoise(p + vec2(0.7, -0.1), 3));
	vec2 w2 = vec2( fractalNoise(p + vec2(-0.4, 0.8) + w1, 3),
					fractalNoise(p + vec2(0.3, -0.3) + w1, 3));

	p.x *= sin(time) * 0.5 + w2.x;
	p.y *= cos(time) * 0.5 + w2.y;
	//p *= time * 0.5;
	float d = rings(p);
	vec4 color = vec4(1.0 - smoothstep(0.0, 0.03, d));
	//color = vec4(step(d, 0.0));
	float mask = 1.0 - smoothstep(0.0, 0.15, circle(uv * 1.2, 0.4));
	color *= mask;
	color.xyz = mix(vec3(0.1, 0.3, 1.0), vec3(0.9), pow(color.a, 1.5));

	// launch sketch
	//color = vec4(1.0 - smoothstep(0.0, 0.2, circle(uv * 1.2, 0.4)));
	vec4 col = vec4(0.0);
	vec2 m = uv;
	uv.x *= pow(uv.y + 1.5, 4.0);
	float b = 10000.0;
	m.x = uv.x + sin(uv.y * 2.0 + sin(time * 0.3) + 1.0) * 0.4;
	b = combine(b, ftlThread(m));
	m.x = uv.x + sin(uv.y * 3.0 + sin(time * 0.4) + 2.0) * 0.2;
	b = combine(b, ftlThread(m));
	m.x = uv.x + sin(uv.y * 4.0 + sin(time * 0.5) + 3.0) * 0.4;
	b = combine(b, ftlThread(m));
	m.x = uv.x + sin(uv.y * 5.0 + sin(time * 0.6) + 4.0) * 0.2;
	b = combine(b, ftlThread(m));
	m.x = uv.x + sin(uv.y * 6.0 + sin(time * 0.7) + 5.0) * 0.25;
	b = combine(b, ftlThread(m));
	m.x = uv.x + sin(uv.y * 7.0 + sin(time * 0.6) + 6.0) * 0.4;
	b = combine(b, ftlThread(m));
	m.x = uv.x + sin(uv.y * 8.0 + sin(time * 0.5) + 7.0) * 0.4;
	b = combine(b, ftlThread(m));
	m.x = uv.x + sin(uv.y * 9.0 + sin(time * 0.4) + 8.0) * 0.4;
	b = combine(b, ftlThread(m));
	m.x = uv.x + sin(uv.y * 10.0 + sin(time * 0.4) + 9.0) * 0.4;
	b = combine(b, ftlThread(m));

	b = 1.0 - smoothstep(0.0, 1.5, b);
	b = pow(b, 4.0);
	col = vec4(b);
	col.xyz = mix(vec3(0.1, 0.3, 1.0), vec3(0.9), pow(col.a, 1.5));

	//col = vec4(uv.xy, 0.0, 0.5);
	FragColor = col;
};


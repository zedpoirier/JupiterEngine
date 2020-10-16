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

float ringDots(vec2 p, float count, float radius, float size, float speed)
{
	p *= mat2(cos(time.x * speed), -sin(time.x * speed),
			  sin(time.x * speed),  cos(time.x * speed));
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
    
	float d6 = ringDots(p, 64.0, 0.48, 0.005, 1.0);
	float d5 = ringDots(q, 32.0, 0.4, 0.008 , 1.0);
	float d4 = ringDots(p, 16.0, 0.3, 0.01, 1.0);
	float d3 = ringDots(q, 8.0, 0.2, 0.02 , 1.0);
	float d2 = ringDots(p, 4.0, 0.1, 0.03  , 1.0);
	float d1 = 100000;
	float d = min(min(min(min(min(d1, d2), d3), d4), d5), d6);
	vec3 dots = vec3(step(d, 0.0));
	//FragColor = vec4(vec3(dots), 1.0);

	float x = 1.0;
	float y = 19.0;
	float z = 71.0;
	float r = ringDots(p, 12.0, 0.3, 0.03, 1.0);
	float g = ringDots(p, 12.0, 0.3, 0.02, 1.1);
	float b = ringDots(p, 12.0, 0.3, 0.04, 1.2 );
	float red = step(r, 0);
	float green = step(g, 0.0);
	float blue = step(b, 0.0);
	FragColor = vec4(red, green, blue, 1.0);
};


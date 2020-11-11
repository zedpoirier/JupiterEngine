#version 330 core
in vec3 color;
in vec2 texcoord;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform int frame;
uniform vec4 time;
uniform vec4 reso;

float easeIn(float val)
{
	float c4 = (2 * 3.14) / 3;
	return -pow(2, 10 * val - 10) * sin((val * 10 - 10.75) * c4);
}

float beam(vec2 p, float width, float phase, float amplitude)
{
	return smoothstep(width + sin(p.y * phase) * amplitude, 0.02, abs(p.x));
}

void main()
{
    vec2 p = texcoord - 0.5; // center
	vec3 color = vec3(0.8, 0.2, 1.0);

	//p *= mat2(easeIn(frame / 10.0), 0.0, 0.0, 1.0);
	float b1 = beam(vec2(p.x, p.y - time.x * 1.0), 0.5, 20.0, 0.03);
	p *= mat2(2.0, 0.0, 0.0, 1.0); 
	float b2 = beam(vec2(p.x, p.y - time.x * 1.2), 0.5, 40.0, 0.03);
	p *= mat2(2.0, 0.0, 0.0, 1.0); 
	float b3 = beam(vec2(p.x, p.y - time.x * 1.3), 0.5, 80.0, 0.03);
	p *= mat2(2.0, 0.0, 0.0, 1.0); 
	float b4 = beam(vec2(p.x, p.y - time.x * 1.4), 0.3, 160.0, 0.03);
	vec3 final = vec3(b1) * color + vec3(b2) * 0.3 + vec3(b3) * 0.3 + vec3(b4) * 0.3;
	FragColor = vec4(final, 1.0 - step(b1, 0.35));
};


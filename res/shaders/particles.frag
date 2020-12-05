#version 330 core
in vec3 color;
in vec2 texcoord;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform int frame;
uniform float time;
uniform vec2 reso;

void main()
{
    vec2 p = texcoord - 0.5;

	// noise generation
	vec3 q = vec3(p * 3.0, time * 0.4);
	float noise = fractalNoise(q, 3) * 0.5 + 0.4;

	// circle cutout to avoid sqaure shape
	vec2 c = p * 1.5;
	float circle = smoothstep(0.2, 0.9, length(c));

	// colors for explosion
	vec3 black = vec3(0.25, 0.25, 0.25);
	vec3 colorA = vec3(0.27, 0.16, 0.10);
	vec3 colorB = vec3(0.96, 0.30, 0.24);
	vec3 colorC = vec3(0.96, 0.96, 0.35);

	// steps for color gradients
	float step1 = 0.4;
	float step2 = 0.65;
	float step3 = 0.8;
	noise -= circle *0.3;
	noise = pow(noise, 1.0);

	// mixing the gradients
	vec3 color = mix(black, colorA, smoothstep(step1, step2, noise));
	color = mix(color, colorB, smoothstep(step2, step3, noise));
	color = mix(color, colorC, smoothstep(step3, 1.0, noise));
	float alpha = (fractalNoise(q * 0.5, 3) * 0.5 + 0.5) - circle;
	alpha = noise - circle;
	FragColor = vec4(color, alpha);
};


#version 330 core
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

// requires noise.glsl to function!!!!

void main()
{
    vec2 p = (gl_FragCoord.xy - 0.5 * reso.xy) / reso.y;

	//float spin = frame * 0.08 * length(p);
	float spin = sin( (frame - (200.5*length(p))) * 0.02);
	p *= mat2(cos(spin), -sin(spin),
			  sin(spin), cos(spin));
	vec3 q = vec3(p.x, p.y, time * 0.04);
	vec3 n = vec3(fractalNoise(q, 5));

	vec3 w1 = vec3(fractalNoise(q + vec3(0.0, 0.0, 0.0), 3),
				   fractalNoise(q + vec3(5.2, 1.3, 3.6), 3),
				   0.0);
				  
	vec3 w2 = vec3(fractalNoise(q + w1 + vec3(1.7, 9.2, 6.8), 3),
				   fractalNoise(q + w1 + vec3(1.9, 4.6, 7.2), 3),
				   0.0);

	float f = fractalNoise(q + w2 * 2.0, 3);

	vec2 o, m;
	vec3 col = vec3(f);
		col = mix( col, col1, w2.x );
		col = mix( col, col2, w2.y );
		col = mix( col, col3, w1.x );
		col *= f *2.0;

	FragColor = vec4(col, 1.0);
};


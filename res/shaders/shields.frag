#version 330 core
in vec3 color;
in vec2 texcoord;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform int frame;
uniform float time;
uniform vec2 reso;

uniform vec3 camPos;
uniform vec3 camFront;

// raymarching sometimes called spghere tracing
#define MAX_STEPS 100
#define MAX_DIST 1000.0
#define SURFACE_DIST 0.01

float Scene(vec3 p)
{
	float geo = 10000.0;
	geo = sphere(p, 3.0);
	return geo;
}

float RayMarch(vec3 rayOrigin, vec3 rayDirection)
{
	float distFromOrigin = 0.0;
	for (int i=0; i < MAX_STEPS; i++)
	{
		vec3 p = rayOrigin + distFromOrigin * rayDirection;
		float distToScene = Scene(p);
		distFromOrigin += distToScene;
		if (distToScene < SURFACE_DIST) return distFromOrigin;
		if (distFromOrigin > MAX_DIST) return 0.0;
	}
	return 0.0;
}

vec3 GetNormal(vec3 p)
{
	float d = Scene(p);
	vec2 e = vec2(0.0001, 0.0);
	vec3 n = vec3(
		Scene(p + e.xyy) - Scene(p - e.xyy), 
		Scene(p + e.yxy) - Scene(p - e.yxy), 
		Scene(p + e.yyx) - Scene(p - e.yyx));
	return normalize(n);
}

float GetLight(vec3 p)
{
	vec3 lightPos = vec3(4.0, 10.0, 3.0); // light within scene
	vec3 lightDir = normalize(lightPos - p);

	lightDir = normalize(lightPos); // light as a "sun" direction (reusing lightpos)
	vec3 normal = GetNormal(p);

	float diff = clamp(dot(normal, lightDir), -1.0, 1.0);
	diff = pow(diff * 0.5 + 0.5, 2.0);
	//float d = RayMarch(p + normal * 0.05, lightDir);
	//if(d < length(lightPos - p)) diff *= 0.1;
	return max(diff,0.05);
}

mat4 viewMatrix(vec3 camPos, vec3 camTarget) {
	vec3 f = normalize(camTarget - camPos);
	vec3 s = normalize(cross(f, vec3(0.0, 1.0, 0.0)));
	vec3 u = cross(s, f);
	return mat4(
		vec4(s, 0.0),
		vec4(u, 0.0),
		vec4(-f, 0.0),
		vec4(0.0, 0.0, 0.0, 1)
	);
}

void main()
{
    vec2 uv = (gl_FragCoord.xy - 0.5 * reso.xy) / reso.y;
	uv *= 1.2; // works as FOV kinda
	vec4 color = vec4(0.0);


	// camera and ray setup
	//vec3 ro = vec3(0.0, 0.0, 6.0);
	vec3 ro = camPos;
	//vec3 rt = vec3(0.0, 0.0, 0.0);
	vec3 rt = camPos + camFront;
	vec3 rd = normalize(vec3(uv.x, uv.y, -1.0));
	rd = (viewMatrix(ro, rt) * vec4(rd, 0.0)).xyz;

	float d = RayMarch(ro, rd);
	if (d > 0.0)
	{
		vec3 p = ro + rd * d;
		vec3 q = vec3(p.x, p.y, time * 0.5);
		vec3 n = vec3(fractalNoise(q, 5));

		vec3 w1 = vec3(
					fractalNoise(q + vec3(0.0, 0.0, 0.0), 3),
					fractalNoise(q + vec3(5.2, 1.3, 3.6), 3),
					0.0);
				  
		vec3 w2 = vec3(
					fractalNoise(q + w1 + vec3(1.7, 9.2, 6.8), 3),
					fractalNoise(q + w1 + vec3(1.9, 4.6, 7.2), 3),
					0.0);

		float f = fractalNoise(q + w2 * 2.0, 3);
		color = vec4(f);
	}
	
	FragColor = vec4(color);
};


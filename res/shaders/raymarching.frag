#version 330 core
in vec3 color;
in vec2 texcoord;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform int frame;
uniform float time;
uniform vec2 reso;

// raymarching sometimes called spghere tracing
#define MAX_STEPS 100
#define MAX_DIST 100.0
#define SURFACE_DIST 0.01

float sdSphere(vec3 p, vec3 pos, float s )
{
  return length(p - pos)-s;
}

float Scene(vec3 p)
{
	// create all geometry here???
	float geo = 10000.0;
	geo = min(geo, sdSphere(p, vec3(0.0, 1.0, -6.0), 1.0));
	geo = min(geo, sdSphere(p, vec3(1.0, 1.0, -7.0), 0.5));
	geo = min(geo, sdSphere(p, vec3(3.0, 2.0, -9.0), 0.5));
	geo = min(geo, sdSphere(p, vec3(-1.0, 0.5, -3.0), 0.2));
	//create plane (aligned to cam axis)
	float planeDist = p.y; // groundplane using the height of cam pos downwards

	geo = min(geo, planeDist);
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
		if (distToScene < SURFACE_DIST || distFromOrigin > MAX_DIST) break;
	}
	return distFromOrigin;
}

vec3 GetNormal(vec3 p)
{
	float d = Scene(p);
	vec2 e = vec2(0.01, 0.0);
	vec3 n = vec3(
		Scene(p + e.xyy) - Scene(p - e.xyy), 
		Scene(p + e.yxy) - Scene(p - e.yxy), 
		Scene(p + e.yyx) - Scene(p - e.yyx));
	return normalize(n);
}

float GetLight(vec3 p)
{
	vec3 lightPos = vec3(0.0, 5.0, -6.0); // fake light within scene
	lightPos.xz += vec2(sin(time), cos(time));
	vec3 lightDir = normalize(lightPos - p); // hard set a vec3 for a "sun" direction
	vec3 normal = GetNormal(p);

	float diff = clamp(dot(normal, lightDir), 0.0, 1.0);
	float d = RayMarch(p + normal * 0.05, lightDir);
	if(d < length(lightPos - p)) diff *= 0.1;
	return diff;
}

void main()
{
    vec2 uv = (gl_FragCoord.xy - 0.5 * reso.xy) / reso.y;
	vec3 color = vec3(0.0);

	vec3 ro = vec3(0.0, 1.0, 0.0);
	vec3 rd = normalize(vec3(uv.x, uv.y, -1.0));

	float d = RayMarch(ro, rd);

	vec3 p = ro + rd * d;

	float diffuse = GetLight(p);

	color = vec3(diffuse);
	FragColor = vec4(color, 1.0);
};


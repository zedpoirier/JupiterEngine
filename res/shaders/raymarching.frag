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
#define MAX_DIST 1000.0
#define SURFACE_DIST 0.01

float sdSphere(vec3 p, vec3 pos, float s )
{
  return length(p - pos)-s;
}

float Scene(vec3 p)
{
	// create all geometry here???
	float geo = 10000.0;
	geo = unionSDF(geo, sdSphere(p, 1.0));
	geo = differenceSDF(geo, sdSphere(p, vec3(0.5, 0.2, 0.8), 0.8));
	geo = unionSDF(geo, sdSphere(p, vec3(sin(time * 1.5) * 1.2, sin(time * 1.5) * -0.8, cos(time * 1.5) * 1.2), 0.1));
	geo = unionSDF(geo, sdSphere(p, vec3(sin(time) * 2.0, sin(time) * 0.5, cos(time) * 2.0), 0.2));
	geo = unionSDF(geo, sdSphere(p, vec3(sin(time * 0.5) * 3.0, sin(time * 0.5) * 0.2, cos(time * 0.5) * 3.0), 0.4));
	geo = unionSDF(geo, sdSphere(p, vec3(sin(time * 0.3) * 5.0, 0.0, cos(time * 0.3) * 5.0), 0.7));
	//create plane (aligned to cam axis)
	float planeDist = p.y; // groundplane using the height of cam pos downwards

	//geo = min(geo, planeDist);
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
		if (distToScene < SURFACE_DIST) break;
		if (distFromOrigin > MAX_DIST) return 0.0;
	}
	return distFromOrigin;
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
	uv *= 1.5; // works as FOV kinda
	vec3 color = vec3(0.0);

	// camera and ray setup
	vec3 ro = vec3(0.0, 0.0, 6.0);
	vec3 rt = vec3(0.0, 0.0, 0.0);
	vec3 rd = normalize(vec3(uv.x, uv.y, -1.0));
	rd = (viewMatrix(ro, rt) * vec4(rd, 0.0)).xyz;

	float d = RayMarch(ro, rd);
	if (d > 0.0)
	{
		vec3 p = ro + rd * d;
		float diffuse = GetLight(p);
		color = vec3(diffuse);
	}
	
	FragColor = vec4(color, 1.0);
};


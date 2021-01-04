#version 330 core
#line 3
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
#define SURFACE_DIST 0.001
#define PI 3.14159

float missle(vec3 p)
{
	float geo = 10000.0;

	// bullet shape
	geo = combine(geo, line(p, min(2.0 - p.y, 0.2), vec3(0.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0)));
	//fin shapes
	float angle = PI * 2.0 / 12.0;
	float sector = round(atan(p.z,p.x)/angle);
	vec3 l = p;
	float r = -20.0;
	float an = sector*angle;
	l.xz = mat2(cos(an), -sin(an), sin(an), cos(an)) * l.xz; // order of operation matters here!!!!
	l -= vec3(0.15, 0.0, 0.0);
	l.xy = mat2(cos(r), -sin(r), sin(r), cos(r)) * l.xy;
	geo = combine(geo, box(l, vec3(0.2, 0.2, 0.02)));
	// sub sphere to create more dynamic shape at bottom of missle 
	geo = difference(geo, sphere(p - vec3(0.0, -0.4, 0.0), 0.5));

	return geo;
}

float Scene(vec3 p)
{
	float geo = 10000.0;
	p.x *= 2.0;
	p.y -= -10.0;
	p.y -= fract(time) * 22.0;

	geo = combine(geo, missle(p));
	geo = combine(geo, missle(p - vec3(1.0, 3.0, 0.0)));
	geo = combine(geo, missle(p - vec3(-1.0, -4.0, 0.0)));
	geo = combine(geo, missle(p - vec3(1.5, -6.0, 0.0)));
	geo = combine(geo, missle(p - vec3(-1.5, 6.0, 0.0)));
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
	vec3 lightPos = vec3(0.0, 0.0, 30.0); // light within scene
	vec3 lightDir = normalize(lightPos - p);

	lightDir = normalize(lightPos); // light as a "sun" direction (reusing lightpos)
	vec3 normal = GetNormal(p);

	float diff = clamp(dot(normal, lightDir), -1.0, 1.0);
	diff = pow(diff * 0.5 + 0.5, 2.0);
	//float d = RayMarch(p + normal * 0.05, lightDir);
	//if(d < length(lightPos - p)) diff *= 0.1;
	return max(diff,0.05);
}

void main()
{
    vec2 uv = (gl_FragCoord.xy - 0.5 * reso.xy) / reso.y;
	uv *= 10.5; // works as FOV kinda
	vec4 color = vec4(0.0);

	// camera and ray setup
	vec3 ro = vec3(uv.x, uv.y, 6.0);
	vec3 rt = vec3(0.0, 0.0, 0.0);
	vec3 rd = normalize(vec3(0.0, 0.0, -1.0));
	//rd = (viewMatrix(ro, rt) * vec4(rd, 0.0)).xyz;

	float d = RayMarch(ro, rd);
	if (d > 0.0)
	{
		vec3 p = ro + rd * d;
		float diffuse = GetLight(p);
		vec3 matte = vec3(diffuse) * vec3(0.7);
		color = vec4(matte, 1.0);
	}
	else 
	{
		color = vec4(0.0);
	}
	
	FragColor = color;
};
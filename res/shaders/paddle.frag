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

uniform vec3 paddleRot;

// raymarching sometimes called spghere tracing
#define MAX_STEPS 100
#define MAX_DIST 1000.0
#define SURFACE_DIST 0.001
#define PI 3.1415

// BOUNCE EASING: exponentially decaying parabolic bounce
float easeOutBounce(float x)
{
	float n1 = 7.5625;
	float d1 = 2.75;

	if (x < 1 / d1) {
		return n1 * x * x;
	} else if (x < 2 / d1) {
		return n1 * (x -= 1.5 / d1) * x + 0.75;
	} else if (x < 2.5 / d1) {
		return n1 * (x -= 2.25 / d1) * x + 0.9375;
	} else {
		return n1 * (x -= 2.625 / d1) * x + 0.984375;
	}
}

float Scene(vec3 p)
{
	float geo = 10000.0;
	float bounceTime = 2.0;

	// ball
	vec3 pa = -p;
	pa -= vec3(0.0, -2.6, 0.0);
	pa.y -= 4.0 * clamp(easeOutBounce(frame / 60.0 / bounceTime), 0.0, 1.0);
	geo = combine(geo, sphere(pa , 0.5));

	// paddle
	float x = paddleRot.x;
	float z = paddleRot.z;
	vec3 pad = -p;
	pad -= vec3(0.0, 2.0, 0.0);
	pad.yz *= mat2(cos(z), -sin(z), sin(z), cos(z));
	pad.xy *= mat2(cos(x), -sin(x), sin(x), cos(x));
	float an = PI / 2;
	geo = combine(geo, cylinder(pad, 2.0, 0.05));
	pad.yz *= mat2(cos(an), -sin(an), sin(an), cos(an));
	geo = combine(geo, hexagon(pad, vec2(1.5, 0.1)));


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

float GetShadow( in vec3 ro, in vec3 rd, float mint, float maxt )
{
    for( float t=mint; t<maxt; )
    {
        float h = Scene(ro + rd*t);
        if( h<SURFACE_DIST )
            return 0.0;
        t += h;
    }
    return 1.0;
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
	vec3 lightPos = vec3(2.0, 10.0, 5.0); // light within scene
	vec3 lightDir = normalize(lightPos - p);
	lightDir = normalize(lightPos); // light as a "sun" direction (reusing lightpos)
	vec3 normal = GetNormal(p);
	float diff = clamp(dot(normal, lightDir), -1.0, 1.0);
	diff = pow(diff * 0.5 + 0.5, 2.0);

	float d = GetShadow(p + normal * SURFACE_DIST * 2.0, lightPos - p, 0.0, length(lightPos - p));
	if(d < 0.5) 
		diff *= 0.1;
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
	//uv *= 1.5; // works as FOV kinda
	vec3 color = vec3(0.0);
	float bounceTime = 2.0;

	// camera and ray setup
	vec3 ro0 = vec3(0.0, 2.0, 8.0);
	vec3 ro1 = vec3(0.0, 1.0, 5.0);
	vec3 rt0 = vec3(0.0, 0.0, 0.0);
	vec3 rt1 = vec3(0.0, -1.0, 0.0);
	float perc = clamp(easeOutBounce(frame / 60.0 / bounceTime), 0.0, 1.0);
	vec3 ro = mix(ro0, ro1, perc);
	vec3 rt = mix(rt0, rt1, perc);
	vec3 rd = normalize(vec3(uv.x, uv.y, -1.0));
	rd = (viewMatrix(ro, rt) * vec4(rd, 0.0)).xyz;

	float d = RayMarch(ro, rd);
	if (d > 0.0)
	{
		vec3 p = ro + rd * d;
		float diffuse = GetLight(p);
		color = vec3(diffuse) * vec3(0.5, 0.1, 0.7);
		//color *= 0.5 + 0.5*GetNormal(p);
	}
	else 
	{
		color = vec3((uv.y + 0.5)*0.6);
	}
	
	FragColor = vec4(color, 1.0);
};


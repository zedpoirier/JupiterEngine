#version 330 core
in vec3 color;
in vec2 texcoord;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform vec4 time;
uniform vec4 reso;

float box(vec2 st, vec2 size)
{
    size = vec2(0.5) - size*0.5;
    vec2 uv = smoothstep(size, size+vec2(0.001), st);
    uv *= smoothstep(size, size+vec2(0.001), vec2(1.0)-st);
    return uv.x*uv.y;
}

float sdfBox(vec3 space, vec3 size)
{
	vec3 q = abs(space) - size;
	float dist = length(max(q, 0.0));
	return dist;
}

float sdfSphere(vec3 p, float radius)
{
	vec3 q = abs(p) - radius;
	float dist = length(p) - radius;
	return dist;
}

float sdfRing(vec2 p, float radius, float halfThickness)
{
	return abs(length(p) - radius) - halfThickness;
}

float sdfCircle(vec2 p, float radius)
{
	return length(p) - radius;
}

vec4 lasers()
{
	vec4 final = vec4(1.0, 1.0, 0.0, 1.0);
	// create single long box

	return final;
}

float sdVesica(vec2 p, float r, float d)
{
    p = abs(p);
    float b = sqrt(r*r-d*d);
    return ((p.y-b)*d>p.x*b) ? length(p-vec2(0.0,b))
                             : length(p-vec2(-d,0.0))-r;
}

float sdRhombus( in vec2 p, in vec2 b ) 
{
    vec2 q = abs(p);
    float h = clamp((-2.0*dot(q,b)+dot(b,b))/dot(b,b),-1.0,1.0);
    float d = length( q - 0.5*b*vec2(1.0-h,1.0+h) );
    return d * sign( q.x*b.y + q.y*b.x - b.x*b.y );
}

void main()
{
    vec2 uv = texcoord - 0.5;
	//FragColor = vec4(step(sdfSphere(vec3(uv.xy - 0.5, abs(sin(time.x)) * 0.5 ), 0.3), 0.0));
	//FragColor = vec4(1.0 - sdfCircle(uv, -0.6));
	vec4 color = vec4(step(sdRhombus(uv, vec2(0.15, 0.4)), 0.0));
	//color += step(sdfCircle(vec2(uv.x, uv.y - 0.3), 0.05), 0.0);
	FragColor = color;
};


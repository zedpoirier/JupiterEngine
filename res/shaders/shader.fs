#version 330 core
out vec4 FragColor;
uniform vec4 time;
uniform vec4 reso;
in vec4 color;

const float TWO_PI = 6.28318530718;

vec3 hsb2rgb(vec3 c){
    vec3 rgb = clamp(abs(mod(c.x*6.0+vec3(0.0,4.0,2.0), 6.0) -3.0) -1.0, 0.0, 1.0);
    rgb = rgb*rgb*(3.0-2.0*rgb);
    return c.z * mix(vec3(1.0), rgb, c.y);
}

void main()
{
	//FragColor = vec4(0.6, 0.65, 0.5, 1.0);
	vec4 st = gl_FragCoord / reso;
	float dist = distance(st.xy, vec2(0.5));
	dist = step(dist, 0.5);


	FragColor = vec4(vec3(dist), 1.0);
};
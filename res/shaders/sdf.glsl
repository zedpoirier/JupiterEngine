#version 330 core

//----------------------------------------------------
// Primitive Operations (Constructive Solid Geometry)
//----------------------------------------------------

float unionSDF(float distA, float distB)
{
	return min(distA, distB);
}

float intersectSDF(float distA, float distB)
{
	return max(distA, distB);
}

float differenceSDF(float distA, float distB)
{
	return max(distA, -distB);
}

//----------------------------------------------------
// 2D SDFs
//----------------------------------------------------

// TODO

//----------------------------------------------------
// 3D SDFs
//----------------------------------------------------

float sdSphere( vec3 p, float s )
{
  return length(p)-s;
}

float sdBox( vec3 p, vec3 b )
{
  vec3 q = abs(p) - b;
  return length(max(q,0.0)) + min(max(q.x,max(q.y,q.z)),0.0);
}

float sdTorus( vec3 p, vec2 t )
{
  vec2 q = vec2(length(p.xz)-t.x,p.y);
  return length(q)-t.y;
}
#include "Utility.h"

vec3 Utility::random_direction_in_unit_sphere()
{
	//[-1,1]
	vec3 reflectDir = 2.0f * vec3(DRand48::drand48(), DRand48::drand48(), DRand48::drand48()) - vec3::ONE;
	return reflectDir;

}
/*
	标准菲涅尔方程，不同的入射角度，会产生不同的反射比
*/

float Utility::fresnel(float cosi, float cost, float etai, float etat)
{
	float Rs = (cosi * etai - cost * etat) / (cosi * etai + cost * etat);
	float Rt = (cosi * etat - cost * etai) / (cosi * etat + cost * etai);

	return (Rs * Rs + Rt * Rt) * 0.5f;
}

float Utility::fresnel(float cosi, float cost, float etai_over_etat)
{
	return fresnel(cosi, cost, etai_over_etat, 1);
}

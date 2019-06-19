#include "Utility.h"

vec3 Utility::random_direction_in_unit_sphere()
{
	//[-1,1]
	vec3 reflectDir = 2.0f * vec3(DRand48::drand48(), DRand48::drand48(), DRand48::drand48()) - vec3::ONE;
	return reflectDir;

}
/*
	��׼���������̣���ͬ������Ƕȣ��������ͬ�ķ����
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

float Utility::schlick(float etai_over_etat, float cosine)
{
	//�����п���ֱ����R0��Ϊ����
	float sqrt_r0 = (etai_over_etat - 1.0) / (etai_over_etat + 1);
	float r0 = sqrt_r0 * sqrt_r0;

	//R0 +(1-R0)(1-cos ��) ^5
	return r0 + (1.0 + r0) * pow((1 - cosine), 5);
}

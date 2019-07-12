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

float Utility::schlick(float etai_over_etat, float cosine)
{
	//引擎中可以直接以R0做为参数
	float sqrt_r0 = (etai_over_etat - 1.0) / (etai_over_etat + 1);
	float r0 = sqrt_r0 * sqrt_r0;

	//R0 +(1-R0)(1-cos θ) ^5
	return r0 + (1.0 + r0) * pow((1 - cosine), 5);
}

float Utility::deg2rad(float degrees)
{
	return (degrees / 180.0f) * M_PI;
}

float Utility::rad2deg(float rad)
{
	return  (rad / M_PI) * 180.f;
}

vec3 Utility::lerp(vec3 a, vec3 b, float factor)
{
	return vec3(lerp(a.x(), b.x(), factor), lerp(a.y(), b.y(), factor), lerp(a.z(), b.z(), factor));
}

float Utility::remap(float currentVal, float inputMin, float inputMax, float outMin, float outMax)
{
	float ratio = (outMax - outMin) / (inputMax - inputMin);
	return outMin + ratio * (currentVal - inputMin);
}

float Utility::frac(float val)
{
	return val - floor(val);
}

float Utility::smoothstep(float val)
{
	return val * val * val * (6 * val * val - 15 * val + 10);		//6t^5-15t^4+10t^3
}

vec3 Utility::smoothstep(vec3 val)
{
	return  vec3(Utility::smoothstep(val.x()), Utility::smoothstep(val.y()), Utility::smoothstep(val.z()));
}

void Utility::shuffleArray(int* arr, int size)
{
	int arraySize = size;
	while (arraySize > 1)
	{
		arraySize--;
		int index = int(DRand48::drand48() * arraySize);

		int temp = arr[arraySize];
		arr[arraySize] = arr[index];
		arr[index] = temp;
	}
}

float Utility::bilinear_interpolate(float a, float b, float c, float d, float factorX, float factorY)
{
	float s = Utility::lerp(a, b, factorX);
	float t = Utility::lerp(c, d, factorX);

	return Utility::lerp(s, t, factorY);
}

float Utility::trilinear_interpolate(float a0, float b0, float c0, float d0, float a, float b, float c, float d, float factorX, float factorY, float factorZ)
{
	float s = Utility::bilinear_interpolate(a0, b0, c0, d0, factorX, factorY);
	float t = Utility::bilinear_interpolate(a, b, c, d, factorX, factorY);

	return Utility::lerp(s, t, factorZ);
}

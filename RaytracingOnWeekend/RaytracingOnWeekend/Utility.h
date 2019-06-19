#pragma once
#include "Vec3.h"
#include "DRand48.h"
/**
 * 各种帮助类
 */
class Utility
{
public:
	/**
	* hitpoint 上取出一个随机方向作为反射方法，继续反射
	   并没有使用物理意义上的Reflect(IncidentRay,Normal)作为反射方向
	*/
	static vec3 random_direction_in_unit_sphere();

	/**
	 * 电介质的Fresnel函数

		PS：η  eta
	 */
	static float fresnel(float cosi, float cost, float etai, float etat);

	static float fresnel(float cosi, float cost, float etai_over_etat);

	/*
		Schlick 对于Fresnel的近似  cosine是入射光与法线的dot
	*/
	static float schlick(float etai_over_etat, float cosine);

	
	inline static float getRandom01() { return DRand48::drand48(); }
};


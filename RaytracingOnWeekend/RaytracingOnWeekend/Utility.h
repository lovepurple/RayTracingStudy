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

};


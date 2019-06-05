#pragma once
#include "ray.h"

/*
	抽象类，用于描述是光线是否击中物理
*/


struct HitInfo
{
	float HitRay_Factor;
	vec3 HitPoint;
	vec3 HitPointNormal;
};


class Hitable
{
	//C++ 纯虚函数（抽象函数）,函数结束是=0 ，子类必须实现
public:
	virtual bool Hit(const ray& ray, float t_min, float t_max, HitInfo& hitInfo) const = 0;
};


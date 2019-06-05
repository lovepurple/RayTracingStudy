#pragma once
#include "Hitable.h"

/*
	球体的击中实现
*/


//C++定义类的访问级别是在:后面
class Sphere :
	public Hitable
{
public:
	Sphere() {}

	//C++中构造函数的赋值
	Sphere(vec3 sphereCenter, float sphereRadius) :sphere_center(sphereCenter), sphere_radius(sphereRadius) {};

	/**
	 * t_min,t_max 用于限定光线的长度
	 */
	virtual bool Hit(const ray& ray, float t_min, float t_max, HitInfo& hitInfo) const override;

	vec3 sphere_center;
	float sphere_radius;
private:
	void ContructHitInfo(HitInfo& hitinfo, const ray& ray, float rayLength) const {
		hitinfo.HitPoint = ray.point_at_parameter(rayLength);
		hitinfo.HitRay_Factor = rayLength;
		hitinfo.HitPointNormal = unit_vector(hitinfo.HitPoint - sphere_center);
	}
};


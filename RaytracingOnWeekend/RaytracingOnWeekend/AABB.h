#pragma once
/*
 *	 AABB 包围盒 (相当于Unity中的Bounds)
 */
#include "Vec3.h"
#include "ray.h"
#include <math.h>

class AABB
{
public:
	/**
	 * @bref:AABB包围盒
	   @boundsMin :包围盒的最小点
	   @boundsMax :包围盒的最大点
	 */
	AABB(vec3& boundsMin, vec3& boundsMax);

	vec3 boundsMin() const;
	vec3 boundsMax() const;

	/**
	 * @brief: 光线是否击中包围盒
	   @tMin: 光线长度的最小值
	   @tMax:光线长度的最大值
	 */
	bool isHit(const ray& ray, float tMin, float tMax);

	/**
	 * @brief:获取两个AABB的组合体
	 */
	static AABB surrounding_box(AABB aabb0, AABB aabb1);

private:
	vec3 m_boundsMin;
	vec3 m_boundsMax;
};


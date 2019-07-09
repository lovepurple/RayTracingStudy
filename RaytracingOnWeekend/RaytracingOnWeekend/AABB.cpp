#include "AABB.h"

AABB::AABB(vec3& boundsMin, vec3& boundsMax)
{
	this->m_boundsMin = boundsMin;
	this->m_boundsMax = boundsMax;
}

vec3 AABB::boundsMin() const
{
	return this->m_boundsMin;
}

vec3 AABB::boundsMax() const
{
	return this->m_boundsMax;
}

bool AABB::isHit(const ray& ray, float tMin, float tMax)
{
	//对x y z 三个轴的分量进行相交性检测如果没有相交,则未击中
	vec3 rayDirectionNormalized = ray.direction().normalize();


	for (int i = 0; i < 3; ++i)
	{
		//Bounds在指定轴的边界
		float boundsMin = this->m_boundsMin[i];
		float boundsMax = this->m_boundsMax[i];

		float rayOriginComponent = ray.direction().e[i];

		float tempMin = (boundsMin - rayOriginComponent) * 1.0 / rayDirectionNormalized.e[i];
		float tempMax = (boundsMax - rayOriginComponent) * 1.0 / rayDirectionNormalized.e[i];

		//方向是否是反的
		if (rayDirectionNormalized.e[i] < 0)
			std::swap(tempMin, tempMax);		//template... 值传入，为什么能改变原来的值？？

		if (tempMin > tMax || tempMax < tMin)
			return false;

		//取交集
		tMin = fmax(tMin, tempMin);
		tMax = fmin(tMax, tempMax);
	}


	return true;
}

AABB AABB::surrounding_box(AABB aabb0, AABB aabb1)
{
	vec3 surroundBoxMin = aabb0.boundsMin();
	vec3 surroundBoxMax = aabb0.boundsMax();
	for (int i = 0; i < 3; ++i)
	{
		surroundBoxMin.e[i] = fmin(aabb0.m_boundsMin.e[i], aabb1.m_boundsMin.e[i]);
		surroundBoxMax.e[i] = fmax(aabb0.m_boundsMax.e[i], aabb1.m_boundsMax.e[i]);
	}

	return AABB(surroundBoxMin, surroundBoxMax);
}

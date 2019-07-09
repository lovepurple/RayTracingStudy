#pragma once
/*
 *	 AABB ��Χ�� (�൱��Unity�е�Bounds)
 */
#include "Vec3.h"
#include "ray.h"
#include <math.h>

class AABB
{
public:
	/**
	 * @bref:AABB��Χ��
	   @boundsMin :��Χ�е���С��
	   @boundsMax :��Χ�е�����
	 */
	AABB(vec3& boundsMin, vec3& boundsMax);

	vec3 boundsMin() const;
	vec3 boundsMax() const;

	/**
	 * @brief: �����Ƿ���а�Χ��
	   @tMin: ���߳��ȵ���Сֵ
	   @tMax:���߳��ȵ����ֵ
	 */
	bool isHit(const ray& ray, float tMin, float tMax);

	/**
	 * @brief:��ȡ����AABB�������
	 */
	static AABB surrounding_box(AABB aabb0, AABB aabb1);

private:
	vec3 m_boundsMin;
	vec3 m_boundsMax;
};


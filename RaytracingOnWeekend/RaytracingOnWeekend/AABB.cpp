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
	//��x y z ������ķ��������ཻ�Լ�����û���ཻ,��δ����
	vec3 rayDirectionNormalized = ray.direction().normalize();


	for (int i = 0; i < 3; ++i)
	{
		//Bounds��ָ����ı߽�
		float boundsMin = this->m_boundsMin[i];
		float boundsMax = this->m_boundsMax[i];

		float rayOriginComponent = ray.direction().e[i];

		float tempMin = (boundsMin - rayOriginComponent) * 1.0 / rayDirectionNormalized.e[i];
		float tempMax = (boundsMax - rayOriginComponent) * 1.0 / rayDirectionNormalized.e[i];

		//�����Ƿ��Ƿ���
		if (rayDirectionNormalized.e[i] < 0)
			std::swap(tempMin, tempMax);		//template... ֵ���룬Ϊʲô�ܸı�ԭ����ֵ����

		if (tempMin > tMax || tempMax < tMin)
			return false;

		//ȡ����
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

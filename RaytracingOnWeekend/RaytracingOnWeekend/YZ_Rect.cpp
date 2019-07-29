#include "YZ_Rect.h"

YZ_Rect::YZ_Rect(float yMin, float yMax, float zMin, float zMax, float x, Material* mat, vec3 normal)
{
	this->m_yMin = yMin;
	this->m_yMax = yMax;
	this->m_zMin = zMin;
	this->m_zMax = zMax;
	this->m_x = x;
	this->m_mat = mat;
	this->m_normal = normal;

	this->m_hitableObjectAABB = getHitable_AABB(0, 0);
}

bool YZ_Rect::Hit(const ray& ray, float t_min, float t_max, HitInfo& hitInfo) const
{
	float factor = (this->m_x - ray.origin().x()) / ray.direction().x();
	if (factor < t_min || factor > t_max)
		return false;

	vec3 hitPoint = ray.point_at_parameter(factor);
	if (hitPoint.y() < m_yMin || hitPoint.y() > m_yMax || hitPoint.z() < m_zMin || hitPoint.z() > m_zMax)
		return false;

	hitInfo.HitPoint = hitPoint;
	hitInfo.HitPointNormal = this->m_normal;
	hitInfo.hitPointUV = vec3((hitPoint.y() - m_yMin) / (m_yMax - m_yMin), (hitPoint.z() - m_zMin) / (m_zMax - m_zMin));
	hitInfo.mat_ptr = this->m_mat;
	hitInfo.HitRay_Factor = factor;

	return true;
}

AABB* YZ_Rect::getHitable_AABB(float time0, float time1)
{
	if (this->m_hitableObjectAABB == nullptr)
	{
		vec3 boundsMin = vec3(m_x - 0.0001, m_yMin, m_zMin);
		vec3 boundsMax = vec3(m_x + 0.0001, m_yMax, m_zMax);
		this->m_hitableObjectAABB = new AABB(boundsMin, boundsMax);
	}
	return this->m_hitableObjectAABB;
}

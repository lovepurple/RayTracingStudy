#include "XZ_Rect.h"

XZ_Rect::XZ_Rect(float xMin, float xMax, float zMin, float zMax, float y, Material* mat, vec3 normal)
{
	this->m_xMin = xMin;
	this->m_xMax = xMax;
	this->m_zMin = zMin;
	this->m_zMax = zMax;
	this->m_y = y;
	this->m_mat = mat;
	this->m_normal = normal;

	this->m_hitableObjectAABB = getHitable_AABB(0, 0);
}

bool XZ_Rect::Hit(const ray& ray, float t_min, float t_max, HitInfo& hitInfo) const
{
	float factor = (m_y - ray.origin().y()) / ray.direction().y();
	if (factor < t_min || factor > t_max)
		return false;

	vec3 hitPoint = ray.point_at_parameter(factor);

	if (hitPoint.x() < m_xMin || hitPoint.x() > m_xMax || hitPoint.z() < m_zMin || hitPoint.z() > m_zMax)
		return false;

	hitInfo.HitPoint = hitPoint;
	hitInfo.hitPointUV = vec3((hitPoint.x() - m_xMin) / (m_xMax - m_xMin), (hitPoint.z() - m_zMin) / (m_zMax - m_zMin));
	hitInfo.HitPointNormal = this->m_normal;
	hitInfo.HitRay_Factor = factor;
	hitInfo.mat_ptr = this->m_mat;

	return true;
}

AABB* XZ_Rect::getHitable_AABB(float time0, float time1)
{
	if (this->m_hitableObjectAABB == nullptr)
	{
		vec3 boundsMin = vec3(this->m_xMin, m_y - 0.0001, this->m_zMin);
		vec3 boundsMax = vec3(this->m_xMax, m_y + 0.0001, this->m_zMax);
		this->m_hitableObjectAABB = new AABB(boundsMin, boundsMax);
	}

	return this->m_hitableObjectAABB;
}

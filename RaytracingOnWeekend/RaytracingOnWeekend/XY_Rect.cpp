#include "XY_Rect.h"

XY_Rect::XY_Rect(float xmin, float xmax, float ymin, float ymax, float z, Material* mat)
{
	this->m_xmin = xmin;
	this->m_xmax = xmax;
	this->m_ymin = ymin;
	this->m_ymax = ymax;
	this->m_z = z;
	this->m_matPtr = mat;
}

bool XY_Rect::Hit(const ray& ray, float t_min, float t_max, HitInfo& hitInfo) const
{
	//z的大小是固定的，因此使用z分量可计算出factor
	float factor = (this->m_z - ray.origin().z()) / ray.direction().z();
	if (factor < t_min || factor > t_max)
		return false;

	float hitPointX = ray.origin().x() + ray.direction().x() * factor;
	float hitPointY = ray.origin().y() + ray.direction().y() * factor;

	if (hitPointX < this->m_xmin || hitPointX > this->m_xmax || hitPointY< this->m_ymin || hitPointY > this->m_ymax)
		return false;

	float hitPointU = (hitPointX - m_xmin) / (m_xmax - m_xmin);
	float hitPointV = (hitPointY - m_ymin) / (m_ymax - m_ymin);

	hitInfo.HitPoint = vec3(hitPointX, hitPointY, m_z);
	hitInfo.HitPointNormal = vec3(0, 0, 1);
	hitInfo.hitPointUV = vec3(hitPointU, hitPointV);
	hitInfo.HitRay_Factor = factor;
	hitInfo.mat_ptr = this->m_matPtr;

	return true;
}

AABB* XY_Rect::getHitable_AABB(float time0, float time1)
{
	if (this->m_hitableObjectAABB == nullptr)
	{
		//一点点厚度
		vec3 boundsMin = vec3(this->m_xmin, this->m_ymin, this->m_z - 0.0001);
		vec3 boundsMax = vec3(this->m_xmax, this->m_ymax, this->m_z + 0.0001);
		this->m_hitableObjectAABB = new AABB(boundsMin, boundsMax);

	}

	return this->m_hitableObjectAABB;
}

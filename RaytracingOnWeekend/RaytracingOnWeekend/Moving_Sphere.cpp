#include "Moving_Sphere.h"

Moving_Sphere::Moving_Sphere(vec3 sphereMoveStartPosition, vec3 sphereMoveEndPosition, float sphereRadius, float moveStartTime, float moveEndTime, Material* mat)
{
	this->m_sphereMoveStartPosition = sphereMoveStartPosition;
	this->m_sphereMoveEndPosition = sphereMoveEndPosition;
	this->m_sphereRadius = sphereRadius;
	this->m_moveStartTime = moveStartTime;
	this->m_moveEndTime = moveEndTime;
	this->m_sphereMat = mat;
}

vec3 Moving_Sphere::getSpherePositionOnTime(float timeMoment) const
{
	return m_sphereMoveStartPosition + getMoveVelocity() * (timeMoment - m_moveStartTime);
}

bool Moving_Sphere::Hit(const ray& ray, float t_min, float t_max, HitInfo& hitInfo) const
{
	//�������Ź��ߣ�����ʱ���ڣ�ʱ�䣬����λ�ò�ͬ
	float rayTime = ray.getTime();
	vec3 sphereCenterOnTime = getSpherePositionOnTime(rayTime);

	vec3 origin_to_center = ray.origin() - sphereCenterOnTime;
	float a = dot(ray.direction(), ray.direction());
	float b = 2.0 * dot(origin_to_center, ray.direction());
	float c = dot(origin_to_center, origin_to_center) - m_sphereRadius * m_sphereRadius;

	float discriminant = b * b - 4 * a * c;

	//��������������ཻ��
	if (discriminant < 0)
		return false;
	else
	{
		float rootA = (-b + sqrt(discriminant)) / (2.0f * a);
		float rootB = (-b - sqrt(discriminant)) / (2.0f * a);

		HitInfo hitableInfoA;
		HitInfo hitableInfoB;

		if (rootA > t_max || rootA < t_min)
			rootA = FLT_MAX;

		if (rootB > t_max || rootB < t_min)
			rootB = FLT_MAX;

		float closestDistance = std::fminf(rootA, rootB);

		//�޽�
		if (closestDistance == FLT_MAX)
			return false;

		ContructHitInfo(hitInfo, ray, closestDistance);

		return true;
	}
}

vec3 Moving_Sphere::getMoveVelocity() const
{
	return (m_sphereMoveEndPosition - m_sphereMoveStartPosition) / (m_moveEndTime - m_moveStartTime);
}

void Moving_Sphere::ContructHitInfo(HitInfo& hitinfo, const ray& ray, float rayLength) const
{
	hitinfo.HitPoint = ray.point_at_parameter(rayLength);
	hitinfo.HitRay_Factor = rayLength;
	hitinfo.HitPointNormal = unit_vector(hitinfo.HitPoint - getSpherePositionOnTime(ray.getTime()));
	hitinfo.mat_ptr = m_sphereMat;		//���м�¼����
}
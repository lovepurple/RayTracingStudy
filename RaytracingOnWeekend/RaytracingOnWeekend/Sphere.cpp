#include "Sphere.h"

bool Sphere::Hit(const ray& ray, float t_min, float t_max, HitInfo& hitInfo) const
{
	vec3 origin_to_center = ray.origin() - sphere_center;
	float a = dot(ray.direction(), ray.direction());
	float b = 2.0 * dot(origin_to_center, ray.direction());
	float c = dot(origin_to_center, origin_to_center) - sphere_radius * sphere_radius;

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

		//�ų�������Χ�Ľ�
		if (rootA > t_max || rootA < t_min)
			rootA = FLT_MAX;

		if (rootB > t_max || rootB < t_min)
			rootB = FLT_MAX;

		//todo:MLGB ���������������������⣬��Ӧ��ȡ�ͽ���һ��
		//SB Bug ���˺ü���
		//��ķ���Ҫ���ķ���һ��,��������ⶼ�����⣬ȡ�������
		float closestDistance = std::fminf(rootA, rootB);

		//�޽�
		if (closestDistance == FLT_MAX)
			return false;

		ContructHitInfo(hitInfo, ray, closestDistance);

		return true;
	}
}

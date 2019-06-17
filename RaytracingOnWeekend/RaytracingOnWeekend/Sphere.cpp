#include "Sphere.h"

bool Sphere::Hit(const ray& ray, float t_min, float t_max, HitInfo& hitInfo) const
{
	vec3 origin_to_center = ray.origin() - sphere_center;
	float a = dot(ray.direction(), ray.direction());
	float b = 2.0 * dot(origin_to_center, ray.direction());
	float c = dot(origin_to_center, origin_to_center) - sphere_radius * sphere_radius;

	float discriminant = b * b - 4 * a * c;

	//计算射线与球的相交点
	if (discriminant < 0)
		return false;
	else
	{
		float rootA = (-b + sqrt(discriminant)) / (2.0f * a);
		float rootB = (-b - sqrt(discriminant)) / (2.0f * a);

		HitInfo hitableInfoA;
		HitInfo hitableInfoB;

		//排除超出范围的解
		if (rootA > t_max || rootA < t_min)
			rootA = FLT_MAX;

		if (rootB > t_max || rootB < t_min)
			rootB = FLT_MAX;

		//todo:MLGB 这里两个根都可能是正解，但应该取就近的一个
		//SB Bug 找了好几天
		//点的方向要与光的方向一致,如果两个解都是正解，取距离近的
		float closestDistance = std::fminf(rootA, rootB);

		//无解
		if (closestDistance == FLT_MAX)
			return false;

		ContructHitInfo(hitInfo, ray, closestDistance);

		return true;
	}
}

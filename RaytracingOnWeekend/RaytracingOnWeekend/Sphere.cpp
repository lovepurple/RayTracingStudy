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

		if ((rootA < t_max) && (rootA > t_min))
			ContructHitInfo(hitInfo, ray, rootA);
		else if (rootB<t_max && rootB >t_min)
			ContructHitInfo(hitInfo, ray, rootB);

		return true;
	}
}

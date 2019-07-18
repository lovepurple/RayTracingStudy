#include "HitableList.h"

bool HitableList::Hit(const ray& ray, float t_min, float t_max, HitInfo& hitInfo) const
{
	HitInfo iterator_hitInfo;

	bool isHit = false;

	//取最近的击中目标
	double cloese_so_far = t_max;
	for (int i = 0; i < hitable_obejct_count; ++i) {
		Hitable* hitableObjectInfo = hitable_object_list[i];


		if (hitableObjectInfo->Hit(ray, t_min, cloese_so_far, iterator_hitInfo)) {
			isHit = true;
			cloese_so_far = iterator_hitInfo.HitRay_Factor;
			hitInfo = iterator_hitInfo;
			//hitInfo.hitPointUV = Utility::get_uv_by_sphere_point(hitInfo.HitPoint);
		}
	}

	return isHit;
}

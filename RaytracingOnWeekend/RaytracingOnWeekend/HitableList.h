#pragma once
#include "Hitable.h"

/**
 * 击中列表，场景里多物体时的击中判断
 */

class HitableList :
	public Hitable
{
public:
	HitableList() {}
	HitableList(Hitable** hitableObjectList, int hitableObjectCount) :hitable_object_list(hitableObjectList), hitable_obejct_count(hitableObjectCount) {}

	//q:为什么需要两个**,如果是数组，使用hitable*表示数组起始位置 + index 不就可以索引了吗
	//Hitable** 表示的是指针数组 hitable_object_list存的是hitable*[] 
	Hitable** hitable_object_list;
	int hitable_obejct_count;


	// Inherited via Hitable
	virtual bool Hit(const ray& ray, float t_min, float t_max, HitInfo& hitInfo) const override;

};


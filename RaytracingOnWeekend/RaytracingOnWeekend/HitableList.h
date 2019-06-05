#pragma once
#include "Hitable.h"

/**
 * �����б������������ʱ�Ļ����ж�
 */

class HitableList :
	public Hitable
{
public:
	HitableList() {}
	HitableList(Hitable** hitableObjectList, int hitableObjectCount) :hitable_object_list(hitableObjectList), hitable_obejct_count(hitableObjectCount) {}

	//q:Ϊʲô��Ҫ����**,��������飬ʹ��hitable*��ʾ������ʼλ�� + index ���Ϳ�����������
	//Hitable** ��ʾ����ָ������ hitable_object_list�����hitable*[] 
	Hitable** hitable_object_list;
	int hitable_obejct_count;


	// Inherited via Hitable
	virtual bool Hit(const ray& ray, float t_min, float t_max, HitInfo& hitInfo) const override;

};


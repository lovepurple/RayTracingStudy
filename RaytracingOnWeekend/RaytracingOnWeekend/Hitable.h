#pragma once
#include "ray.h"
#include "Material.h"

/*
	�����࣬���������ǹ����Ƿ��������
*/

struct HitInfo
{
	float HitRay_Factor;
	vec3 HitPoint;
	vec3 HitPointNormal;
	Material* mat_ptr;		//�������ʣ����ദ����һ������ʱ��ʹ��ָ��
};


class Hitable
{
	//C++ ���麯������������,����������=0 ���������ʵ��
public:
	virtual bool Hit(const ray& ray, float t_min, float t_max, HitInfo& hitInfo) const = 0;
};


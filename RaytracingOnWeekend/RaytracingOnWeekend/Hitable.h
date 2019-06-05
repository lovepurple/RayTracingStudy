#pragma once
#include "ray.h"

/*
	�����࣬���������ǹ����Ƿ��������
*/


struct HitInfo
{
	float HitRay_Factor;
	vec3 HitPoint;
	vec3 HitPointNormal;
};


class Hitable
{
	//C++ ���麯������������,����������=0 ���������ʵ��
public:
	virtual bool Hit(const ray& ray, float t_min, float t_max, HitInfo& hitInfo) const = 0;
};


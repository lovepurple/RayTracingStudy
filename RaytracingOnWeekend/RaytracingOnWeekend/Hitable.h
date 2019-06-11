#pragma once
#include "ray.h"

/**
 * ��⣬����Material.h����Ҫ����Hitable.h �� hitable.h����Ҫinclude Material.h �����ѭ��include
	���������ﲻȥinclude ֱ������Ҫʹ�õ��࣬��ǰ���߱�����Ҫʹ�õ��࣬���Ҳ���ʹ���౾������Ҫ��ָ�룬����������໹û�����ڴ棬��ָ�����ռ��4���ֽڹ̶���С
 */
class Material;

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


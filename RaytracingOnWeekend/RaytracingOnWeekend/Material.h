#pragma once
#include "ray.h"
#include "Hitable.h"
/**
 * �����࣬�Բ�ͬ�Ĳ��ʽ��в�ͬ����ɫ
 */
class Material
{
public:
	/**
	 * ���߾������ʵ����ռ�����
	 */
	virtual bool scatter(const ray& incidentRay, const HitInfo& hitInfo, vec3& attenuation, ray& outRay) const = 0;
};


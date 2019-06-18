#pragma once
#include "ray.h"
#include "Hitable.h"
#include "Utility.h"
/**
 * �����࣬�Բ�ͬ�Ĳ��ʽ��в�ͬ����ɫ
 */
class Material
{
public:
	/**
	 * ���߾������ʵ����ռ�����

		@outRay ָ���߾������ʺ�����Ĺ���
	 */
	virtual bool scatter(const ray& incidentRay, const HitInfo& hitInfo, vec3& attenuation, ray& outRay) const = 0;

	/*
		˥��
	*/
	vec3 m_albedo;
};


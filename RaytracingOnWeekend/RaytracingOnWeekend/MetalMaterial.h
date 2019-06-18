#pragma once
#include "Material.h"
/**
 * �⻬�Ľ�������
 */
class MetalMaterial :
	public Material
{
public:
	//�������ƫ��ֵ��
	/*
		����fuzzier ������
		The bigger the sphere, the fuzzier the reflections will be. This suggests adding a fuzziness parameter that is just the radius of the sphere (so zero is no perturbation).
		The catch is that for big spheres or grazing rays, we may scatter below the surface. We can just have the surface absorb those.
		We��ll put a maximum of 1 on the radius of the sphere which yields

		����뾶Խ�󣬿���Խģ���������ܶ����⣿�����Է��䷽�����һ�����������Ŷ����൱�����뷨����ͼ����
		��������Ͳ���ȫ���䣨ȫ��������һ��������һЩ����ɫ�������Ŷ����÷�������һЩ
	*/
	MetalMaterial(const vec3& albedo, float fuzzier) {
		this->m_albedo = albedo;
		this->m_fuzzierFactor = fuzzier > 1 ? 1 : fuzzier;
	}

	// Inherited via Material
	virtual bool scatter(const ray& incidentRay, const HitInfo& hitInfo, vec3& attenuation, ray& outRay) const override;

	//�Ŷ�����
	float m_fuzzierFactor = 0;
};


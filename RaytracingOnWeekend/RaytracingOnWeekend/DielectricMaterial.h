#pragma once
#include "Material.h"
/*
	����ʲ��ʣ���������²����磬��һ������¿��ܵ��磬��Ե���Ǹ���������
	�������Ҫ�Ĺ�ģ�����ڲ�����,�����淴�� ���⴫���Ľ��ʷ����ı�
*/

class DielectricMaterial :
	public Material
{
public:
	DielectricMaterial(float n1_over_n2) {
		this->m_n1_over_n2 = n1_over_n2;
	}

	//n1 / n2
	float m_n1_over_n2;

	// Inherited via Material
	virtual bool scatter(const ray& incidentRay, const HitInfo& hitInfo, vec3& attenuation, ray& outRay) const override;
};


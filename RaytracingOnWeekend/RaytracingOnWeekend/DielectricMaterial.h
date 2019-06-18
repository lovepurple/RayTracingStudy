#pragma once
#include "Material.h"
/*
	电介质材质，正常情况下不导电，在一定情况下可能导电，绝缘体是根本不导电
	电介质主要的光模型是内部折射,及表面反射 ，光传播的介质发生改变
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


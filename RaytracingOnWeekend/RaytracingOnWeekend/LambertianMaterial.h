#pragma once
#include "Material.h"
#include "Utility.h"
/**
 * Lambertian ���������
 */
class LambertianMaterial :
	public Material
{
public:
	LambertianMaterial(vec3& mainColor) :albedoColor(mainColor) {}

	// Inherited via Material
	virtual bool scatter(const ray& incidentRay, const HitInfo& hitInfo, vec3& attenuation, ray& outRay) const override;

	vec3 albedoColor;

};


#pragma once
#include "Material.h"
/**
 * 光滑的金属材质
 */
class MetalMaterial :
	public Material
{
public:
	MetalMaterial(vec3& mainColor) :albedoColor(mainColor) {}

	vec3 albedoColor;

	// Inherited via Material
	virtual bool scatter(const ray& incidentRay, const HitInfo& hitInfo, vec3& attenuation, ray& outRay) const override;
};


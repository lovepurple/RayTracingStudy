#pragma once
#include "Material.h"
/**
 * 光滑的金属材质
 */
class MetalMaterial :
	public Material
{
public:
	MetalMaterial(const vec3& albedo) :m_albedo(albedo) {}

	vec3 m_albedo;

	// Inherited via Material
	virtual bool scatter(const ray& incidentRay, const HitInfo& hitInfo, vec3& attenuation, ray& outRay) const override;
};


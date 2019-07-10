#pragma once
/*
 *	带有贴图的Lambertian材质
 */
#include "LambertianMaterial.h"
#include "Texture.h"
class LambertianWithTextureMaterial :
	public LambertianMaterial
{
public:
	LambertianWithTextureMaterial(Texture* albedoTex);

	virtual bool scatter(const ray& incidentRay, const HitInfo& hitInfo, vec3& attenuation, ray& outRay) const override;

private:
	Texture* m_albedoTexture;
};


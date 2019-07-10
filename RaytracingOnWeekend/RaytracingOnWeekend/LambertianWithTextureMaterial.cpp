#include "LambertianWithTextureMaterial.h"

LambertianWithTextureMaterial::LambertianWithTextureMaterial(Texture* albedoTex)
{
	this->m_albedoTexture = albedoTex;
}

bool LambertianWithTextureMaterial::scatter(const ray& incidentRay, const HitInfo& hitInfo, vec3& attenuation, ray& outRay) const
{
	//调用父类中的方法，带域调用
	LambertianMaterial::scatter(incidentRay, hitInfo, attenuation, outRay);
	attenuation = this->m_albedoTexture->sample(0, 0, hitInfo.HitPoint);

	return true;
}

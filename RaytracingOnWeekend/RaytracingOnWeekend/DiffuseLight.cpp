#include "DiffuseLight.h"

DiffuseLight::DiffuseLight(Texture* tex)
{
	this->m_matTexturePtr = tex;
}

bool DiffuseLight::scatter(const ray& incidentRay, const HitInfo& hitInfo, vec3& attenuation, ray& outRay) const
{
	return false;		//�Է�������Թ�û��ɢ�䡢����
}

vec3 DiffuseLight::emitted(float u, float v, const vec3& hitPoint) const
{
	return this->m_matTexturePtr->sample(u, v, hitPoint);
}

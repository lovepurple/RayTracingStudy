#pragma once
#include "Material.h"
#include "Texture.h"

class DiffuseLight :
	public Material
{
public:
	DiffuseLight() {}
	DiffuseLight(Texture* tex);


	// Inherited via Material
	virtual bool scatter(const ray& incidentRay, const HitInfo& hitInfo, vec3& attenuation, ray& outRay) const override;

	virtual vec3 emitted(float u, float v, const vec3& hitPoint) const override;

private:
	Texture* m_matTexturePtr;		//²ÄÖÊÌùÍ¼
};


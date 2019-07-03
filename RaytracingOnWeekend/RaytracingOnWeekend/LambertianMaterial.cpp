#include "LambertianMaterial.h"

bool LambertianMaterial::scatter(const ray& incidentRay, const HitInfo& hitInfo, vec3& attenuation, ray& outRay) const
{
	//Lambertian 是向随机方向反射
	vec3 outRayRandomDir = hitInfo.HitPointNormal + unit_vector(Utility::random_direction_in_unit_sphere());
	outRay = ray(hitInfo.HitPoint, unit_vector(outRayRandomDir), incidentRay.getTime());		//反射加入时间
	attenuation = m_albedo;
	return true;
}

LambertianMaterial* LambertianMaterial::getRandomAlbedoLambertianMat()
{
	LambertianMaterial* randomAlbedoMat = new LambertianMaterial(vec3(Utility::getRandom01() * Utility::getRandom01(), Utility::getRandom01() * Utility::getRandom01(), Utility::getRandom01() * Utility::getRandom01()));
	return randomAlbedoMat;
}

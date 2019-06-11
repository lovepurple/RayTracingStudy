#include "MetalMaterial.h"

/**
 * ����������ʣ�ֱ�ӷ���
 */
bool MetalMaterial::scatter(const ray& incidentRay, const HitInfo& hitInfo, vec3& attenuation, ray& outRay) const
{
	vec3 reflectDir = unit_vector(reflect(incidentRay.direction(), hitInfo.HitPointNormal));
	outRay = ray(hitInfo.HitPoint, reflectDir);
	attenuation = m_albedo;

	return (dot(outRay.direction(), hitInfo.HitPointNormal)) > 0;
}

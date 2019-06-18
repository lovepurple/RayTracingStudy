#include "MetalMaterial.h"

/**
 * ����������ʣ�ֱ�ӷ���
 */
bool MetalMaterial::scatter(const ray& incidentRay, const HitInfo& hitInfo, vec3& attenuation, ray& outRay) const
{
	vec3 reflectDir = unit_vector(reflect(incidentRay.direction(), hitInfo.HitPointNormal));

	//�����Ŷ�
	outRay = ray(hitInfo.HitPoint, reflectDir + m_fuzzierFactor * Utility::random_direction_in_unit_sphere());
	attenuation = m_albedo;

	return (dot(outRay.direction(), hitInfo.HitPointNormal)) > 0;
}

#include "DielectricMaterial.h"

bool Dielectric::scatter(const ray& incidentRay, const HitInfo& hitInfo, vec3& attenuation, ray& outRay) const
{
	//����������ʱ���п��ܷ������䣬�п��ܷ���ȫ����
	//���߸����������ܷ������ 
	//	���粣��������벣��һ�Σ�֮��Ӳ�������������У����ʳ����ᷢ���ı䣬���ߵķ���Ҳ�п����Ƿ���
	//			�����ɿ������벣�� ��������ķ��߷����������
	//			������һ���ɲ����ڲ�����������У����߼���Ҫȡ��

	/*
		ͨ������� n1_over_n2 ������>0 ������1�����>0 �п��ܴ������ ���� /����  ������Ҫȷ�����ĸ����ʵ��ĸ�

		�ڿ����� �����ڽ��ʱ��� IDotN <0 ������ⷽ��ָ����棩������Щ�����У�Unity��LightDir ������Ĭ���Ƿ������ģ���Ҫ��һ��ȷ�������ķ���
	*/

	attenuation = vec3(1.0, 1.0, 0);

	//ֻ�Ǽ�������������һ��Normalize�������Ż�����  
	float IDotN = dot(incidentRay.direction(), hitInfo.HitPointNormal);

	//IDotN>0�ɽ���������� ��ΪhitInfo.HitPointNormal ����������
	vec3 realMediumNormal = IDotN > 0 ? -hitInfo.HitPointNormal : hitInfo.HitPointNormal;
	float mediumFactor = IDotN > 0 ? m_n1_over_n2 : (1.0 / m_n1_over_n2);

	vec3 refractDir;
	if (refract(incidentRay.direction(), realMediumNormal, mediumFactor, refractDir))
	{
		outRay = ray(hitInfo.HitPoint, refractDir);
		return true;
	}
	else  //ȫ����
	{
		vec3 reflectDir = reflect(hitInfo.HitPoint, hitInfo.HitPointNormal);
		outRay = ray(hitInfo.HitPoint, unit_vector(reflectDir));
		return false;
	}
}

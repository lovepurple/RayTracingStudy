#include "DielectricMaterial.h"

bool DielectricMaterial::scatter(const ray& incidentRay, const HitInfo& hitInfo, vec3& attenuation, ray& outRay) const
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

	attenuation = vec3(1.0, 1.0, 1.0);		//����ʹ�õ���vec(1,1,0) ������� Ҫ���������ֽ磬˥����1 ��Ϊ�����������չ⣬��˥��

	//ֻ�Ǽ�������������һ��Normalize�������Ż�����  
	float IDotN = dot(incidentRay.direction(), hitInfo.HitPointNormal);

	//IDotN>0�ɽ���������� ��ΪhitInfo.HitPointNormal ����������
	vec3 realMediumNormal = IDotN > 0 ? -hitInfo.HitPointNormal : hitInfo.HitPointNormal;
	float etai_over_etat = IDotN > 0 ? m_n1_over_n2 : (1.0 / m_n1_over_n2);

	float fresnelReflectFactor = 1.0;
	vec3 refractDir;

	if (refract(incidentRay.direction(), realMediumNormal, etai_over_etat, refractDir))
	{
		//����Fresnel (cosi,cost ���߷���һ�£�������Ҫ��Ч�������ȡ��)		
		float cosi = dot(incidentRay.direction(), realMediumNormal);
		float cost = dot(unit_vector(refractDir), realMediumNormal);
		float etai = etai_over_etat;
		float etat = 1.0;

		fresnelReflectFactor = Utility::fresnel(cosi, cost, etai, etat);		//[0,1]

		//����Schlick����ֵ,���ڵ�������->�������ʣ�eta_over_etat <1�� Ҫ�õ�cos t
		//dot���ܳ�����ֱ��ʹ�þ���ֵ
		float cosine = abs(cosi);

		fresnelReflectFactor = Utility::schlick(etai_over_etat, cosine);
	}
	else  //ȫ����
		fresnelReflectFactor = 1.0;

	//������Shader��ʹ�õ��Ǹ��ⲿ���룬���仹������   fresnel������Ƿ���ȣ�Խ�ӽ�1����Խ��
	if (0.8 < fresnelReflectFactor)
	{
		vec3 reflectDir = reflect(incidentRay.direction(), hitInfo.HitPointNormal);
		outRay = ray(hitInfo.HitPoint, unit_vector(reflectDir));
	}
	else
		outRay = ray(hitInfo.HitPoint, refractDir);

	return true;
}

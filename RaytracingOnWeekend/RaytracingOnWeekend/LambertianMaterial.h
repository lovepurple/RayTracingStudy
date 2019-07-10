#pragma once
#include "Material.h"
#include "Utility.h"
/**
 * Lambertian ���������
 */
class LambertianMaterial :
	public Material
{
public:
	LambertianMaterial(){}			//��Ҫ�и�Ĭ�ϵĹ��죬��������ʵ��ʱ�ᱨ������
	/**
	 * albedo ָ���Ƿ�����

	 �Ӳ���const ���ڵ��÷�ʽ������
		 ��const ����ֱ��
			Material* mat_ptr = new LambertianMaterial(vec(1,1,1))
		 �������const��������⣬����Ĳ����ڱ��λ�ÿ����õ���������Ҫ������
			Vec albedoCol = vec(1,1,1);
			Material* mat_ptr = new LambertianMaterial(albedoCol);
	 */
	LambertianMaterial(const vec3& albedo) { this->m_albedo = albedo; }

	// Inherited via Material
	virtual bool scatter(const ray& incidentRay, const HitInfo& hitInfo, vec3& attenuation, ray& outRay) const override;

	//@brief:��ȡһ�������ɫ�����������
	static LambertianMaterial* getRandomAlbedoLambertianMat();
};


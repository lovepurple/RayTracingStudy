#pragma once
#include "Hitable.h"

/*
	����Ļ���ʵ��
*/


//C++������ķ��ʼ�������:����
class Sphere :
	public Hitable
{
public:
	Sphere() {}

	//C++�й��캯���ĸ�ֵ
	Sphere(vec3 sphereCenter, float sphereRadius) :sphere_center(sphereCenter), sphere_radius(sphereRadius) {};

	//������� ,C++�����������캯���ķ�ʽ,д�ıȽϷ�
	Sphere(vec3 sphere_center, float sphereRadius, Material* renderMat) :mat(renderMat) {
		this->Sphere::Sphere(sphere_center, sphereRadius);
	}


	/**
	 * t_min,t_max �����޶����ߵĳ���
	 */
	virtual bool Hit(const ray& ray, float t_min, float t_max, HitInfo& hitInfo) const override;

	vec3 sphere_center;
	float sphere_radius;
	Material* mat;
private:
	void ContructHitInfo(HitInfo& hitinfo, const ray& ray, float rayLength) const {
		hitinfo.HitPoint = ray.point_at_parameter(rayLength);
		hitinfo.HitRay_Factor = rayLength;
		hitinfo.HitPointNormal = unit_vector(hitinfo.HitPoint - sphere_center);
		hitinfo.mat_ptr = mat;		//���м�¼����
	}
};


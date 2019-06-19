#pragma once
#include "Vec3.h"
#include "DRand48.h"
/**
 * ���ְ�����
 */
class Utility
{
public:
	/**
	* hitpoint ��ȡ��һ�����������Ϊ���䷽������������
	   ��û��ʹ�����������ϵ�Reflect(IncidentRay,Normal)��Ϊ���䷽��
	*/
	static vec3 random_direction_in_unit_sphere();

	/**
	 * ����ʵ�Fresnel����

		PS����  eta
	 */
	static float fresnel(float cosi, float cost, float etai, float etat);

	static float fresnel(float cosi, float cost, float etai_over_etat);

	/*
		Schlick ����Fresnel�Ľ���  cosine��������뷨�ߵ�dot
	*/
	static float schlick(float etai_over_etat, float cosine);

	
	inline static float getRandom01() { return DRand48::drand48(); }
};


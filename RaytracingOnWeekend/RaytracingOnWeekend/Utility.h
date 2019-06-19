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

	
	inline static float getRandom01() { return DRand48::drand48(); }
};


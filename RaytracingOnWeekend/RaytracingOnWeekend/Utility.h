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

};


#pragma once
#define  _USE_MATH_DEFINES			//C++���ĵĵط������ֺ���룬ʹ��M_PI��Ҫ�� #include math.h ֮ǰ#define һ�������
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

	/*
		�Ƕ�ת����
	*/
	static float deg2rad(float degrees);

	/*
		����ת�Ƕ�
	*/
	static float rad2deg(float rad);

	inline static float getRandom01() { return DRand48::drand48(); }

	/*
		lerp
	*/
	inline static float lerp(float a, float b, float lerpFactor01) { return a + (b - a) * lerpFactor01; }

	/*
		����ӳ��
	*/
	static float remap(float currentVal, float inputMin, float inputMax, float outMin, float outMax);

	/*
		@brief:��ȡС������
	*/
	static float frac(float val);

	/*
		@brief:smoothstep ƽ������
	*/
	static float smoothstep(float val);

	/*
		@brief:���list,����ϴ���㷨
	*/
	static void shuffleArray(int* arr, int size);

};


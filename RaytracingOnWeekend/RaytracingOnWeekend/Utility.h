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
		lerp
	*/
	static vec3 lerp(vec3 a, vec3 b, float factor);

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
		@brief:vec3 ��smoothstepƽ������
	*/
	static vec3 smoothstep(vec3 val);

	/*
		@brief:���list,����ϴ���㷨
	*/
	static void shuffleArray(int* arr, int size);

	/*
		@brief:2D���Բ�ֵ
		lerpҲ��1D���Բ�ֵ��bilinear ����1D������
	*/
	static float bilinear_interpolate(float a, float b, float c, float d, float factorX, float factorY);

	/*
		@brief:Vector3��˫���Բ�ֵ
	*/


	/*
		@brief:3D���Բ�ֵ
	*/
	static float trilinear_interpolate(float a0, float b0, float c0, float d0, float a, float b, float c, float d, float factorX, float factorY, float factorZ);

	/*
		@brief:��ȡ�����ϵ��UV����

	*/
	static vec3 get_uv_by_sphere_point(const vec3 pointOnSphere);

	static float clamp(float val,float min,float max);

	static int clamp(int val, int min, int max);
};


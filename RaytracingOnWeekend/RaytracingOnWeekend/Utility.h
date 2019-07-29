#pragma once
#define  _USE_MATH_DEFINES			//C++恶心的地方，各种宏编译，使用M_PI需要在 #include math.h 之前#define 一次这个宏
#include "Vec3.h"
#include "DRand48.h"

/**
 * 各种帮助类
 */
class Utility
{
public:
	/**
	* hitpoint 上取出一个随机方向作为反射方法，继续反射
	   并没有使用物理意义上的Reflect(IncidentRay,Normal)作为反射方向
	*/
	static vec3 random_direction_in_unit_sphere();

	/**
	 * 电介质的Fresnel函数

		PS：η  eta
	 */
	static float fresnel(float cosi, float cost, float etai, float etat);

	static float fresnel(float cosi, float cost, float etai_over_etat);

	/*
		Schlick 对于Fresnel的近似  cosine是入射光与法线的dot
	*/
	static float schlick(float etai_over_etat, float cosine);

	/*
		角度转弧度
	*/
	static float deg2rad(float degrees);

	/*
		弧度转角度
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
		区间映射
	*/
	static float remap(float currentVal, float inputMin, float inputMax, float outMin, float outMax);

	/*
		@brief:获取小数部分
	*/
	static float frac(float val);

	/*
		@brief:smoothstep 平滑函数
	*/
	static float smoothstep(float val);

	/*
		@brief:vec3 的smoothstep平滑函数
	*/
	static vec3 smoothstep(vec3 val);

	/*
		@brief:随机list,还是洗牌算法
	*/
	static void shuffleArray(int* arr, int size);

	/*
		@brief:2D线性差值
		lerp也叫1D线性差值，bilinear 是在1D基础上
	*/
	static float bilinear_interpolate(float a, float b, float c, float d, float factorX, float factorY);

	/*
		@brief:Vector3的双线性差值
	*/


	/*
		@brief:3D线性差值
	*/
	static float trilinear_interpolate(float a0, float b0, float c0, float d0, float a, float b, float c, float d, float factorX, float factorY, float factorZ);

	/*
		@brief:获取球面上点的UV坐标

	*/
	static vec3 get_uv_by_sphere_point(const vec3 pointOnSphere);

	static float clamp(float val,float min,float max);

	static int clamp(int val, int min, int max);
};


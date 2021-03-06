#pragma once
/*
	Perlin 噪声

	每个点的值来源于一个grid 一般取点就近的整数值的4个方向（3D中8个方向的坐标）
		2D: 左上 左下 右上 右下
		3D: 2D基础上加入 前 后
*/
#include "Vec3.h"
#include "Utility.h"
class PerlinNoise
{
public:
	/**
	 * @brief:获取point的 Perlin 噪声值
	 */
	static float perlinNoise(const vec3& point);

	/**
	 * @brief:根据hitpoint的位置各种随机获取一个噪声值
	 */
	static float getRandomNoise(const vec3& point);

	/**
	 * @brief:PerlinNoise原理性的过程，在点所在立方体内的随机噪声
	 */
	static float noiseInCubic(const vec3& point);

	/*
	   @brief:生成随机数组，用于grid获取随机方向梯度

	   下面是一个普通使用的permutation
	   private static readonly int[] permutation = { 151,160,137,91,90,15,					// Hash lookup table as defined by Ken Perlin.  This is a randomly
		131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,	// arranged array of all numbers from 0-255 inclusive.
		190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
		88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
		77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
		102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
		135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
		5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
		223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
		129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
		251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
		49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
		138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,151
	};
	*/
	static float* permute_generater();

	/*
		每个轴上的随机梯度因子
	*/
	static int* perlin_permute_axis();

	//周期频率函数  也叫turbulence 加入其它点对于当前点的贡献
	static float Fbm(vec3 point, int octave);


	//一个总的随机器
	static float* perlin_permutation;
private:

	/*
		随机梯度生成器
	*/
	static vec3* permuate_vector_generator();

	/*
		随机梯度Hash表 ,使用真实的PerlinNoise的实现，原书中的 trilinear_interpo有点难理解
	*/
	static int* perlin_permution_table;

	//随机梯度值 获取u,v,w 位置的随机梯度值
	static float Gradient(int hash, float u, float v, float w);




	static int* permute_x;
	static int* permute_y;
	static int* permute_z;
};


#include "PerlinNoise.h"

float PerlinNoise::perlinNose(const vec3& point)
{
	float u = Utility::frac(point.x());
	float v = Utility::frac(point.y());
	float w = Utility::frac(point.z());

	return 0;
}

float PerlinNoise::getRandomNoise(const vec3& point)
{
	//乘个Factor 扩大区间 随机颜色产生
	int xRandom = int(10 * point.x()) & 255;
	int yRandom = int(10 * point.y()) & 255;
	int zRandom = int(10 * point.z()) & 255;

	//目的就是随机产生一个颜色值，
	return perlin_permutation[permute_x[xRandom] ^ permute_y[yRandom] ^ permute_z[zRandom]];
}

float* PerlinNoise::permute_generater()
{
	float* permutetion = new float[256];
	for (int i = 0; i < 256; ++i)
		permutetion[i] = DRand48::drand48();		//include相当于直接copy ，Utility.h中Include了DRand48.h，这里就不需要再重新include

	return permutetion;
}

int* PerlinNoise::perlin_permute_axis()
{
	int* axisPermute = new int[256];
	for (int i = 0; i < 256; ++i)
		axisPermute[i] = i;

	Utility::shuffleArray(axisPermute, 256);

	return axisPermute;
}

float* PerlinNoise::perlin_permutation = PerlinNoise::permute_generater();

//用于控制随机性
int* PerlinNoise::permute_x = PerlinNoise::perlin_permute_axis();
int* PerlinNoise::permute_y = PerlinNoise::perlin_permute_axis();
int* PerlinNoise::permute_z = PerlinNoise::perlin_permute_axis();
#include "PerlinNoise.h"

float PerlinNoise::perlinNoise(const vec3& point)
{
	//以一个单位立方体为单位
	float u = Utility::frac(point.x());
	float v = Utility::frac(point.y());
	float w = Utility::frac(point.z());

	int i = floor(point.x());

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

/*
	直接使用u,v,w插值会出现格子的效果
	再对u,v,w插值 Smoothstep

	getRanDomNoise() 如果密度特别大有点像白噪声，
		cubic之后，平滑了很多
		再一次smoothstep 近一步平滑，趋近于PerlinNoise
*/
float PerlinNoise::noiseInCubic(const vec3& point)
{
	//以一个单位立方体为单位
	float u = Utility::frac(point.x());
	float v = Utility::frac(point.y());
	float w = Utility::frac(point.z());

	//再一次对u,v,w smoothstep 
	u = Utility::smoothstep(u);
	v = Utility::smoothstep(v);
	w = Utility::smoothstep(w);

	//点所在的最小点
	int iX = floor(point.x());
	int iY = floor(point.y());
	int iZ = floor(point.z());

	//point 所在立方体8个顶点的随机梯度
	float cubicCorner[2][2][2];
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			for (int k = 0; k < 2; ++k)
			{
				int cornerIndexX = (iX + i) & 255;
				int cornerIndexY = (iY + j) & 255;
				int cornerIndexZ = (iZ + k) & 255;
				cubicCorner[i][j][k] = perlin_permutation[permute_x[cornerIndexX] ^ permute_y[cornerIndexY] ^ permute_z[cornerIndexZ]];
			}
		}
	}

	return Utility::trilinear_interpolate(
		cubicCorner[0][0][0], cubicCorner[1][0][0],
		cubicCorner[0][1][0], cubicCorner[1][1][0],
		cubicCorner[0][0][1], cubicCorner[1][0][1],
		cubicCorner[0][1][1], cubicCorner[1][1][1], u, v, w);
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
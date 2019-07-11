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
	//�˸�Factor �������� �����ɫ����
	int xRandom = int(10 * point.x()) & 255;
	int yRandom = int(10 * point.y()) & 255;
	int zRandom = int(10 * point.z()) & 255;

	//Ŀ�ľ����������һ����ɫֵ��
	return perlin_permutation[permute_x[xRandom] ^ permute_y[yRandom] ^ permute_z[zRandom]];
}

float* PerlinNoise::permute_generater()
{
	float* permutetion = new float[256];
	for (int i = 0; i < 256; ++i)
		permutetion[i] = DRand48::drand48();		//include�൱��ֱ��copy ��Utility.h��Include��DRand48.h������Ͳ���Ҫ������include

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

//���ڿ��������
int* PerlinNoise::permute_x = PerlinNoise::perlin_permute_axis();
int* PerlinNoise::permute_y = PerlinNoise::perlin_permute_axis();
int* PerlinNoise::permute_z = PerlinNoise::perlin_permute_axis();
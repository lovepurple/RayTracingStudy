#include "PerlinNoise.h"

float PerlinNoise::perlinNoise(const vec3& point)
{
	//��һ����λ������Ϊ��λ
	float u = Utility::frac(point.x());
	float v = Utility::frac(point.y());
	float w = Utility::frac(point.z());

	int i = floor(point.x());

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

/*
	ֱ��ʹ��u,v,w��ֵ����ָ��ӵ�Ч��
	�ٶ�u,v,w��ֵ Smoothstep

	getRanDomNoise() ����ܶ��ر���е����������
		cubic֮��ƽ���˺ܶ�
		��һ��smoothstep ��һ��ƽ����������PerlinNoise
*/
float PerlinNoise::noiseInCubic(const vec3& point)
{
	//��һ����λ������Ϊ��λ
	float u = Utility::frac(point.x());
	float v = Utility::frac(point.y());
	float w = Utility::frac(point.z());

	//��һ�ζ�u,v,w smoothstep 
	u = Utility::smoothstep(u);
	v = Utility::smoothstep(v);
	w = Utility::smoothstep(w);

	//�����ڵ���С��
	int iX = floor(point.x());
	int iY = floor(point.y());
	int iZ = floor(point.z());

	//point ����������8�����������ݶ�
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
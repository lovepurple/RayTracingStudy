#include "PerlinNoise.h"

float PerlinNoise::perlinNoise(const vec3& point)
{
	float u = Utility::frac(point.x());
	float v = Utility::frac(point.y());
	float w = Utility::frac(point.z());

	u = Utility::smoothstep(u);
	v = Utility::smoothstep(v);
	w = Utility::smoothstep(w);

	// 有负的情况
	int iX = abs(int(floor(point.x())) % 256);		//直接&255 如果数特别大的情况下，低位有可能相同的太多，造成重复选相同的随机数
	int iY = abs(int(floor(point.y())) % 256);
	int iZ = abs(int(floor(point.z())) % 256);

	//八个坐标的随机梯度表
	/*  Perlin 使用的方法，取2维 3维的随机梯度（直接当成固定算法去用）
		G2[P[x] + y]       ——二维
　　		G3[P[P[x] + y] +z]   ——三维
	*/

	int A = (PerlinNoise::perlin_permution_table[iX] + iY) & 255;
	int B = (PerlinNoise::perlin_permution_table[iX + 1] + iY) & 255;

	int AA = (PerlinNoise::perlin_permution_table[A] + iZ) & 255;
	int AB = (PerlinNoise::perlin_permution_table[A + 1] + iZ) & 255;

	int BA = (PerlinNoise::perlin_permution_table[B] + iZ) & 255;
	int BB = (PerlinNoise::perlin_permution_table[B + 1] + iZ) & 255;

	float x1 = Utility::lerp(
		Gradient(PerlinNoise::perlin_permution_table[AA], u, v, w),		//(0,0,0)
		Gradient(PerlinNoise::perlin_permution_table[BA], u - 1, v, w),	//(-1,0,0)
		u);

	float x2 = Utility::lerp(
		Gradient(PerlinNoise::perlin_permution_table[AB], u, v - 1, w),	//(0,-1,0)
		Gradient(PerlinNoise::perlin_permution_table[BB], u - 1, v - 1, w), //(-1,-1,0)
		u
	);

	float x3 = Utility::lerp(
		Gradient(PerlinNoise::perlin_permution_table[AA + 1], u, v, w - 1),		//(0,0,-1)
		Gradient(PerlinNoise::perlin_permution_table[BA + 1], u - 1, v, w - 1),	//(-1,0,-1
		u
	);

	float x4 = Utility::lerp(
		Gradient(PerlinNoise::perlin_permution_table[AB + 1], u, v - 1, w - 1),	//(0,-1,-1)
		Gradient(PerlinNoise::perlin_permution_table[BB + 1], u - 1, v - 1, w - 1), //(-1,-1,-1)
		u
	);
	float y1 = Utility::lerp(x1, x2, v);
	float y2 = Utility::lerp(x3, x4, v);


	//[-1,1] ->[0,1]
	return  (Utility::lerp(y1, y2, w) + 1) * 0.5;
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


vec3* PerlinNoise::permuate_vector_generator()
{
	vec3* perlin_permute_table = new vec3[256];
	for (int i = 0; i < 256; ++i)
		perlin_permute_table[i] = Utility::random_direction_in_unit_sphere();

	return perlin_permute_table;
}

//改进版的PerlinGrad 算法原算法太难理解 
float PerlinNoise::Gradient(int hash, float u, float v, float w)
{
	switch (hash & 0xF)
	{
	case 0x0: return  u + v;
	case 0x1: return -u + v;
	case 0x2: return  u - v;
	case 0x3: return -u - v;
	case 0x4: return  u + w;
	case 0x5: return -u + w;
	case 0x6: return  u - w;
	case 0x7: return -u - w;
	case 0x8: return  v + w;
	case 0x9: return -v + w;
	case 0xA: return  v - w;
	case 0xB: return -v - w;
	case 0xC: return  v + u;
	case 0xD: return -v + w;
	case 0xE: return  v - u;
	case 0xF: return -v - w;
	default: return 0; // never happens
	}
	return 0.0f;
}

float PerlinNoise::Fbm(vec3 point, int octave)
{
	float finalPerlinValue = 0.0f;
	float weight = 0.5f;
	vec3 tempPoint = point;

	for (int i = 0; i < octave; ++i)
	{
		finalPerlinValue += weight * perlinNoise(tempPoint);
		//越远的点影响越小,每次权重减小一半
		weight *= 0.5;
		tempPoint *= 2;
	}

	return finalPerlinValue;
}

//真实PerlinNoise的 Hash表
int* PerlinNoise::perlin_permution_table = new int[257]{
	151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225,
		140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148,
		247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32,
		57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175,
		74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122,
		60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54,
		65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169,
		200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64,
		52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212,
		207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213,
		119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9,
		129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104,
		218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241,
		81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 157,
		184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93,
		222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180,
		151
};

//一维
float* PerlinNoise::perlin_permutation = PerlinNoise::permute_generater();

//用于控制随机性
int* PerlinNoise::permute_x = PerlinNoise::perlin_permute_axis();
int* PerlinNoise::permute_y = PerlinNoise::perlin_permute_axis();
int* PerlinNoise::permute_z = PerlinNoise::perlin_permute_axis();
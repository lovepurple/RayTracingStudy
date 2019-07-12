# 渲染图像说明
### 第一部分都是简单算法跟据Point的xyz XOR出的一个颜色，频率非常高，无规律
+ SimpleNoise_1.png 采用随机数组，根据Point的位置获取颜色
+ SimpleNoise_2.png 在1的基础上，加入tiling *point 控制疏密程序
+ SimpleNoise_3.png seed[x] ^ seed[y] ^ seed[z] 控制最终 Point 对应的颜色
+ SimpleNoise_LargeTilling.png 更大的Tilling 更密的噪音

### 第二部分，Cubic ，每个点的颜色值用 立方体插值出颜色，频率更低
>
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
+ CubicInterpolateNoise.png 用上方的算法，再计算时，使用周围8个点的坐标进行插值，问题是由于上面使用的都是整数坐标，可能在不同的point上就近的坐标采样到了一个上，有方块感
+ CubicInterpolateNoise_SmoothStep.png 对frac(x,y,z) 再进行smoothstep插值，两段频率更低相对于上面看上去更柔和 
    
    float u = Utility::frac(point.x());
    float v = Utility::frac(point.y());
    float w = Utility::frac(point.z());
    //再一次对u,v,w smoothstep 
    u = Utility::smoothstep(u);
    v = Utility::smoothstep(v);
    w = Utility::smoothstep(w);
+ CubicInterpolateNoise_SmoothStep_InputTilling.png 在上面的基础上加入>1 的tiling 

### 第三部分，真实的Perlin Noise
+ PerlinNoise.png 真实的Perlin Noise算法，Perlin Hash 
+ PerlinNOise_Octave.png PerlinNoise基础上加入Octave每个点的权重迭代，接近于大部分PerlinNoise效果。
+ PerlinNoise_Octace_Sin.png vec3::ONE * 0.5 * (1 + sin(m_tiling * point.z() + 20 * PerlinNoise::Fbm(point, 8)));

PerlinNoise 可进行分形叠加 a * perlinNoise(point * b) + .... 
加入各种经验模型 可产生很多效果
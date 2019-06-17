#pragma once
/**
 * 引入Screen 方便计算像素一些逻辑
 */
#include "Vec3.h"

#define DOWNLOAD_SAMPLE_RATIO 1
#define RENDER_IMAGE_WIDTH 1920.0/DOWNLOAD_SAMPLE_RATIO
#define RENDER_IMAGE_HEIGHT 1200.0/DOWNLOAD_SAMPLE_RATIO
#define SCREEN_PARAM (RENDER_IMAGE_WIDTH)/(RENDER_IMAGE_HEIGHT)		//宏是直接展开，加不加括号的问题
#define ANTI_ANTIALIASING_TIMES 1			//上采样次数，同一像素中随机采样次数

class Screen
{
public:
	static vec3 normalizedUVtoReal(const vec3& normalizedUV);
};


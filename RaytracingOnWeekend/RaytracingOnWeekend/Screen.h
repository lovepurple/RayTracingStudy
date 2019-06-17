#pragma once
/**
 * ����Screen �����������һЩ�߼�
 */
#include "Vec3.h"

#define DOWNLOAD_SAMPLE_RATIO 1
#define RENDER_IMAGE_WIDTH 1920.0/DOWNLOAD_SAMPLE_RATIO
#define RENDER_IMAGE_HEIGHT 1200.0/DOWNLOAD_SAMPLE_RATIO
#define SCREEN_PARAM (RENDER_IMAGE_WIDTH)/(RENDER_IMAGE_HEIGHT)		//����ֱ��չ�����Ӳ������ŵ�����
#define ANTI_ANTIALIASING_TIMES 1			//�ϲ���������ͬһ�����������������

class Screen
{
public:
	static vec3 normalizedUVtoReal(const vec3& normalizedUV);
};


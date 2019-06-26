#pragma once
#include <iostream>
#include <fstream>
#include "Sphere.h"
#include "HitableList.h"
#include "float.h"
#include "Screen.h"
#include "Camera.h"
#include "Utility.h"
#include "LambertianMaterial.h"
#include "MetalMaterial.h"
#include "DielectricMaterial.h"
#include <typeinfo>
#include <time.h>

#define cout fout
#define MAX_TRACING_TIMES 10		//最大追踪次数


float hit_sphere(const vec3 & center, float sphereRadius, const ray & r) {
	//直线方程和圆方程联立，中间步骤省略
	//对于渲染出的图，sphereRadius使用的是物理的距离，并不是实际像素的半径，要进行uv变换
	//球方程 (x-x0)^2 + (y-y0)^2 + (z-z0)^2 = R*R
	vec3 origin_to_center = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(origin_to_center, r.direction());
	float c = dot(origin_to_center, origin_to_center) - sphereRadius * sphereRadius;

	float discriminant = b * b - 4 * a * c;

	//计算射线与球的相交点
	if (discriminant < 0)
		return -1;
	else
		return (-b - sqrt(discriminant)) / (2.0 * a);
}


int m_reflectTimes = 0;

vec3 get_skybox_color(const ray& cameraRay) {
	vec3 normalized_direction = unit_vector(cameraRay.direction());
	float backgroundLerpFactor = (normalized_direction.y() + 1.0f) * 0.5f;

	return (1.0f - backgroundLerpFactor) * vec3(1.0, 1.0, 1.0) + backgroundLerpFactor * vec3(0.5, 0.7, 1);
}

vec3 debug_hitpoint_normal(const ray& tracingRay, Hitable* world) {
	HitInfo hitInfo;
	if (world->Hit(tracingRay, FLT_TRUE_MIN, FLT_MAX, hitInfo))
		return toColor(hitInfo.HitPointNormal);

	return get_skybox_color(tracingRay);
}

vec3 debug_reflect_dir(const ray& tracingRay, Hitable* world) {
	HitInfo hitInfo;
	if (world->Hit(tracingRay, FLT_TRUE_MIN, FLT_MAX, hitInfo))
	{
		vec3 reflectDir = reflect(tracingRay.direction(), hitInfo.HitPointNormal);
		float dotValue = dot(reflectDir, hitInfo.HitPointNormal);
		vec3 col = dotValue > 0 ? toColor(dotValue) : vec3::ZERO;
		return col;
	}

	return get_skybox_color(tracingRay);
}

vec3 debug_hitpoint(const ray& tracingRay, Hitable* world) {
	HitInfo hitInfo;
	if (world->Hit(tracingRay, FLT_TRUE_MIN, FLT_MAX, hitInfo))
		return toColor(hitInfo.HitPoint);

	return get_skybox_color(tracingRay);
}

/**
 * world中存的是场景，hitable*实现是hitable_list
	击中返回击中点法线
 */
vec3 color(const ray& tracingRay, Hitable* world) {
	HitInfo hitInfo;
	if (world->Hit(tracingRay, 0.0, FLT_MAX, hitInfo)) {
		m_reflectTimes++;
		//return toColor(hitInfo.HitPointNormal);

		//击中之后取随机方向继续跟踪，直到不击中
		vec3 reflectDir = hitInfo.HitPoint + hitInfo.HitPointNormal + Utility::random_direction_in_unit_sphere();

		ray reflectRayFromHitpoint = ray(hitInfo.HitPoint, unit_vector(reflectDir));

		/*递归调用，对于C++ 默认栈的大小是1M，多次反射在分辨率高的情况下（递归次数过多），极有可能出现栈溢出的情况
				Properties->Linker->System -> Stack Reseve Size 修改栈的大小 （单位是字节 byte ）
				也可以用指针解决，在堆中分配内存
		*/

		//每次击中，变暗一半
		if (m_reflectTimes > MAX_TRACING_TIMES)
			return vec3::ZERO;

		return 0.5f * color(reflectRayFromHitpoint, world);

	}
	else
	{
		vec3 normalized_direction = unit_vector(tracingRay.direction());			//C++里名不能重复，函数参数名不能跟类名一样
		float backgroundLerpFactor = (normalized_direction.y() + 1.0f) * 0.5f;			//（-1,1） to color

		return (1.0f - backgroundLerpFactor) * vec3(1.0, 1.0, 1.0) + backgroundLerpFactor * vec3(0.5, 0.7, 1);		//lerp(vec3(1,1,1),vec3(0.5,0.7,1),t)
	}
}

vec3 color(const ray& tracingRay, Hitable* world, int tracingTimes) {
	HitInfo hitInfo;

	if (world->Hit(tracingRay, 0.0001f, FLT_MAX, hitInfo)) {
		ray	outRay;
		vec3 attenuation;
		bool isContinueTracing = hitInfo.mat_ptr->scatter(tracingRay, hitInfo, attenuation, outRay);

		//光线根据击中材质的不同进一步散射
		if (tracingTimes < MAX_TRACING_TIMES && isContinueTracing)
		{
			return attenuation * color(outRay, world, ++tracingTimes);
		}
		else
			return vec3::ZERO;			//一个像素会进行多次追踪，有可能该点就是黑色的
	}
	else
		return get_skybox_color(tracingRay);
}

vec3 color(const ray& r) {		//C++中，传的参数如果是引用类型，定义的时候需要使用&
	vec3 sphereCenter = Screen::normalizedUVtoReal(vec3(0.2, 0.2, -1));
	//todo:使用半径为0.5时会超出区域，原因可能是球有z的方向，在屏幕上投影问题

	//计算相交点
	float t = hit_sphere(sphereCenter, 0.1, r);
	if (t > 0.0f)
	{
		vec3 hitPointOnSphere = r.point_at_parameter(t);
		vec3 sphereNormal = unit_vector(hitPointOnSphere - sphereCenter);
		return toColor(sphereNormal);
	}

	vec3 normalized_direction = unit_vector(r.direction());
	float backgroundLerpFactor = (normalized_direction.y() + 1.0f) * 0.5f;			//（-1,1） to color

	return (1.0f - backgroundLerpFactor) * vec3(1.0, 1.0, 1.0) + backgroundLerpFactor * vec3(0.5, 0.7, 1);		//lerp(vec3(1,1,1),vec3(0.5,0.7,1),t)
}



vec3 pixelToNormalizeUV(int pixelX, int pixelY) {

	return vec3(pixelX / (RENDER_IMAGE_WIDTH - 1), pixelY / (RENDER_IMAGE_HEIGHT - 1));
}


HitableList* getHitableWorld() {
	//加入扰动
	Sphere* sphere1 = new Sphere(Screen::normalizedUVtoReal(vec3(0, 0, -1)), 0.5f, new MetalMaterial(vec3(0.8, 0.6, 0.2), 0.1));
	Sphere* sphere2 = new Sphere(Screen::normalizedUVtoReal(vec3(-1, 0, -1)), 0.5f, new DielectricMaterial(1.5f));

	Sphere* sphere3 = new Sphere(Screen::normalizedUVtoReal(vec3(0.5f, 0.5f, -1)), 0.125f, new LambertianMaterial(vec3(0.8, 0.3, 0.3)));
	Sphere* sphere4 = new Sphere(Screen::normalizedUVtoReal(vec3(0.5f, -50.0f, -1)), 50.0f, new LambertianMaterial(vec3(0.8, 0.8, 0)));
	Sphere* sphere5 = new Sphere(Screen::normalizedUVtoReal(vec3(0.25f, 0.2f, -1)), 0.125f, new DielectricMaterial(0.8f));

	int worldObjectCount = 5;
	Hitable** worldObjectList = new Hitable * [worldObjectCount];			//指针数组的声明
	worldObjectList[0] = sphere1;
	worldObjectList[1] = sphere2;
	worldObjectList[2] = sphere3;
	worldObjectList[3] = sphere4;
	worldObjectList[4] = sphere5;

	HitableList* world = new HitableList(worldObjectList, worldObjectCount);

	return world;
}

HitableList* getRandomWorld() {
	int worldObjectCount = 500;

	Hitable** worldObjectList = new Hitable * [worldObjectCount + 1];
	worldObjectList[0] = new Sphere(vec3(0, -1000, 1), 1000, new LambertianMaterial(vec3(0.5, 0.5, 0.5)));
	int i = 1;
	for (int a = -8; a < 8; ++a)
	{
		for (int b = -8; b < 8; ++b)
		{
			float radMat = Utility::getRandom01();
			vec3 sphereCenter(a + 0.9f * Utility::getRandom01(), 0.2, b + 0.9f * Utility::getRandom01());
			if (radMat < 0.33)
				worldObjectList[i++] = new Sphere(sphereCenter, 0.2f, new LambertianMaterial(vec3(Utility::getRandom01() * Utility::getRandom01(), Utility::getRandom01() * Utility::getRandom01(), Utility::getRandom01() * Utility::getRandom01())));
			else if (radMat < 0.66)
				worldObjectList[i++] = new Sphere(sphereCenter, 0.2f, new MetalMaterial(vec3(
					0.5 * (1 + Utility::getRandom01()),
					0.5 * (1 + Utility::getRandom01()),
					0.5 * (1 + Utility::getRandom01())), 0.5 * Utility::getRandom01()));
			else
				worldObjectList[i++] = new Sphere(sphereCenter, 0.2, new DielectricMaterial(1.5));
		}
	}

	worldObjectList[i++] = new Sphere(vec3(1.5, 1.2, -2.5), 1.2, new DielectricMaterial(1.5));
	worldObjectList[i++] = new Sphere(vec3(-1, 1.5, -3), 1.5, new LambertianMaterial(vec3(0.4, 0.2, 0.1)));
	worldObjectList[i++] = new Sphere(vec3(3.5, 1, -2), 1.0, new MetalMaterial(vec3(0.7, 0.6, 0.5), 0));


	return new HitableList(worldObjectList, i);
}

int main() {

	std::ofstream fout("d:\\renderImage.ppm");			//重定向cout到文件

	//以PPM格式记录
	cout << "P3 \n" << RENDER_IMAGE_WIDTH << " " << RENDER_IMAGE_HEIGHT << "\n255\n";

	/*
		关于uv*screenParam的理解：
			1. 整个屏幕的uv范围是[0,1]正方形 ，但实现屏幕分辨率大多数情况下都是长宽不相等
			2. 为了方便计算，所有的坐标都是按[0,1]计算，因此像素实际的位置需要*screenParam
	*/

	Camera camera = Camera(vec3(5, 1.5, 2), vec3(0.5, 1.2, -1), vec3(0, 1, 0), 75.0, SCREEN_PARAM, 2.0);
	//camera = Camera(vec3(0, 3, 0), vec3(0, 0, -1), vec3::UP, 90, SCREEN_PARAM, 2.0f, 1);


	HitableList* world = getRandomWorld();

	try
	{
		//Pixel Coordiate
		for (int j = RENDER_IMAGE_HEIGHT - 1; j >= 0; j--)
		{
			for (int i = 0; i < RENDER_IMAGE_WIDTH; ++i)
			{
				//对每个像素内部再随机采样，差值出颜色，抗锯齿
				vec3 pixelColor = vec3::ZERO;
				for (int k = 0; k < ANTI_ANTIALIASING_TIMES; ++k)
				{
					//获取当前像素的随机采样
					float texel_u = (((float)i + DRand48::drand48()) / (RENDER_IMAGE_WIDTH - 1));
					float texel_v = (((float)j + DRand48::drand48()) / (RENDER_IMAGE_HEIGHT - 1));

					ray cameraRayToPixel = camera.get_camera_ray(texel_u, texel_v);

					pixelColor += color(cameraRayToPixel, world, 0);
				}
				pixelColor /= (float)ANTI_ANTIALIASING_TIMES;

				//gamma纠正， color ^ 1/gamma,提亮暗部（多次追踪后，颜色一次次衰减太暗）
				//pixelColor = toGammaColor(pixelColor, 0.95f);

				int ir = int(255.99 * pixelColor[0]);
				int ig = int(255.99 * pixelColor[1]);
				int ib = int(255.99 * pixelColor[2]);

				cout << ir << " " << ig << " " << ib << " ";

			}
			cout << "\n";
		}
	}
	catch (const std::exception&)
	{

	}


	return 0;
}
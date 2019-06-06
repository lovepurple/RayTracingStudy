#pragma once
#include <iostream>
#include <fstream>
#include "Sphere.h"
#include "HitableList.h"
#include "float.h"
#include "Screen.h"
#include "Camera.h"
#include "DRand48.h"

#define cout fout



float hit_sphere(const vec3& center, float sphereRadius, const ray& r) {
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

/**
 * world中存的是场景，hitable*实现是hitable_list
	击中返回击中点法线
 */
vec3 color(const ray& ray, Hitable* world) {
	HitInfo hitInfo;
	if (world->Hit(ray, 0.0, FLT_MAX, hitInfo)) {
		return toColor(hitInfo.HitPointNormal);
	}
	else
	{
		vec3 normalized_direction = unit_vector(ray.direction());
		float backgroundLerpFactor = (normalized_direction.y() + 1.0f) * 0.5f;			//（-1,1） to color

		return (1.0f - backgroundLerpFactor) * vec3(1.0, 1.0, 1.0) + backgroundLerpFactor * vec3(0.5, 0.7, 1);		//lerp(vec3(1,1,1),vec3(0.5,0.7,1),t)
	}
}

vec3 color(const ray& r) {		//C++中，传的参数如果是引用类型，定义的时候需要使用&
	vec3 sphereCenter = Screen::normalizedUVtoReal(vec3(0.5, 0.5, -1));

	//todo:使用半径为0.5时会超出区域，原因可能是球有z的方向，在屏幕上投影问题

	//计算相交点
	float t = hit_sphere(sphereCenter, 0.4, r);
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

vec3 lerp(const vec3& vec1, const vec3& vec2, float factor) {
	return (1 - factor) * vec1 + vec2 * factor;
}

vec3 pixelToNormalizeUV(int pixelX, int pixelY) {

	return vec3(pixelX / (RENDER_IMAGE_WIDTH - 1), pixelY / (RENDER_IMAGE_HEIGHT - 1));
}


vec3 uvToPixel(const vec3& uv) {
	return vec3(uv.x() * RENDER_IMAGE_WIDTH, uv.y() * RENDER_IMAGE_HEIGHT, 0);
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

	Camera camera = Camera();

	//构建多个物体
	Sphere* sphere1 = new Sphere(Screen::normalizedUVtoReal(vec3(0.5f, 0.5f, -1)), 0.4f);
	Sphere* sphere2 = new Sphere(Screen::normalizedUVtoReal(vec3(0.5f, -50.0f, -1)), 50.0f);	//特别大的球
	Hitable* worldObjectList[2];
	worldObjectList[0] = sphere1;
	worldObjectList[1] = sphere2;

	HitableList* world = new HitableList(worldObjectList, 2);

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

				vec3 pixelUV = Screen::normalizedUVtoReal(vec3(texel_u, texel_v, -1));
				ray cameraRayToPixel = camera.get_ray(pixelUV.x(), pixelUV.y());
				pixelColor += color(cameraRayToPixel, world);
			}
			pixelColor /= (float)ANTI_ANTIALIASING_TIMES;


			int ir = int(255.99 * pixelColor[0]);
			int ig = int(255.99 * pixelColor[1]);
			int ib = int(255.99 * pixelColor[2]);

			cout << ir << " " << ig << " " << ib << " ";

		}
		cout << "\n";
	}

	return 0;
}
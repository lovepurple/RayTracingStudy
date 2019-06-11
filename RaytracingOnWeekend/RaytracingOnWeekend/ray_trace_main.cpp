#pragma once
#include <iostream>
#include <fstream>
#include "Sphere.h"
#include "HitableList.h"
#include "float.h"
#include "Screen.h"
#include "Camera.h"
#include "DRand48.h"
#include "Utility.h"
#include "LambertianMaterial.h"
#include "MetalMaterial.h"

#define cout fout
#define MAX_TRACING_TIMES 10		//���׷�ٴ���


float hit_sphere(const vec3 & center, float sphereRadius, const ray & r) {
	//ֱ�߷��̺�Բ�����������м䲽��ʡ��
	//������Ⱦ����ͼ��sphereRadiusʹ�õ�������ľ��룬������ʵ�����صİ뾶��Ҫ����uv�任
	//�򷽳� (x-x0)^2 + (y-y0)^2 + (z-z0)^2 = R*R
	vec3 origin_to_center = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(origin_to_center, r.direction());
	float c = dot(origin_to_center, origin_to_center) - sphereRadius * sphereRadius;

	float discriminant = b * b - 4 * a * c;

	//��������������ཻ��
	if (discriminant < 0)
		return -1;
	else
		return (-b - sqrt(discriminant)) / (2.0 * a);
}


int m_reflectTimes = 0;
/**
 * world�д���ǳ�����hitable*ʵ����hitable_list
	���з��ػ��е㷨��
 */
vec3 color(const ray& tracingRay, Hitable* world) {
	HitInfo hitInfo;
	if (world->Hit(tracingRay, 0.0, FLT_MAX, hitInfo)) {
		m_reflectTimes++;
		//return toColor(hitInfo.HitPointNormal);

		//����֮��ȡ�������������٣�ֱ��������
		vec3 reflectDir = hitInfo.HitPoint + hitInfo.HitPointNormal + Utility::random_direction_in_unit_sphere();

		ray reflectRayFromHitpoint = ray(hitInfo.HitPoint, unit_vector(reflectDir));

		/*�ݹ���ã�����C++ Ĭ��ջ�Ĵ�С��1M����η����ڷֱ��ʸߵ�����£��ݹ�������ࣩ�����п��ܳ���ջ��������
				Properties->Linker->System -> Stack Reseve Size �޸�ջ�Ĵ�С ����λ���ֽ� byte ��
				Ҳ������ָ�������ڶ��з����ڴ�
		*/

		//ÿ�λ��У��䰵һ��

		if (m_reflectTimes > MAX_TRACING_TIMES)
			return vec3::ZERO;

		return 0.5f * color(reflectRayFromHitpoint, world);

	}
	else
	{
		vec3 normalized_direction = unit_vector(tracingRay.direction());			//C++���������ظ����������������ܸ�����һ��
		float backgroundLerpFactor = (normalized_direction.y() + 1.0f) * 0.5f;			//��-1,1�� to color

		return (1.0f - backgroundLerpFactor) * vec3(1.0, 1.0, 1.0) + backgroundLerpFactor * vec3(0.5, 0.7, 1);		//lerp(vec3(1,1,1),vec3(0.5,0.7,1),t)
	}
}

vec3 color(const ray& tracingRay, Hitable* world, int tracingTimes) {
	HitInfo hitInfo;

	if (world->Hit(tracingRay, 0.0001f, FLT_MAX, hitInfo)) {
		ray	reflectRay;
		vec3 attenuation;

		//��һ��׷��
		if (tracingTimes < MAX_TRACING_TIMES && hitInfo.mat_ptr->scatter(tracingRay, hitInfo, attenuation, reflectRay)) {
			return attenuation * color(reflectRay, world, ++tracingTimes);
		}
		else
			return vec3::ZERO;
	}
	else
	{
		//�൱��Skybox
		vec3 normalized_direction = unit_vector(tracingRay.direction());
		float backgroundLerpFactor = (normalized_direction.y() + 1.0f) * 0.5f;

		return (1.0f - backgroundLerpFactor) * vec3(1.0, 1.0, 1.0) + backgroundLerpFactor * vec3(0.5, 0.7, 1);
	}

}

vec3 color(const ray& r) {		//C++�У����Ĳ���������������ͣ������ʱ����Ҫʹ��&
	vec3 sphereCenter = Screen::normalizedUVtoReal(vec3(0.5, 0.5, -1));

	//todo:ʹ�ð뾶Ϊ0.5ʱ�ᳬ������ԭ�����������z�ķ�������Ļ��ͶӰ����

	//�����ཻ��
	float t = hit_sphere(sphereCenter, 0.4, r);
	if (t > 0.0f)
	{
		vec3 hitPointOnSphere = r.point_at_parameter(t);
		vec3 sphereNormal = unit_vector(hitPointOnSphere - sphereCenter);
		return toColor(sphereNormal);
	}

	vec3 normalized_direction = unit_vector(r.direction());
	float backgroundLerpFactor = (normalized_direction.y() + 1.0f) * 0.5f;			//��-1,1�� to color

	return (1.0f - backgroundLerpFactor) * vec3(1.0, 1.0, 1.0) + backgroundLerpFactor * vec3(0.5, 0.7, 1);		//lerp(vec3(1,1,1),vec3(0.5,0.7,1),t)
}



vec3 pixelToNormalizeUV(int pixelX, int pixelY) {

	return vec3(pixelX / (RENDER_IMAGE_WIDTH - 1), pixelY / (RENDER_IMAGE_HEIGHT - 1));
}


vec3 uvToPixel(const vec3& uv) {
	return vec3(uv.x() * RENDER_IMAGE_WIDTH, uv.y() * RENDER_IMAGE_HEIGHT, 0);
}

HitableList* getHitableWorld(int& worldObjectCount) {
	Sphere* sphere1 = new Sphere(Screen::normalizedUVtoReal(vec3(0.5f, 0.5f, -1)), 0.2f, new LambertianMaterial(vec3(0.8, 0.3, 0.3)));
	Sphere* sphere2 = new Sphere(Screen::normalizedUVtoReal(vec3(0.5f, -50.0f, -1)), 50.0f, new LambertianMaterial(vec3(0.8, 0.8, 0)));
	Sphere* sphere3 = new Sphere(Screen::normalizedUVtoReal(vec3(0.5f, 0.5f, -1)), 0.2f, new MetalMaterial(vec3(0.6, 0.6, 0.2)));
	Sphere* sphere4 = new Sphere(Screen::normalizedUVtoReal(vec3(0.2f, 0.5f, -1)), 0.2f, new MetalMaterial(vec3(0.8, 0.8, 0.8)));
	sphere1 = sphere3;

	worldObjectCount = 4;
	Hitable** worldObjectList = new Hitable * [worldObjectCount];			//ָ�����������
	worldObjectList[0] = sphere1;
	worldObjectList[1] = sphere2;
	worldObjectList[2] = sphere3;
	worldObjectList[3] = sphere4;

	HitableList* world = new HitableList(worldObjectList, 1);

	return world;
}

int main() {
	std::ofstream fout("d:\\renderImage.ppm");			//�ض���cout���ļ�


	//��PPM��ʽ��¼
	cout << "P3 \n" << RENDER_IMAGE_WIDTH << " " << RENDER_IMAGE_HEIGHT << "\n255\n";


	/*
		����uv*screenParam����⣺
			1. ������Ļ��uv��Χ��[0,1]������ ����ʵ����Ļ�ֱ��ʴ��������¶��ǳ������
			2. Ϊ�˷�����㣬���е����궼�ǰ�[0,1]���㣬�������ʵ�ʵ�λ����Ҫ*screenParam
	*/

	Camera camera = Camera();

	//�����������
	Sphere* sphere1 = new Sphere(Screen::normalizedUVtoReal(vec3(0.5f, 0.5f, -1)), 0.4f);
	Sphere* sphere2 = new Sphere(Screen::normalizedUVtoReal(vec3(0.5f, -50.0f, -1)), 50.0f);	//�ر�����
	Hitable* worldObjectList[2];
	worldObjectList[0] = sphere1;
	worldObjectList[1] = sphere2;

	//HitableList* world = new HitableList(worldObjectList, 2);
	int worldObjectCount = 0;
	HitableList* world = getHitableWorld(worldObjectCount);


	//Pixel Coordiate
	for (int j = RENDER_IMAGE_HEIGHT - 1; j >= 0; j--)
	{
		for (int i = 0; i < RENDER_IMAGE_WIDTH; ++i)
		{
			//��ÿ�������ڲ��������������ֵ����ɫ�������
			vec3 pixelColor = vec3::ZERO;
			for (int k = 0; k < ANTI_ANTIALIASING_TIMES; ++k)
			{
				//��ȡ��ǰ���ص��������
				float texel_u = (((float)i + DRand48::drand48()) / (RENDER_IMAGE_WIDTH - 1));
				float texel_v = (((float)j + DRand48::drand48()) / (RENDER_IMAGE_HEIGHT - 1));

				vec3 pixelUV = Screen::normalizedUVtoReal(vec3(texel_u, texel_v, -1));
				ray cameraRayToPixel = camera.get_ray(pixelUV.x(), pixelUV.y());

				pixelColor += color(cameraRayToPixel, world, 0);
			}
			pixelColor /= (float)ANTI_ANTIALIASING_TIMES;

			//gamma������ color ^ 1/gamma,��������
			//pixelColor = toGammaColor(pixelColor, 0.5f);

			int ir = int(255.99 * pixelColor[0]);
			int ig = int(255.99 * pixelColor[1]);
			int ib = int(255.99 * pixelColor[2]);

			cout << ir << " " << ig << " " << ib << " ";

		}
		cout << "\n";
	}

	return 0;
}
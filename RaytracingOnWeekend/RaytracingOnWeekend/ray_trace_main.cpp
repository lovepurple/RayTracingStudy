#include <iostream>
#include <fstream>
#include "Sphere.h"
#include "HitableList.h"
#include "float.h"


#define DOWNLOAD_SAMPLE_RATIO 1
#define RENDER_IMAGE_WIDTH 1920.0/DOWNLOAD_SAMPLE_RATIO
#define RENDER_IMAGE_HEIGHT 1200.0/DOWNLOAD_SAMPLE_RATIO
#define SCREEN_PARAM (RENDER_IMAGE_WIDTH)/(RENDER_IMAGE_HEIGHT)		//����ֱ��չ�����Ӳ������ŵ�����
#define cout fout

vec3 normalizeUVtoRealCoord(const vec3 & normalizedUV) {
	return vec3(normalizedUV.x() * SCREEN_PARAM, normalizedUV.y(), normalizedUV.z());
}


float hit_sphere(const vec3& center, float sphereRadius, const ray& r) {
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

/**
 * world�д���ǳ�����hitable*ʵ����hitable_list
	���з��ػ��е㷨��
 */
vec3 color(const ray& ray, Hitable* world) {
	HitInfo hitInfo;
	if (world->Hit(ray, 0.0, FLT_MAX, hitInfo)) {
		return toColor(hitInfo.HitPointNormal);
	}
	else
	{
		vec3 normalized_direction = unit_vector(ray.direction());
		float backgroundLerpFactor = (normalized_direction.y() + 1.0f) * 0.5f;			//��-1,1�� to color

		return (1.0f - backgroundLerpFactor) * vec3(1.0, 1.0, 1.0) + backgroundLerpFactor * vec3(0.5, 0.7, 1);		//lerp(vec3(1,1,1),vec3(0.5,0.7,1),t)
	}
}

vec3 color(const ray& r) {		//C++�У����Ĳ���������������ͣ������ʱ����Ҫʹ��&
	vec3 sphereCenter = normalizeUVtoRealCoord(vec3(0.5, 0.5, -1));

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

vec3 lerp(const vec3& a, const vec3& b, float factor) {
	return (1 - factor) * a + b * factor;
}

vec3 pixelToNormalizeUV(int pixelX, int pixelY) {

	return vec3(pixelX / (RENDER_IMAGE_WIDTH - 1), pixelY / (RENDER_IMAGE_HEIGHT - 1));
}


vec3 uvToPixel(const vec3& uv) {
	return vec3(uv.x() * RENDER_IMAGE_WIDTH, uv.y() * RENDER_IMAGE_HEIGHT, 0);
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
	vec3 rayOrigin = normalizeUVtoRealCoord(vec3(0.5, 0.5, 0));

	//�����������
	Sphere* sphere1 = new Sphere(normalizeUVtoRealCoord(vec3(0.5f, 0.5f, -1)), 0.4f);
	Sphere* sphere2 = new Sphere(normalizeUVtoRealCoord(vec3(0.5f, -50.0f, -1)), 50.0f);	//�ر�����
	Hitable* worldObjectList[2];
	worldObjectList[0] = sphere1;
	worldObjectList[1] = sphere2;

	HitableList* world = new HitableList(worldObjectList, 2);


	//Pixel Coordiate
	for (int j = RENDER_IMAGE_HEIGHT - 1; j >= 0; j--)
	{
		for (int i = 0; i < RENDER_IMAGE_WIDTH; ++i)
		{
			float texel_u = ((float)i / (RENDER_IMAGE_WIDTH - 1));
			float texel_v = ((float)j / (RENDER_IMAGE_HEIGHT - 1));

			vec3 pixelUV = normalizeUVtoRealCoord(vec3(texel_u, texel_v, -1));
			ray rayToPixel = ray(rayOrigin, unit_vector(pixelUV - rayOrigin));
			vec3 pixelColor = color(rayToPixel, world);

			int ir = int(255.99 * pixelColor[0]);
			int ig = int(255.99 * pixelColor[1]);
			int ib = int(255.99 * pixelColor[2]);

			cout << ir << " " << ig << " " << ib << " ";

		}
		cout << "\n";
	}

	return 0;
}
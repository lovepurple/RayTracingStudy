#include <iostream>
#include <fstream>
#include "ray.h"

#define DOWNLOAD_SAMPLE_RATIO 1
#define RENDER_IMAGE_WIDTH 1920.0/DOWNLOAD_SAMPLE_RATIO
#define RENDER_IMAGE_HEIGHT 1200.0/DOWNLOAD_SAMPLE_RATIO
#define SCREEN_PARAM (RENDER_IMAGE_WIDTH)/(RENDER_IMAGE_HEIGHT)		//宏是直接展开，加不加括号的问题
#define cout fout

vec3 normalizeUVtoRealCoord(const vec3 & normalizedUV) {
	return vec3(normalizedUV.x() * SCREEN_PARAM, normalizedUV.y(), normalizedUV.z());
}


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


vec3 color(const ray& r) {		//C++中，传的参数如果是引用类型，定义的时候需要使用&
	vec3 sphereCenter = normalizeUVtoRealCoord(vec3(0.5, 0.5, -1));

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
	std::ofstream fout("d:\\renderImage.ppm");			//重定向cout到文件

	//以PPM格式记录
	cout << "P3 \n" << RENDER_IMAGE_WIDTH << " " << RENDER_IMAGE_HEIGHT << "\n255\n";

	/*
		关于uv*screenParam的理解：
			1. 整个屏幕的uv范围是[0,1]正方形 ，但实现屏幕分辨率大多数情况下都是长宽不相等
			2. 为了方便计算，所有的坐标都是按[0,1]计算，因此像素实际的位置需要*screenParam
	*/
	vec3 rayOrigin = normalizeUVtoRealCoord(vec3(0.5, 0.5, 0));


	//Pixel Coordiate
	for (int j = RENDER_IMAGE_HEIGHT - 1; j >= 0; j--)
	{
		for (int i = 0; i < RENDER_IMAGE_WIDTH; ++i)
		{
			float texel_u = ((float)i / (RENDER_IMAGE_WIDTH - 1));
			float texel_v = ((float)j / (RENDER_IMAGE_HEIGHT - 1));

			vec3 pixelUV = normalizeUVtoRealCoord(vec3(texel_u, texel_v, -1));
			ray rayToPixel = ray(rayOrigin, unit_vector(pixelUV - rayOrigin));
			vec3 pixelRayDirectionCol = color(rayToPixel);

			int ir = int(255.99 * pixelRayDirectionCol[0]);
			int ig = int(255.99 * pixelRayDirectionCol[1]);
			int ib = int(255.99 * pixelRayDirectionCol[2]);

			cout << ir << " " << ig << " " << ib << " ";

		}
		cout << "\n";
	}
	/*



		vec3 lower_left_corner(-2.0, -1.0, -1.0);
		vec3 horizontal(4.0, 0, 0);			//屏幕范围
		vec3 vertical(0, 2.0, 0);
		vec3 origin(0, 0, 0);


		for (int j = ny - 1; j >= 0; j--)
		{
			for (int i = 0; i < nx; i++)
			{
				float u = float(i) / float(nx);
				float v = float(j) / float(ny);

				ray r(origin, lower_left_corner + u * horizontal + v * horizontal);
				vec3 col = color(r);
				int ir = int(255.99 *col[0]);
				int ig = int(255.99 *col[1]);
				int ib = int(255.99 *col[2]);

				cout << ir << " " << ig << " " << ib << "\n";
			}
		}*/

	return 0;
}
#include <iostream>
#include <fstream>
#include "ray.h"

#define RENDER_IMAGE_WIDTH 256
#define RENDER_IMAGE_HEIGHT 256
#define cout fout


bool hit_sphere(const vec3 & center, float sphereRadius, const ray & r) {
	//ֱ�߷��̺�Բ�����������м䲽��ʡ��
	vec3 origin_to_center = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(origin_to_center, r.direction());
	float c = dot(origin_to_center, origin_to_center) - sphereRadius * sphereRadius;

	float discriminant = b * b - 4 * a * c;

	return discriminant > 0;
}


vec3 color(const ray& r) {		//C++�У����Ĳ���������������ͣ������ʱ����Ҫʹ��&

	//if (hit_sphere(vec3(0, 0, -1), 0.5, r))
	//	return vec3(1, 0, 0);

	vec3 normalized_direction = unit_vector(r.direction());
	float t = (normalized_direction.y() + 1.0f) * 0.5f;			//��-1,1�� to color

	return (1.0f - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5f, 0.7f, 1.0f);		//lerp(vec3(1,1,1),vec3(0.5,0.7,1),t)
}



int main() {
	std::ofstream fout("d:\\renderImage.ppm");			//�ض���cout���ļ�

	//��PPM��ʽ��¼
	cout << "P3 \n" << RENDER_IMAGE_WIDTH << " " << RENDER_IMAGE_HEIGHT << "\n255\n";

	vec3 lower_left_corner(-2.0f, -1.0f, -1.f);
	vec3 vertial(0, 2.0f, 0);
	vec3 horizontal(4.0f, 0, 0);
	vec3 rayOrigin(0, 0, 0);

	for (int j = RENDER_IMAGE_HEIGHT - 1; j >= 0; j--)
	{
		for (int i = 0; i < RENDER_IMAGE_WIDTH; ++i)
		{
			float u = ((float)i / RENDER_IMAGE_WIDTH);
			float v = ((float)j / RENDER_IMAGE_HEIGHT);
			vec3 uv(u, v, 0);

			ray r(rayOrigin, uv * vec3(horizontal.r(), vertial.g(), 0));
			vec3 rayDirectionCol = color(r);

			int ir = (int)(rayDirectionCol.r() * 255.f);
			int ig = (int)(rayDirectionCol.g() * 255.f);
			int ib = (int)(rayDirectionCol.b() * 255.f);

			cout << ir << " " << ig << " " << " " << ib << " ";
		}      
		cout << std::endl;
	}
	 
	/*



		vec3 lower_left_corner(-2.0, -1.0, -1.0);
		vec3 horizontal(4.0, 0, 0);			//��Ļ��Χ
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
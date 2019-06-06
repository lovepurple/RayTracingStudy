#pragma once
/**
 * �������
 */

#include "Screen.h"
#include "ray.h"

class Camera
{
public:
	Camera() {
		camera_position = vec3(0.5, 0.5, 0);
	}

	ray get_ray(float u, float v);

	vec3 camera_position;
};


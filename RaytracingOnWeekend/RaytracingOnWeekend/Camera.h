#pragma once
/**
 * �������
 */

#include "Screen.h"
#include "ray.h"
#include "Utility.h"

class Camera
{
public:
	Camera() {
		camera_position = vec3(0.5, 0.5, 0);
	}

	//����Camrea����ϵ ������Ļ ����� ����
	Camera(vec3 cameraPosition, vec3 cameraForwardDir, vec3 cameraUpDir, float fov, float aspect);


	ray get_ndc_ray(float u, float v);

	ray get_camera_ray(float x, float y);

	vec3 camera_position;

	float m_cameraFOV;
	float m_aspect;

private:
	vec3 m_lower_left_corner;
	vec3 m_camera_world_position;

	vec3 m_camera_forward_dir;		//Z��  = lookat_center - camera_world_position;
	vec3 m_camera_up_dir;			//Y��
	vec3 m_camera_right_dir;	    //X�ᣬ ʹ����������ϵ

	float width;					//�������Ұ�ü����
	float height;

	vec3 u;
	vec3 v;
};


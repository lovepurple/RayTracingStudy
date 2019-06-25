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
		this->m_camera_world_position = vec3(0.5, 0.5, 0);
	}

	//����Camrea����ϵ ������Ļ ����� ����
	Camera(vec3 cameraPosition, vec3 cameraForwardDir, vec3 cameraUpDir, float fov, float aspect);

	/*
		��Ȧ��������֮ǰԶ����������Ϊ-1

		@cameraLookAtPoint  �������ע�����ĵ�(�������������zΪ����ƽ��),Զ�����������
	*/
	Camera(vec3 cameraPosition, vec3 cameraLookAtPoint, vec3 cameraUpDir, float fov, float aspect, float aperture);


	ray get_ndc_ray(float u, float v);

	ray get_camera_ray(float x, float y);

	float m_cameraFOV;
	float m_aspect;

private:
	vec3 m_farClipPlane_lowerLeft;		//�ü������½ǵ���������
	vec3 m_camera_world_position;

	vec3 m_camera_forward_dir;		//Z��  = lookat_center - camera_world_position;
	vec3 m_camera_up_dir;			//Y��
	vec3 m_camera_right_dir;	    //X�ᣬ ʹ����������ϵ

	float width;					//�������Ұ�ü����
	float height;

	//�������
	float m_aperture;			//��Ȧ��С
	float m_focus_depth;		//��������ȣ�����
};


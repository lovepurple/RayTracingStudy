#include "Camera.h"



Camera::Camera(vec3 cameraPosition, vec3 cameraForwardDir, vec3 cameraUpDir, float fov, float aspect)
{
	this->m_camera_world_position = cameraPosition;
	this->m_camera_forward_dir = unit_vector(cameraForwardDir);
	this->m_camera_up_dir = unit_vector(cameraUpDir);
	this->m_camera_right_dir = cross(m_camera_forward_dir, m_camera_up_dir);		//forward ������-z

	float halfHeight = tan(Utility::deg2rad(fov) * 0.5f);
	float halfWidth = halfHeight * aspect;

	this->width = 2.0 * halfWidth;
	this->height = 2.0 * halfHeight;

	this->u = this->m_camera_right_dir;
	this->v = this->m_camera_up_dir;

	//���������ϵ���½� ��NDC����ϵ�����������ϵ�Ĺ�ϵ��
	this->m_lower_left_corner = vec3(-halfWidth, -halfHeight, -1);
}


ray Camera::get_camera_ray(float u01, float v01)
{
	//��Ļ������0��0 
	vec3 rayDirection = vec3(this->m_lower_left_corner + this->u * u01 * this->width + this->v * v01 * this->height) - this->m_camera_world_position;

	return ray(this->m_camera_world_position, unit_vector(rayDirection));
}

//update: ��ʹ��nomralizedU,normalizedV ֮ǰ��������⣬�����õ������������ϵ��������NDC����ϵ
ray Camera::get_ndc_ray(float normalizedU, float normalizedV)
{
	vec3 rayOrigin = Screen::normalizedUVtoReal(camera_position);
	vec3 realPixelPos = vec3(normalizedU, normalizedV, -1);

	return ray(rayOrigin, unit_vector(realPixelPos - rayOrigin));
}

#include "Camera.h"



Camera::Camera(vec3 cameraPosition, vec3 cameraForwardDir, vec3 cameraUpDir, float fov, float aspect)
{
	this->m_camera_world_position = cameraPosition;
	this->m_camera_forward_dir = unit_vector(cameraForwardDir);
	this->m_camera_up_dir = unit_vector(cameraUpDir);
	this->m_camera_right_dir = cross(m_camera_forward_dir, m_camera_up_dir);		//forward 方向是-z

	float halfHeight = tan(Utility::deg2rad(fov) * 0.5f);
	float halfWidth = halfHeight * aspect;

	this->width = 2.0 * halfWidth;
	this->height = 2.0 * halfHeight;

	this->u = this->m_camera_right_dir;
	this->v = this->m_camera_up_dir;

	//摄像机坐标系左下角 （NDC坐标系和摄像机坐标系的关系）
	this->m_lower_left_corner = vec3(-halfWidth, -halfHeight, -1);
}


ray Camera::get_camera_ray(float u01, float v01)
{
	//屏幕左下是0，0 
	vec3 rayDirection = vec3(this->m_lower_left_corner + this->u * u01 * this->width + this->v * v01 * this->height) - this->m_camera_world_position;

	return ray(this->m_camera_world_position, unit_vector(rayDirection));
}

//update: 不使用nomralizedU,normalizedV 之前理解有问题，这里用的是摄像机坐标系，而不是NDC坐标系
ray Camera::get_ndc_ray(float normalizedU, float normalizedV)
{
	vec3 rayOrigin = Screen::normalizedUVtoReal(camera_position);
	vec3 realPixelPos = vec3(normalizedU, normalizedV, -1);

	return ray(rayOrigin, unit_vector(realPixelPos - rayOrigin));
}

#include "Camera.h"



Camera::Camera(vec3 cameraPosition, vec3 cameraForwardDir, vec3 cameraUpDir, float fov, float aspect)
{
	this->m_camera_world_position = camera_position;
	this->m_camera_forward_dir = unit_vector(cameraForwardDir);
	this->m_camera_up_dir = unit_vector(cameraUpDir);
	this->m_camera_right_dir = cross(m_camera_up_dir, m_camera_forward_dir);

	float halfHeight = tan(Utility::deg2rad(fov) * 0.5f);
	float halfWidth = halfHeight * aspect;

	//裁剪面的uv方向
	this->u = this->m_camera_right_dir;
	this->v = this->m_camera_up_dir;

}

ray Camera::get_ray(float normalizedU, float normalizedV)
{
	vec3 rayOrigin = Screen::normalizedUVtoReal(camera_position);
	vec3 realPixelPos = vec3(normalizedU, normalizedV, -1);

	return ray(rayOrigin, unit_vector(realPixelPos - rayOrigin));
}

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

	//摄像机坐标系左下角 （NDC坐标系和摄像机坐标系的关系）
	this->m_farClipPlane_lowerLeft = vec3(-halfWidth, -halfHeight, -1);
}

/*
Camera::Camera(vec3 cameraPosition, vec3 cameraForwardDir, vec3 cameraUpDir, float fov, float aspect, float aperture, float focus_distance)
{
	this->m_camera_world_position = cameraPosition;
	this->m_cameraFOV = fov;
	this->m_aspect = aspect;

	this->m_aperture = aperture * 0.5f;
	this->m_focus_depth = focus_distance;

	this->m_camera_up_dir = cameraUpDir;
	this->m_camera_forward_dir = unit_vector(cameraForwardDir);
	this->m_camera_right_dir = cross(m_camera_forward_dir, m_camera_up_dir);


	//远平面为变量
	float halfHeight = tan(Utility::deg2rad(fov) * 0.5f) * focus_distance;
	float halfWidth = halfHeight * aspect;

	this->u = this->m_camera_right_dir;
	this->v = this->m_camera_up_dir;


	this->width = 2.0f * halfWidth;
	this->height = 2.0f * halfHeight;

	//摄像机坐标系
	this->m_farClipPlane_lowerLeft = this->m_camera_world_position - vec3(width * 0.5f, height * 0.5f, focus_distance);

}*/



ray Camera::get_camera_ray(float u01, float v01)
{
	//屏幕左下是0，0 
	//景深效果：ray的起始点是在一定范围内的随机方向 不是一个定点

	vec3 apertureOffset = this->m_aperture * Utility::random_direction_in_unit_sphere();
	vec3 rayOrigin = this->m_camera_world_position;

	//在光圈圆范围内为起点
	vec3 rayOriginWithAperture = this->m_camera_world_position + vec3(apertureOffset.x(), apertureOffset.y());

	vec3 rayDirection = vec3(this->m_farClipPlane_lowerLeft + this->m_camera_right_dir * u01 * this->width + this->m_camera_up_dir * v01 * this->height) - this->m_camera_world_position;

	return ray(rayOrigin, unit_vector(rayDirection));

}

/*
	坐标系问题
		1. 其实就是FarPlane的世界坐标系
		2. 所有追踪操作都是以世界坐标系为准
		3. 下面计算的摄像机坐标系的u,v方向是FarPlane的世界坐标系的方向
		4. cameraUpDir 如果在坐标系健全的情况下(Unity) ,可以当做旋转，这里是个辅助坐标轴，为了构建本地坐标系 ？？todo：给了一个方向怎么计算出旋转的Rotation
		5. Camera一般都是反着照(为啥？)
*/
Camera::Camera(vec3 cameraPosition, vec3 cameraLookAtPoint, vec3 cameraUpDir, float fov, float aspect, float aperture)
{
	this->m_camera_world_position = cameraPosition;

	vec3 cameraToFarClippingPlaneCenter = cameraLookAtPoint - cameraPosition;
	this->m_camera_forward_dir = unit_vector(cameraToFarClippingPlaneCenter);
	this->m_camera_right_dir = cross(this->m_camera_forward_dir, cameraUpDir).normalize();		//摄像机坐标系的u方向，结果不一点是normalized的
	this->m_camera_up_dir = cross(this->m_camera_right_dir, this->m_camera_forward_dir).normalize();		//v

	this->m_focus_depth = cameraToFarClippingPlaneCenter.length();

	this->m_cameraFOV = fov;
	this->m_aspect = aspect;

	float halfHeight = tan(Utility::deg2rad(fov) * 0.5f) * this->m_focus_depth;
	float halfWidth = halfHeight * aspect;

	//远裁剪面的大小
	this->width = halfWidth * 2.0f;
	this->height = halfHeight * 2.0f;

	//远裁剪面的世界空间坐标
	this->m_farClipPlane_lowerLeft = cameraLookAtPoint - halfWidth * this->m_camera_right_dir - halfHeight * this->m_camera_up_dir;
}

//update: 不使用nomralizedU,normalizedV 之前理解有问题，这里用的是摄像机坐标系，而不是NDC坐标系
ray Camera::get_ndc_ray(float normalizedU, float normalizedV)
{
	vec3 rayOrigin = Screen::normalizedUVtoReal(m_camera_world_position);
	vec3 realPixelPos = vec3(normalizedU, normalizedV, -1);

	return ray(rayOrigin, unit_vector(realPixelPos - rayOrigin));
}

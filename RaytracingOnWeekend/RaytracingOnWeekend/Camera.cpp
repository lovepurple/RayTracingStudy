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

	//���������ϵ���½� ��NDC����ϵ�����������ϵ�Ĺ�ϵ��
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


	//Զƽ��Ϊ����
	float halfHeight = tan(Utility::deg2rad(fov) * 0.5f) * focus_distance;
	float halfWidth = halfHeight * aspect;

	this->u = this->m_camera_right_dir;
	this->v = this->m_camera_up_dir;


	this->width = 2.0f * halfWidth;
	this->height = 2.0f * halfHeight;

	//���������ϵ
	this->m_farClipPlane_lowerLeft = this->m_camera_world_position - vec3(width * 0.5f, height * 0.5f, focus_distance);

}*/



ray Camera::get_camera_ray(float u01, float v01)
{
	//��Ļ������0��0 
	//����Ч����ray����ʼ������һ����Χ�ڵ�������� ����һ������

	vec3 apertureOffset = this->m_aperture * Utility::random_direction_in_unit_sphere();
	vec3 rayOrigin = this->m_camera_world_position;

	//�ڹ�ȦԲ��Χ��Ϊ���
	vec3 rayOriginWithAperture = this->m_camera_world_position + vec3(apertureOffset.x(), apertureOffset.y());

	vec3 rayDirection = vec3(this->m_farClipPlane_lowerLeft + this->m_camera_right_dir * u01 * this->width + this->m_camera_up_dir * v01 * this->height) - this->m_camera_world_position;

	return ray(rayOrigin, unit_vector(rayDirection));

}

/*
	����ϵ����
		1. ��ʵ����FarPlane����������ϵ
		2. ����׷�ٲ�����������������ϵΪ׼
		3. �����������������ϵ��u,v������FarPlane����������ϵ�ķ���
		4. cameraUpDir ���������ϵ��ȫ�������(Unity) ,���Ե�����ת�������Ǹ����������ᣬΪ�˹�����������ϵ ����todo������һ��������ô�������ת��Rotation
		5. Cameraһ�㶼�Ƿ�����(Ϊɶ��)
*/
Camera::Camera(vec3 cameraPosition, vec3 cameraLookAtPoint, vec3 cameraUpDir, float fov, float aspect, float aperture)
{
	this->m_camera_world_position = cameraPosition;

	vec3 cameraToFarClippingPlaneCenter = cameraLookAtPoint - cameraPosition;
	this->m_camera_forward_dir = unit_vector(cameraToFarClippingPlaneCenter);
	this->m_camera_right_dir = cross(this->m_camera_forward_dir, cameraUpDir).normalize();		//���������ϵ��u���򣬽����һ����normalized��
	this->m_camera_up_dir = cross(this->m_camera_right_dir, this->m_camera_forward_dir).normalize();		//v

	this->m_focus_depth = cameraToFarClippingPlaneCenter.length();

	this->m_cameraFOV = fov;
	this->m_aspect = aspect;

	float halfHeight = tan(Utility::deg2rad(fov) * 0.5f) * this->m_focus_depth;
	float halfWidth = halfHeight * aspect;

	//Զ�ü���Ĵ�С
	this->width = halfWidth * 2.0f;
	this->height = halfHeight * 2.0f;

	//Զ�ü��������ռ�����
	this->m_farClipPlane_lowerLeft = cameraLookAtPoint - halfWidth * this->m_camera_right_dir - halfHeight * this->m_camera_up_dir;
}

//update: ��ʹ��nomralizedU,normalizedV ֮ǰ��������⣬�����õ������������ϵ��������NDC����ϵ
ray Camera::get_ndc_ray(float normalizedU, float normalizedV)
{
	vec3 rayOrigin = Screen::normalizedUVtoReal(m_camera_world_position);
	vec3 realPixelPos = vec3(normalizedU, normalizedV, -1);

	return ray(rayOrigin, unit_vector(realPixelPos - rayOrigin));
}

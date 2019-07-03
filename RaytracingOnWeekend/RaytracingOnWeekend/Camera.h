#pragma once
/**
 * 引入相机
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

	//构建Camrea坐标系 关联屏幕 摄像机 世界
	Camera(vec3 cameraPosition, vec3 cameraForwardDir, vec3 cameraUpDir, float fov, float aspect);

	/*
		光圈及景深概念，之前远裁面限制死为-1

		@cameraLookAtPoint  摄像机关注的中心点(摄像机的正方向，z为景深平面),远裁判面的中心

		@remark
				2019-07-03 14:17:45 模拟快门时间，加入摄像机时间片
	*/
	Camera(vec3 cameraPosition, vec3 cameraLookAtPoint, vec3 cameraUpDir, float fov, float aspect, float aperture, float cameraShutterOpenTime, float cameraShutterCloseTime);

	
	ray get_ndc_ray(float u, float v);

	ray get_camera_ray(float x, float y);


	float m_cameraFOV;
	float m_aspect;

private:
	//@brief:摄像机快门开着的过程中，获取随机时间
	float getRandomTimeInShutterOpening();

	vec3 m_farClipPlane_lowerLeft;		//裁剪面左下角的世界坐标
	vec3 m_camera_world_position;

	vec3 m_camera_forward_dir;		//Z轴  = lookat_center - camera_world_position;
	vec3 m_camera_up_dir;			//Y轴
	vec3 m_camera_right_dir;	    //X轴， 使用右手坐标系

	float width;					//摄像机视野裁剪面宽
	float height;

	//景深控制
	float m_aperture;			//光圈大小
	float m_focus_depth;		//焦点面深度，焦距

	//摄像机快门的开关时间
	float m_shutterOpenTime;
	float m_shutterCloseTime;
};


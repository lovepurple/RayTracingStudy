/*
 *	模拟移动的球
 */
#pragma once
#include "Hitable.h"

class Moving_Sphere :
	public Hitable
{
public:
	Moving_Sphere(){}
	Moving_Sphere(vec3 sphereMoveStartPosition, vec3 sphereMoveEndPosition, float sphereRadius, float moveStartTime, float moveEndTime, Material* mat);

	//@brief:获取在指定时刻物体的位置
	//@param:timeMoment  指定时刻
	vec3 getSpherePositionOnTime(float timeMoment) const;

	// Inherited via Hitable
	virtual bool Hit(const ray& ray, float t_min, float t_max, HitInfo& hitInfo) const override;

	//@brief:获取移动速度
	vec3 getMoveVelocity() const;


private:
	void ContructHitInfo(HitInfo& hitinfo, const ray& ray, float rayLength) const;

	vec3 m_sphereMoveStartPosition;
	vec3 m_sphereMoveEndPosition;
	float m_sphereRadius;
	float m_moveStartTime, m_moveEndTime;
	Material* m_sphereMat;



};


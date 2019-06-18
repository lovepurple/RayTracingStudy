#include "DielectricMaterial.h"

bool Dielectric::scatter(const ray& incidentRay, const HitInfo& hitInfo, vec3& attenuation, ray& outRay) const
{
	//光入射电介质时，有可能发生折射，有可能发生全反射
	//光线跟踪里，折射可能发生多次 
	//	例如玻璃，光进入玻璃一次，之后从玻璃射出到空气中，介质常量会发生改变，法线的方向也有可能是反向
	//			光线由空气进入玻璃 玻璃表面的法线方向计算正常
	//			光线再一次由玻璃内部射出到空气中，法线计算要取反

	/*
		通常情况下 n1_over_n2 可能是>0 空气是1，如果>0 有可能传入的是 介质 /空气  所以需要确定是哪个介质到哪个

		在空气中 正常在介质表面 IDotN <0 （入射光方向指向表面），但有些引擎中（Unity的LightDir ）方向默认是反过来的，需要再一次确定入射光的方向
	*/

	attenuation = vec3(1.0, 1.0, 0);

	//只是计算正负，减少一次Normalize操作，优化计算  
	float IDotN = dot(incidentRay.direction(), hitInfo.HitPointNormal);

	//IDotN>0由介质射向空气 因为hitInfo.HitPointNormal 方向朝物体外
	vec3 realMediumNormal = IDotN > 0 ? -hitInfo.HitPointNormal : hitInfo.HitPointNormal;
	float mediumFactor = IDotN > 0 ? m_n1_over_n2 : (1.0 / m_n1_over_n2);

	vec3 refractDir;
	if (refract(incidentRay.direction(), realMediumNormal, mediumFactor, refractDir))
	{
		outRay = ray(hitInfo.HitPoint, refractDir);
		return true;
	}
	else  //全反射
	{
		vec3 reflectDir = reflect(hitInfo.HitPoint, hitInfo.HitPointNormal);
		outRay = ray(hitInfo.HitPoint, unit_vector(reflectDir));
		return false;
	}
}

#pragma once
#include "Material.h"
/**
 * 光滑的金属材质
 */
class MetalMaterial :
	public Material
{
public:
	//随机反射偏移值，
	/*
		关于fuzzier 参数：
		The bigger the sphere, the fuzzier the reflections will be. This suggests adding a fuzziness parameter that is just the radius of the sphere (so zero is no perturbation).
		The catch is that for big spheres or grazing rays, we may scatter below the surface. We can just have the surface absorb those.
		We’ll put a maximum of 1 on the radius of the sphere which yields

		球体半径越大，可能越模糊（像素密度问题？），对反射方向加入一个随机方向的扰动（相当于引入法线贴图），
		本身金属就不是全反射（全反射像镜子一样），有一些固有色，加入扰动，让反射更随机一些
	*/
	MetalMaterial(const vec3& albedo, float fuzzier) {
		this->m_albedo = albedo;
		this->m_fuzzierFactor = fuzzier > 1 ? 1 : fuzzier;
	}

	// Inherited via Material
	virtual bool scatter(const ray& incidentRay, const HitInfo& hitInfo, vec3& attenuation, ray& outRay) const override;

	//扰动参数
	float m_fuzzierFactor = 0;
};


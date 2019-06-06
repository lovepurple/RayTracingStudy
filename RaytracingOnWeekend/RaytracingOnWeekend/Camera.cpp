#include "Camera.h"

ray Camera::get_ray(float normalizedU, float normalizedV)
{
	vec3 rayOrigin = Screen::normalizedUVtoReal(camera_position);
	vec3 realPixelPos = vec3(normalizedU, normalizedV, -1);

	return ray(rayOrigin, unit_vector(realPixelPos - rayOrigin));
}

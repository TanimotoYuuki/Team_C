#include "k2EngineLowPreCompile.h"
#include "SceneLight.h"

namespace nsK2EngineLow
{
	void SceneLight::Init()
	{
		//‘¾—zŒõ
		m_light.directionLight.color.x = 1.2f;
		m_light.directionLight.color.y = 1.2f;
		m_light.directionLight.color.z = 1.2f;

		m_light.directionLight.direction.x = 1.0f;
		m_light.directionLight.direction.y = -1.0f;
		m_light.directionLight.direction.z = -1.0f;
		m_light.directionLight.direction.Normalize();

		//ŠÂ‹«Œõ
		m_light.ambientLight.x = 0.5f;
		m_light.ambientLight.y = 0.5f;
		m_light.ambientLight.z = 0.5f;
		m_light.eyePos = g_camera3D->GetPosition();
	}
}
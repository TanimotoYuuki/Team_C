#pragma once

#include "GeometryData.h"

namespace nsK2EngineLow
{
	class SceneGeometryData : public Noncopyable
	{
	public:

		void RegisterGeometryData(GeometryData* geomData)
		{
			m_geometryDatas.push_back(geomData);
		}

		void UnregisterGeometryData(GeometryData* geomData)
		{
			auto it = std::find(
				m_geometryDatas.begin(),
				m_geometryDatas.end(),
				geomData
			);
			if (it != m_geometryDatas.end())
			{
				m_geometryDatas.erase(it);
			}
		}

		void Update();
		const Vector3& GetShadowCasterMaxPositionInViewFrustum() const
		{
			return m_shadowCasterMaxPositionInViewFrustum;
		}
		const Vector3& GetShadowCasterMinPositionInViewFrustum() const
		{
			return m_shadowCasterMinPositionInViewFrustum;
		}
		bool IsBuildshadowCasterGeometryData() const
		{
			return m_isBuildshadowCasterGeometryData;
		}
	private:
		Vector3 m_shadowCasterMaxPositionInViewFrustum;     // ビューフラスタムに含まれているシャドウキャスターの最大座標。
		Vector3 m_shadowCasterMinPositionInViewFrustum;     // ビューフラスタムに含まれているシャドウキャスターの最小座標。
		bool m_isBuildshadowCasterGeometryData = false;     // シャドウキャスターに関するジオメトリ情報を構築できた？
		std::list< GeometryData* > m_geometryDatas;
	};
}


#pragma once

#include "SceneGeometryData.h"

namespace nsK2EngineLow
{
	class IRenderer;
	class RenderingEngine : public Noncopyable
	{
	public:

		RenderingEngine();
		~RenderingEngine();

		bool Start();
		void Update();

		void AddRenderObject(IRenderer* renderObject)
		{
			m_renderObjects.push_back(renderObject);
		}

		Texture& GetZPressDepthTexture()
		{
			return m_zprepassRenderTarget.GetRenderTargetTexture();
		}

		void SetMainRenderTargetAndDepthStencilBuffer(RenderContext& rc)
		{
			rc.SetRenderTarget(m_mainRenderTarget.GetRTVCpuDescriptorHandle(), m_zprepassRenderTarget.GetDSVCpuDescriptorHandle());
		}

		void Init();

		void Execute(RenderContext& rc);

		const Matrix& GetViewProjectionMatrixForViewCulling() const
		{
			return m_viewProjMatrixForViewCulling;
		}

	private:

		void ZPrepass(RenderContext& rc);

		void ForwardRendering(RenderContext& rc);

		void Render2D(RenderContext& rc);

		void CopyMainRenderTargetToFrameBuffer(RenderContext& rc);

		void CalcViewProjectionMatrixForViewCulling();

		void InitZPrepassRenderTarget();

		void InitMainRenderTarget();

		void Init2DRenderTarget();

		void InitCopyMainRenderTargetToFrameBufferSprite();
	
	private:
		Sprite m_copyMainRtToFrameBufferSprite;
		RenderTarget m_zprepassRenderTarget;
		RenderTarget m_mainRenderTarget;
		SceneGeometryData m_sceneGeometryData;
		Matrix m_viewProjMatrixForViewCulling;
		RenderTarget m_2DRenderTarget;
		Sprite m_2DSprite;
		Sprite m_mainSprite;
		std::vector< IRenderer* > m_renderObjects;
	};
}


#pragma once

#include "SceneGeometryData.h"

namespace nsK2EngineLow
{
	class IRenderer;
	class RenderingEngine : public Noncopyable
	{
	public:
		enum class EnMainRTSnapshot
		{
			enDrawnOpacity,     // �s�����I�u�W�F�N�g�̕`�抮�����_
			enNum,              // �X�i�b�v�V���b�g�̐�
		};

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

		Texture& GetGBufferAlbedoTexture()
		{
			return m_gBuffer[enGBufferAlbedoDepth].GetRenderTargetTexture();
		}

		Texture& GetGBufferNormalTexture()
		{
			return m_gBuffer[enGBufferNormal].GetRenderTargetTexture();
		}

		Texture& GetMainRenderTargetSnapshotDrawnOpacity()
		{
			return m_mainRTSnapshots[(int)EnMainRTSnapshot::enDrawnOpacity].GetRenderTargetTexture();
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
		enum EnGBuffer
		{
			enGBufferAlbedoDepth,           // �A���x�h�Ɛ[�x�l�B���ɐ[�x�l���L������Ă��܂��B
			enGBufferNormal,                // �@��
			enGBufferMetaricShadowSmooth,   // ���^���b�N�A�e�p�����[�^�A�X���[�X�B
			// ���^���b�N��r�A�e�p�����[�^��g�A�X���[�X��a�Bg�͖��g�p�B
			enGBufferNum,                   // G-Buffer�̐�
		};

		void ZPrepass(RenderContext& rc);

		void SnapshotMainRenderTarget(RenderContext& rc, EnMainRTSnapshot enSnapshot);

		void ForwardRendering(RenderContext& rc);

		void Render2D(RenderContext& rc);

		void CopyMainRenderTargetToFrameBuffer(RenderContext& rc);

		void CalcViewProjectionMatrixForViewCulling();

		void InitZPrepassRenderTarget();

		void InitGBuffer();

		void InitMainRenderTarget();
		
		void InitMainRTSnapshotRenderTarget();

		void InitCopyMainRenderTargetToFrameBufferSprite();

		void Init2DRenderTarget();

		Sprite m_copyMainRtToFrameBufferSprite;
		RenderTarget m_zprepassRenderTarget;
		RenderTarget m_mainRenderTarget;
		RenderTarget m_mainRTSnapshots[(int)EnMainRTSnapshot::enNum];
		RenderTarget m_gBuffer[enGBufferNum];
		SceneGeometryData m_sceneGeometryData;
		Matrix m_viewProjMatrixForViewCulling;
		RenderTarget m_2DRenderTarget;
		Sprite m_2DSprite;
		Sprite m_mainSprite;
		std::vector< IRenderer* > m_renderObjects;
	};
}


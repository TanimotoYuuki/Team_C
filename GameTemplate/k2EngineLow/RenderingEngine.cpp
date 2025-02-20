#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow
{
	RenderingEngine::RenderingEngine()
	{
		
	}

	RenderingEngine::~RenderingEngine()
	{

	}

	void RenderingEngine::Init()
	{
		InitZPrepassRenderTarget();
		InitMainRenderTarget();
		Init2DRenderTarget();
		InitCopyMainRenderTargetToFrameBufferSprite();
	}

	void RenderingEngine::InitZPrepassRenderTarget()
	{
		m_zprepassRenderTarget.Create(
			g_graphicsEngine->GetFrameBufferWidth(),
			g_graphicsEngine->GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);
	}

	void RenderingEngine::InitMainRenderTarget()
	{
		float clearColor[4] = { 0.5f,0.5f,0.5f,1.0f };
		m_mainRenderTarget.Create(
			g_graphicsEngine->GetFrameBufferWidth(),
			g_graphicsEngine->GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			//g_mainRenderTargetFormat.colorBufferFormat,
			//g_mainRenderTargetFormat.depthBufferFormat,
			clearColor
		);
	}

	void RenderingEngine::Init2DRenderTarget()
	{
		float clearColor[4] = { 0.0f,0.0f,0.0f,0.0f };
		m_2DRenderTarget.Create(
			g_graphicsEngine->GetFrameBufferWidth(),
			g_graphicsEngine->GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_UNKNOWN,
			clearColor
		);

		//最終合成用のスプライトを初期化する
		SpriteInitData spriteInitData;
		//テクスチャは2Dレンダーターゲット
		spriteInitData.m_textures[0] = &m_2DRenderTarget.GetRenderTargetTexture();
		//解像度はmainRenderTargetの幅と高さ
		spriteInitData.m_width = m_mainRenderTarget.GetWidth();
		spriteInitData.m_height = m_mainRenderTarget.GetHeight();
		//2D用のシェーダーを使用する
		spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		spriteInitData.m_vsEntryPointFunc = "VSMain";
		spriteInitData.m_psEntryPoinFunc = "PSMain";
		//上書き
		spriteInitData.m_alphaBlendMode = AlphaBlendMode_None;
		//レンダリングターゲットのフォーマット
		spriteInitData.m_colorBufferFormat[0] = m_mainRenderTarget.GetColorBufferFormat();

		m_2DSprite.Init(spriteInitData);

		//テクスチャはメインレンダ―ターゲット。
		spriteInitData.m_textures[0] = &m_mainRenderTarget.GetRenderTargetTexture();
		//解像度は2Dレンダ―ターゲットの幅と高さ
		spriteInitData.m_width = m_2DRenderTarget.GetWidth();
		spriteInitData.m_height = m_2DRenderTarget.GetHeight();
		spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		spriteInitData.m_alphaBlendMode = AlphaBlendMode_None;
		//レンダリングターゲットのフォーマット。
		spriteInitData.m_colorBufferFormat[0] = m_2DRenderTarget.GetColorBufferFormat();

		m_mainSprite.Init(spriteInitData);
	}

	void RenderingEngine::InitCopyMainRenderTargetToFrameBufferSprite()
	{
		SpriteInitData spriteInitData;

		// テクスチャはyBlurRenderTargetのカラーバッファー
		spriteInitData.m_textures[0] = &m_mainRenderTarget.GetRenderTargetTexture();

		// レンダリング先がフレームバッファーなので、解像度はフレームバッファーと同じ
		spriteInitData.m_width = g_graphicsEngine->GetFrameBufferWidth();
		spriteInitData.m_height = g_graphicsEngine->GetFrameBufferHeight();

		// ガンマ補正ありの2D描画のシェーダーを指定する
		spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		spriteInitData.m_psEntryPoinFunc = "PSMain";
		spriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R8G8B8A8_UNORM;

		// 初期化オブジェクトを使って、スプライトを初期化する
		m_copyMainRtToFrameBufferSprite.Init(spriteInitData);

	}

	void RenderingEngine::CalcViewProjectionMatrixForViewCulling()
	{
		Matrix projMatrix;
		projMatrix.MakeProjectionMatrix(
			g_camera3D->GetViewAngle() * 1.5f,
			g_camera3D->GetAspect(),
			g_camera3D->GetNear(),
			g_camera3D->GetFar()
		);
		m_viewProjMatrixForViewCulling.Multiply(g_camera3D->GetViewMatrix(), projMatrix);
	}

	void RenderingEngine::Update()
	{
		CalcViewProjectionMatrixForViewCulling();

		m_sceneGeometryData.Update();
	}

	void RenderingEngine::Execute(RenderContext& rc)
	{
		ZPrepass(rc);

		ForwardRendering(rc);

		Render2D(rc);
		
		CopyMainRenderTargetToFrameBuffer(rc);

		m_renderObjects.clear();
	}
	
	void RenderingEngine::ZPrepass(RenderContext& rc)
	{
		BeginGPUEvent("ZPrepass");
		// まず、レンダリングターゲットとして設定できるようになるまで待つ
		rc.WaitUntilToPossibleSetRenderTarget(m_zprepassRenderTarget);

		// レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(m_zprepassRenderTarget);

		// レンダリングターゲットをクリア
		rc.ClearRenderTargetView(m_zprepassRenderTarget);

		for (auto& renderObj : m_renderObjects) {
			renderObj->OnZPrepass(rc);
		}

		rc.WaitUntilFinishDrawingToRenderTarget(m_zprepassRenderTarget);
		EndGPUEvent();
	}

	void RenderingEngine::ForwardRendering(RenderContext& rc)
	{
		BeginGPUEvent("ForwardRendering");
		rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderTarget);
		rc.SetRenderTarget(m_mainRenderTarget);
		rc.ClearRenderTargetView(m_mainRenderTarget);

		for (auto& renderObj : m_renderObjects) {
			renderObj->OnForwardRender(rc);
		}

		// メインレンダリングターゲットへの書き込み終了待ち
		rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);

		EndGPUEvent();
	}

	void RenderingEngine::Render2D(RenderContext& rc)
	{
		BeginGPUEvent("Render2D");

		// レンダリングターゲットとして利用できるまで待つ。
		//PRESENTからRENDERTARGETへ。
		rc.WaitUntilToPossibleSetRenderTarget(m_2DRenderTarget);

		// レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(m_2DRenderTarget);

		// レンダリングターゲットをクリア
		rc.ClearRenderTargetView(m_2DRenderTarget);

		m_mainSprite.Draw(rc);

		for (auto& renderObj : m_renderObjects) {
			renderObj->OnRender2D(rc);
		}

		
		rc.WaitUntilFinishDrawingToRenderTarget(m_2DRenderTarget);

		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);

		// レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(m_mainRenderTarget);

		m_2DSprite.Draw(rc);

		//RENDERTARGETからPRESENTへ。
		rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);

		EndGPUEvent();
	}

	void RenderingEngine::CopyMainRenderTargetToFrameBuffer(RenderContext& rc)
	{
		BeginGPUEvent("CopyMainRenderTargetToFrameBuffer");

		// メインレンダリングターゲットの絵をフレームバッファーにコピー
		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);

		// ビューポートを指定する
		D3D12_VIEWPORT viewport;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = static_cast<FLOAT>(g_graphicsEngine->GetFrameBufferWidth());
		viewport.Height = static_cast<FLOAT>(g_graphicsEngine->GetFrameBufferHeight());
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		rc.SetViewportAndScissor(viewport);
		m_copyMainRtToFrameBufferSprite.Draw(rc);

		EndGPUEvent();
	}
}
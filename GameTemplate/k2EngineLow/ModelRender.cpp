#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow
{
	void ModelRender::Init(const char* filePath,
		AnimationClip* animationClips,
		int numAnimationClip,
		EnModelUpAxis enModelUpAxis)
	{
		InitSkeleton(filePath);
		InitAnimation(animationClips, numAnimationClip, enModelUpAxis);
		InitModel(filePath, enModelUpAxis);

		UpdateWorldMatrixInModes();
	}

	void ModelRender::InitSkyCube(ModelInitData& initData)
	{
		//initData.m_colorBufferFormat[0] = DXGI_FORMAT_R16G16B16A16_FLOAT;
		m_model.Init(initData);
	}

	void ModelRender::InitSkeleton(const char* filePath)
	{
		//スケルトンのデータを読み込み
		std::string skeletonFilePath = filePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		m_skeleton.Init(skeletonFilePath.c_str());
	}

	void ModelRender::InitAnimation(AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis
	)
	{
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;
		if (m_animationClips != nullptr)
		{
			m_animation.Init(m_skeleton,
				m_animationClips,
				numAnimationClips
			);
		}
	}

	void ModelRender::InitModel(const char* filePath, EnModelUpAxis enModelUpAxis)
	{
		ModelInitData initData;
		//tkmファイルのファイルパスを指定する
		initData.m_tkmFilePath = filePath;
		//シェーダーファイルのファイルパスを指定する
		initData.m_fxFilePath = "Assets/shader/model.fx";
		//ノンスキンメッシュ用の頂点シェーダーのエントリーポイントを指定する
		initData.m_vsEntryPointFunc = "VSMain";

		if (m_animationClips != nullptr)
		{
			//スキンメッシュ用の頂点シェーダーのエントリーポイントを指定
			initData.m_vsSkinEntryPointFunc = "VSSkinMain";
			//スケルトンを指定する
			initData.m_skeleton = &m_skeleton;
		}

		//モデルの上方向を指定する。
		initData.m_modelUpAxis = enModelUpAxis;

		//作成した初期化データをもとにモデルを初期化する
		m_model.Init(initData);

		InitZPrepassModel(filePath, enModelUpAxis);
	}

	void ModelRender::InitZPrepassModel(
		const char* tkmFilePath,
		EnModelUpAxis modelUpAxis
		)
	{
		ModelInitData modelInitData;
		modelInitData.m_tkmFilePath = tkmFilePath;
		modelInitData.m_fxFilePath = "Assets/shader/zprepass.fx";
		modelInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32_FLOAT;
		modelInitData.m_modelUpAxis = modelUpAxis;

		if (m_skeleton.IsInited()) {
			//スケルトンを指定する。
			modelInitData.m_skeleton = &m_skeleton;
			modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
		}

		m_zprepassModel.Init(modelInitData);
	}

	void ModelRender::UpdateWorldMatrixInModes()
	{
		//モデルの更新処理
		if (m_model.IsInited()) {
			m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		}
		if (m_zprepassModel.IsInited()) {
			m_zprepassModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		}
	}

	void ModelRender::Update()
	{
		UpdateWorldMatrixInModes();

		//スケルトンを更新
		m_skeleton.Update(m_model.GetWorldMatrix());

		//モデルの更新
		m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

		//アニメーションを進める
		m_animation.Progress(g_gameTime->GetFrameDeltaTime() * m_animationSpeed);
	}

	void ModelRender::Draw(RenderContext& rc)
	{
		g_renderingEngine->AddRenderObject(this);
		//m_model.Draw(rc);
	}

	void ModelRender::OnZPrepass(RenderContext& rc)
	{
		if (m_zprepassModel.IsInited()) {
			m_zprepassModel.Draw(rc);
		}
	}

	void ModelRender::OnForwardRender(RenderContext& rc)
	{
		if (m_model.IsInited()) {
			m_model.Draw(rc);
		}
	}
}
#pragma once
class Player : public IGameObject
{
public:
	bool Start();
	void Update();
	void Move();
	void AnimationManager();
	void PlayAnimation();
	void Render(RenderContext& rc);

	enum EnAnimationClip {
		enAnimationClips_Idle,
		enAnimationClips_Run,
		enAnimationClips_Walk,
		enAnimationClips_Num,
	};

	enum EnAnimationState {
		enAnimationState_Idle,
		enAnimationState_Run,
		enAnimationState_Walk,
		enAnimationState_Num,
	};
	AnimationClip m_animationClips[enAnimationClips_Num];
	ModelRender m_modelRender;

	Vector3 m_position = Vector3::Zero;
	int m_animationState = enAnimationState_Idle;
};


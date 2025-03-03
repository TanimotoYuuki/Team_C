#pragma once
class Player : public IGameObject
{
public:
	bool Start();
	void Update();
	void Move();
	void Rotation();
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
	CharacterController m_charaCon;

	Vector3 m_position = Vector3::Zero;
	Vector3 m_moveSpeed = Vector3::Zero;
	Quaternion m_rotation = Quaternion::Identity;
	int m_animationState = enAnimationState_Idle;
};


#include "stdafx.h"
#include "Player.h"

bool Player::Start()
{
	m_animationClips[enAnimationClips_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClips_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClips_Run].Load("Assets/animData/run.tka");
	m_animationClips[enAnimationClips_Run].SetLoopFlag(true);
	m_animationClips[enAnimationClips_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClips_Walk].SetLoopFlag(true);

	m_modelRender.Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClips_Num, enModelUpAxisY);
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
	return true;
}

void Player::Update()
{
	Move();

	AnimationManager();

	PlayAnimation();

	m_modelRender.Update();
	m_modelRender.SetPosition(m_position);
}

void Player::Move()
{
	if (g_pad[0]->IsPress(enButtonUp))
	{
		m_position.z += 1.0f;
	}
	else if (g_pad[0]->IsPress(enButtonDown))
	{
		m_position.z -= 1.0f;
	}
	else if (g_pad[0]->IsPress(enButtonLeft))
	{
		m_position.x -= 1.0f;
	}
	else if (g_pad[0]->IsPress(enButtonRight))
	{
		m_position.x += 1.0f;
	}
}

void Player::AnimationManager()
{
	if (g_pad[0]->IsPress(enButtonA))
	{
		m_animationState = enAnimationState_Run;
	}
	else if (g_pad[0]->IsPress(enButtonB))
	{
		m_animationState = enAnimationState_Walk;
	}
	else
	{
		m_animationState = enAnimationState_Idle;
	}
}

void Player::PlayAnimation()
{
	switch (m_animationState)
	{
	case enAnimationState_Idle:
		m_modelRender.PlayAnimation(enAnimationClips_Idle);
		break;
	case enAnimationState_Run:
		m_modelRender.PlayAnimation(enAnimationClips_Run);
		break;
	case enAnimationClips_Walk:
		m_modelRender.PlayAnimation(enAnimationClips_Walk);
		break;
	default:
		break;
	}
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
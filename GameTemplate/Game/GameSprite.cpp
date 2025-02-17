#include "stdafx.h"
#include "GameSprite.h"

bool GameSprite::Start()
{
	m_spriteRender.Init("Assets/debug/sprite/titlename1.dds", 910.0f, 128.0f);
	m_spriteRender.SetPosition(0.0f, 350.0f, 0.0f);
	m_spriteRender.SetScale(1.0f,1.0f,1.0f);
	m_spriteRender.Update();
	return true;
}

void GameSprite::Update()
{
	m_spriteRender.Update();
}

void GameSprite::ViewSprite()
{

}

void GameSprite::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}
#include "stdafx.h"
#include "GameText.h"

bool GameText::Start()
{
	return true;
}

void GameText::Update()
{
	m_time += g_gameTime->GetFrameDeltaTime();
	ViewText();
}

void GameText::ViewText()
{
	wchar_t debug[256];
	swprintf_s(debug, 256, L"%d•b", int(m_time));
	m_fontRender.SetText(debug);
	m_fontRender.SetPosition(-450.0f, 0.0f, 0.0f);
	m_fontRender.SetScale(1.0f);
	m_fontRender.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void GameText::Render(RenderContext& rc)
{
	m_fontRender.Draw(rc);
}
#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameText.h"
#include "GameSprite.h"
#include "BackGround.h"
#include "SkyCube.h"

Game::Game()
{

}

Game::~Game()
{

}

bool Game::Start()
{
	InitSky();

	NewGO<Player>(0,"player");
	NewGO<GameText>(0,"gametext");
	NewGO<GameSprite>(0,"gamesprite");
	NewGO<BackGround>(0,"background");

	m_player = FindGO<Player>("player");
	m_gameText = FindGO<GameText>("gametext");
	m_gameSprite = FindGO<GameSprite>("gamesprite");
	m_backGround = FindGO<BackGround>("background");
	return true;
}

void Game::InitSky()
{
	DeleteGO(m_skyCube);
	m_skyCube = NewGO<SkyCube>(0,"skycube");

	m_skyCube->SetLuminance(1.0f);
	m_skyCube->SetType((EnSkyCubeType)m_skyCubeType);
}

void Game::Update()
{
	if (g_pad[0]->IsTrigger(enButtonX))
	{
		m_skyCubeType++;
		m_skyCubeType = m_skyCubeType % enSkyCubeType_Num;
		InitSky();
	}
	if (g_pad[0]->IsTrigger(enButtonY))
	{
		m_skyCubeType--;
		if (m_skyCubeType < 0)
		{
			m_skyCubeType = enSkyCubeType_Num - 1;
		}
		InitSky();
	}
}
#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameText.h"
#include "GameSprite.h"

Game::Game()
{

}

Game::~Game()
{

}

bool Game::Start()
{
	NewGO<Player>(0,"player");
	NewGO<GameText>(0,"gametext");
	NewGO<GameSprite>(0,"gamesprite");

	m_player = FindGO<Player>("player");
	m_gameText = FindGO<GameText>("gametext");
	m_gameSprite = FindGO<GameSprite>("gamesprite");
	return true;
}

void Game::Update()
{

}
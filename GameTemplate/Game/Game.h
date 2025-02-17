#pragma once
class Player;
class GameText;
class GameSprite;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();

	Player* m_player = nullptr;
	GameText* m_gameText = nullptr;
	GameSprite* m_gameSprite = nullptr;
};


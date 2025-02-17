#pragma once
class GameSprite : public IGameObject
{
public:
	bool Start();
	void Update();
	void ViewSprite();
	void Render(RenderContext& rc);

	SpriteRender m_spriteRender;
};


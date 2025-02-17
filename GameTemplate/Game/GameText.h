#pragma once
class GameText : public IGameObject
{
public:
	bool Start();
	void Update();
	void ViewText();
	void Render(RenderContext& rc);

	FontRender m_fontRender;
	float m_time;
};


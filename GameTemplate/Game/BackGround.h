#pragma once
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	//メンバ変数
	ModelRender stage; //ステージ
	PhysicsStaticObject physicsStaticObject; //静的物理オブジェクト
};


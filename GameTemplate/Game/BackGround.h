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
	//�����o�ϐ�
	ModelRender stage; //�X�e�[�W
	PhysicsStaticObject physicsStaticObject; //�ÓI�����I�u�W�F�N�g
};


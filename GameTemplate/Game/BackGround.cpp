#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{

}

BackGround::~BackGround()
{

}

bool BackGround::Start()
{
	//�X�e�[�W
	stage.Init("Assets/modelData/ground.tkm");
	physicsStaticObject.CreateFromModel(stage.GetModel(), stage.GetModel().GetWorldMatrix());
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}

void BackGround::Update()
{
	//�X�V
	stage.Update();
}

void BackGround::Render(RenderContext& rc)
{
	//�`��
	stage.Draw(rc);
}
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
	//ステージ
	stage.Init("Assets/modelData/ground.tkm");
	physicsStaticObject.CreateFromModel(stage.GetModel(), stage.GetModel().GetWorldMatrix());
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}

void BackGround::Update()
{
	//更新
	stage.Update();
}

void BackGround::Render(RenderContext& rc)
{
	//描画
	stage.Draw(rc);
}
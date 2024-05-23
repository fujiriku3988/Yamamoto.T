#include "GameScene.h"
#include"../SceneManager.h"
#include"Application/Object/BackGround/BackGround.h"
#include"Application/Object/Ground/Ground.h"

void GameScene::Event()
{
	Math::Matrix transMat = Math::Matrix::CreateTranslation(0, 3,-3);
	Math::Matrix rotMatX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(30));
	Math::Matrix cameraMat = rotMatX * transMat;
	m_camera->SetCameraMatrix(cameraMat);
	
}

void GameScene::Init()
{
	//カメラ生成＆視野角設定
	m_camera = std::make_unique<KdCamera>();//1メモリ確保
	m_camera->SetProjectionMatrix(60);//視野角設定

	std::shared_ptr<BackGround>back = std::make_shared<BackGround>();
	back->Init();
	AddObject(back);

	std::shared_ptr<Ground>ground = std::make_shared<Ground>();
	ground->Init();
	AddObject(ground);
}

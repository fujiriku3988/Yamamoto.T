#include "GameScene.h"
#include"../SceneManager.h"
#include"Application/Object/BackGround/BackGround.h"
#include"Application/Object/Ground/Ground.h"
#include"Application/Object/Player/Player.h"

void GameScene::Event()
{
	//プレイヤーの座標を取得する
	Math::Vector3 playerPos = {};
	if (m_player.expired() == false)
	{
		playerPos = m_player.lock()->GetPos();
	}

	Math::Matrix transMat = Math::Matrix::CreateTranslation(Math::Vector3(0, 3,-3) + playerPos);
	//Math::Matrix playerMat = Math::Matrix::CreateTranslation(playerPos);
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

	std::shared_ptr<Player>player = std::make_shared<Player>();
	player->Init();
	AddObject(player);
	m_player = player;
}

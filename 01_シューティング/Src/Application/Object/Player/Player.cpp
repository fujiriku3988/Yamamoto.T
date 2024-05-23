#include "Player.h"
#include"../../Scene/GameScene.h"
#include"../Bullet/Bullet.h"

void Player::Update()
{
	if (GetAsyncKeyState('W') & 0x8000) { m_pos.y += 5; }
	if (GetAsyncKeyState('S') & 0x8000) { m_pos.y -= 5; }
	if (GetAsyncKeyState('A') & 0x8000) { m_pos.x -= 5; }
	if (GetAsyncKeyState('D') & 0x8000) { m_pos.x += 5; }

	//プレイヤーと敵の当たり判定・・・敵の情報が必要
	//オブジェクトリストを全て見ていく
	for (auto& obj : m_owner->GetObjList())
	{
		//自分自身とは当たり判定はしない
		if (obj->GetObjType() == ObjectType::Player)continue;
		if (obj->GetObjType() == ObjectType::Bullet)continue;
		//敵だったら当たり判定を行う
		if (obj->GetObjType() == ObjectType::Enemy)
		{
			//対象座標ー自分の座標
			Math::Vector3 v;
			v = obj->GetPos() - m_pos;

			//球判定・・・ベクトルの長さで判定
			if (v.Length()<64.0f)
			{
				obj->OnHit();
			}
		}
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		std::shared_ptr<Bullet>bullet = std::make_shared<Bullet>();
		bullet->Init();
		bullet->SetPos(m_pos);
		bullet->SetOwner(m_owner);
		m_owner->AddObject(bullet);
	}

	if (m_pos.x < -640 + 32) { m_pos.x = -640 + 32; }
	if (m_pos.x > 640 - 32) { m_pos.x = 640 - 32; }
	if (m_pos.y < -360 + 32) { m_pos.y = -360 + 32; }
	if (m_pos.y > 360 - 32) { m_pos.y = 360 - 32; }
	
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mat = transMat;

}

void Player::Draw()
{
	Math::Rectangle rc;
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);

	rc = { 0,0,64,64 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, 64, 64, &rc);
}

void Player::Init()
{
	m_tex.Load("Asset/Textures/player.png");
	m_pos = {};						//0,0で初期化
	m_mat = Math::Matrix::Identity;	//単位行列で初期化
	m_objType = ObjectType::Player;

	//単位行列・・・拡大率全て1.0,他の値は全て0

}

void Player::Release()
{
	//テクスチャはKdTexture型のデストラクタで
	//自動Releaseで通るから書かなくて大丈夫
}

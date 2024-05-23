#include "Bullet.h"
#include"../../Scene/GameScene.h"

void Bullet::Update()
{
	if (!m_aliveflg)return;
	m_pos += m_movePow;

	if (m_pos.x < -650) { m_aliveflg = false; }
	if (m_pos.x > 650) { m_aliveflg = false; }
	if (m_pos.y > 370) { m_aliveflg = false; }
	if (m_pos.y < -370) { m_aliveflg = false; }

	//オブジェクトリストを全て見ていく
	for (auto& obj : m_owner->GetObjList())
	{
		////自分自身とは当たり判定はしない
		if (obj->GetObjType() == ObjectType::Bullet)continue;
		if (obj->GetObjType() == ObjectType::Player)continue;
		//敵だったら当たり判定を行う
		if (obj->GetObjType() == ObjectType::Enemy)
		{
			//対象座標ー自分の座標
			Math::Vector3 v;
			v = obj->GetPos() - m_pos;

			//球判定・・・ベクトルの長さで判定
			if (v.Length() < 64.0f)
			{
				obj->OnHit();
				OnHit();
				break;
			}
		}
	}

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mat = transMat;
}

void Bullet::Draw()
{
	if (!m_aliveflg)return;
	Math::Rectangle rc;
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);

	rc = { 0,0,13,37 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, 13, 37,&rc);
}

void Bullet::Init()
{
	m_tex.Load("Asset/Textures/bullet.png");
	m_pos = {};						//0,0で初期化
	m_mat = Math::Matrix::Identity;	//単位行列で初期化
	m_objType = ObjectType::Bullet;
	m_movePow = {0.0f,10.0f,0.0f};
}

void Bullet::OnHit()
{
	m_aliveflg = false;
}

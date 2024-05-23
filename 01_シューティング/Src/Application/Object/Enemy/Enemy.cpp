#include "Enemy.h"

void Enemy::Update()
{
	m_pos += m_movePow;
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mat = transMat;

	if (m_pos.y < -360 - 64)
	{
		m_pos.y = 360 + 64;
	}

}

void Enemy::Draw()
{
	Math::Rectangle rc;
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);

	rc = { 0,0,64,64 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, 64, 64, &rc);
}

void Enemy::Init()
{
	m_tex.Load("Asset/Textures/enemy.png");
	m_pos = {};
	m_mat = Math::Matrix::Identity;
	m_objType = ObjectType::Enemy;
	m_movePow = { 0.0f,-2.0f,0.0f };
}

void Enemy::OnHit()
{
	m_aliveflg = false;
}

void Enemy::Release()
{
}

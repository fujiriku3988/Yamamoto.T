#include "Player.h"

void Player::Init()
{
	m_poly.SetMaterial("Asset/Textures/Player.png");
	m_poly.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_scale = {3};
	m_pos = {};
	m_speed = 0.1f;
	//アニメーション分割：横・縦
	m_poly.SetSplit(4, 8);
	m_mWorld = Math::Matrix::Identity;
}

void Player::Update()
{
	//m_pos.x += m_speed;
	//m_pos.z += m_speed;
	m_dir = {};
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		//m_pos.x -= m_speed;
		m_dir.x += -1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		//m_pos.x += m_speed;
		m_dir.x = 1;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		//m_pos.z += m_speed;
		m_dir.z = 1;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		//m_pos.z -= m_speed;
		m_dir.z += -1;
	}
	m_poly.SetUVRect(12);
}

void Player::PostUpdate()
{
	//座標 += ベクトルの方向(1.0f)固定*ベクトルの量
	m_pos += (m_dir * m_speed);
	//こっちに行列を置いた方が安全
	//Udpate()で確定したパラメータから座標行列を作成
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * transMat;
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_poly, m_mWorld);
}

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_poly, m_mWorld);
}

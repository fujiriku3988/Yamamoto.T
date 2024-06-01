#include "Player.h"
#include"../../Scene/SceneManager.h"

void Player::Init()
{
	m_poly.SetMaterial("Asset/Textures/Player.png");
	m_poly.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_scale = {3};
	m_pos = {};
	m_speed = 0.1f;
	m_gravity = 0.0f;
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
	//座標 += ベクトルの方向(1.0f)固定*ベクトルの量
	m_pos += (m_dir * m_speed);
	m_pos.y -= m_gravity;
	m_gravity += 0.0005f;

	//レイの判定
	KdCollider::RayInfo rayInfo;
	//レイの発射位置を設定
	rayInfo.m_pos = m_pos;
	//レイの発射方向（ベクトル）
	rayInfo.m_dir = Math::Vector3::Down;
	rayInfo.m_pos.y += 0.1f;

	//段差登れるように
	//float enableStepHigh = 0.2f;
	//rayInfo.m_pos.y += enableStepHigh;

	//レイの長さ
	rayInfo.m_range = m_gravity;

	//当たり判定するタイプの設定
	rayInfo.m_type = KdCollider::TypeGround;

	//レイに当たったobj情報
	std::list<KdCollider::CollisionResult>retRayList;
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(rayInfo, &retRayList);
	}

}

void Player::PostUpdate()
{

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

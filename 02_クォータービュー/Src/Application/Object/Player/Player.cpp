#include "Player.h"
#include"../../Scene/SceneManager.h"

void Player::Init()
{
	//プレイヤー
	m_poly.SetMaterial("Asset/Textures/Player.png");
	m_poly.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_scale = {3};
	m_pos = {};
	m_speed = 0.1f;
	m_gravity = 0.0f;
	//アニメーション分割：横・縦
	m_poly.SetSplit(4, 8);
	m_mWorld = Math::Matrix::Identity;
	//デバッグワイヤー作成
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
	//向いている方向
	m_dirType = DirType::Down;
	//初期アニメーション
	m_animeInfo.start = ;
	m_animeInfo.end = ;
	m_animeInfo.count = ;
	m_animeInfo.speed = 0.2f;
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
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_gravity += -0.055f;
	}
	m_poly.SetUVRect(12);
	//座標 += ベクトルの方向(1.0f)固定*ベクトルの量
	m_pos += (m_dir * m_speed);
	m_pos.y -= m_gravity;
	m_gravity += 0.005f;

	//レイの判定
	KdCollider::RayInfo rayInfo;
	//レイの発射位置を設定
	rayInfo.m_pos = m_pos;
	//レイの発射方向（ベクトル）
	rayInfo.m_dir = Math::Vector3::Down;
	//rayInfo.m_pos.y += 0.1f;

	//段差の許容範囲
	static const float enableStepHigh = 0.2f;
	//static const float enableStepHigh = 1.0f;
	rayInfo.m_pos.y += enableStepHigh;

	//レイの長さ
	rayInfo.m_range = m_gravity+ enableStepHigh;

	//当たり判定するタイプの設定
	rayInfo.m_type = KdCollider::TypeGround;

	//①線の開始位置、②線の方向、③線の長さ
	m_pDebugWire->AddDebugLine(rayInfo.m_pos, rayInfo.m_dir, rayInfo.m_range);

	//レイに当たったobj情報を格納するリスト
	std::list<KdCollider::CollisionResult>retRayList;
	//作成したレイ情報でObjリストと当たり判定をする
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(rayInfo, &retRayList);
	}
	
	//レイに当たったリストから一番近いオブジェクトを検出
	bool hit = false;
	float maxOverLap = 0;
	Math::Vector3 groundPos = {};//レイが遮断された（Hitした）座標

	//
	for (auto& ret : retRayList)
	{
		//レイが当たった場合の貫通した長さが一番長いものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			groundPos = ret.m_hitPos;
			hit = true;
		}
	}

	//当たっていたら
	if (hit)
	{
		m_pos = groundPos+Math::Vector3 (0,-0.1f,0);
		//m_pos = groundPos+ Math::Vector3::Down;
		m_gravity = 0;
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

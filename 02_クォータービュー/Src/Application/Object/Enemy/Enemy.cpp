#include "Enemy.h"
#include"../../Scene/SceneManager.h"
#include"../../Object/Player/Player.h"

void Enemy::Init()
{
	//敵
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/Enemy.png");
	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_scale = { 2 };
	m_dir = {};
	m_pos = {};
	m_gravity = 0.0f;
	m_chaseFlg = false;
	m_searchArea = 6.0f;
	//アニメーション分割：横・縦
	m_poly->SetSplit(6, 6);
	m_mWorld = Math::Matrix::Identity;
	//デバッグワイヤー作成
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
	//向いている方向
	m_speed = 0.05f;
	m_animeCnt = 0.0f;
	//当たり判定設定(コライダー)
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Enemy",m_poly, KdCollider::TypeDamage);
}


void Enemy::Update()
{
	int walk[4] = { 3,4,3,5 };
	m_animeCnt += 0.05f;
	m_poly->SetUVRect(walk[(int)m_animeCnt]);
	if (m_animeCnt >= 4)
	{
		m_animeCnt = 0;
	}
	//座標 += ベクトルの方向(1.0f)固定*ベクトルの量
	m_pos.y -= m_gravity;
	m_gravity += 0.005f;

	//追尾
	Math::Vector3 playerPos = {};
	//lockでweakをshareに変換
	if (m_target.expired() == false)
	{
		playerPos = m_target.lock()->GetPos();
		Math::Vector3 vec;
		vec = playerPos - m_pos;

		if (vec.Length() < m_searchArea)
		{
			m_chaseFlg = true;
		}
		else
		{
			m_chaseFlg = false;
		}

		if (m_chaseFlg)
		{
			//y軸を０にして、空中まで追いかけてこないように	
			vec.y = 0.0f;
			//ベクトルの長さを１に
			vec.Normalize();
			//向き確定
			m_dir = vec;
		}
		else
		{
			m_dir = {};
		}
	}
	//search();
	m_pos += (m_dir * m_speed);



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
	rayInfo.m_range = m_gravity + enableStepHigh;

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
		m_pos = groundPos + Math::Vector3(0, -0.1f, 0);
		//m_pos = groundPos+ Math::Vector3::Down;
		m_gravity = 0;
	}
	//=====================================================================//

	m_pDebugWire->AddDebugSphere(m_pos + Math::Vector3{ 0,0.5f,0 }, 3.0f, kGreenColor);

}

void Enemy::PostUpdate()
{
	//こっちに行列を置いた方が安全
	//Udpate()で確定したパラメータから座標行列を作成
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * transMat;
}

void Enemy::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
}

void Enemy::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
}

void Enemy::search()
{
	Math::Vector3 playerPos = {};
	if (m_target.expired() == false)
	{
		playerPos = m_target.lock()->GetPos();
		Math::Vector3 vec;
		vec = playerPos - m_pos;

		if (vec.Length() < m_searchArea)
		{
			m_chaseFlg = true;
		}
		else
		{
			m_chaseFlg = false;
		}

		if (m_chaseFlg)
		{
			vec.Normalize();
		}
		else
		{
			m_dir = {};
		}
	}
}

void Enemy::SetTarget(std::weak_ptr<Player> _target)
{
	if (_target.expired() == false)
	{
		m_target = _target;
	}
}

void Enemy::OnHit()
{
	m_isExpired = true;
}

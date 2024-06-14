#include "Attack.h"
#include"../../Scene/SceneManager.h"

void Attack::Init()
{
	m_polygon.SetMaterial("Asset/Textures/Attack.png");
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_polygon.SetSplit(9, 1);
	m_animeSpeed = 1.0f;
	m_attackArea = 0.3f;
	m_animeCnt = 0.0f;
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
	m_mWorld = Math::Matrix::Identity;
	
}

void Attack::Update()
{
	m_polygon.SetUVRect((int)m_animeCnt);
	m_animeCnt += m_animeSpeed;
	if (m_animeCnt > 9)
	{
		m_isExpired = true;//消える
	}

	//当たり判定
	KdCollider::SphereInfo sphereInfo;

	sphereInfo.m_sphere.Center = GetPos() + Math::Vector3(0, 0.5f, 0);

	sphereInfo.m_sphere.Radius = m_attackArea;

	sphereInfo.m_type = KdCollider::TypeDamage;

	//デバッグ
	m_pDebugWire->AddDebugSphere(sphereInfo.m_sphere.Center, sphereInfo.m_sphere.Radius, kRedColor);

	bool hit = false;
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		hit = obj->Intersects(sphereInfo, nullptr);

		if (hit)
		{
			//Hit時の相手オブジェクト処理
			obj->OnHit();
			//Hit時の自分の処理
			OnHit();

			//ループから抜ける
			break;
		}
	}

}

void Attack::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void Attack::OnHit()
{
	m_isExpired = true;
}

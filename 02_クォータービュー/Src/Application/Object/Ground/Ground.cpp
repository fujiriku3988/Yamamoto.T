#include "Ground.h"

void Ground::DrawLit()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat* transMat;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model,m_mWorld);
}

void Ground::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Ground/Ground.gltf");
	m_mWorld = Math::Matrix::Identity;
	m_scale = {100.0f};
	m_pos = {};

	//コライダー（当たり判定情報）の初期化（登録）
	m_pCollider = std::make_unique<KdCollider>();
	//								登録名		モデルデータ	判定種類
	m_pCollider->RegisterCollisionShape("Ground", m_model, KdCollider::TypeGround);
}

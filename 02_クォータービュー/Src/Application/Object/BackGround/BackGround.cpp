#include "BackGround.h"

void BackGround::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void BackGround::Init()
{
	//板ポリにテクスチャ（マテリアル）ロード
	m_polygon.SetMaterial("Asset/Textures/BackGround.png");

	//板ポリゴンのサイズを拡大
	m_polygon.SetScale(200.0f);

	//板ポリの原点（真ん中下段指定）
	//m_polygon.SetUVRect(10);
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	//奥川に座標を更新
	m_mWorld = Math::Matrix::CreateTranslation(Math::Vector3(0.0f, 0.0f, 100.0f));
	//m_mWorld.Translation() = { 0,0,100 };
}

#pragma once
class Player :public KdGameObject
{
public:
	Player() {}
	~Player() {}

	void Init()override;

	void Update()override;
	void PostUpdate()override;

	void DrawLit()override;
	//影だけ生み出すもの描画とかはしない
	void GenerateDepthMapFromLight()override;
private:
	//板ポリ
	KdSquarePolygon m_poly;
	Math::Vector3 m_scale;
	Math::Vector3 m_pos;
	//方向（ベクトルの向き）
	Math::Vector3 m_dir;
	//移動量（ベクトルの向き）
	float m_speed;
	float m_anima;
	int m_run[4];
	//重力
	float m_gravity;
};

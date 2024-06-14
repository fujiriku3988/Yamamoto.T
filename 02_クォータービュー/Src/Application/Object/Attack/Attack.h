#pragma once
class Attack :public KdGameObject
{
public:
	Attack() {}
	~Attack() override{}

	void Init()override;
	void Update()override;
	void DrawUnLit()override;

	void OnHit()override;

private:
	KdSquarePolygon m_polygon;

	float m_animeCnt;//9コマ
	float m_animeSpeed;

	float m_attackArea;
};

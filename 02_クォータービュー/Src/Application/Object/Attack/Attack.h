#pragma once
class Attack :public KdGameObject
{
public:
	Attack() {}
	~Attack() override{}

	void Init()override;
	void Update()override;
	void DrawUnLit()override;

private:

	KdSquarePolygon m_polygon;

	float m_animeCnt;
	float m_animeSpeed;

	float m_attackArea;
};

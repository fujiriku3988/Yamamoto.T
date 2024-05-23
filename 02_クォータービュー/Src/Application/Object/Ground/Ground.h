#pragma once
class Ground :public KdGameObject
{
public:
	Ground() {}
	~Ground() override{}

	void DrawLit()override;
	void Init()override;

private:
	//モデル
	std::shared_ptr<KdModelData> m_model;
	Math::Vector3 m_scale;
	Math::Vector3 m_pos;
	Math::Matrix m_mat;
};

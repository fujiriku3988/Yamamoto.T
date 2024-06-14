#pragma once
class Player;
class Enemy :public KdGameObject
{
public:


	Enemy() {}
	~Enemy() {}

	void Init()override;

	void Update()override;
	void PostUpdate()override;

	void DrawLit()override;
	//影だけ生み出すもの描画とかはしない
	void GenerateDepthMapFromLight()override;

	void search();

	void SetPosEnemy(Math::Vector3 pos) { m_pos = pos; }

	void SetTarget(std::weak_ptr<Player>_target);

	void OnHit()override;
private:

	//void ChangeAnimation();

	//板ポリ
	std::shared_ptr<KdSquarePolygon> m_poly;
	std::weak_ptr<Player> m_target;
	Math::Vector3 m_scale;
	Math::Vector3 m_pos;

	//アニメーション情報
	float m_animeCnt;
	float m_animeSpeed;

	//サーチ
	bool m_chaseFlg;
	float m_searchArea;

	//キャラが向いている方向種類 ビット管理
	UINT m_dirType;
	//方向（ベクトルの向き）
	Math::Vector3 m_dir;
	//移動量（ベクトルの向き）
	float m_speed;
	//重力
	float m_gravity;
};

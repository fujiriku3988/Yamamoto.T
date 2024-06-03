#pragma once
class Player :public KdGameObject
{
public:
	enum DirType
	{
		Up = 1 << 0,	//上
		Down = 1 << 1,	//下
		Left = 1 << 2,	//左
		Right = 1 << 3	//右
	};
	//アニメーション情報
	struct AnimetionInfo
	{
		int start;	//開始コマ
		int end;	//終了コマ
		float count;//現在のコマ数カウント
		float speed;//アニメーションの速度
	};

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

	//アニメーション情報
	AnimetionInfo m_animeInfo;

	//キャラが向いている方向種類 ビット管理
	UINT m_dirType;
	//方向（ベクトルの向き）
	Math::Vector3 m_dir;
	//移動量（ベクトルの向き）
	float m_speed;
	float m_anima;
	int m_run[4];
	//重力
	float m_gravity;
};

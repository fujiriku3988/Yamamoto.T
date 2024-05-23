#pragma once
class BaseObject
{
public:
	BaseObject() {};
	virtual ~BaseObject() {};//

	//オブジェクトの種類
	enum class ObjectType
	{
		Player,
		Enemy,
		Bullet
	};

	//仮想関数
	virtual void Update();//書き換えたいものにvirtual付ける
	virtual void Draw();
	virtual void Init();
	virtual void Release();
	//virtual void Update() = 0;これで純粋仮想関数？になる

	void SetTexture(std::string _fileName);

	ObjectType GetObjType() { return m_objType; }
	Math::Vector3 GetPos() { return m_pos; }


	bool GetAliveFlg(){return m_aliveflg;}
	//Hitじの処理
	virtual void OnHit();

protected://privateではなくprotected(基底のやつは使える)

	KdTexture m_tex;
	Math::Vector3 m_pos;
	Math::Matrix m_mat;
	bool m_aliveflg = true;
	ObjectType m_objType;
};
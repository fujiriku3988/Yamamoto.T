#pragma once
#include "../BaseObject.h"
class GameScene;
class Enemy:public BaseObject
{
public:
	Enemy() {}
	~Enemy() { Release(); }

	void Update()override;	//更新
	void Draw()override;	//描画
	void Init()override;	//初期化

	void OnHit()override;

	void SetOwner(GameScene* _owner) { m_owner = _owner; }

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
	void SetPos(float _x, float _y) { m_pos = {_x,_y,0.0f}; }//SetPosオーバーロード

	void SetMovePow(Math::Vector3 _movePow) { m_movePow = _movePow; }

private:
	GameScene* m_owner = nullptr;
	void Release()override;
	Math::Vector3 m_movePow;
};

#pragma once
#include"../BaseObject.h"
class GameScene;
class Bullet :public BaseObject
{
public:

	Bullet() {};
	~Bullet() {};

	void Update()override;
	void Draw()override;
	void Init()override;
	void OnHit()override;



	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
	void SetOwner(GameScene* _owner) { m_owner = _owner; }

private:
	Math::Vector3 m_movePow;
	GameScene* m_owner = nullptr;
};

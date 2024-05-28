#pragma once
#include"../BaseScene/BaseScene.h"
class Player;

class GameScene : public BaseScene
{
public :

	GameScene() { Init(); }
	~GameScene() {}



private:
	std::weak_ptr<Player>m_player;
	void Event() override;
	void Init() override;
	//shaared_ptr...（参照カウンタがある、アクセス可能）
	//weak_ptr ...（参照カウンタがない、アクセスする権利がない）
	//unieque_ptr...（１つのポインタでしか所有できない）
};

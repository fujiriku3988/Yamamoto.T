#pragma once
//#include"Application/Object/BaseObject.h"

//基本的にヘッダーファイルの中で
//別のヘッダーファイルをインクルードするのはNG
//継承元のクラスのヘッダーのみインクルードが必須なので可とする
#include "../BaseObject.h"//コロン使ったら前の階層に戻ってすぐ取ってこれる
class GameScene;
//class Bullet;

class Player :public BaseObject
{
public://パブリック付け忘れあかん	
	Player() {};
	~Player() { Release(); }

	//基底クラスの仮想関数をオーバーライド
	//override指定子はなくてもオーバーライドはされるが
	//override可能かどうかを判別する目的で付けるべき（可読性の問題もある）

	void Update()override;
	void Draw()override;
	void Init()override;
	
	void SetOwner(GameScene* _owner) { m_owner = _owner; }

private:
	GameScene* m_owner = nullptr;
	void Release()override;
	//Math::Vector2 m_pos;
	//Math::Vector2 m_move;
};
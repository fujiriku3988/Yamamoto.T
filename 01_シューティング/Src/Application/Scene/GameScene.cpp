#include "GameScene.h"
#include"../Object/Player/Player.h"
#include"../Object/Enemy/Enemy.h"
#include"../Object/Bullet/Bullet.h"
void GameScene::PreUpadate()
{
	//Updateno前の更新処理
	//オブジェクトリストの整理をしておく

	//イテレータとは・・・コンテナクラス用のポインタ（のようなもの
	//コンテナを先頭から末尾までたどる際に使用
	
	//イテレータ作成　べた書き
	//std::vector<std::shared_ptr<BaseObject>>::iterator it;
	//it = m_objList.begin();

	//イテレータ作成　auto版
	auto it = m_objList.begin();

	while (it != m_objList.end())//end()は最後の要素の１個後ろを返す　
	{
		//オブジェクトの有効チェック
		if ((*it)->GetAliveFlg() == false)
		{
			//無効なオブジェクトをリスト方から削除
			it = m_objList.erase(it);
		}
		else
		{
			it++;//津次の要素へイテレータを進める
		}
	}

	//↑の後に有効なオブジェクトだけのリストになっている
}

void GameScene::Upadate()
{
	//m_player->Update();
	//m_enemy->Update();
	
	//３％の確率で敵を出現させる
	if (rand()% 100<3)
	{
		std::shared_ptr<Enemy>enemy;
		enemy = std::make_shared<Enemy>();
		enemy->Init();
		enemy->SetPos(640,320);
		enemy->SetMovePow({ -2.0f ,-2.0f,0.0f});
		m_objList.push_back(enemy);
	}

	//全オブジェクトの更新関数を一括で呼ぶ
	for (int i = 0; i < m_objList.size(); i++)
	{
		m_objList[i]->Update();
	}

}

void GameScene::Draw()
{
	//m_player->Draw();
	//m_enemy->Draw();

	//全オブジェクトの描画関数を一括で呼ぶ
	//範囲ベースFor
	/*for (auto& obj : m_objList)
	{
		obj->Draw();
	}*/
	for (int i = 0; i < m_objList.size(); i++)
	{
		m_objList[i]->Draw();
	}
}

void GameScene::Init()
{
	//m_player = new player();
	//m_player = std::make_shared<player>();
	//m_player->Init();
	//m_enemy = std::make_shared<Enemy>();
	//m_enemy->Init();
	
	//エネミー
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<Enemy>enemy;
		enemy = std::make_shared<Enemy>();
		enemy->Init();
		enemy->SetPos(( - 640.0f + 32.0f) + 128 * i, 360.0f);
		m_objList.push_back(enemy);
	}

	//プレイヤー
	std::shared_ptr<Player>player;
	player = std::make_shared<Player>();
	player->Init();
	player->SetOwner(this);//配列のリストに追加される前に情報を渡しておく
	m_objList.push_back(player);//リスト追加
	
	//std::shared_ptr<Bullet>bulet;
	//bulet = std::make_shared<Bullet>();
	//bulet->SetOwner(this);//配列のリストに追加される前に情報を渡しておく
	//m_objList.push_back(enemy);
	
	//m_player->SetOwner(this);
}

void GameScene::Release()
{
	//delete m_player;
}

#pragma once
//class player;
class BaseObject;
class GameScene
{
public:

	GameScene() {}
	~GameScene() { Release(); }//破棄時のRelease()

	void PreUpadate();	//更新を呼ぶ前の処理
	void Upadate();		//更新
	void Draw();		//描画
	void Init();		//初期化
	
	//オブジェクトリストを取得
	std::vector<std::shared_ptr<BaseObject>> GetObjList() { return m_objList; }

	//オブジェクトリストにオブジェクトを追加
	void AddObject(std::shared_ptr<BaseObject> _obj)
	{
		m_objList.push_back(_obj);
	}

private:

	void Release();		//終了処理※外部に呼ばれたくないのでprivate
	//player* m_player=nullptr;//派生クラスのポインタ
	//BaseObject* m_player = nullptr;//基底クラスのポインター
	//std::shared_ptr<player>m_player = nullptr
	//std::shared_ptr<BaseObject>m_player = nullptr;//スマートポインター
	//std::shared_ptr<BaseObject>m_enemy = nullptr;//スマートポインター

	//全オブジェクトを可変長配列で管理
	std::vector<std::shared_ptr<BaseObject>>m_objList;

};

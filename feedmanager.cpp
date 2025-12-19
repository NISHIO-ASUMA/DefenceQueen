//=========================================================
//
// 複数の餌を管理する処理 [ feedmanager.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "feedmanager.h"
#include "feed.h"
#include "meshcylinder.h"
#include "gamesceneobject.h"
#include "time.h"

//*********************************************************
// 名前空間
//*********************************************************
namespace FEED_INFO
{
	const char* MODEL_NAME[2]
	{
		"FEED/Lemon.x",
		"FEED/Suger.x"
	};
};

//=========================================================
// コンストラクタ
//=========================================================
CFeedManager::CFeedManager() :m_pFeed{}, m_nCreateLastTime(-1), m_nStopCount(NULL)
{

}
//=========================================================
// デストラクタ
//=========================================================
CFeedManager::~CFeedManager()
{
	// 破棄
	Uninit();
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CFeedManager::Init(void)
{
	// 配列クリア
	m_pFeed.clear();

	// 初期生成の餌
	m_pFeed.push_back(CFeed::Create(D3DXVECTOR3(-700.0f, 60.0f,-600.0f), VECTOR3_NULL, INITSCALE, "FEED/Suger.x",85.0f));
	m_pFeed.push_back(CFeed::Create(D3DXVECTOR3(700.0f, 60.0f, -600.0f), VECTOR3_NULL, INITSCALE, "FEED/Suger.x", 85.0f));
	m_pFeed.push_back(CFeed::Create(D3DXVECTOR3(0.0f, 40.0f, 570.0f), VECTOR3_NULL, INITSCALE, "FEED/Lemon.x", 85.0f));

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CFeedManager::Uninit(void)
{
	m_pFeed.clear();
}
//=========================================================
// 更新処理
//=========================================================
void CFeedManager::Update(void)
{
#if 1
	// 経過時間によって出現する
	 auto GameSceneObject = CGameSceneObject::GetInstance();
	 auto time = GameSceneObject->GetTime()->GetToAll();

	 // ランダム数
	 int nRand = rand() % 2;

	 // 総ゲーム時間から計算 (25秒ごとに一個追加で出現させたい 配列を拡張するのでサイズを変える)
	 if (time != 120 && time % 25 == 0 && time != m_nCreateLastTime)
	 {
		 // ランダムな座標
		 D3DXVECTOR3 pos = CreateRandomPos();

		 // 配列に追加
		 m_pFeed.push_back(
			 CFeed::Create(pos,
				 VECTOR3_NULL,
				 INITSCALE,
				 FEED_INFO::MODEL_NAME[nRand],
				 85.0f)
		 );

		 // 時間変更
		 m_nCreateLastTime = time;
	 }
#endif
}
//=========================================================
// 描画処理
//=========================================================
void CFeedManager::Draw(void)
{
	// 無し
}
//=========================================================
// 要素を消す
//=========================================================
void CFeedManager::Erase(CFeed* pFeed)
{
	// 削除処理
	auto DeleteDestObj = std::find(m_pFeed.begin(), m_pFeed.end(), pFeed);

	// もし最後尾なら
	if (DeleteDestObj == m_pFeed.end())
	{
		return;
	}

	// 削除
	(*DeleteDestObj)->Uninit();

	// 先をnullにする
	pFeed = nullptr;

	// 配列の要素を消す
	DeleteDestObj = m_pFeed.erase(DeleteDestObj);
}
//=========================================================
// 未登録の餌を探す
//=========================================================
CFeed* CFeedManager::FindFreeFeed(void)
{
	// 最大数を見る
	for (auto& feed : m_pFeed)
	{
		// もし割り当てられてなかったら
		if (!feed->IsAssigned())
			return feed;
	}

	return nullptr;
}
//=========================================================
// ランダムな座標を計算する関数
//=========================================================
D3DXVECTOR3 CFeedManager::CreateRandomPos(void)
{
	// 変数計算
	float x = static_cast<float>((rand() % 1000 - 500)); 
	float y = 60.0f; 
	float z = static_cast<float>((rand() % 1000 - 500));

	// 値を返す
	return D3DXVECTOR3(x, y, z);
}

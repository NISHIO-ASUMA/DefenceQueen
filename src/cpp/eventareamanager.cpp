//=========================================================
//
// イベントエリア複数管理処理 [ eventareamanager.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// クラス定義ヘッダーファイル
//*********************************************************
#include "eventareamanager.h"

//*********************************************************
// インクルードファイル
//*********************************************************
#include "gamesceneobject.h"
#include "gametime.h"
#include "eventarea.h"
#include "feed.h"

//*********************************************************
// 定数宣言空間
//*********************************************************
namespace EventManager
{
	constexpr int NUMPATH = 3;				// モデルの種類
	constexpr float COLLISIONRANGE = 65.0f; // 餌の衝突判定半径
	constexpr int ACTIVEPOS = 4;

	const char* MODEL_NAME[NUMPATH]			// モデルパス配列	
	{
		"FEED/Lemon.x",
		"FEED/Suger.x",
		"FEED/Solt.x"
	};

	const D3DXVECTOR3 EventPos[ACTIVEPOS] // 出現座標の値
	{
		{ 0.0f, 0.0f,-390.0f},
		{ 435.0f,0.0f, 30.0f},
		{-530.0f,0.0f, -45.0f},
		{ -5.0f, 0.0f, 400.0f}
	};

	const D3DXVECTOR3 EventFeedPos[ACTIVEPOS] // 出現餌の座標の値
	{
		{ 0.0f, 0.0f, -360.0f},
		{ 525.0f,0.0f,  30.0f},
		{-600.0f,0.0f, -45.0f},
		{ -35.0f,0.0f, 410.0f}
	};

	const int RANDOMHP[ACTIVEPOS] // 体力値配列
	{
		10,
		20,
		25,
		30
	};

};

//=========================================================
// コンストラクタ
//=========================================================
CEventAreaManager::CEventAreaManager() : m_pAreas{}, 
m_pFeeds{},
m_nLastEventTime(NULL), 
m_nCreateidx(NULL)
{

}
//=========================================================
// デストラクタ
//=========================================================
CEventAreaManager::~CEventAreaManager()
{
	Uninit();
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CEventAreaManager::Init(void)
{
	// 配列のクリア
	m_pAreas.clear();
	m_pFeeds.clear();

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CEventAreaManager::Uninit(void)
{
	// 配列をクリア
	m_pAreas.clear();
	m_pFeeds.clear();

	// フラグリセット
	for (int nCnt = 0; nCnt < NUM_ACTIVEPOS; nCnt++)
	{
		m_isActivePos[nCnt] = false;
	}
}
//=========================================================
// 更新処理
//=========================================================
void CEventAreaManager::Update(void)
{
	// 名前空間を使用する
	using namespace EventManager;

	// ゲーム時間から計測する
	const auto& Time = CGameSceneObject::GetInstance()->GetTime();
	int nTime = Time->GetToAll();

	// 総ゲーム時間から計算
	if (nTime % 5 == 0 && nTime != m_nLastEventTime)
	{
		// 全ての場所が埋まっていないか確認
		if (m_pAreas.size() >= NUM_ACTIVEPOS) return;

		// 空いているインデックスをランダムに決定
		int nRand;
		do 
		{
			nRand = rand() % NUM_ACTIVEPOS;
		} while (m_isActivePos[nRand] == true); // すでに使われていたらやり直し

		// モデルパスを設定
		int nPathRand = rand() % NUMPATH;

		CEventArea* area = CEventArea::Create(EventPos[nRand]);
		CFeed* feed = CFeed::Create(EventFeedPos[nRand], VECTOR3_NULL, INITSCALE, MODEL_NAME[nPathRand], COLLISIONRANGE, RANDOMHP[nRand]);

		// インデックスを保存しておく
		area->SetIdx(nRand);

		// 配列に追加する
		feed->SetOwnerArea(area);
		m_pAreas.push_back(area);
		m_pFeeds.push_back(feed);

		// 使用中フラグを立てる
		m_isActivePos[nRand] = true;

		m_nLastEventTime = nTime;
	}
}
//=========================================================
// エリア配列の要素をクリアする関数
//=========================================================
void CEventAreaManager::Erase(CEventArea* pArea)
{
	// nullなら
	if (pArea == nullptr) return;

	// インデックス取得
	int nIdx = pArea->GetIdx();

	if (nIdx >= 0 && nIdx < NUM_ACTIVEPOS)
	{
		// 生成場所のフラグを無効化する
		m_isActivePos[nIdx] = false; 
	}

	// 削除処理
	auto DeleteDestObj = std::find(m_pAreas.begin(), m_pAreas.end(), pArea);

	// もし最後尾なら
	if (DeleteDestObj == m_pAreas.end()) return;

	// 自身の削除
	(*DeleteDestObj)->Uninit();

	// 配列の要素を消す
	DeleteDestObj = m_pAreas.erase(DeleteDestObj);
}
//=========================================================
// 餌配列の要素をクリアする関数
//=========================================================
void CEventAreaManager::EraseFeed(CFeed* pFeed)
{
	// 削除処理
	auto DeleteDestObj = std::find(m_pFeeds.begin(), m_pFeeds.end(), pFeed);

	// もし最後尾なら
	if (DeleteDestObj == m_pFeeds.end()) return;

	// 自身の削除
	(*DeleteDestObj)->Uninit();

	// 配列の要素を消す
	DeleteDestObj = m_pFeeds.erase(DeleteDestObj);
}
//=========================================================
//
// イベントエリア複数管理処理 [ eventareamanager.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "eventareamanager.h"
#include "gamesceneobject.h"
#include "time.h"
#include "eventarea.h"
#include "feed.h"

//*********************************************************
// 定数宣言空間
//*********************************************************
namespace EventManager
{
	constexpr int NUMPATH = 3;		 // パス配列
	constexpr int NUM_ACTIVEPOS = 4; // イベントが起きる場所の数

	const char* MODEL_NAME[NUMPATH] // パス配列
	{
		"FEED/Lemon.x",
		"FEED/Suger.x",
		"FEED/Solt.x"
	};

	const D3DXVECTOR3 EventPos[NUM_ACTIVEPOS] // 出現座標の値
	{
		{ 15.0f, 0.0f,-420.0f},
		{ 465.0f,0.0f,  30.0f},
		{-540.0f,0.0f, -45.0f},
		{ -5.0f, 0.0f, 410.0f}
	};
};

//=========================================================
// コンストラクタ
//=========================================================
CEventAreaManager::CEventAreaManager() : m_pAreas{}, m_nLastEventTime(NULL)
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
	m_pAreas.clear();
	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CEventAreaManager::Uninit(void)
{
	// 配列をクリア
	m_pAreas.clear();
}
//=========================================================
// 更新処理 TODO : ここで重ならないように出すかどうかは考える
//=========================================================
void CEventAreaManager::Update(void)
{
	// ゲーム時間から計測する
	const auto& Time = CGameSceneObject::GetInstance()->GetTime();
	int nTime = Time->GetToAll();

	// ランダム値を生成
	int nRand = rand() % EventManager::NUM_ACTIVEPOS;
	int nPathRand = rand() % EventManager::NUMPATH;

	// 総ゲーム時間から計算
	if (nTime % 15 == 0 && nTime != m_nLastEventTime)
	{
		// ランダムな座標
		D3DXVECTOR3 ActivePos = EventManager::EventPos[nRand];

		// 配列に追加
		m_pAreas.push_back(CEventArea::Create(ActivePos));

		// オブジェクトを配置する
		CFeed::Create(ActivePos,VECTOR3_NULL,INITSCALE,EventManager::MODEL_NAME[nPathRand],5.0f,1);

		// 出現時間変更
		m_nLastEventTime = nTime;
	}
}
//=========================================================
// 配列の要素をクリアする関数
//=========================================================
void CEventAreaManager::Erase(CEventArea* pArea)
{
	// 削除処理
	auto DeleteDestObj = std::find(m_pAreas.begin(), m_pAreas.end(), pArea);

	// もし最後尾なら
	if (DeleteDestObj == m_pAreas.end())
	{
		return;
	}

	// 自身の削除
	(*DeleteDestObj)->Uninit();

	// 配列の要素を消す
	DeleteDestObj = m_pAreas.erase(DeleteDestObj);
}
//=========================================================
//
// 仲間のスポナー管理処理 [ arrayspawnmanager.cpp ]
// Author: Asuma Nishio
// 
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "arrayspawnmanager.h"
#include "arraymanager.h"
#include "arrayspawner.h"
#include "topant.h"
#include "debugproc.h"

//*********************************************************
// 使用名前空間
//*********************************************************
using namespace SpawnManager;

//=========================================================
// コンストラクタ
//=========================================================
CArraySpawnManager::CArraySpawnManager() : m_pArraySpawner{}
{

}
//=========================================================
// デストラクタ
//=========================================================
CArraySpawnManager::~CArraySpawnManager()
{
	// 終了処理
	Uninit();
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CArraySpawnManager::Init(CArrayManager* pManager)
{
	
	for (int nCnt = 0; nCnt < NUM_ARRAYSPAWNER; nCnt++)
	{
		// スポナー生成 ( スポナー座標,初期の仲間のストック数,アリ管理マネージャーポインタ )
		m_pArraySpawner[nCnt] = CArraySpawner::Create(SpawnManager::POS[nCnt], NUM_CREATEARRAY, pManager);

		// アクティブなアリを加算
		pManager->CountActiveArrays(m_pArraySpawner[nCnt]->GetStockArray());
	}

	// 全体のアクティブ化
	pManager->SetActiveAll();

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CArraySpawnManager::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_ARRAYSPAWNER; nCnt++)
	{
		if (m_pArraySpawner[nCnt])
		{
			delete m_pArraySpawner[nCnt];
			m_pArraySpawner[nCnt] = nullptr;
		}
	}
}
//=========================================================
// 更新処理
//=========================================================
void CArraySpawnManager::Update(void)
{
	for (int nCnt = 0; nCnt < NUM_ARRAYSPAWNER; nCnt++)
	{
		// 更新処理
		m_pArraySpawner[nCnt]->Update();
	}
}
//=========================================================
// 描画処理
//=========================================================
void CArraySpawnManager::Draw(void)
{
	// デバッグ情報表示処理
	CDebugproc::Print("各スポナーのアリ情報\n[0]番目 : ストックアリ数 [ %d ]\n[1]番目 : ストックアリ数 [ %d ]\n[2]番目 : ストックアリ数 [ %d ]\n",
		m_pArraySpawner[0]->GetStockArray(), m_pArraySpawner[1]->GetStockArray(), m_pArraySpawner[2]->GetStockArray());
	CDebugproc::Draw(0, 260);

	// アリの状態表示
	CDebugproc::Print("各スポナーの先頭アリ情報\n[0]番目 : アクティブ =  %d\n[1]番目 : アクティブ =  %d\n[2]番目 : アクティブ =  %d\n",
		m_pArraySpawner[0]->GetTopAnt()->GetIsActive(), m_pArraySpawner[1]->GetTopAnt()->GetIsActive(), m_pArraySpawner[2]->GetTopAnt()->GetIsActive());
	CDebugproc::Draw(0, 340);
}
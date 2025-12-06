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
		// スポナー生成
		m_pArraySpawner[nCnt] = CArraySpawner::Create(SpawnManager::POS[nCnt],10, pManager);
	}

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

}
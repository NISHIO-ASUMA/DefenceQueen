//=========================================================
//
// 敵のスポナー複数管理処理 [ enemyspawnmanager.cpp ]
// Author: Asuma Nishio
// 
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "enemyspawnmanager.h"
#include "enemyspawner.h"
#include "block.h"

//=========================================================
// コンストラクタ
//=========================================================
CEnemySpawnManager::CEnemySpawnManager() : m_pSpawners{}
{

}
//=========================================================
// デストラクタ
//=========================================================
CEnemySpawnManager::~CEnemySpawnManager()
{
	Uninit();
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CEnemySpawnManager::Init(void)
{
	// 名前空間使用
	using namespace SET_INFO;

	for (int nCnt = 0; nCnt < CREATE_NUM; nCnt++)
	{
		// 初期スポナー生成
		m_pSpawners[nCnt] = new CEnemySpawner;
		m_pSpawners[nCnt]->SetPos(SpawnPos[nCnt]);

		// オブジェクト配置
		CBlock::Create(SpawnPos[nCnt], VECTOR3_NULL, INITSCALE, "STAGEOBJ/EnemySpawn.x");
	}

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CEnemySpawnManager::Uninit(void)
{
	// 配列の破棄
	for (auto Spawn : m_pSpawners)
	{
		if (Spawn)
		{
			Spawn->Uninit();
			delete Spawn;
			Spawn = nullptr;
		}
	}
}
//=========================================================
// 更新処理
//=========================================================
void CEnemySpawnManager::Update(void)
{

}
//=========================================================
// 描画処理
//=========================================================
void CEnemySpawnManager::Draw(void)
{
	
}
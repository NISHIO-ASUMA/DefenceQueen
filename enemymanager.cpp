//=========================================================
//
// 敵の複数管理処理 [ enemymanager.cpp ]
// Author: Asuma Nishio
// 
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "enemymanager.h"
#include "enemy.h"
#include "gamesceneobject.h"
#include "time.h"
#include "enemyspawnmanager.h"

//=========================================================
// コンストラクタ
//=========================================================
CEnemyManager::CEnemyManager() : m_pEnemys{}, m_nCreateLastTime(-1)
{

}
//=========================================================
// デストラクタ
//=========================================================
CEnemyManager::~CEnemyManager()
{
	Uninit();
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CEnemyManager::Init(void)
{
	// 配列クリア
	m_pEnemys.clear();

	// 配列のサイズを設定
	m_pEnemys.reserve(Config::NUM_ENEMY);

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CEnemyManager::Uninit(void)
{
	// 配列クリア
	m_pEnemys.clear();
}
//=========================================================
// 更新処理
//=========================================================
void CEnemyManager::Update(void)
{
	auto GameSceneObject = CGameSceneObject::GetInstance();
	int time = GameSceneObject->GetTime()->GetToAll();

	// 使用名前空間
	using namespace SET_INFO;

	// サイズオーバーチェック
	if (m_pEnemys.size() >= Config::NUM_ENEMY) return;

	if (time > 0 &&
		time % 15 == 0 &&
		time != m_nCreateLastTime)
	{
		// 今回の湧き数
		int spawnCount = SPAWN_MIN + rand() % (SPAWN_MAX + 1);

		for (int i = 0; i < spawnCount; i++)
		{
			// スポーン位置ランダム
			int index = rand() % CREATE_NUM;
			D3DXVECTOR3 pos = SpawnPos[index];

			// 
			D3DXVECTOR3 offset(
				(rand() % 50 - 25) * 2.0f,
				0.0f,
				(rand() % 50 - 25) * 2.0f
			);

			pos += offset;

			CEnemy* pEnemy = CEnemy::Create(pos, VECTOR3_NULL, Config::LIFE);

			if (pEnemy)
			{
				pEnemy->SetIsActive(true);
				m_pEnemys.push_back(pEnemy);
			}
		}

		m_nCreateLastTime = time;
	}
}
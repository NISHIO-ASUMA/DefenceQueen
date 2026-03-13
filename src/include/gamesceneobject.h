//=========================================================
//
// ゲームのオブジェクト管理処理 [ gamesceneobject.h ]
// Author: Asuma Nishio
// 
//=========================================================

//*********************************************************
// インクルードガード
//*********************************************************
#pragma once

//*********************************************************
// インクルードファイル
//*********************************************************
#include <memory>

//*********************************************************
// 前方宣言
//*********************************************************
class CBlockManager;
class CEnemyManager;
class CGameTime;
class CEnemy;
class CArrayManager;
class CArraySpawnManager;
class CQueen;
class CEnemySpawner;
class CScore;
class CEnemySpawnManager;
class CEnemyManager;
class CGameWallManager;
class CTopAnt;
class CBaseMapFeed;

//*********************************************************
// ゲームシーンで使うオブジェクト管理クラスを定義
//*********************************************************
class CGameSceneObject
{
public:

	~CGameSceneObject();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void DeleteQueen(void);
	
	CGameTime* GetTime(void) const { return m_pTimer; }
	CScore* GetScore(void) const { return m_pScore; }
	CQueen* GetQueen(void) const { return m_pQueen; }
	CTopAnt* GetTopAnt(void) const { return m_pTopAnt; }

	CEnemySpawner* GetEnemySpawn(void) const { return m_pSpawn.get(); }
	CBaseMapFeed* GetBaseMapFeed(void) const { return m_pBasemapFeed.get(); }
	CGameWallManager* GetGameWall(void) const { return m_pWallManager.get(); }
	CEnemyManager* GetEnemyManager(void) const { return m_pEnemyManager.get(); }
	CBlockManager* GetBlockManager(void) const { return m_pBlocks.get(); }
	CArrayManager* GetArrayManager(void) const { return m_pArrayManager.get(); }
	CArraySpawnManager* GetArraySpawn(void) const { return m_pArraySpawn.get(); }
	CEnemySpawnManager* GetEnemySpawnManager(void) const { return m_pEnemySpawnManager.get(); }

	static CGameSceneObject* GetInstance(void);

private:

	static CGameSceneObject* m_pInstance;	// シングルトン変数

	CGameSceneObject();			// コンストラクタ
	void CreatePointer(void);	// 初期化処理関数分け

	CScore* m_pScore;		// スコアクラスのポインタ
	CGameTime* m_pTimer;	// タイマークラスのポインタ
	CQueen* m_pQueen;		// 女王アリクラス
	CTopAnt* m_pTopAnt;		// 操作できるトップアリ

	std::unique_ptr<CBlockManager>m_pBlocks;				// ブロックマネージャークラスのポインタ
	std::unique_ptr<CArrayManager>m_pArrayManager;			// 仲間アリ管理クラス
	std::unique_ptr<CEnemySpawner>m_pSpawn;					// スポーン管理クラス
	std::unique_ptr<CArraySpawnManager>m_pArraySpawn;		// 仲間スポーン管理クラス
	std::unique_ptr<CEnemySpawnManager>m_pEnemySpawnManager;// 敵スポーン管理
	std::unique_ptr<CEnemyManager>m_pEnemyManager;			// 敵管理クラス
	std::unique_ptr<CGameWallManager>m_pWallManager;		// ゲームの壁管理
	std::unique_ptr<CBaseMapFeed>m_pBasemapFeed;			// マップの標準の餌管理クラス
};
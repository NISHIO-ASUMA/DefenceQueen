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
class CSelectPoint;
class CFeedManager;
class CTime;
class CEnemy;
class CWorkerUiManager;
class CWorkerManager;
class CArrayManager;
class CQueen;
class CEnemySpawner;
class CArraySpawnManager;
class CScore;
class CPlayer;
class CEnemySpawnManager;

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

	CTime* GetTime(void) { return m_pTimer; }
	CScore* GetScore(void) { return m_pScore; }
	CQueen* GetQueen(void) { return m_pQueen; }
	CPlayer* GetPlayer(void) { return m_pPlayer; }
	CSelectPoint* GetPoint(void) { return m_pSelectPoint; }
	CFeedManager* GetFeedManager(void) { return m_pFeed.get(); }
	CEnemySpawner* GetEnemySpawn(void) { return m_pSpawn.get(); }
	CWorkerUiManager* GetWorkUi(void) { return m_pWorkUi.get(); }
	CBlockManager* GetBlockManager(void) { return m_pBlocks.get(); }
	CWorkerManager* GetWorkerM(void) { return m_pWorkerManager.get(); }
	CArrayManager* GetArrayManager(void) { return m_pArrayManager.get(); }
	CArraySpawnManager* GetArraySpawn(void) { return m_pArraySpawn.get(); }
	CEnemySpawnManager* GetEnemySpawnManager(void) { return m_pEnemySpawnManager.get(); }

	static CGameSceneObject* GetInstance(void);

private:

	//*****************************
	// 定数構造体
	//*****************************
	struct Config
	{
		static constexpr int INITIAL_ARRAY = 90; // 初期設定数
	};

	CGameSceneObject();	// コンストラクタ
	
	static CGameSceneObject* m_pInstance;	// シングルトン変数

	CScore* m_pScore;	// スコアクラスのポインタ
	CTime* m_pTimer;	// タイマークラスのポインタ
	CSelectPoint* m_pSelectPoint;	// 選択ポイントのクラス
	CQueen* m_pQueen;	// 女王クラス
	CPlayer* m_pPlayer; // プレイヤークラスのポインタ

	std::unique_ptr<CWorkerUiManager>m_pWorkUi;	// 表示uiクラスポインタ
	std::unique_ptr<CFeedManager>m_pFeed;	// 餌管理クラスのポインタ
	std::unique_ptr<CBlockManager>m_pBlocks; // ブロックマネージャークラスのポインタ
	std::unique_ptr<CWorkerManager>m_pWorkerManager;	// 司令塔アリ管理クラス
	std::unique_ptr<CArrayManager>m_pArrayManager;	// 仲間アリ管理クラス
	std::unique_ptr<CEnemySpawner>m_pSpawn;			// スポーン管理クラス
	std::unique_ptr<CArraySpawnManager>m_pArraySpawn; // 仲間スポーン管理クラス
	std::unique_ptr<CEnemySpawnManager>m_pEnemySpawnManager; // 敵スポーン管理
};
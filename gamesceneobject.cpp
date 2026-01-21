//=========================================================
//
// ゲームのオブジェクト管理処理 [ gamesceneobject.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "gamesceneobject.h"
#include "ui.h"
#include "player.h"
#include "meshfield.h"
#include "blockmanager.h"
#include "feedmanager.h"
#include "selectpoint.h"
#include "grass.h"
#include "feed.h"
#include "time.h"
#include "enemy.h"
#include "array.h"
#include "workeruimanager.h"
#include "worker.h"
#include "workermanager.h"
#include "arraymanager.h"
#include "enemyspawner.h"
#include "gimmicksuction.h"
#include "arrayspawnmanager.h"
#include "topant.h"
#include "score.h"
#include "manager.h"
#include "input.h"
#include "queen.h"
#include "enemyspawnmanager.h"
#include "meshdome.h"
#include "enemymanager.h"
#include "gamemanager.h"
#include "gamewallmanager.h"
#include "meshcylinder.h"
#include "sendnumber.h"

//*********************************************************
// 静的メンバ変数
//*********************************************************
CGameSceneObject* CGameSceneObject::m_pInstance = nullptr; // 1つのインスタンス

//=========================================================
// コンストラクタ
//=========================================================
CGameSceneObject::CGameSceneObject() : 
m_pBlocks(nullptr),
m_pSelectPoint(nullptr),
m_pTimer(nullptr),
m_pScore(nullptr),
m_pArrayManager(nullptr),
m_pWorkUi(nullptr),
m_pQueen(nullptr),
m_pSpawn(nullptr),
m_pArraySpawn(nullptr),
m_pPlayer(nullptr),
m_pEnemySpawnManager(nullptr),
m_pEnemyManager(nullptr),
m_pWallManager(nullptr)
{
}
//=========================================================
// デストラクタ
//=========================================================
CGameSceneObject::~CGameSceneObject()
{

}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CGameSceneObject::Init(void)
{
	// メッシュフィールド生成
	CMeshField::Create(VECTOR3_NULL,3200.0f,2000.0f,1,1);

	// メッシュドーム生成
	CMeshDome::Create(D3DXVECTOR3(0.0f,-20.0f,0.0f), 80.0f);

	// メッシュシリンダー生成
	CMeshCylinder::Create(VECTOR3_NULL,80.0f);
	
	// コロン生成
	CUi::Create(D3DXVECTOR3(1125.0f, 60.0f, 0.0f), 0, 15.0f, 30.0f, "coron.png", false);
	CUi::Create(D3DXVECTOR3(1125.0f, 55.0f, 0.0f), 0, 140.0f, 55.0f, "Time_frame.png", false);
	CUi::Create(D3DXVECTOR3(105.0f, 35.0f, 0.0f), 0, 100.0f, 30.0f, "SendNum.png", false);

	// 各種ポインタクラスの生成
	CreatePointer();

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CGameSceneObject::Uninit(void)
{
#if 1
	// 餌管理クラスの破棄
	m_pFeed.reset();

	// 配置オブジェクトクラスの破棄
	m_pBlocks.reset();

	// 仲間アリの破棄
	m_pArrayManager.reset();

	// 働き司令塔アリの破棄
	m_pWorkerManager.reset();

	// 敵スポナー破棄
	m_pSpawn.reset();

	// 仲間スポナー破棄
	m_pArraySpawn.reset();

	// 敵のスポナー管理クラス
	m_pEnemySpawnManager.reset();

	// 敵管理の破棄
	m_pEnemyManager.reset();

	// 世界の壁の破棄
	m_pWallManager.reset();

	// ui処理
	m_pWorkUi.reset();
#endif

	// インスタンスの破棄
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
//=========================================================
// 更新処理
//=========================================================
void CGameSceneObject::Update(void)
{
	// 仲間アリ管理クラスの更新
	if (m_pArrayManager)
	{
		m_pArrayManager->Update();
	}

	// 働きアリuiクラスの更新
	if (m_pWorkUi)
	{
		m_pWorkUi->Update();
	}

	// 仲間アリのスポナー情報更新
	if (m_pArraySpawn)
	{
		m_pArraySpawn->Update();
	}

	// 働きアリの更新
	if (m_pWorkerManager)
	{
		m_pWorkerManager->Update();
	}

	// 餌管理クラスの更新
	if (m_pFeed)
	{
		m_pFeed->Update();
	}

	// 敵の更新
	if (m_pEnemyManager)
	{
		m_pEnemyManager->Update();
	}

	if (m_pSendNumber)
	{
		//m_pSendNumber->SetDestScore(m_pPlayer->GetSendNum());
	}

#ifdef _DEBUG

	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_F9))
	{
		// スコア加算テスト
		m_pScore->AddScore(12000);
	}

	//
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_F8))
	{
		// 書き出しテスト
		m_pScore->SaveScore();
		m_pQueen->SaveHp();
	}

#endif // _DEBUG
}
//=========================================================
// 描画処理
//=========================================================
void CGameSceneObject::Draw(void)
{
#ifdef _DEBUG

	// アリ管理クラスのデバッグ情報
	if (m_pArrayManager)
	{
		m_pArrayManager->Draw();
	}

	// スポナー管理クラスのデバッグ情報
	if (m_pArraySpawn)
	{
		m_pArraySpawn->Draw();
	}
#endif // _DEBUG
}
//=========================================================
// 対象オブジェクトの破棄
//=========================================================
void CGameSceneObject::DeleteQueen(void)
{
	// nullじゃなかったら
	if (m_pQueen)
	{
		m_pQueen->Uninit();
		m_pQueen = nullptr;
	}

	// ゲームフラグを有効化し、進行を停止する
	CGameManager::GetInstance()->SetIsGameEnd(true);
}
//=========================================================
// インスタンス取得処理
//=========================================================
CGameSceneObject* CGameSceneObject::GetInstance(void)
{
	// nullなら
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CGameSceneObject;
	}

	// インスタンスを返す
	return m_pInstance;
}
//=========================================================
// ポインタの生成を行う関数
//=========================================================
void CGameSceneObject::CreatePointer(void)
{
	// ブロックマネージャー生成
	m_pBlocks = std::make_unique<CBlockManager>();
	m_pBlocks->Init();

	// タイマー生成
	m_pTimer = CTime::Create(D3DXVECTOR3(1020.0f,60.0f,0.0f),60.0f,40.0f);

	// 餌の管理クラスを生成
	m_pFeed = std::make_unique<CFeedManager>();
	m_pFeed->Init();

	//// 仲間アリの大軍を生成
	//m_pArrayManager = std::make_unique<CArrayManager>();
	//m_pArrayManager->Init();

	//// 出現場所生成
	//m_pArraySpawn = std::make_unique<CArraySpawnManager>();
	//m_pArraySpawn->Init(m_pArrayManager.get());

	//// 司令塔アリ管理生成
	//m_pWorkerManager = std::make_unique<CWorkerManager>();
	//m_pWorkerManager->Init();

	// プレイヤー生成
	//m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -800.0f), VECTOR3_NULL);

	// 防衛対象のクイーン生成
	m_pQueen = CQueen::Create(D3DXVECTOR3(0.0f, 55.0f, -5.0f), VECTOR3_NULL);

	// 敵場所生成
	m_pEnemySpawnManager = std::make_unique<CEnemySpawnManager>();
	m_pEnemySpawnManager->Init();

	// スコア生成
	m_pScore = CScore::Create(D3DXVECTOR3(1220.0f, 620.0f, 0.0f), 100.0f, 60.0f);

	// 敵管理クラスの生成
	m_pEnemyManager = std::make_unique<CEnemyManager>();
	m_pEnemyManager->Init();

	// 世界の壁管理クラスの生成
	m_pWallManager = std::make_unique<CGameWallManager>();
	m_pWallManager->Init();

	// ナンバー生成
	m_pSendNumber = CSendNumber::Create(D3DXVECTOR3(280.0f, 30.0f, 0.0f), 40.0f, 30.0f);
}
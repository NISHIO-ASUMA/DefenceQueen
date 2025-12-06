//=========================================================
//
// ゲームのオブジェクト管理処理 [ gameobject.cpp ]
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
m_pArraySpawn(nullptr)
{
	// 値のクリア
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
	// 選択ポイント生成
	m_pSelectPoint = CSelectPoint::Create(VECTOR3_NULL, VECTOR3_NULL, 80.0f, 3.0f, 80.0f);

	// タイマー生成
	m_pTimer = CTime::Create(D3DXVECTOR3(960.0f,40.0f,0.0f),60.0f,40.0f);

	// メッシュフィールド生成
	CMeshField::Create(VECTOR3_NULL,3200.0f,2000.0f,1,1);

	// ブロックマネージャー生成
	m_pBlocks = std::make_unique<CBlockManager>();
	m_pBlocks->Init();

	// 餌を配置
	m_pFeed = std::make_unique<CFeedManager>();
	m_pFeed->Init();

	// 司令塔アリ管理生成
	m_pWorkerManager = std::make_unique<CWorkerManager>();
	m_pWorkerManager->Init();

	// 仲間アリの大軍を生成
	m_pArrayManager = std::make_unique<CArrayManager>();
	m_pArrayManager->Init(50);

	// 出現場所生成
	m_pArraySpawn = std::make_unique<CArraySpawnManager>();
	m_pArraySpawn->Init(m_pArrayManager.get());

	// ui配置
	m_pWorkUi = std::make_unique<CWorkerUiManager>();
	m_pWorkUi->Init();

	// プレイヤー生成
	CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -600.0f), VECTOR3_NULL, 10, "data/MOTION/Player/Player_100motion.txt");

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CGameSceneObject::Uninit(void)
{
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

	// ui処理
	m_pWorkUi.reset();

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

	// uiクラスの更新
	if (m_pWorkUi)
	{
		m_pWorkUi->Update();
	}

	// スポナー情報更新
	if (m_pArraySpawn)
	{
		m_pArraySpawn->Update();
	}
}
//=========================================================
// 描画処理
//=========================================================
void CGameSceneObject::Draw(void)
{
	// TODO : 提出の際にデバッグのみにする
	if (m_pArrayManager)
	{
		m_pArrayManager->Draw();
	}

	// スポナー情報描画
	if (m_pArraySpawn)
	{
		m_pArraySpawn->Draw();
	}
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
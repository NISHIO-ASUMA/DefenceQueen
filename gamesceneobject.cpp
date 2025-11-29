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

//*********************************************************
// 静的メンバ変数
//*********************************************************
CGameSceneObject* CGameSceneObject::m_pInstance = nullptr; // インスタンス

//=========================================================
// コンストラクタ
//=========================================================
CGameSceneObject::CGameSceneObject() : 
m_pBlocks(nullptr),
m_pSelectPoint(nullptr),
m_pTimer(nullptr),
m_pScore(nullptr),
m_pWorkUi(nullptr)
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
	// プレイヤー生成
	// CPlayer::Create(D3DXVECTOR3(600.0f, 0.0f, 0.0f), VECTOR3_NULL, 10, "data/MOTION/Player/Player100motion.txt");

	// NOTE: 実験
	// CArray::Create(D3DXVECTOR3(-400.0f,0.0f,-200.0f),VECTOR3_NULL,10);

	// 選択ポイント生成
	m_pSelectPoint = CSelectPoint::Create(VECTOR3_NULL, VECTOR3_NULL, 80.0f, 3.0f, 80.0f);

	// タイマー生成
	m_pTimer = CTime::Create(D3DXVECTOR3(HALFWIDTH - 80.0f,40.0f,0.0f),60.0f,40.0f);

	// メッシュフィールド生成
	CMeshField::Create(VECTOR3_NULL,3200.0f,2000.0f,2,2);

	// 敵生成
	CEnemy::Create(D3DXVECTOR3(720.0f, 0.0f, 300.0f), VECTOR3_NULL, 10);

	// ブロックマネージャー生成
	m_pBlocks = std::make_unique<CBlockManager>();
	m_pBlocks->Init();

	// 餌を配置
	m_pFeed = std::make_unique<CFeedManager>();
	m_pFeed->Init();

	// ui配置
	m_pWorkUi = std::make_unique<CWorkerUiManager>();
	m_pWorkUi->Init();

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
	// 無し
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
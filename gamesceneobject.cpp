//==================================================
//
// ゲームのオブジェクト管理処理 [ gameobject.cpp ]
// Author: Asuma Nishio
//
//==================================================

//**********************
// インクルードファイル
//**********************
#include "gamesceneobject.h"
#include "ui.h"
#include "player.h"
#include "meshfield.h"
#include "blockmanager.h"
#include "feedmanager.h"
#include "selectpoint.h"
#include "grass.h"
#include "feed.h"

//**********************
// 静的メンバ変数
//**********************
CScore* CGameSceneObject::m_pScore = nullptr; // スコアクラスの静的ポインタ

//===========================
// コンストラクタ
//===========================
CGameSceneObject::CGameSceneObject() : 
m_pBlocks(nullptr),
m_pSelectPoint(nullptr)
{
	// 値のクリア
}
//===========================
// デストラクタ
//===========================
CGameSceneObject::~CGameSceneObject()
{
	// 終了関数
	Uninit();
}
//===========================
// 初期化処理
//===========================
HRESULT CGameSceneObject::Init(void)
{
	// プレイヤー生成
	CPlayer::Create(D3DXVECTOR3(600.0f, 0.0f, 0.0f), VECTOR3_NULL, 10, "data/MOTION/Player/Player100motion.txt");

	// スコア生成
	// m_pScore = CScore::Create(D3DXVECTOR3(600.0f, 200.0f, 0.0f), 60.0f, 40.0f);

	// メッシュフィールド生成
	CMeshField::Create(VECTOR3_NULL,3200.0f,2000.0f,1,1);

	// 選択ポイント生成
	m_pSelectPoint = CSelectPoint::Create(VECTOR3_NULL, VECTOR3_NULL, 80.0f, 3.0f, 80.0f);

	// ブロックマネージャー生成
	m_pBlocks = std::make_unique<CBlockManager>();
	m_pBlocks->Init();

	// 餌を配置
	m_pFeed = new CFeedManager;
	m_pFeed->Init();

	return S_OK;
}
//===========================
// 終了処理
//===========================
void CGameSceneObject::Uninit(void)
{
	// null初期化
	m_pScore = nullptr;

	if (m_pFeed)
	{
		m_pFeed->Uninit();
		delete m_pFeed;
		m_pFeed = nullptr;
	}

	// 破棄
	m_pBlocks.reset();
}
//===========================
// 更新処理
//===========================
void CGameSceneObject::Update(void)
{
	// 無し
}
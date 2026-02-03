//=========================================================
//
// チュートリアルのオブジェクト管理 [ tutorialobject.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "tutorialobject.h"
#include "meshfield.h"
#include "meshdome.h"
#include "ui.h"
#include "block.h"
#include "blockmanager.h"
#include "queen.h"
#include "tutoarrayant.h"
#include "tutorialtopant.h"
#include "billboard.h"
#include "feed.h"
#include "eventarea.h"

//*********************************************************
// 静的メンバ変数宣言
//*********************************************************
CTutorialObject* CTutorialObject::m_pInstance = nullptr; // シングルトン変数

//=========================================================
// コンストラクタ
//=========================================================
CTutorialObject::CTutorialObject() :
m_pBlockManager(nullptr),
m_pTopAnt(nullptr),
m_pArrayAnt(nullptr),
m_pBlock(nullptr),
m_pFeed(nullptr),
m_pEventArea(nullptr)
{
	// 値のクリア
}
//=========================================================
// デストラクタ
//=========================================================
CTutorialObject::~CTutorialObject()
{

}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CTutorialObject::Init(void)
{
	// ステージマップ読み込み
	m_pBlockManager = std::make_unique<CBlockManager>();
	m_pBlockManager->Init();

	// メッシュフィールド生成
	CMeshField::Create(VECTOR3_NULL, 3200.0f, 2000.0f, 1, 1);

	// メッシュドーム生成
	CMeshDome::Create(D3DXVECTOR3(0.0f, -20.0f, 0.0f), 60.0f);

	// キャラクターの生成
	CQueen::Create(D3DXVECTOR3(0.0f, 30.0f, -5.0f), VECTOR3_NULL);

	// チュートリアルトップアリの生成
	m_pTopAnt = CTutoTopAnt::Create(D3DXVECTOR3(0.0f, 0.0f, -450.0f), VECTOR3_NULL);
	
	// 仲間の黒アリ生成
	m_pArrayAnt = CTutoArrayAnt::Create(D3DXVECTOR3(350.0f, 0.0f, 0.0f), VECTOR3_NULL);

	// 画面遷移用のブロックを生成
	m_pBlock = CBlock::Create(D3DXVECTOR3(880.0f, 0.0f, 500.0f), VECTOR3_NULL, INITSCALE, "STAGEOBJ/SpawnBase.x");

	// 餌を生成
	m_pFeed = CFeed::Create(D3DXVECTOR3(-500.0f, 0.0f, 0.0f), VECTOR3_NULL, INITSCALE, "FEED/Lemon.x", 80.0f, 1);

	// 判定範囲を生成
	m_pEventArea = CEventArea::Create(D3DXVECTOR3 (-450.0f, 0.0f, 0.0f));

	// 操作UIの生成
	CBillboard::Create(D3DXVECTOR3(880.0f, 200.0f, 450.0), VECTOR3_NULL, 180.0f, 80.0f, "Scenemenu.jpg");
	CUi::Create(D3DXVECTOR3(HALFWIDTH,80.0f,0.0f),0,240.0f,80.0f,"tutorial_logo.png");
	CUi::Create(D3DXVECTOR3(0.0f, 360.0f, 0.0f), 0, 280.0f, SCREEN_HEIGHT, "backboard.png");
	CUi::Create(D3DXVECTOR3(120.0f, 360.0f, 0.0f), 0, 110.0f, 300.0f, "manual.png");

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CTutorialObject::Uninit(void)
{
	// ポインタの破棄
	m_pBlockManager.reset();

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
void CTutorialObject::Update(void)
{

}
//=========================================================
// 描画処理
//=========================================================
void CTutorialObject::Draw(void)
{

}
//=========================================================
// インスタンス取得
//=========================================================
CTutorialObject* CTutorialObject::GetInstance(void)
{
	// nullなら
	if (m_pInstance == nullptr)
	{
		// インスタンス生成
		m_pInstance = new CTutorialObject;
	}

	// インスタンスを返す
	return m_pInstance;
}
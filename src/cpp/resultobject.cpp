//=========================================================
//
// リザルトのオブジェクト管理 [ resultobject.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "resultobject.h"
#include "ui.h"
#include "resultscore.h"
#include "meshfield.h"
#include "queen.h"
#include "meshdome.h"
#include "resultscoremanager.h"
#include "blockmanager.h"

//*********************************************************
// 静的メンバ変数宣言
//*********************************************************
CResultObject* CResultObject::m_pInstance = nullptr; // 1つのインスタンス

//=========================================================
// コンストラクタ
//=========================================================
CResultObject::CResultObject()
{
	// 値のクリア
}
//=========================================================
// デストラクタ
//=========================================================
CResultObject::~CResultObject()
{

}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CResultObject::Init(void)
{// 各種オブジェクト生成

	// ファイル読み込み
	m_pBlock = std::make_unique<CBlockManager>();
	m_pBlock->Init();

	// 女王生成
	CQueen::Create(D3DXVECTOR3(0.0f, 30.0f, -5.0f), VECTOR3_NULL);

	// メッシュドーム生成
	CMeshDome::Create(D3DXVECTOR3(0.0f, -20.0f, 0.0f), 60.0f);

	// UI生成
	CUi::Create(D3DXVECTOR3(1040.0f, 360.0f, 0.0f), 0, 360.0f, 720.0f, "backboard.png");
	CUi::Create(D3DXVECTOR3(840.0f, 50.0f, 0.0f), 0, 160.0f, 40.0f, "result_logo.png");
	CUi::Create(D3DXVECTOR3(800.0f, 245.0f, 0.0f),0,120.0f, 30.0f, "result_feed.png");
	CUi::Create(D3DXVECTOR3(790.0f, 425.0f, 0.0f),0,100.0f, 30.0f, "Defence_Late.png");
	CUi::Create(D3DXVECTOR3(815.0f, 645.0f, 0.0f),0,130.0f, 35.0f, "Total_Logo.png");
	CUi::Create(D3DXVECTOR3(1045.0f, 280.0f, 0.0f), 0, 360.0f, 5.0f, "underbar.png");
	CUi::Create(D3DXVECTOR3(1045.0f, 455.0f, 0.0f), 0, 360.0f, 5.0f, "underbar.png");
	CUi::Create(D3DXVECTOR3(1045.0f, 690.0f, 0.0f), 0, 360.0f, 5.0f, "underbar.png");

	// メッシュフィールド生成
	CMeshField::Create(VECTOR3_NULL, 3200.0f, 2000.0f, 1, 1);

	// リザルト表示スコア
	m_pResultScoreManager = std::make_unique<CResultScoreManager>();
	m_pResultScoreManager->Init();

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CResultObject::Uninit(void)
{
	// 管理クラスの破棄
	m_pResultScoreManager.reset();

	// ステージマップの破棄
	m_pBlock.reset();

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
void CResultObject::Update(void)
{
	
}
//=========================================================
// 描画処理
//=========================================================
void CResultObject::Draw(void)
{

}
//=========================================================
// インスタンス取得処理
//=========================================================
CResultObject* CResultObject::GetInstance(void)
{
	// nullなら生成
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CResultObject;
	}

	// インスタンスを返す
	return m_pInstance;
}
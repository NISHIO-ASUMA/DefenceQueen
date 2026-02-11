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
#include "manager.h"
#include "jsonmanager.h"

//*********************************************************
// 静的メンバ変数宣言
//*********************************************************
CResultObject* CResultObject::m_pInstance = nullptr; // シングルトン変数

//=========================================================
// コンストラクタ
//=========================================================
CResultObject::CResultObject()
{
	
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
{
	// マップ読み込み
	m_pBlock = std::make_unique<CBlockManager>();
	m_pBlock->Init();

	auto jsonmanager = CManager::GetInstance()->GetJsonManager();
	jsonmanager->Load("data/JSON/Resultobject.json");

	// 女王生成
	CQueen::Create(D3DXVECTOR3(0.0f, 30.0f, -5.0f), VECTOR3_NULL);

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
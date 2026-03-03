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

//*********************************************************
// 定数宣言空間
//*********************************************************
namespace RESULTOBJECT
{
	constexpr const char* LoadName = "data/JSON/Resultobject.json"; // 読み込むjsonファイル
};

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
	auto jsonManager = CManager::GetInstance()->GetJsonManager();
	jsonManager->SetBlockManager(m_pBlock.get());
	m_pBlock->Init();
	m_pBlock->Load();

	// リザルトシーンオブジェクトの読み込み
	auto jsonmanager = CManager::GetInstance()->GetJsonManager();
	jsonmanager->Load(RESULTOBJECT::LoadName);

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
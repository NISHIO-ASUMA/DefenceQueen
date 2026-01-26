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
#include "blockmanager.h"
#include "queen.h"

//*********************************************************
// 静的メンバ変数宣言
//*********************************************************
CTutorialObject* CTutorialObject::m_pInstance = nullptr; // クラスインスタンス

//=========================================================
// コンストラクタ
//=========================================================
CTutorialObject::CTutorialObject() : m_pBlockManager(nullptr)
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
	// マップ読み込み
	m_pBlockManager = std::make_unique<CBlockManager>();
	m_pBlockManager->Init();

	// メッシュフィールド生成
	CMeshField::Create(VECTOR3_NULL, 3200.0f, 2000.0f, 1, 1);

	// メッシュドーム生成
	CMeshDome::Create(D3DXVECTOR3(0.0f, -20.0f, 0.0f), 60.0f);

	// キャラクターの生成
	CQueen::Create(D3DXVECTOR3(0.0f, 30.0f, -5.0f), VECTOR3_NULL);
	
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
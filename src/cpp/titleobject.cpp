//=========================================================
//
// タイトルで出現するオブジェクト処理 [ titleobject.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "titleobject.h"
#include "ui.h"
#include "meshfield.h"
#include "titleant.h"
#include "titlewallmanager.h"
#include "titleantmanager.h"

//*********************************************************
// 静的メンバ変数宣言
//*********************************************************
CTitleObject* CTitleObject::m_pInstance = nullptr; // ただ一つのインスタンス

//=========================================================
// コンストラクタ
//=========================================================
CTitleObject::CTitleObject() : m_pWallManager(nullptr)
{
	// 値のクリア
}
//=========================================================
// デストラクタ
//=========================================================
CTitleObject::~CTitleObject()
{
	
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CTitleObject::Init(void)
{
	// 壁生成
	m_pWallManager = std::make_unique<CTitleWallManager>();
	m_pWallManager->Init();

	// アリ生成
	m_pTitleAntManager = std::make_unique<CTitleAntManager>();
	m_pTitleAntManager->Init();

	// メッシュフィールド生成
	CMeshField::Create(VECTOR3_NULL, 4000.0f, 2000.0f, 1, 1);

	// 初期UI生成
	CUi::Create(D3DXVECTOR3(HALFWIDTH, 650.0f, 0.0f), 30, 180.0f, 60.0f, "GameStart.png", true);
	CUi::Create(D3DXVECTOR3(HALFWIDTH, 180.0f, 0.0f), 0, 300.0f, 150.0f, "TitleLogo.png", false,false,0,true);

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CTitleObject::Uninit(void)
{
	// タイトルの壁の破棄
	m_pWallManager.reset();

	// タイトルのアリたちの破棄
	m_pTitleAntManager.reset();

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
void CTitleObject::Update(void)
{
	// タイトルのアリ管理クラスの更新
	if (m_pTitleAntManager) m_pTitleAntManager->Update();
}
//=========================================================
// シングルトン取得処理
//=========================================================
CTitleObject* CTitleObject::GetInstance(void)
{
	// nullなら
	if (m_pInstance == nullptr)
	{
		// インスタンス生成
		m_pInstance = new CTitleObject;
	}

	// シングルトンを返す
	return m_pInstance;
}
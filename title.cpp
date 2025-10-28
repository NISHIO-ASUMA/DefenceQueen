//====================================
//
// タイトル処理 [ title.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// インクルードファイル宣言
//****************************
#include "title.h"
#include "manager.h"
#include "game.h"
#include "ui.h"
#include "titlemanager.h"
#include "input.h"

//=====================================
// コンストラクタ
//=====================================
CTitle::CTitle() : CScene(CScene::MODE_TITLE)
{
	// 値のクリア
	m_pTitleManager = nullptr;
}
//=====================================
// デストラクタ
//=====================================
CTitle::~CTitle()
{
	// 無し
}
//=====================================
// 初期化処理
//=====================================
HRESULT CTitle::Init(void)
{
	// インスタンス生成
	m_pTitleManager = std::make_unique<CTitleManager>();
	if (m_pTitleManager == nullptr) return E_FAIL;

	// マネージャーの初期化処理
	m_pTitleManager->Init();

	// 初期化結果を返す
	return S_OK;
}
//=====================================
// 終了処理
//=====================================
void CTitle::Uninit(void)
{
	// 破棄
	m_pTitleManager.reset();
}
//=====================================
// 更新処理
//=====================================
void CTitle::Update(void)
{
	// nullじゃなかったら
	if (m_pTitleManager != nullptr)
	{
		// マネージャーの更新処理
		m_pTitleManager->Update();
	}
}
//=====================================
// 描画処理
//=====================================
void CTitle::Draw(void)
{
	// 無し
}

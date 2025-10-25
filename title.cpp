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
	//無し
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
	m_pTitleManager = new CTitleManager();

	// 生成失敗時
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
	// nullチェック
	if (m_pTitleManager != nullptr)
	{
		// 終了処理
		m_pTitleManager->Uninit();

		// 破棄
		delete m_pTitleManager;

		// nullptrする
		m_pTitleManager = nullptr;
	}
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

	CJoyPad* pJoyPad = CManager::GetInstance()->GetJoyPad();

	// コントローラー取得
	if (CManager::GetInstance()->GetJoyPad()->GetTrigger(pJoyPad->JOYKEY_BACK))
	{
		PostQuitMessage(0);
		return;
	}
}
//=====================================
// 描画処理
//=====================================
void CTitle::Draw(void)
{
	// 無し
}

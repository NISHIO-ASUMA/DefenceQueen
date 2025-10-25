//=================================================
//
// チュートリアル管理処理 [ tutorialmanager.cpp ]
// Author: Asuma Nishio
//
//=================================================

//**********************
// インクルードファイル
//**********************
#include "tutorialmanager.h"
#include "tutorialui.h"
#include "manager.h"
#include "fade.h"
#include "game.h"
#include "ui.h"

//==========================
// コンストラクタ
//==========================
CTutorialManager::CTutorialManager()
{
	// 値のクリア
	m_pTutoui = nullptr;
	m_isFreeDone = false;
	m_isCreate = false;
	m_Tasktype = TASKTYPE_MOVE;
}
//==========================
// デストラクタ
//==========================
CTutorialManager::~CTutorialManager()
{
	// 無し
}
//==========================
// 初期化処理
//==========================
HRESULT CTutorialManager::Init(void)
{
	// 初期化
	m_isCreate = false;

	// ui生成
	CUi::Create(D3DXVECTOR3(65.0f, 200.0f, 0.0f), 0, 60.0f, 30.0f, "bullet.png", false);

	// 初期化結果を返す
	return S_OK;
}
//==========================
// 終了処理
//==========================
void CTutorialManager::Uninit(void)
{
	// 破棄
}
//==========================
// 更新処理
//==========================
void CTutorialManager::Update(void)
{
	// 入力デバイス取得
	CInputKeyboard* pKey = CManager::GetInstance()->GetInputKeyboard();
	CJoyPad* pJoyPad = CManager::GetInstance()->GetJoyPad();

	// 取得失敗時
	if (pKey == nullptr) return;
	if (pJoyPad == nullptr) return;
}
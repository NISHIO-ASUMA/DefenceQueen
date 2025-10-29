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
CTutorialManager::CTutorialManager() : m_pTutoui(nullptr)
{
	// 値のクリア
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

}
//==========================
// 描画処理
//==========================
void CTutorialManager::Draw(void)
{

}
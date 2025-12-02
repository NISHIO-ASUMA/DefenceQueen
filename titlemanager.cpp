//=========================================================
//
// タイトル管理処理 [ titlemanager.cpp ]
// Author: Asuma Nishio
// 
//=========================================================

//*********************************************************
// インクルードファイル宣言
//*********************************************************
#include "titlemanager.h"
#include "titleui.h"
#include "manager.h"
#include "game.h"
#include "tutorial.h"
#include "input.h"
#include "ui.h"
#include "sound.h"
#include "fade.h"

//=========================================================
// コンストラクタ
//=========================================================
CTitleManager::CTitleManager() : 
m_pUi(nullptr),
m_nIdx(NULL)
{
	// 値のクリア
}
//=========================================================
// デストラクタ
//=========================================================
CTitleManager::~CTitleManager()
{
	// 破棄
}
//==========================================================
//インスタンス取得
//==========================================================
CTitleManager* CTitleManager::GetInstance(void)
{
	// インスタンスを返す
	static CTitleManager pTitleManager;
	return &pTitleManager;
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CTitleManager::Init(void)
{	
	// 背景
	CUi::Create(D3DXVECTOR3(HALFWIDTH, HALFHEIGHT, 0.0f), 0, HALFWIDTH, HALFHEIGHT, "ground.jpg", false);

	// 初期UI生成
	m_pUi = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 650.0f, 0.0f),30, 250.0f, 60.0f, "exit.png", false);

	// サウンド取得
	CSound* pSound = CManager::GetInstance()->GetSound();
	if (pSound == nullptr) return E_FAIL;

	// サウンド再生
	//	pSound->Play(CSound::SOUND_LABEL_TITLE_BGM);

	// 初期化結果を返す
	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CTitleManager::Uninit(void)
{
	// 無し
}
//=========================================================
// 更新処理
//=========================================================
void CTitleManager::Update(void)
{
	// 入力デバイス取得
	CInputKeyboard* pKey = CManager::GetInstance()->GetInputKeyboard();
	CJoyPad* pJoyPad = CManager::GetInstance()->GetJoyPad();

	// 取得失敗時
	if (pKey == nullptr) return;
	if (pJoyPad == nullptr) return;

	// フェード取得
	CFade* pFade = CManager::GetInstance()->GetFade();
	if (pFade == nullptr) return;

	// キー入力時 かつ uiが生成されていなかったら
	if ((pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_START)))
	{
		pFade->SetFade(std::make_unique<CGame>());	// ゲームシーンに遷移
		return;
	}
}
//==========================================================
// 描画処理
//==========================================================
void CTitleManager::Draw(void)
{

}
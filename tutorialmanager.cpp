//=========================================================
//
// チュートリアル管理処理 [ tutorialmanager.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//********************************************************
// インクルードファイル
//********************************************************
#include "tutorialmanager.h"
#include "tutorialui.h"
#include "manager.h"
#include "fade.h"
#include "game.h"
#include "ui.h"
#include "meshfield.h"
#include "meshdome.h"
#include "sound.h"
#include "input.h"
#include "game.h"

//=========================================================
// インスタンス取得
//=========================================================
CTutorialManager* CTutorialManager::GetInstance(void)
{
	// 生成されたインスタンス
	static CTutorialManager pTutoManager;
	return &pTutoManager;
}
//=========================================================
// コンストラクタ
//=========================================================
CTutorialManager::CTutorialManager()
{
	// 値のクリア
}
//=========================================================
// デストラクタ
//=========================================================
CTutorialManager::~CTutorialManager()
{
	// 無し
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CTutorialManager::Init(void)
{

	// 初期化結果を返す
	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CTutorialManager::Uninit(void)
{
	// 破棄
}
//=========================================================
// 更新処理
//=========================================================
void CTutorialManager::Update(void)
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

	// キー入力時の遷移
	if ((pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_START)))
	{
		// サウンド取得
		CSound* pSound = CManager::GetInstance()->GetSound();
		if (pSound == nullptr) return;

		// チュートリアルシーンに遷移
		pFade->SetFade(std::make_unique<CGame>());

		// サウンド再生
		pSound->Play(CSound::SOUND_LABEL_TITLEENTER);
		return;
	}
}
//=========================================================
// 描画処理
//=========================================================
void CTutorialManager::Draw(void)
{

}
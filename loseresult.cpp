//=========================================================
//
// 負けリザルトシーン処理 [ loseresult.cpp ]
// Author: Asuma Nishio
// 
//=========================================================

//*********************************************************
// インクルードファイル宣言
//*********************************************************
#include "loseresult.h"
#include "manager.h"
#include "ui.h"
#include "title.h"
#include "sound.h"
#include "fade.h"
#include "input.h"
#include <memory>

//=========================================================
// コンストラクタ
//=========================================================
CLoseResult::CLoseResult() : CScene(CScene::MODE_LOSERESULT)
{
	// 値のクリア
}
//=========================================================
// デストラクタ
//=========================================================
CLoseResult::~CLoseResult()
{
	// 無し
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CLoseResult::Init(void)
{
	// UI生成
	CUi::Create(CENTERPOS, 0, HALFWIDTH, HALFHEIGHT, "grass000.png",false);

	// サウンド取得
	CSound* pSound = CManager::GetInstance()->GetSound();
	if (pSound == nullptr) return E_FAIL;

	// サウンド再生
// 	pSound->Play(CSound::SOUND_LABEL_LOSERESULTBGM);

	// 初期化結果を返す
	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CLoseResult::Uninit(void)
{
	// 無し
}
//=========================================================
// 更新処理
//=========================================================
void CLoseResult::Update(void)
{
	// キー入力でタイトルに戻る
	if ((CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetInstance()->GetJoyPad()->GetTrigger(CManager::GetInstance()->GetJoyPad()->JOYKEY_START)))
	{
		// ポインタ取得
		CFade* pFade = CManager::GetInstance()->GetFade();

		// nullじゃないとき
		if (pFade != nullptr)
		{
			// シーン遷移
			pFade->SetFade(std::make_unique<CTitle>());
			return;
		}
	}
}
//=========================================================
// 描画処理
//=========================================================
void CLoseResult::Draw(void)
{
	// 無し
}
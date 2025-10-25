//==========================================
//
// タイトル管理処理 [ titlemanager.cpp ]
// Author: Asuma Nishio
// 
//==========================================

//***************************
// インクルードファイル宣言
//***************************
#include "titlemanager.h"
#include "titleui.h"
#include "manager.h"
#include "game.h"
#include "tutorial.h"
#include "input.h"
#include "ui.h"
#include "sound.h"
#include "fade.h"
#include <memory>

//*************************
// 名前空間
//*************************
namespace TITLEMANAGERINFO
{
	const D3DXVECTOR3 BacePos = { 210.0f, 520.0f, 0.0f };	// 基準座標
	constexpr int FLASHCOUNT = 10;	// 点滅間隔
};

//============================
// コンストラクタ
//============================
CTitleManager::CTitleManager(bool isCreate) : m_isFirstuiCreate(isCreate)
{
	// 値のクリア
	m_nIdx = NULL;
	m_Info = {};

	for (int nCnt = 0; nCnt < TITLEINFO::TITLE_MENU; nCnt++)
	{
		m_pTitleui[nCnt] = nullptr;
	}
	m_pUi = nullptr;
	m_isuiCreate = false;
}
//============================
// デストラクタ
//============================
CTitleManager::~CTitleManager()
{
	// 無し
}
//============================
// 初期化処理
//============================
HRESULT CTitleManager::Init(void)
{	
	// 他のシーン等から戻ってきたとき
	if (!m_isFirstuiCreate) 
	{
		// タイトルのuiを生成
		for (int nCnt = 0; nCnt < m_Info.TITLE_MENU; nCnt++)
		{
			// 横の間隔を空ける
			D3DXVECTOR3 pos = TITLEMANAGERINFO::BacePos;

			pos.x += nCnt * m_Info.INTERVAL;

			// uiを生成
			m_pTitleui[nCnt] = CTitleUi::Create(pos, COLOR_WHITE, m_Info.UIWIDTH, m_Info.UIHEIGHT, nCnt);
		}

		// フラグを有効化
		m_isuiCreate = true;
	}

	// 初期UI生成
	m_pUi = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 650.0f, 0.0f),30, 250.0f, 60.0f, "Enterkey.png", true);

	// サウンド取得
	CSound* pSound = CManager::GetInstance()->GetSound();

	// nullだったら
	if (pSound == nullptr) return E_FAIL;

	// サウンド再生
	//	pSound->Play(CSound::SOUND_LABEL_TITLE_BGM);

	// 初期化結果を返す
	return S_OK;
}
//============================
// 終了処理
//============================
void CTitleManager::Uninit(void)
{
	// 無し
}
//============================
// 更新処理
//============================
void CTitleManager::Update(void)
{
	// 入力デバイス取得
	CInputKeyboard* pKey = CManager::GetInstance()->GetInputKeyboard();
	CJoyPad* pJoyPad = CManager::GetInstance()->GetJoyPad();

	// 取得失敗時
	if (pKey == nullptr) return;
	if (pJoyPad == nullptr) return;

	// サウンド取得
	CSound* pSound = CManager::GetInstance()->GetSound();
	if (pSound == nullptr) return;

	// フェード取得
	CFade* pFade = CManager::GetInstance()->GetFade();
	if (pFade == nullptr) return;

	// カメラ取得
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	if (pCamera == nullptr) return;

	// キー入力時 かつ uiが生成されていなかったら
	if ((pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_START)))
	{
		pFade->SetFade(std::make_unique<CGame>());	// ゲームシーンに遷移

		return;
	}
}
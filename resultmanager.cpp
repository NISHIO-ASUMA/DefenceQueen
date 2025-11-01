//==============================================
//
// リザルトシーン管理処理 [ resultmanager.cpp ]
// Author: Asuma Nishio
// 
//==============================================

//**************************
// インクルードファイル宣言
//**************************
#include "resultmanager.h"
#include "manager.h"
#include "sound.h"
#include "input.h"
#include "title.h"
#include "ranking.h"
#include "fade.h"
#include <fstream>

//=================================
// コンストラクタ
//=================================
CResultManager::CResultManager() : m_nGameScore(NULL)
{
	// 値のクリア
}
//=================================
// デストラクタ
//=================================
CResultManager::~CResultManager()
{
	// 無し
}
//=================================
// インスタンス取得
//=================================
CResultManager* CResultManager::GetInstance(void)
{
	static CResultManager pResultManager;
	return &pResultManager;
}
//=================================
// 初期化処理
//=================================
HRESULT CResultManager::Init(void)
{	
	// データの読み込み
	Load();

	// サウンド取得
	CSound* pSound = CManager::GetInstance()->GetSound();
	if (pSound == nullptr) return E_FAIL;

	// サウンド再生
	pSound->Play(CSound::SOUND_LABEL_RESULTBGM);

	// 初期化結果を返す
	return S_OK;
}
//=================================
// 終了処理
//=================================
void CResultManager::Uninit(void)
{
	// nullチェック
}
//=================================
// 更新処理
//=================================
void CResultManager::Update(void)
{
	// 入力デバイスを取得
	CInputKeyboard* pInput = CManager::GetInstance()->GetInputKeyboard();
	CJoyPad* pJyoPad = CManager::GetInstance()->GetJoyPad();

	// 取得失敗時
	if (pInput == nullptr) return;
	if (pJyoPad == nullptr) return;

	// 決定キーが押された
	if ((pInput->GetTrigger(DIK_RETURN) || pJyoPad->GetTrigger(pJyoPad->JOYKEY_A)))
	{
		// ポインタ取得
		CFade* pFade = CManager::GetInstance()->GetFade();

		// nullじゃないとき
		if (pFade != nullptr)
		{
			// シーン遷移
			pFade->SetFade(std::make_unique <CRanking>());

			return;
		}
	}
}
//=================================
// 描画処理
//=================================
void CResultManager::Draw(void)
{

}
//=================================
// 読み込み処理
//=================================
void CResultManager::Load(void)
{
	// 読み取った値を格納するメンバ変数
	m_nGameScore = NULL;
}
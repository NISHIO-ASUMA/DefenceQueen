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
#include "ui.h"
#include "ranking.h"
#include "fade.h"
#include <fstream>

//**************************
// 定数宣言
//**************************
namespace RESULTINFO
{
	constexpr int BOSS_SCOREIDX = 0; // ボススコアのインデックス
	constexpr int TIME_SCOREIDX = 1; // タイムスコアのインデックス
	constexpr int LAST_SCOREIDX = 2; // 最終スコアのインデックス
};

//=================================
// コンストラクタ
//=================================
CResultManager::CResultManager()
{
	// 値のクリア
	m_isKeyDown = false;
	m_nGameScore = NULL;
	m_nLastTime = NULL;

	for (int nCnt = 0; nCnt < SCORELISTNUM; nCnt++)
	{
		m_pResultScore[nCnt] = nullptr;
	}
}
//=================================
// デストラクタ
//=================================
CResultManager::~CResultManager()
{
	// 無し
}
//=================================
// 初期化処理
//=================================
HRESULT CResultManager::Init(void)
{	
	// UI生成
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), 0, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, "resultback.jpg", false);

	// データの読み込み
	// Load();

	// サウンド取得
	CSound* pSound = CManager::GetInstance()->GetSound();

	// nullだったら
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

	// カメラを取得
	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	// 取得失敗時
	if (pCamera == nullptr) return;

	// 決定キーが押された
	if ((pInput->GetTrigger(DIK_RETURN) || pJyoPad->GetTrigger(pJyoPad->JOYKEY_A)))
	{
		// ポインタ取得
		CFade* pFade = CManager::GetInstance()->GetFade();

		// nullじゃないとき
		if (pFade != nullptr)
		{
			// フラグ有効化
			m_isKeyDown = true;

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
	m_nLastTime = NULL;
}
//=================================
// インスタンス取得
//=================================
CResultManager* CResultManager::GetInstance(void)
{
	static CResultManager pResultManager;
	return &pResultManager;
}
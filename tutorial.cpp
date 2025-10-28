//=====================================
//
// チュートリアル処理 [ tutorial.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "tutorial.h"
#include "tutorialmanager.h"
#include "manager.h"
#include "sound.h"
#include "game.h"
#include "input.h"
#include "fade.h"
#include <memory>

//===============================
// オーバーロードコンストラクタ
//===============================
CTutorial::CTutorial() : CScene(CScene::MODE_TUTORIAL), m_pTutoManager(nullptr)
{
	// 値のクリア
}
//===============================
// デストラクタ
//===============================
CTutorial::~CTutorial()
{
	// 無し
}
//===============================
// 初期化処理
//===============================
HRESULT CTutorial::Init(void)
{
	// マネージャーのインスタンス生成
	m_pTutoManager = std::make_unique<CTutorialManager>();
	if (m_pTutoManager != nullptr) m_pTutoManager->Init();

	// サウンド取得
	CSound* pSound = CManager::GetInstance()->GetSound();
	if (pSound == nullptr) return E_FAIL;

	// サウンド再生
	pSound->Play(CSound::SOUND_LABEL_TUTORIALBGM);

	// 初期化結果を返す
	return S_OK;
}
//===============================
// 終了処理
//===============================
void CTutorial::Uninit(void)
{
	// 破棄
	m_pTutoManager.reset();
}
//===============================
// 更新処理
//===============================
void CTutorial::Update(void)
{
	// ポインタが存在するなら
	if (m_pTutoManager != nullptr)
	{
		// マネージャーの更新処理
		m_pTutoManager->Update();
	}

	// キー入力で遷移
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::GetInstance()->GetFade()->SetFade(std::make_unique <CGame>());
	}
}
//===============================
// 描画処理
//===============================
void CTutorial::Draw(void)
{
	// 無し
}
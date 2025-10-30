//=====================================
//
// メインゲーム処理 [ game.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// インクルードファイル宣言
//****************************
#include "game.h"
#include "manager.h"
#include "debugproc.h"
#include "gamemanager.h"
#include "gamesceneobject.h"
#include "gamestate.h"
#include "input.h"

//**************************
// 静的メンバ変数宣言
//**************************
CPauseManager* CGame::m_pPausemanager = nullptr; // ポーズマネージャーのポインタ

//==================================
// コンストラクタ
//==================================
CGame::CGame() : CScene(CScene::MODE_GAME), m_pGameManager(nullptr)
{
	// 値のクリア
}
//==================================
// デストラクタ
//==================================
CGame::~CGame()
{
	// 無し
}
//==================================
// 初期化処理
//==================================
HRESULT CGame::Init(void)
{
	// ポーズマネージャー生成
	m_pPausemanager = new CPauseManager;
	if (m_pPausemanager == nullptr) return E_FAIL;

	// ポーズマネージャー初期化処理
	m_pPausemanager->Init();

	// ゲームマネージャー
	CGameManager::GetInstance()->Init();

	// ゲームオブジェクト生成
	m_pGameObject = std::make_unique<CGameSceneObject>();
	if (m_pGameObject == nullptr) return E_FAIL;

	// ゲームオブジェクト初期化処理
	m_pGameObject->Init();

	// ステート生成
	m_pState = new CGameState;
	if (m_pState == nullptr) return E_FAIL;

	// 開始
	m_pState->SetGame(this);
	m_pState->OnStart();

	// 初期化結果を返す
	return S_OK;
}
//==================================
// 終了処理
//==================================
void CGame::Uninit(void)
{
	CGameManager::GetInstance()->Uninit();

	// nullチェック
	if (m_pPausemanager != nullptr)
	{
		// 終了処理
		m_pPausemanager->Uninit();

		// ポインタの破棄
		delete m_pPausemanager;

		// nullptrにする
		m_pPausemanager = nullptr;
	}

	// 破棄
	// m_pGameManager.reset();

	// 破棄
	m_pGameObject.reset();

	// nullチェック
	if (m_pState)
	{
		// 終了処理
		m_pState->OnExit();

		// ポインタ破棄
		delete m_pState;

		// null初期化
		m_pState = nullptr;
	}
}
//==================================
// 更新処理
//==================================
void CGame::Update(void)
{	
	// ゲーム進行管理の更新処理
	m_pState->OnUpdate();

	// 状態取得
	auto State = m_pState->GetProgress();
	if (State == m_pState->PROGRESS_END) return;

	// ポーズのキー入力判定
	m_pPausemanager->SetEnablePause();
	
	// ポーズの更新処理
	m_pPausemanager->Update();
	
	// falseの時に更新
	if (!m_pPausemanager->GetPause())
	{
		// ゲームマネージャー更新
		CGameManager::GetInstance()->Update();

		// ゲームオブジェクト更新
		m_pGameObject->Update();
	}

#ifdef _DEBUG

	// 検証
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_0))
	{
		// 状態変更
		m_pState->SetProgress(CGameState::PROGRESS_END);
	}

#endif // _DEBUG

}
//==================================
// 描画処理
//==================================
void CGame::Draw(void)
{
	// 無し
}
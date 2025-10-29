//=============================================================================
//
// 各シーンごとに使うManagerクラスを一括管理する処理 [ scenemanagement.cpp ]
// Author: Asuma Nishio
//
//=============================================================================

//**********************
// インクルードファイル
//**********************
#include "scenemanagement.h"
#include "scenemanagebase.h"
#include "gamemanager.h"
#include "titlemanager.h"
#include "resultmanager.h"
#include "tutorialmanager.h"
#include "rankingmanager.h"

//==================================
// コンストラクタ
//==================================
CSceneManagement::CSceneManagement() : m_pCurrentManager(nullptr),m_CurrentScene(TYPE_TITLE)
{
	// 値のクリア
}
//==================================
// デストラクタ
//==================================
CSceneManagement::~CSceneManagement()
{
	// 終了処理
	Uninit();
}
//==================================
// 初期化処理
//==================================
HRESULT CSceneManagement::Init(void)
{
	return S_OK;
}
//==================================
// 終了処理
//==================================
void CSceneManagement::Uninit(void)
{
	if (m_pCurrentManager)
	{
		m_pCurrentManager->Uninit();
		m_pCurrentManager.reset();
	}
}
//==================================
// 更新処理
//==================================
void CSceneManagement::Update(void)
{
	// 現在のシーンに応じた更新
	if (m_pCurrentManager)
		m_pCurrentManager->Update();
}
//==================================
// 描画処理
//==================================
void CSceneManagement::Draw(void)
{
	// 描画
	if (m_pCurrentManager)
		m_pCurrentManager->Draw();
}
//==================================
// 各シーンに切り替え処理
//==================================
void CSceneManagement::ChangeScene(TYPE NewType)
{
	// 各シーンの終了処理
	if (m_pCurrentManager)
	{
		m_pCurrentManager->Uninit();
		m_pCurrentManager.reset();
	}

	switch (NewType)
	{
	case TYPE_TITLE:
		m_pCurrentManager = std::make_unique<CTitleManager>();
		break;

	case TYPE_TUTORIAL:
		m_pCurrentManager = std::make_unique<CTutorialManager>();
		break;

	case TYPE_GAME:
		m_pCurrentManager = std::make_unique<CGameManager>();
		break;

	case TYPE_RESULT:
		m_pCurrentManager = std::make_unique<CResultManager>();
		break;

	case TYPE_RANKING:
		m_pCurrentManager = std::make_unique<CRankingManager>();
		break;
	}

	// 新しいマネージャーを初期化
	if (m_pCurrentManager)
	{
		m_pCurrentManager->Init();
		m_CurrentScene = NewType;
	}
}
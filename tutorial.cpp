//=========================================================
//
// チュートリアル処理 [ tutorial.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "tutorial.h"
#include "tutorialmanager.h"
#include "manager.h"
#include "sound.h"
#include "game.h"
#include "input.h"
#include "fade.h"
#include "camera.h"
#include <memory>
#include "tutorialobject.h"

//=========================================================
// オーバーロードコンストラクタ
//=========================================================
CTutorial::CTutorial() : CScene(CScene::MODE_TUTORIAL)
{
	// 値のクリア
}
//=========================================================
// デストラクタ
//=========================================================
CTutorial::~CTutorial()
{
	// 無し
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CTutorial::Init(void)
{	
	// カメラ初期化
	auto Camera = CManager::GetInstance()->GetCamera();
	Camera->Init();

	// マネージャー初期化
	CTutorialManager::GetInstance()->Init();

	// オブジェクト初期化
	CTutorialObject::GetInstance()->Init();

	// サウンド取得
	CSound* pSound = CManager::GetInstance()->GetSound();
	if (pSound == nullptr) return E_FAIL;

	// サウンド再生
	pSound->Play(CSound::SOUND_LABEL_TUTORIALBGM);

	// 初期化結果を返す
	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CTutorial::Uninit(void)
{
	// マネージャー終了
	CTutorialManager::GetInstance()->Uninit();

	// オブジェクト終了
	CTutorialObject::GetInstance()->Uninit();
}
//=========================================================
// 更新処理
//=========================================================
void CTutorial::Update(void)
{
	// マネージャー更新
	CTutorialManager::GetInstance()->Update();

	// キー入力で遷移
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		// ゲーム開始
		CManager::GetInstance()->GetFade()->SetFade(std::make_unique<CGame>());
	}
}
//=========================================================
// 描画処理
//=========================================================
void CTutorial::Draw(void)
{
	// 無し
}
//=========================================================
//
// ゲーム管理処理 [ gamemanager.cpp ]
// Author: Asuma Nishio
// 
//=========================================================

//*********************************************************
// インクルードファイル宣言
//*********************************************************
#include "gamemanager.h"
#include "manager.h"
#include "debugproc.h"
#include "result.h"
#include "sound.h"
#include "game.h"
#include "input.h"
#include "fade.h"
#include "blockmanager.h"
#include "gamesceneobject.h"

//=========================================================
// インスタンス取得
//=========================================================
CGameManager* CGameManager::GetInstance(void)
{
	static CGameManager pInstance;
	return &pInstance;
}
//=========================================================
// コンストラクタ
//=========================================================
CGameManager::CGameManager()
{
	// 値のクリア
}
//=========================================================
// デストラクタ
//=========================================================
CGameManager::~CGameManager()
{
	// 終了処理
	Uninit();
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CGameManager::Init(void)
{
	// サウンド取得
	CSound* pSound = CManager::GetInstance()->GetSound();
	if (pSound == nullptr) return E_FAIL;

	// 初期化結果を返す
	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CGameManager::Uninit(void)
{

}
//=========================================================
// 更新処理
//=========================================================
void CGameManager::Update(void)
{
#ifdef _DEBUG
	// 画面遷移
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_2))
	{
		// 遷移更新
		CManager::GetInstance()->GetFade()->SetFade(std::make_unique<CResult>());

		return;
	}
#endif
}
//=========================================================
// 描画処理
//=========================================================
void CGameManager::Draw(void)
{

}
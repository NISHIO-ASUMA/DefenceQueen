//==========================================================
//
// メインゲーム処理 [ game.h ]
// Author: Asuma Nishio
//
//==========================================================

//*********************************************************
// インクルードガード
//*********************************************************
#pragma once

//*********************************************************
// インクルードファイル
//*********************************************************
#include "scene.h"
#include "pausemanager.h"
#include <memory>

//*********************************************************
// 前方宣言
//*********************************************************
class CGameManager;
class CGameState;

//*********************************************************
// ゲームシーンクラスを定義
//*********************************************************
class CGame : public CScene
{
public:

	CGame();
	~CGame();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	inline CGameState* GetState(void) { return m_pState; }

	static CPauseManager* GetPause(void) { return m_pPausemanager; }

private:
	static CPauseManager* m_pPausemanager;			// ポーズマネージャークラスポインタ
	CGameState * m_pState;							// ゲーム進行管理クラスのポインタ
};
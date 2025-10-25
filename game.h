//====================================
//
// メインゲーム処理 [ game.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードガード
//**********************
#pragma once

//****************************
// インクルードファイル宣言
//****************************
#include "scene.h"
#include "pausemanager.h"
#include <memory>

//****************************
// 前方宣言
//****************************
class CGameManager;
class CGameSceneObject;
class CGameState;

//****************************
// ゲームシーンクラスを定義
//****************************
class CGame : public CScene
{
public:
	//***********************
	// ゲーム状態列挙型
	//***********************
	enum GAMESTATE
	{
		GAMESTATE_NONE,
		GAMESTATE_NORMAL,
		GAMESTATE_END,
		GAMESTATE_LOSEEND,
		GAMESTATE_MAX
	};

	CGame();
	~CGame();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CGameManager* GetGameManager(void) { return m_pGameManager.get(); }
	CGameSceneObject* GetGameObject(void) { return m_pGameObject.get(); }
	CGameState* GetState(void) { return m_pState; }

	static CPauseManager* GetPause(void) { return m_pPausemanager; }

private:
	static CPauseManager* m_pPausemanager;			// ポーズマネージャークラスポインタ
	CGameState * m_pState;							// ゲーム進行管理クラスのポインタ
	std::unique_ptr<CGameManager>m_pGameManager;	// ゲームマネージャークラスのポインタ
	std::unique_ptr<CGameSceneObject>m_pGameObject;	// ゲーム中のオブジェクトクラスのポインタ

};
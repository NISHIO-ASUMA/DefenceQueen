//==========================================
//
// ゲーム進行管理処理 [ gamemanager.h ]
// Author: Asuma Nishio
// 
//==========================================

//**********************
// インクルードガード
//**********************
#pragma once

//*****************************
// インクルードファイル
//*****************************
#include <memory>

//*****************************
// 前方宣言
//*****************************
class CStateMachine;
class CGameStateBase;
class CGame;

//*****************************
// ゲーム進行管理クラスを定義
//*****************************
class CGameManager
{
public:

	CGameManager();
	~CGameManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
};


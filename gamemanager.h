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
// ゲーム進行管理クラスを定義
//*****************************
class CGameManager
{
public:
	
	~CGameManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGameManager* GetInstance(void);

private:

	CGameManager();
};
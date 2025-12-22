//==========================================================
//
// ゲーム進行管理処理 [ gamemanager.h ]
// Author: Asuma Nishio
// 
//=========================================================

//*********************************************************
// インクルードガード
//*********************************************************
#pragma once

//*********************************************************
// インクルードファイル
//*********************************************************
#include <memory>

//*********************************************************
// ゲーム進行管理クラスを定義
//*********************************************************
class CGameManager
{
public:
	
	~CGameManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetIsGameEnd(const bool isEnd) { m_isGameEnd = isEnd; }
	bool GetIsGameEnd(void) { return m_isGameEnd; }

	static CGameManager* GetInstance(void);

private:

	CGameManager();

	bool m_isGameEnd; // ゲーム進行管理を終わらせるフラグ
};
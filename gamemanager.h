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

//**********************
// インクルードファイル
//**********************
#include "scenemanagebase.h"

//*****************************
// 前方宣言
//*****************************
class CBlockManager;

//*****************************
// ゲーム進行管理クラスを定義
//*****************************
class CGameManager : public CSceneManageBase
{
public:

	CGameManager();
	~CGameManager();

	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void) override;

	CBlockManager* GetBlockM(void) { return m_pBlock; }

private:

	CBlockManager* m_pBlock;		// ブロックマネージャーのポインタ
};
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
// 前方宣言
//*****************************
class CBlockManager;

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

	CBlockManager* GetBlockManager(void) { return m_pBlockManager.get(); }

	static CGameManager* GetInstance(void);

private:

	CGameManager();

	std::unique_ptr<CBlockManager>m_pBlockManager;		// ブロックマネージャーのポインタ
};
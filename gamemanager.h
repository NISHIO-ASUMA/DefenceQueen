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
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CBlockManager* GetBlockManager(void) { return m_pBlockManager.get(); }

	// インスタンス取得
	static CGameManager* GetInstance(void)
	{
		// インスタンスを返す
		static CGameManager pGameManager;
		return &pGameManager;
	}

private:

	CGameManager();
	~CGameManager() {};

	std::unique_ptr<CBlockManager>m_pBlockManager;		// ブロックマネージャーのポインタ
};
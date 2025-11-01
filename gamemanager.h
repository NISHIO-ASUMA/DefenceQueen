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
class CGameSceneObject;

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

	CGameSceneObject* GetGameObj(void) { return m_pGameObj.get(); }

private:

	CGameManager();

	std::unique_ptr<CGameSceneObject>m_pGameObj;		// ゲームオブジェクト管理クラス
};
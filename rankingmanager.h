//==========================================
//
// ランキング管理処理 [ rankingmanager.h ]
// Author: Asuma Nishio
//
//==========================================

//**********************
// インクルードガード
//**********************
#pragma once 

//******************************
// インクルードファイル
//******************************
#include "scenemanagebase.h"

//******************************
// ランキング管理クラスを定義
//******************************
class CRankingManager : public CSceneManageBase
{
public:
	CRankingManager();
	~CRankingManager();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

};
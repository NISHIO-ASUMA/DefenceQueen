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
// 前方宣言
//******************************
class CResultScore;

//******************************
// ランキング管理クラスを定義
//******************************
class CRankingManager
{
public:
	CRankingManager();
	~CRankingManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:

};
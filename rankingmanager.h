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
// ランキング管理クラスを定義
//******************************
class CRankingManager
{
public:

	HRESULT Init(void);
	void Update(void);
	void Uninit(void);
	void Draw(void);

	// インスタンス取得
	static CRankingManager* GetInstance(void)
	{
		// インスタンスを返す
		static CRankingManager pRankManager;
		return &pRankManager;
	}

private:

	CRankingManager();
	~CRankingManager();
};
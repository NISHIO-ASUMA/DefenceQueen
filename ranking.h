//=====================================
//
// ランキングシーン処理 [ ranking.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードガード
//**********************
#pragma once 

//******************************
// インクルードファイル宣言
//******************************
#include "scene.h"

//******************************
// 前方宣言
//******************************
class CRankingManager;

//******************************
// ランキングシーンクラスを定義
//******************************
class CRanking : public CScene
{
public:

	CRanking();
	~CRanking();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRanking* Create(void);

private:
};
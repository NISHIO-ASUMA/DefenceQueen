//=========================================================
//
// ランキングスコア処理 [ rankingscore.h ]
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
#include "object.h"
#include <array>
#include <algorithm>
#include <memory>

//*********************************************************
// 前方宣言
//*********************************************************
class CNumber;
class CLoad;

//*********************************************************
// ランキングスコアクラス定義
//*********************************************************
class CRankingScore : public CObject
{
public:

	CRankingScore(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CRankingScore();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Load(void);

	static CRankingScore* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:

	static constexpr int RANKSCOREDIGIT = 8; // 表示桁数
	static constexpr int RANKING_MAX = 5;	// ランキング数

	std::array<int, RANKING_MAX>m_aRankData;	// スコア配列
	std::unique_ptr<CLoad>m_pLoad;	// 配列スコア読み込み

	D3DXVECTOR3 m_pos;		// 座標
	float m_fWidth;			// 横幅
	float m_fHeight;		// 高さ

	CNumber* m_apNumber[RANKING_MAX][RANKSCOREDIGIT]; // 各スコアと桁数
};
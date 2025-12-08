//=========================================================
//
// リザルトに表示するスコアの処理 [ resultscore.h ]
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
#include <memory>
#include <array>

//*********************************************************
// 前方宣言
//*********************************************************
class CLoad;
class CNumber;

//*********************************************************
// リザルトに出すスコアを表示するクラスを定義
//*********************************************************
class CResultScore : public CObject
{
public:

	CResultScore(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CResultScore();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Load(void);

	static CResultScore* Create(const D3DXVECTOR3 pos, const float fWidth, const float fHeight);

private:

	//***********************
	// 定数構造体
	//***********************
	struct Config
	{
		static constexpr int NUM_SCORE = 8; // 桁数
		static constexpr int NUM_DIGIT = 10; // 桁数
	};

	std::array<CNumber* ,Config::NUM_SCORE>m_pNumber;		// 桁数分のナンバーのポインタ
	std::unique_ptr<CLoad>m_pLoad; // ユニークポインタ
	D3DXVECTOR3 m_pos;				// 座標
	int m_nScore;					// スコア保持用
	float m_fWidth;					// 横幅
	float m_fHeight;				// 高さ
};
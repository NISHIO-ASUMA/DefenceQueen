//====================================
//
// スコア処理 [ score.h ]
// Author: Asuma Nishio
// 
//=====================================

//**********************
// インクルードガード
//**********************
#pragma once 

//**********************
// インクルードファイル
//**********************
#include "number.h"
#include "object.h"
#include <memory>

//**********************
// 前方宣言
//**********************
class CLoad;

//*******************************************
// スコアクラスを定義
//*******************************************
class CScore : public CObject
{
public:

	CScore(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CScore();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3 GetPos(void) { return m_pos; }

	void AddScore(int nValue);
	void DeleteScore(void);
	void SaveScore(void);
	void SetScore(int nDestScore) { m_nScore = nDestScore; }

	static CScore* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

	int GetScore(void) { return m_nScore; }

private: 

	static constexpr int NUM_SCORE = 8; // 桁数
	static constexpr int NUM_DIGIT = 10; // 表示する分割桁数の値

	CNumber *m_apNumber[NUM_SCORE];	// 桁数分のナンバーのポインタ
	D3DXCOLOR m_col;				// カラー
	D3DXVECTOR3 m_pos;				// 座標
	D3DXVECTOR3 m_rot;				// 角度
	
	float m_fWidth;					// 横幅
	float m_fHeight;				// 高さ
	int m_nScore;			// スコア保持用

	std::unique_ptr< CLoad>m_pLoad; // ユニークポインタ
};

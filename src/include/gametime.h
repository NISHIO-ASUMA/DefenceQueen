//=========================================================
//
// タイマー処理 [ gametime.h ]
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

//*********************************************************
// 前方宣言
//*********************************************************
class CNumber;

//*********************************************************
// タイムクラスを定義
//*********************************************************
class CTime : public CObject
{
public:

	CTime(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CTime();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetToAll(void) { return m_nAllTime; }
	int GetToCurrent(void) { return m_nSecond; }

	static CTime* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:

	void Second(void);		// 秒計算
	void Minute(void);		// 分計算

	static constexpr int DIGIT_TIME = 2;	// 桁数
	static constexpr int NUMTIME = 90;		// 最大タイマー
	static constexpr int CARVETIME = 60;	// カウント上限
	static constexpr int DIVIDE = 10;		// 桁分割の値
	static constexpr int REDTIMEZONE = 10;  // 赤く点滅させる時間
	static constexpr float VALUE_WIDTH = 150.0f; // 横幅の増加分

	int m_nAllTime;		// 全体の時間
	int m_nSecond;		// 現在時間 ( 秒 )
	int m_nMinute;		// 現在時間 ( 分 )
	int m_nDecTime;		// 減った時間量
	int m_nCount;		// 時間カウンター
	float m_fHeight;// 横幅
	float m_fWidth;	// 高さ

	CNumber* m_pNumberMinute[DIGIT_TIME];	// 分
	CNumber* m_pNumberSecond[DIGIT_TIME];	// 秒

	D3DXVECTOR3 m_pos;		// 座標
};

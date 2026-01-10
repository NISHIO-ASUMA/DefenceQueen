//========================================================
//
// UI処理 [ ui.h ]
// Author: Asuma Nishio
//
//========================================================

//*********************************************************
// インクルードガード
//*********************************************************
#pragma once 

//*********************************************************
// インクルードファイル宣言
//*********************************************************
#include "object2D.h"

//*********************************************************
// UIクラスを定義
//*********************************************************
class CUi : public CObject2D
{
public:

	CUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CUi();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CUi* Create(D3DXVECTOR3 pos, int nFlashFrame,float fWidth, float fHeight,const char * Filename,bool isUse = false,bool isAlphaEnable = false,
					   int nAlphaFrame = 0);

private:

	void UpdateAlphaEnable(void); // フェードイメージの点滅関数

	int m_nFlashFrame;		// 点滅間隔
	int m_nAlphaFrame;		// フェード全体のフレーム数
	int m_nAlphaCnt;		// 現在のフレーム

	bool m_isFlash;			// 点滅するかどうか
	bool m_isAlphaEnable; // 描画開始から透明度を触るかどうか
};
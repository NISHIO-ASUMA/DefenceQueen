//====================================
//
// UI処理 [ ui.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードガード
//**********************
#pragma once 

//****************************
// インクルードファイル宣言
//****************************
#include "object2D.h"

//****************************
// UIクラスを定義
//****************************
class CUi : public CObject2D
{
public:

	CUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CUi();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CUi* Create(D3DXVECTOR3 pos, int nFlashFrame,float fWidth, float fHeight,const char * Filename,bool isUse);

private:

	int m_nFlashFrame;		// 点滅間隔
	bool m_isFlash;			// 点滅するかどうか
};
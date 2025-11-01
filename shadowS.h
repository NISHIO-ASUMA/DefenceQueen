//======================================
//
// ステンシルシャドウ処理 [ shadowS.h ]
// Author: Asuma Nishio
//
//======================================

//**********************
// インクルードガード
//**********************
#pragma once 

//**********************
// インクルードファイル
//**********************
#include "objectX.h"

//**********************************
// シャドウステンシルクラスを定義
//**********************************
class CShadowS :public CObjectX
{
public:

	CShadowS(int nPriority = static_cast<int>(CObject::PRIORITY::SHADOW));
	~CShadowS();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CShadowS* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtx;		// 頂点バッファ

};
//=========================================================
//
// ステンシルシャドウ処理 [ shadowstencil.h ]
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
#include "objectX.h"

//*********************************************************
// シャドウステンシルクラスを定義
//*********************************************************
class CShadowStencil :public CObjectX
{
public:

	CShadowStencil(int nPriority = static_cast<int>(CObject::PRIORITY::SHADOW));
	~CShadowStencil();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CShadowStencil* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtx;		// 頂点バッファ

};
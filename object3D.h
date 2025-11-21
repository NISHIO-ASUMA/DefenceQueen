//=========================================================
//
// 3Dオブジェクト基底クラス処理 [ object3D.h ]
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
// オブジェクト3Dクラスを定義
//*********************************************************
class CObject3D : public CObject
{ 
public:

	CObject3D(int nPriority = static_cast<int>(CObject::PRIORITY::BASENUMBER));
	~CObject3D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetCol(D3DXCOLOR col = COLOR_WHITE) { m_col = col;}
	void SetSize(float fWidth, float fHeight) { m_fWidth = fWidth, m_fHeight = fHeight; }
	void SetTexture(const char * pTexName);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXCOLOR GetCol(void) { return m_col; }
	float GetWidth(void) { return m_fWidth; }
	float Getheight(void) { return m_fHeight; }

	float GetHeight(D3DXVECTOR3 pos);

	static CObject3D* Create(D3DXVECTOR3 pos);

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファ

	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3 m_pos;	// 座標情報
	D3DXVECTOR3 m_rot;	// 角度情報
	D3DXCOLOR m_col;	// 色情報
	int m_nIdxTexture;	// テクスチャインデックス
	float m_fWidth;		// 横幅
	float m_fHeight;	// 高さ
};
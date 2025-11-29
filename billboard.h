//=========================================================
//
// ビルボード処理 [ billboard.h ]
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
// ビルボードクラスを定義
//*********************************************************
class CBillboard : public CObject
{
public:

	CBillboard(int nPriority = static_cast<int>(CObject::PRIORITY::BILLBOARD));
	~CBillboard();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Flash(const int nMaxFlashTime,const int Digittime);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetCol(D3DXCOLOR col) { m_col = col; }
	void SetTexture(const char* pTexName);
	void SetSize(float fWidth, float fHeight) { m_fWidth = fWidth, m_fHeight = fHeight; }
	void SetEnableZtest(bool isflags) { m_isTests = isflags; }
	void SetAnim(const int nMaxPattern, const int nMaxAnimCount, float fTexU, float fTexV);
	void SetUV(float fTexU, float fTexU1, float fTexV);

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	D3DXVECTOR3 GetRot(void) { return m_rot; };
	D3DXCOLOR GetCol(void) { return m_col; };
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }

	static CBillboard* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, const char* pTexName);

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファ
	D3DXVECTOR3 m_rot;	// 角度情報
	D3DXVECTOR3 m_pos;	// 座標情報
	D3DXCOLOR m_col;	// 色情報
	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス

	int m_nIdxTexture;	// テクスチャインデックス
	int m_FlashCount;	// 点滅間隔
	int m_nCountAnim;	// アニメ―ション間隔
	int m_nPatterAnim;	// アニメ―ションパターン
	float m_fHeight, m_fWidth;	// 横幅,高さ
	bool m_isTests;				// Zテストするかどうか
};
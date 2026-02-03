//=========================================================
//
// 草の処理 [ grass.h ]
// Author: Asuma Nishio
//
// TODO : 自前で座標とかを持つ
// NOTE : これは草一個に関する処理をまとめたクラス
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
#include <vector>

//*********************************************************
// 前方宣言
//*********************************************************
class CSphereCollider;

//*********************************************************
// 草クラスを定義
//*********************************************************
class CGrass : public CObject
{
public:

	CGrass(int nPriority = static_cast<int>(CObject::PRIORITY::BILLBOARD));
	~CGrass();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	bool Collision(D3DXVECTOR3 * pPos);

	void SetTexture(const char* pTexName);
	void SetRadius(const float fRadius) { m_fRadius = fRadius; }
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }
	void SetCol(const D3DXCOLOR col) { m_col = col; }
	void SetSize(const float fWidth, const float fHeight) { m_fWidth = fWidth, m_fHeight = fHeight; }

	static CGrass* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight);

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファ

	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3 m_pos;	// 座標情報
	D3DXVECTOR3 m_rot;	// 角度情報
	D3DXCOLOR m_col;	// 色情報
	D3DXVECTOR3 m_PushAngle;

	int m_nIdxTexture;	// テクスチャインデックス
	float m_fWidth;		// 横幅
	float m_fHeight;	// 高さ
	float m_fRadius;	// 半径
};
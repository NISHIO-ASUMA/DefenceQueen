//=============================================
//
// メッシュインパクト処理 [ meshimpact.h ]
// Author: Asuma Nishio
//
//=============================================

//**********************
// インクルードガード
//**********************
#pragma once 

//**********************
// インクルードファイル
//**********************
#include "object.h"

//**********************
// 衝撃波のクラス定義
//**********************
class CMeshImpact : public CObject
{
public:
	CMeshImpact(int nPriority = static_cast<int>(CObject::PRIORITY::IMPACT));
	~CMeshImpact();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(D3DXVECTOR3* pPos);

	void SetCol(D3DXCOLOR col) { m_col = col; }

	D3DXVECTOR3 GetPos(void) { return m_pos; }

	static CMeshImpact* Create(D3DXVECTOR3 pos, int nLife, float fRadius, float fInRadius,float fSpeed);

private:
	D3DXVECTOR3 m_pos;	// 座標
	D3DXVECTOR3 m_rot;  // 角度
	D3DXCOLOR m_col;	// 色
	D3DXMATRIX m_mtxWorld; // ワールドマトリックス
	LPDIRECT3DINDEXBUFFER9 m_pIdx;	// インデックスバッファ
	LPDIRECT3DVERTEXBUFFER9 m_pVtx; // 頂点バッファ

	float m_fInRadius;		// 内径
	float m_fOutRadius;		// 外径
	int m_nLife;			// 寿命
	float m_DecAlpha;		// α値減少
	float m_fSpeed;			// 拡大速度
};
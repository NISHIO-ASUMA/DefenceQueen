//============================================
//
// メッシュフィールド処理 [ meshfield.h ]
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

//**********************************
// メッシュフィールドクラスを定義
//**********************************
class CMeshField : public CObject
{
public:
	CMeshField(int nPrio = static_cast<int>(CObject::PRIORITY::MESH));
	~CMeshField();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetTexture(void);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRaiusZ(float fRadius) { m_fRadiusZ = fRadius; }
	void SetRaiusX(float fRadius) { m_fRadius = fRadius; }

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	float GetRadiusX(void) { return m_fRadius; }
	float GetRadiusZ(void) { return m_fRadiusZ; }

	static CMeshField* Create(D3DXVECTOR3 pos, float fRadiusX, float fRadiusZ, int nNumX, int nNumZ);

private:
	LPDIRECT3DINDEXBUFFER9 m_pIdx; // インデックスバッファ
	LPDIRECT3DVERTEXBUFFER9 m_pVtx;	// 頂点バッファ

	D3DXVECTOR3 m_pos;		// 座標
	D3DXVECTOR3 m_rot;		// 角度
	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
	float m_fRadius;		// X方向の半径
	float m_fRadiusZ;		// Z方向の半径

	int m_nNumPrimitive;	// プリミティブ数
	int m_nNumIdx;			// インデックス数
	int m_nNumAllVtx;		// 全体頂点数
	int m_nTexIdx;			// テクスチャインデックス
	int m_nNumX;			// X頂点
	int m_nNumZ;			// Z頂点

};
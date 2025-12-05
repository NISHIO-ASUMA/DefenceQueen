//=========================================================
//
// Xファイルオブジェクト基底クラス処理 [ objectX.h ]
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
// オブジェクトXクラスを定義
//*********************************************************
class CObjectX : public CObject
{
public:
	CObjectX(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CObjectX();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void); 
	void DrawShadow(void);

	void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetRot(const D3DXVECTOR3& rot = VECTOR3_NULL) { m_rot = rot; }
	void SetScale(const D3DXVECTOR3& scale = INITSCALE) { m_Scale = scale; }
	void SetMtxWorld(D3DXMATRIX mtxworld) { m_mtxWorld = mtxworld; }
	void SetFilePass(const char* pFilePass);
	void SetModelIdx(const int nIdx) { m_nIdxModel = nIdx; }
	void SetShadow(bool isFlags) { m_isShadow = isFlags; }

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	D3DXVECTOR3 GetRot(void) { return m_rot; };
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }
	int GetModelIdx(void) const { return m_nIdxModel; }

	static CObjectX* Create(const char* pModelName, const D3DXVECTOR3& pos);

private:

	D3DXVECTOR3 m_pos;		// 座標
	D3DXVECTOR3 m_rot;		// 角度
	D3DXVECTOR3 m_Scale;	// 拡大率
	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
	int m_nIdxModel;		// モデルインデックス
	bool m_isShadow;		// 影を出すかどうか
};
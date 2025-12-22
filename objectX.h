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
	void SetFilePass(const char* pFilePass);

	inline void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
	inline void SetRot(const D3DXVECTOR3& rot = VECTOR3_NULL) { m_rot = rot; }
	inline void SetScale(const D3DXVECTOR3& scale = INITSCALE) { m_Scale = scale; }
	inline void SetMtxWorld(D3DXMATRIX mtxworld) { m_mtxWorld = mtxworld; }
	inline void SetModelIdx(const int nIdx) { m_nIdxModel = nIdx; }
	inline void SetShadow(bool isFlags) { m_isShadow = isFlags; }

	inline D3DXVECTOR3 GetPos(void) const { return m_pos; };
	inline D3DXVECTOR3 GetRot(void) const { return m_rot; };
	inline D3DXMATRIX GetMtxWorld(void) const { return m_mtxWorld; }
	inline int GetModelIdx(void) const { return m_nIdxModel; }

	static CObjectX* Create(const char* pModelName, const D3DXVECTOR3& pos, const D3DXVECTOR3& rot = VECTOR3_NULL);

private:

	D3DXVECTOR3 m_pos;		// 座標
	D3DXVECTOR3 m_rot;		// 角度
	D3DXVECTOR3 m_Scale;	// 拡大率
	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
	int m_nIdxModel;		// モデルインデックス
	bool m_isShadow;		// 影を出すかどうか
};
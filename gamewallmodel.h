//=========================================================
//
// 世界の壁オブジェクト処理 [ gamewallmodel.h ]
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
// 前方宣言
//*********************************************************
class CBoxCollider;

//*********************************************************
// 壁を生成するクラスを定義
//*********************************************************
class CGameWallModel : public CObjectX
{
public:

	CGameWallModel(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CGameWallModel();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(CBoxCollider* pOther, D3DXVECTOR3* OutPos);

	inline CBoxCollider* GetCollider(void) { return m_pCollider; }

	static CGameWallModel* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale, const char* pModelName);

private:
	CBoxCollider* m_pCollider;	// 矩形のコライダー
};
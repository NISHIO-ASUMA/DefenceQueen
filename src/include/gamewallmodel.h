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
#include <memory>

//*********************************************************
// 前方宣言
//*********************************************************
class CBoxCollider;
class CSphereCollider;

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
	bool Collision(CSphereCollider* pOther);

	inline CBoxCollider* GetCollider(void) const { return m_pCollider.get(); }
	static CGameWallModel* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale, const char* pModelName);

private:
	std::unique_ptr<CBoxCollider>m_pCollider;	// 矩形のコライダー
};
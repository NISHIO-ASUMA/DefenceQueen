//=========================================================
//
// ブロック処理 [ block.h ]
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
// ブロックオブジェクトクラスを定義
//*********************************************************
class CBlock : public CObjectX
{
public:

	CBlock(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CBlock();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(CBoxCollider * pOther,D3DXVECTOR3 * OutPos);

	inline CBoxCollider* GetCollider(void) { return m_pCollider; }

	static CBlock* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 scale, const char* pModelName);

private:
	CBoxCollider* m_pCollider;	// 矩形のコライダー
};


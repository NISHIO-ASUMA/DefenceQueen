//=========================================================
//
// 出現する餌の処理 [ feed.h ]
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
class CSphereCollider;
class CParameter;

//*********************************************************
// 餌クラスを定義
//*********************************************************
class CFeed : public CObjectX
{
public:

	CFeed(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CFeed();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DecLife(const int nDecValue);
	void SetRadius(const float fRadius) { m_fRadius = fRadius; }
	bool Collision(CSphereCollider* other);

	float GetRadius(void) const { return m_fRadius; }
	CSphereCollider* GetCollider(void) const { return m_pSphere; }

	static CFeed* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, const char* pModelName,const float fRadius);

private:

	CSphereCollider* m_pSphere; // 球形コライダー
	std::unique_ptr<CParameter>m_pParam; // パラメーター
	float m_fRadius;			// 半径
};
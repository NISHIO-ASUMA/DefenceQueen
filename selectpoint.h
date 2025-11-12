//=====================================
//
// 選択ポイント処理 [ selectpoint.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードガード
//**********************
#pragma once

//**********************
// インクルードファイル
//**********************
#include "object3d.h"
#include "move3dobject.h"

//**********************
// 前方宣言
//**********************
class CSphereCollider;
class CBoxCollider;

//****************************
// 円選択の範囲描画クラス定義
//****************************
class CSelectPoint : public CMove3DObject
{
public:

	CSelectPoint(int nPriority = static_cast<int>(CObject::PRIORITY::MOVE3D));
	~CSelectPoint();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Moving(void);
	void MovePad(void);

	void SetfRange(float fRange) { m_fHitRange = fRange; }
	void SetIsHit(const bool isHit) { m_isHit = isHit; }

	bool Collision(CSphereCollider* other);
	bool CollisionBox(CBoxCollider* pothere, D3DXVECTOR3* pOutPos);

	CSphereCollider* GetSphere(void) const { return m_pSphere; }
	float GetfRange(void) const { return m_fHitRange; }
	bool GetIsHit(void) const { return m_isHit; }

	static CSelectPoint* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, const float fRadius);

private:

	CSphereCollider* m_pSphere; // 球形コライダー
	CBoxCollider* m_pBox;		// 矩形コライダー
	float m_fHitRange;			// 半径
	bool m_isHit;				// 当たっているかどうか
};
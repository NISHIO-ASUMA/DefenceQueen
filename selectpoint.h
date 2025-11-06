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

//**********************
// 前方宣言
//**********************
class CSphereCollider;

//****************************
// 円選択の範囲描画クラス定義
//****************************
class CSelectPoint : CObject3D
{
public:

	CSelectPoint(int nPriority = static_cast<int>(CObject::PRIORITY::CIRCLE));
	~CSelectPoint();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	void SetfRange(float fRange) { m_fHitRange = fRange; }
	void Moving(D3DXVECTOR3 pos);
	void MovePad(D3DXVECTOR3 pos);

	bool Collision(CSphereCollider* other);
	float GetfRange(void) const { return m_fHitRange; }

	static CSelectPoint* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, const float fRadius);

private:

	CSphereCollider* m_pSphere; // 球形コライダー
	float m_fHitRange;			// 半径
};
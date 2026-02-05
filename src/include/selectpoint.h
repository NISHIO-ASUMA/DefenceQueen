//=========================================================
//
// 選択ポイント処理 [ selectpoint.h ]
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
#include "move3dobject.h"

//*********************************************************
// 前方宣言
//*********************************************************
class CSphereCollider;
class CBoxCollider;
class CBlackBoard;
class CNode;

//*********************************************************
// 円選択の範囲描画クラス定義
//*********************************************************
class CSelectPoint : public CMove3DObject
{
public:

	CSelectPoint(int nPriority = static_cast<int>(CObject::PRIORITY::MOVE3D));
	~CSelectPoint();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	bool Collision(CSphereCollider* other);
	bool CollisionBox(CBoxCollider* pothere, D3DXVECTOR3* pOutPos);

	inline void SetfRange(float fRange) { m_fHitRange = fRange; }
	inline void SetIsHit(const bool isHit) { m_isHit = isHit; }

	inline CSphereCollider* GetSphere(void) const { return m_pSphere; }
	inline float GetfRange(void) const { return m_fHitRange; }
	inline bool GetIsHit(void) const { return m_isHit; }

	/// <summary>
	/// ポインタ生成処理
	/// </summary>
	/// <param name="pos">生成座標</param>
	/// <param name="rot">角度</param>
	/// <param name="fWidth">横幅</param>
	/// <param name="fHeight">高さ</param>
	/// <param name="fRadius">判定半径</param>
	/// <returns></returns>
	static CSelectPoint* Create
	(
		const D3DXVECTOR3& pos, 
		const D3DXVECTOR3& rot, 
		const float fWidth, 
		const float fHeight, 
		const float fRadius
	);

private:

	void Moving(void);
	void MovePad(void);

	CSphereCollider* m_pSphere; // 球形コライダー
	CBoxCollider* m_pBox;		// 矩形コライダー

	float m_fHitRange;			// 半径
	bool m_isHit;				// 当たっているかどうか
};
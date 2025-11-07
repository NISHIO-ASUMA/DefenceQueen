//==================================================
//
// 吸い込みギミック処理 [ gimmicksuction.h ]
// Author: Asuma Nishio
//
//==================================================

//**********************
// インクルードガード
//**********************
#pragma once

//**********************
// インクルードファイル
//**********************
#include "objectX.h"

//*******************************
// 吸い込みギミッククラスを定義
//*******************************
class CGimmickSuction : public CObjectX
{
public:

	CGimmickSuction(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CGimmickSuction();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetTime(const int nTime) { m_nActiveTime = nTime; }
	void SetRadius(const float fRadius) { m_fRadius = fRadius; }

	int GetAtiveTime(void) const { return m_nActiveTime; }
	float GetRadius(void) const { return m_fRadius; }

	static CGimmickSuction* Create(
		const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const char* pModelName,const int nActiveTime,const float fRadius);

private:

	int m_nActiveTime; // 継続時間
	float m_fRadius;	// 影響範囲
};
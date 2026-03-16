//=========================================================
//
// 柱状エフェクト処理 [ effectpiler.h ]
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
#include "billboard.h"

//*********************************************************
// 柱状エフェクトクラスを定義
//*********************************************************
class CEffectPiler : public CBillboard
{
public:

	CEffectPiler(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CEffectPiler();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="pos">生成座標</param>
	/// <param name="rot">角度</param>
	/// <param name="fRadius">半径</param>
	/// <param name="nLife">寿命</param>
	/// <returns></returns>
	static CEffectPiler* Create
	(
		const D3DXVECTOR3& pos, 
		const D3DXVECTOR3& rot, 
		const float& fRadius, 
		const int& nLife
	);

private:
	int m_nLife;		// 体力
	float m_fRadius;	// 半径
};
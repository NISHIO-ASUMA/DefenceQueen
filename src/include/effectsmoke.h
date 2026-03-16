//=========================================================
//
// 煙エフェクト処理 [ effectsmoke.h ]
// Author : Asuma Nishi
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
// 煙エフェクトクラスを定義
//*********************************************************
class CEffectSmoke : public CBillboard
{
public:

	CEffectSmoke(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CEffectSmoke();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="pos">生成座標</param>
	/// <param name="col">色</param>
	/// <param name="nLife">寿命</param>
	/// <param name="fRadius">半径</param>
	/// <returns></returns>
	static CEffectSmoke* Create
	(
		const D3DXVECTOR3& pos, 
		const D3DXCOLOR& col, 
		int nLife, 
		float fRadius
	);
private:
	int m_nLife;		// 体力
	float m_fRadius;	// 半径
};
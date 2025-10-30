//==========================================
//
// 煙エフェクト処理 [ effectsmoke.h ]
// Author : Asuma Nishi
//
//==========================================

//**********************
// インクルードガード
//**********************
#pragma once

//**********************************
// インクルードファイル
//**********************************
#include "billboard.h"

//**********************************
// 煙エフェクトクラスを定義
//**********************************
class CEffectSmoke : public CBillboard
{
public:
	CEffectSmoke(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CEffectSmoke();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEffectSmoke* Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius);

private:
	int m_nLife;		// 体力
	float m_fRadius;	// 半径
	D3DXVECTOR3 m_move;	// 移動量
};
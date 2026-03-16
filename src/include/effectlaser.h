//=========================================================
//
// レーザーエフェクト処理 [ effectlaser.h ]
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
// レーザーエフェクトクラスを定義
//*********************************************************
class CEffectLaser : public CBillboard
{
public:

	CEffectLaser(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CEffectLaser();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="pos">生成座標</param>
	/// <param name="Endpos">終端座標</param>
	/// <param name="col">色</param>
	/// <param name="move">移動量</param>
	/// <param name="nLife">寿命</param>
	/// <param name="fRadius">半径</param>
	/// <returns></returns>
	static CEffectLaser* Create
	(
		const D3DXVECTOR3& pos, 
		const D3DXVECTOR3& Endpos,
		const D3DXCOLOR& col, 
		const D3DXVECTOR3& move, 
		const int& nLife, 
		const float& fRadius
	);

private:
	int m_nLife;		  // 体力
	float m_fRadius;	  // 半径
	float m_fLength;	  // 長さ
	D3DXVECTOR3 m_move;	  // 移動量
	D3DXVECTOR3 m_EndPos; // 終点座標
	D3DXVECTOR3 m_OldPos; // 過去の座標
};
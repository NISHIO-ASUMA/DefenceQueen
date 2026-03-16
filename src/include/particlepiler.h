//=========================================================
//
// 柱状パーティクル生成処理 [ particlepiler.h ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードガード
//*********************************************************
#pragma once

//*********************************************************
// システムインクルードファイル
//*********************************************************
#include <vector>

//*********************************************************
// インクルードファイル
//*********************************************************
#include "object.h"

//*********************************************************
// 前方宣言
//*********************************************************
class CEffect;

//*********************************************************
// パーティクルクラスを定義
//*********************************************************
class CParticlePiler : public CObject
{
public:

	CParticlePiler(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CParticlePiler();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override {};

	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="pos">生成座標</param>
	/// <param name="col">色</param>
	/// <param name="nMaxParticle">最大粒子数</param>
	/// <param name="nRadius">半径</param>
	/// <param name="nLength">飛散距離</param>
	/// <param name="nLife">寿命</param>
	/// <param name="fAngle">角度</param>
	/// <returns></returns>
	static CParticlePiler* Create
	(
		const D3DXVECTOR3& pos, 
		const D3DXCOLOR& col, 
		const int& nMaxParticle, 
		const int& nRadius, 
		const int& nLength, 
		const int& nLife,
		const float& fAngle
	);

private:

	std::vector<CEffect*> m_pEffect; // エフェクト配列

	D3DXVECTOR3 m_pos;	// 座標
	D3DXCOLOR m_col;	// 色
	int m_nMaxParticle; // 最大数
	int m_nLife;		// 寿命
	int m_nLength;		// 飛散する距離
	int m_nRadius;		// 粒の大きさ
	float m_fAngle;		// 角度
};
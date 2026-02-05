//=========================================================
//
// ポップアップナンバー表示処理 [ popupnumber.h ]
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
// ナンバーポップアップを生成するクラスを定義
//*********************************************************
class CPopUpNumber : public CBillboard
{
public:

	CPopUpNumber(int nPriority = static_cast<int>(CObject::PRIORITY::BILLBOARD));
	~CPopUpNumber();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	/// <summary>
	/// ポインタ生成処理
	/// </summary>
	/// <param name="pos">生成座標</param>
	/// <param name="rot">角度</param>
	/// <param name="fWidth">横幅</param>
	/// <param name="fHeight">高さ</param>
	/// <param name="nLife">寿命</param>
	/// <returns></returns>
	static CPopUpNumber* Create
	(
		const D3DXVECTOR3& pos, 
		const D3DXVECTOR3& rot,
		const float fWidth,
		const float fHeight,
		const int nLife
	);

	inline void SetLife(const int& nLife) { m_nLife = nLife; }

private:

	//****************************
	// 定数構造体宣言
	//****************************
	struct Config
	{
		static constexpr float UP_SPEED = 3.0f; // 上昇速度
	};

	int m_nLife; // 寿命
};
//=========================================================
//
// 切り離し可能を合図するUI処理 [ sepalationsign.h ]
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
// 切り離し可能を合図するUI表示クラスを定義
//*********************************************************
class CSepalationSign : public CBillboard
{
public:

	CSepalationSign(int nPriority = static_cast<int>(CObject::PRIORITY::BILLBOARD));
	~CSepalationSign();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	inline void SetIsDraw(const bool isDraw) { m_isDraw = isDraw; }

	static CSepalationSign* Create(const D3DXVECTOR3& pos);

private:

	//******************************
	// 定数構造体
	//******************************
	struct Config
	{
		static constexpr const char* TEXNAME = "Sepalation.png"; // テクスチャファイル
		static constexpr float SIZE = 70.0f; // 描画のサイズ
	};

	bool m_isDraw;		// 描画フラグ
};
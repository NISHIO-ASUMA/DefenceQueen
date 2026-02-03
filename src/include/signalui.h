//=========================================================
//
// アリのシグナル状態を表すUI表示クラス処理 [ signalui.h ]
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
// シグナルを表すUIのクラスを定義
//*********************************************************
class CSignalUi : public CBillboard
{
public:

	CSignalUi(int nPriority = static_cast<int>(CObject::PRIORITY::BILLBOARD));
	~CSignalUi();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	inline void SetIsDraw(const bool isDraw) { m_isDraw = isDraw; }
	inline bool GetIsDraw(void) const { return m_isDraw; }

	static CSignalUi* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot,
		const float fWidth,const float fHeight,const D3DXCOLOR& color = COLOR_WHITE);

private:

	//**********************************
	// 定数構造体宣言
	//**********************************
	struct Config
	{
		static constexpr const char* TEX_NAME = "Signal.png"; // テクスチャ名
	};

	bool m_isDraw;				// 描画するかどうか
};
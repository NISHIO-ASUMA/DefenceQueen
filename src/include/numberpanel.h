//=========================================================
//
// 数字パネルを表示するビルボード処理 [ numberpanel.h ]
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
// 数値表示パネルのクラスを定義
//*********************************************************
class CNumberPanel : public CBillboard
{
public:

	//****************************
	// 表示する数のパネルの種類
	//****************************
	enum TYPE
	{
		TYPE_LITTLE, // 最小量
		TYPE_MIDDLE, // 中間
		TYPE_LARGE,	 // 最大量
		TYPE_MAX
	};

	CNumberPanel(int nPriority = static_cast<int>(CObject::PRIORITY::BILLBOARD));
	~CNumberPanel();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void SetTexture(void);
	void SetType(const int nType) { m_nType = nType; }

	static CNumberPanel* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const int nType);

private:

	//***********************************
	// 定数構造体
	//***********************************
	struct Config
	{
		static constexpr float WIDTH = 120.0f; // 横幅
		static constexpr float HEIGHT = 40.0f; // 高さ
	};

	int m_nType;	// 種類変数
};
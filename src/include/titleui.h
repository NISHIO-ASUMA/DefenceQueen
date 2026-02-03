//=========================================================
//
// タイトルui処理 [ titleui.h ]
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
#include "object2D.h"

//*********************************************************
// 前方宣言
//*********************************************************
class CObject;

//*********************************************************
// タイトルUIオブジェクトクラスを定義
//*********************************************************
class CTitleUi : public CObject2D
{
public:

	//*********************
	// メニュー識別列挙型
	//*********************
	enum MENU
	{
		MENU_GAME,
		MENU_EXIT,
		MENU_MAX
	};

	CTitleUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CTitleUi();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetTexture(int nType);

	static CTitleUi* Create(D3DXVECTOR3 pos,D3DXCOLOR col,float fWidth,float fHeight,int nType);

private:
};
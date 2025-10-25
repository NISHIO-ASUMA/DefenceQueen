//====================================
//
// タイトル処理 [ title.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードガード
//**********************
#pragma once 

//****************************
// インクルードファイル宣言
//****************************
#include "scene.h"

//**************************
// 前方宣言
//**************************
class CTitleManager;

//****************************
// タイトルクラスを定義
//****************************
class CTitle :public CScene
{
public:
	CTitle();
	~CTitle();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CTitleManager* m_pTitleManager; // マネージャークラスポインタ
};

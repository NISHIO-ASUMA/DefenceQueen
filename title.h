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
#include <memory>

//****************************
// タイトルシーンクラスを定義
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

};
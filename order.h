//===========================================
//
// 司令塔処理 [ order.h ]
// Author: Asuma Nishio
//
//===========================================

//**********************
// インクルードガード
//**********************
#pragma once

//**********************
// インクルードファイル
//**********************
#include <memory>

//********************************
// 司令塔キャラクタークラスを定義
//********************************
class COrder
{
public:

	COrder();
	~COrder();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static COrder* Create(void);

private:
};
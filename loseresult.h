//============================================
//
// 負けリザルトシーン処理 [ loseresult.h ]
// Author: Asuma Nishio
// 
//============================================

//**********************
// インクルードガード
//**********************
#pragma once 

//**************************
// インクルードファイル宣言
//**************************
#include "scene.h"

//********************************
// 負けリザルトシーンクラスを定義
//********************************
class CLoseResult : public CScene
{
public:
	CLoseResult();
	~CLoseResult();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};

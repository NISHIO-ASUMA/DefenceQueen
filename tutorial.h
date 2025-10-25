//=====================================
//
// チュートリアル処理 [ tutorial.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードガード
//**********************
#pragma once 

//**********************
// インクルードファイル
//**********************
#include "scene.h"

//**********************
// 前方宣言
//**********************
class CTutorialManager;

//************************************
// チュートリアルシーンクラスを定義
//************************************
class CTutorial : public CScene
{
public:
	CTutorial();
	~CTutorial();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTutorial* Create(void);

private:
	CTutorialManager* m_pTutoManager; // マネージャークラスのポインタ
};

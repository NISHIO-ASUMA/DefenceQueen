//=============================================
//
// チュートリアル管理処理 [ tutorialmanager.h ]
// Author: Asuma Nishio
//
//=============================================

//**********************
// インクルードガード
//**********************
#pragma once 

//**********************
// インクルードファイル
//**********************
#include "scenemanagebase.h"

//******************************
// 前方宣言
//******************************
class CTutorialUi;

//********************************
// チュートリアル管理クラスを定義
//********************************
class CTutorialManager : public CSceneManageBase
{
public:

	CTutorialManager();
	~CTutorialManager();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:
	CTutorialUi* m_pTutoui; // チュートリアルuiクラスのポインタ
};
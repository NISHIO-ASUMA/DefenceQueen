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

//******************************
// 前方宣言
//******************************
class CTutorialUi;

//********************************
// チュートリアル管理クラスを定義
//********************************
class CTutorialManager
{
public:

	CTutorialManager();
	~CTutorialManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	CTutorialUi* m_pTutoui; // チュートリアルuiクラスのポインタ
};
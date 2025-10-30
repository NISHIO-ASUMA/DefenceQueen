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

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// インスタンス取得
	static CTutorialManager* GetInstance(void)
	{
		// 生成されたインスタンス
		static CTutorialManager pTutoManager;
		return &pTutoManager;
	}

private:

	CTutorialManager();
	~CTutorialManager();

	CTutorialUi* m_pTutoui; // チュートリアルuiクラスのポインタ
};
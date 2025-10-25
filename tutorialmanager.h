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
	//***********************
	// 動かすタスクの種類
	//***********************
	enum TASKTYPE
	{
		TASKTYPE_MOVE,
		TASKTYPE_ATTACK,
		TASKTYPE_JUMP,
		TASKTYPE_JUMPATTACK,
		TASKTYPE_AVOID,
		TASKTYPE_LASER,
		TASKTYPE_LASERACTION,
		TASKTYPE_FREE,
		TASKTYPE_MAX
	};

	CTutorialManager();
	~CTutorialManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	CTutorialUi* m_pTutoui; // チュートリアルuiクラスのポインタ
	TASKTYPE m_Tasktype;	// 種類

	bool m_isFreeDone;
	bool m_isCreate;
};
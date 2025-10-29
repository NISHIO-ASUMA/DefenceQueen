//==========================================
//
// タイトル管理処理 [ titlemanager.h ]
// Author: Asuma Nishio
// 
//==========================================

//**********************
// インクルードガード
//**********************
#pragma once 

//***********************
// インクルードファイル
//***********************
#include "scenemanagebase.h"

//***********************
// 前方宣言
//***********************
class CTitleUi;
class CUi;

//**************************************
// タイトルマネージャー管理クラスを定義
//**************************************
class CTitleManager : public CSceneManageBase
{
public:

	CTitleManager();
	~CTitleManager();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	CUi* m_pUi;				// クラスポインタ
	int m_nIdx;				// 選択番号
	bool m_isuiCreate;		// 生成されたかどうかの判別フラグ
	bool m_isFirstuiCreate;	// 最初のシーンで生成されたか判別フラグ
};
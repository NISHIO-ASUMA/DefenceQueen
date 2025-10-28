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
// 前方宣言
//***********************
class CTitleUi;
class CUi;

//**************************************
// タイトルマネージャー管理クラスを定義
//**************************************
class CTitleManager
{
public:

	CTitleManager();
	~CTitleManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:

	CUi* m_pUi;				// クラスポインタ
	int m_nIdx;				// 選択番号
	bool m_isuiCreate;		// 生成されたかどうかの判別フラグ
	bool m_isFirstuiCreate;	// 最初のシーンで生成されたか判別フラグ
};
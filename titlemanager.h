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

//***********************
// インクルードファイル
//***********************
#include <memory>

//**************************************
// タイトルマネージャー管理クラスを定義
//**************************************
class CTitleManager
{
public:

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// インスタンス取得
	static CTitleManager* GetInstance(void)
	{
		// インスタンスを返す
		static CTitleManager pTitleManager;
		return &pTitleManager;
	}

private:

	CTitleManager();
	~CTitleManager();

	CUi* m_pUi;				// クラスポインタ
	int m_nIdx;				// 選択番号
};
//=====================================
//
// ポーズ管理処理 [ pausemanager.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードガード
//**********************
#pragma once 

//********************************
// 前方宣言
//********************************
class CPause;

//*********************************
// ポーズメニュー管理クラスを定義
//*********************************
class CPauseManager
{
public:

	CPauseManager();
	~CPauseManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	static void SetEnablePause(bool isFlags) { m_isPause = isFlags; }
	void SetEnablePause(void);

	static bool GetPause(void) { return m_isPause; }

private:

	static constexpr int SELECT_BEGIN = 1;	// メニュー開始番号
	static constexpr int SELECT_END = 3;	// メニュー終了番号
	static constexpr int SELECT_MAX = 4;	// 最大生成数

	static bool m_isPause;			// ポーズかどうか
	int m_nSelectIdx;				// セレクト番号
	CPause* m_pPause[SELECT_MAX];	// ポーズクラスのポインタ配列
};
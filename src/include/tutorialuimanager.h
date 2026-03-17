//=========================================================
//
// チュートリアルui複数管理処理 [ tutorialuimanager.h ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードガード
//*********************************************************
#pragma once

//*********************************************************
// システムインクルード
//*********************************************************
#include <list>
#include <vector>
#include <memory>

//*********************************************************
// 前方宣言
//*********************************************************
class CTutorialUi;
class CTutorialStateBase;

//*********************************************************
// 管理クラスを定義
//*********************************************************
class CTutorialUiManager
{
public:

	~CTutorialUiManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	/// <summary>
	/// リストから要素を消す
	/// </summary>
	/// <param name="pUi">消去対象のポインタ</param>
	void Erase(CTutorialUi* pUi);

	static CTutorialUiManager* GetInstance(void);

private:

	CTutorialUiManager();

	std::vector<std::unique_ptr<CTutorialStateBase>> m_pStateList;	// ステート管理ポインタ
	std::list<CTutorialUi*> m_pUiList;				// uiを格納するリスト
	int m_nStateIndex;								// ステートのインデックス番号
};
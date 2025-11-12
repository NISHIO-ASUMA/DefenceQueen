//===============================================
//
// 複数の餌を管理する処理 [ feedmanager.h ]
// Author: Asuma Nishio
//
//===============================================

//**********************
// インクルードガード
//**********************
#pragma once

//**********************
// インクルードファイル
//**********************
#include <vector>

//**********************
// 前方宣言
//**********************
class CFeed;

//***************************
// 餌を管理するクラスを定義
//***************************
class CFeedManager
{
public:

	CFeedManager();
	~CFeedManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	/// <summary>
	/// 配列の指定番号から取得
	/// </summary>
	/// <param name="nIdx">取得したいインデックス番号</param>
	/// <returns></returns>
	CFeed* GetFeed(const int nIdx) { return m_pFeed[nIdx]; }

	/// <summary>
	/// 配列の要素数を取得
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	int GetSize(void) const { return static_cast<int>(m_pFeed.size()); }

private:

	std::vector<CFeed*>m_pFeed; // 動的配列
};
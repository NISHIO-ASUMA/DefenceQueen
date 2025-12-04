//=========================================================
//
// 仲間のスポナー管理処理 [ arrayspawnmanager.h ]
// Author: Asuma Nishio
// 
//=========================================================

//*********************************************************
// インクルードガード
//*********************************************************
#pragma once

//*********************************************************
// インクルードファイル
//*********************************************************

//*********************************************************
// 前方宣言
//*********************************************************
class CArraySpawner;
class CArrayManager;

//*********************************************************
// スポーン配列の管理クラスを定義
//*********************************************************
class CArraySpawnManager
{
public:

	CArraySpawnManager();
	~CArraySpawnManager();

	HRESULT Init(CArrayManager * pManager);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	/// <summary>
	/// 自身で選択したスポナーの取得
	/// </summary>
	/// <param name="nIdx"></param>
	/// <returns></returns>
	CArraySpawner* GetIndexSpawner(const int& nIdx) { return m_pArraySpawner[nIdx]; }

private:

	static inline constexpr int NUM_ARRAYSPAWNER = 3; // スポナーの数

	CArraySpawner* m_pArraySpawner[NUM_ARRAYSPAWNER]; // 所持するスポナー
	int m_nSelectIdx; // 選択してるスポナーインデックス
};


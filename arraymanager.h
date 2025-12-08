//=========================================================
//
// 仲間クラス全体の管理処理 [ arraymanager.h ]
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
#include <vector>

//*********************************************************
// 前方宣言
//*********************************************************
class CArray;
class CTopAnt;

//*********************************************************
// 仲間全体を管理するクラスを定義
//*********************************************************
class CArrayManager
{
public:

	CArrayManager();
	~CArrayManager();

	HRESULT Init(const int nActives);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	/// <summary>
	/// 現在のアクティブな数を取得する
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	int GetUseArray(void) { return m_nActiveAll; }

	/// <summary>
	/// 配列の要素数を取得する
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	int GetAll(void) { return static_cast<int>(m_pArrays.size()); }

	/// <summary>
	/// 配列の要素番号から取得
	/// </summary>
	/// <param name="nIdx">取得したい番号</param>
	/// <returns></returns>
	CArray* GetArrays(const int nIdx) { return m_pArrays[nIdx]; }

	/// <summary>
	/// 動的配列全体を取得する
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	std::vector<CArray*>& GetArray(void) { return m_pArrays; }

	/// <summary>
	/// スポナー用に確保する関数
	/// </summary>
	/// <param name="nfalseData">未使用数</param>
	/// <returns></returns>
	std::vector<CArray*> Allocate(const int& nStock);

	/// <summary>
	/// 大元の配列に戻す処理
	/// </summary>
	/// <param name="pArray">クラスのポインタ</param>
	void ReleaseCharactor(CArray* pArray);

private:

	//**********************
	// 定数構造体
	//**********************
	struct ArrayConfig
	{
		static constexpr int LIFE = 10; // 体力値
		static constexpr int ALLARRAYS = 100; // 最大使用数
	};

	std::vector<CArray*>m_pArrays; // 動的配列
	int m_nActiveAll;		// 現在の出現数
	std::vector<CTopAnt*>m_pTopAnts; // トップアリの配列
};
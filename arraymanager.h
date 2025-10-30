//===============================================
//
// 仲間クラス全体の管理処理 [ arraymanager.h ]
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
#include <list>

//**********************
// 前方宣言
//**********************
class CArray;

//***************************************
// 仲間全体を管理するクラスを定義
//***************************************
class CArrayManager
{
public:

	CArrayManager();
	~CArrayManager();

	HRESULT Init(const int nActives);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetUseArray(void) { return m_nActiveAll; }

	/// <summary>
	/// 仲間を出現させる関数
	/// </summary>
	/// <param name="pos">出現座標</param>
	/// <param name="rot">出現時の角度</param>
	/// <param name="nLife">体力値</param>
	/// <returns></returns>
	void Spawn(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, int nLife,const int nNumSpawn);

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
	/// 全体を取得する
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	std::vector<CArray*>& GetArray(void) { return m_pArrays; }

private:
	std::vector<CArray*>m_pArrays; // 動的配列
	int m_nActiveAll;		// 現在の出現数
};
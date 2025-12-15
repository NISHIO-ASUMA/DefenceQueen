//=========================================================
//
// 敵のスポナー処理 [ enemyspawner.h ]
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
#include <memory>
#include <vector>

//*********************************************************
// 前方宣言
//*********************************************************
class CEnemy;

//*********************************************************
// 敵の出現するスポナー1個に対するクラスを定義
//*********************************************************
class CEnemySpawner
{
public:

	CEnemySpawner();
	~CEnemySpawner();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void SetPos(const D3DXVECTOR3& pos) { m_Activepos = pos; }
	void SetEnemy(void);

	/// <summary>
	/// スポナーに登録されている敵の配列番号情報の取得
	/// </summary>
	/// <param name="nIdx">取得するインデックス</param>
	/// <returns></returns>
	CEnemy* GetEnemyIdx(const int nIdx) { return m_pEnemy[nIdx]; }

	/// <summary>
	/// スポナーに登録されている敵の動的配列本体を取得する
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	std::vector<CEnemy*>& GetEnemy(void) { return m_pEnemy; }

private:

	std::vector<CEnemy*>m_pEnemy; // 出現するオブジェクトの配列
	D3DXVECTOR3 m_Activepos;	// 出現座標

	int m_SpawnInterval;
	int m_Timer;
};
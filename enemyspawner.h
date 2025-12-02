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
// 敵の出現するスポナーのクラスを定義
//*********************************************************
class CEnemySpawner
{
public:

	CEnemySpawner();
	~CEnemySpawner();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void SetEnemy(const D3DXVECTOR3 pos);

	/// <summary>
	/// 配列番号情報の取得
	/// </summary>
	/// <param name="nIdx">取得するインデックス</param>
	/// <returns></returns>
	CEnemy* GetEnemyIdx(const int nIdx) { return m_pEnemy[nIdx]; }

	/// <summary>
	/// 動的配列本体を取得する
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	std::vector<CEnemy*>& GetEnemy(void) { return m_pEnemy; }

private:

	std::vector<CEnemy*>m_pEnemy; //配列

	D3DXVECTOR3 m_SpawnPos; // スポナーの座標
};
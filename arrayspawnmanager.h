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
#include <array>

//*********************************************************
// 前方宣言
//*********************************************************
class CArraySpawner;
class CArrayManager;
class CTopAnt;

//*********************************************************
// 名前空間
//*********************************************************
namespace SpawnManager
{
	static constexpr int NUM_ARRAYSPAWNER = 3; // スポナーの数

	const D3DXVECTOR3 POS[NUM_ARRAYSPAWNER] =
	{
		{300.0f,0.0f,-300.0f},
		{-300.0f,0.0f,300.0f},
		{0.0f,0.0f,-550.0f}
	};

	const D3DXVECTOR3 TOP_POS[NUM_ARRAYSPAWNER] =
	{
		{300.0f,0.0f,-200.0f},
		{-300.0f,0.0f,200.0f},
		{0.0f,0.0f,-350.0f}
	};
};

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
	/// <param name="nIdx">取得したいスポナー番号</param>
	/// <returns></returns>
	CArraySpawner* GetIndexSpawner(const int& nIdx) { return m_pArraySpawner[nIdx]; }

private:

	CArraySpawner* m_pArraySpawner[SpawnManager::NUM_ARRAYSPAWNER]; // 所持するスポナー
};
//=========================================================
//
// 敵のスポナー複数管理処理 [ enemyspawnmanager.h ]
// Author: Asuma Nishio
// NOTE : ここら辺のオブジェクトの配置も外部ファイルで読み込む バイナリとかで
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
#include <array>

//*********************************************************
// 前方宣言
//*********************************************************
class CEnemySpawner;

//*********************************************************
// 名前空間
//*********************************************************
namespace SET_INFO
{
	static constexpr int CREATE_NUM = 4; // 最大生成数
	static constexpr int SPAWN_MIN = 5;       // 最小湧き数
	static constexpr int SPAWN_MAX = 8;       // 最大湧き数

	const D3DXVECTOR3 SpawnPos[CREATE_NUM] // スポーンの生成座標
	{
		{ 1125.0f,0.0f,308.0f },
		{ 1125.0f,0.0f,-308.0f },
		{ -1125.0f,0.0f,320.0f },
		{ -1125.0f,0.0f,-320.0f }
	};
};

//*********************************************************
// 複数スポナーの管理クラスを定義
//*********************************************************
class CEnemySpawnManager
{
public:

	CEnemySpawnManager();
	~CEnemySpawnManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	/// <summary>
	/// 各所のスポナーを取得する
	/// </summary>
	/// <param name="nIdx">取得するスポナーのインデックス番号</param>
	/// <returns></returns>
	CEnemySpawner* GetSpawner(const int& nIdx) { return m_pSpawners[nIdx]; }

private:

	std::array<CEnemySpawner*, SET_INFO::CREATE_NUM>m_pSpawners; // 敵のスポナー配列
};
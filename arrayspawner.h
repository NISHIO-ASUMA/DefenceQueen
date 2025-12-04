//=========================================================
//
// 各ポイントごとのスポーン処理 [ arrayspawner.h ]
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
class CArrayManager;

//*********************************************************
// 一個のスポナーに対する処理のクラスを定義
//*********************************************************
class CArraySpawner
{	
public:

	CArraySpawner();
	~CArraySpawner();

	HRESULT Init(CArrayManager * pManager);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	/// <summary>
	/// 移動命令を出す関数
	/// </summary>
	/// <param name="nNum">移動させる数</param>
	/// <param name="destPos">移動先の座標</param>
	void OrderMove(int nNum, const D3DXVECTOR3& destPos);

	void SetPos(const D3DXVECTOR3& pos) { m_SpawnBasePos = pos; }
	void SetMaxArray(const int& nMaxArray);

	/// <summary>
	/// ランダムに配置
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="fRadius"></param>
	/// <param name="nMoveActiveNum"></param>
	/// <param name="nIdx"></param>
	/// <returns></returns>
	D3DXVECTOR3 RandomSetPos(const D3DXVECTOR3& pos, float fRadius, int nMoveActiveNum, int nIdx);

	static CArraySpawner* Create(const D3DXVECTOR3 pos,const int nMaxArray, CArrayManager* pManager);

private:

	//****************************************
	// 定数構造体宣言
	//****************************************
	struct Config
	{
		static constexpr int MAX_STOCK = 50; // 最大保持数
	};

	D3DXVECTOR3 m_SpawnBasePos; // スポーンのベース座標
	int m_nStockArrays;			// 1スポナーが保持できるアリの数
	std::vector<CArray*> m_AssignedArrays; // 自分の担当アリ
};


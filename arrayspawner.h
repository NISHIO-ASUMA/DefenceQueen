//=========================================================
//
// 各ポイントごとのスポーン処理 [ arrayspawner.h ]
// Author: Asuma Nishio
// 
// TODO : トップをどう持つか考える
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
#include <array>

//*********************************************************
// 前方宣言
//*********************************************************
class CArray;
class CArrayManager;
class CTopAnt;

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
	void SetPos(const D3DXVECTOR3& pos) { m_SpawnBasePos = pos; }
	void SetMaxArray(const int& nMaxArray);

	/// <summary>
	/// 移動命令を出す関数
	/// </summary>
	/// <param name="nNum">移動させる数</param>
	/// <param name="destPos">移動先の座標</param>
	void OrderMove(int nNum, const D3DXVECTOR3& destPos);

	/// <summary>
	/// 基地にもどる命令をする
	/// </summary>
	/// <param name="nNum">戻す数</param>
	/// <param name="returnpos">戻したい座標</param>
	void OrderReturn(int nNum, const D3DXVECTOR3& returnpos);

	/// <summary>
	/// ランダムに配置
	/// </summary>
	/// <param name="pos">出現座標</param>
	/// <param name="fRadius">半径</param>
	/// <param name="nMoveActiveNum">移動させる数</param>
	/// <param name="nIdx">配列番号</param>
	/// <returns></returns>
	D3DXVECTOR3 RandomSetPos(const D3DXVECTOR3& pos, float fRadius, int nMoveActiveNum, int nIdx);

	/// <summary>
	/// トップアリを取得する関数
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	CTopAnt* GetTopAnt(void) { return m_pTopAnts; }

	/// <summary>
	/// アリのインデックスを設定する
	/// </summary>
	/// <param name="pArray">仲間アリのポインタ</param>
	/// <returns></returns>
	int GetArrayIndex(CArray* pArray);

	/// <summary>
	/// スポナーに格納されているアリをindexで取得
	/// </summary>
	/// <param name="index">指定番号</param>
	/// <returns></returns>
	CArray* GetArray(int index);

	/// <summary>
	/// ストックされているアリの数を取得する関数
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	int GetStockArray(void) { return m_nStockArrays; }

	D3DXVECTOR3 GetPos(void) { return m_SpawnBasePos; }

	/// <summary>
	/// 先頭の仲間のアリを取得
	/// </summary>
	/// <returns></returns>
	CArray* GetTopArray() const;

	/// <summary>
	/// 生成関数
	/// </summary>
	/// <param name="pos">出現座標</param>
	/// <param name="nMaxArray">最大保持数</param>
	/// <param name="pManager">管理クラスのポインタ</param>
	/// <returns></returns>
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
	CTopAnt * m_pTopAnts;	// トップアリの配列
	std::vector<CArray*> m_AssignedArrays; // 自分の担当アリ
	int m_nStockArrays;			// 1スポナーが保持できるアリの数
};
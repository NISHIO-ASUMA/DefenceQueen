//==========================================================
//
// 草の一括管理処理 [ grassmanager.h ]
// Author: Asuma Nishio
//
//==========================================================

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
class CGrass;

//*********************************************************
// 管理クラスを定義
//*********************************************************
class CGrassManager
{
public:
	
	CGrassManager();
	~CGrassManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void PushBack(CGrass* pNewGrass) { m_pGrass.push_back(pNewGrass); }

	/// <summary>
	/// 指定番号から取得
	/// </summary>
	/// <param name="nIdx">取得したいインデックス</param>
	/// <returns></returns>
	CGrass* GetGrass(const int nIdx) { return m_pGrass[nIdx]; }

	/// <summary>
	/// 動的配列そのものを取得
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	std::vector<CGrass*>& GetAll(void) { return m_pGrass; }

	/// <summary>
	/// 配列の要素数を返す
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	inline int GetSize(void) const { return static_cast<int>(m_pGrass.size()); }

	CGrass* CreateManager(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight);

private:

	void Load(void);		// 外部ファイル読み込み

	std::vector<CGrass*>m_pGrass; // 動的配列
};
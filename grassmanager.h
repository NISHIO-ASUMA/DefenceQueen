//=====================================
//
// 草の一括管理処理 [ grassmanager.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードガード
//**********************
#pragma once

//**********************
// インクルードファイル
//**********************
#include <vector>

//**********************
// 前方宣言
//**********************
class CGrass;

//**********************
// 管理クラスを定義
//**********************
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

	static CGrass* CreateManager(const D3DXVECTOR3 pos);

private:

	void Load(void);		// 外部ファイル読み込み

	std::vector<CGrass*>m_pGrass; // 動的配列
};
//=======================================
//
// ブロック管理処理 [ blockmanager.h ]
// Author: Asuma Nishio
//
//=======================================

//**********************
// インクルードガード
//**********************
#pragma once

//**********************
// インクルードファイル
//**********************
#include "block.h"
#include <vector>

//**********************
// 前方宣言
//**********************
class CBoxCollider;

//**********************************
// ブロック一括管理クラスを定義
//**********************************
class CBlockManager
{
public:

	CBlockManager();
	~CBlockManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	HRESULT Load();

	static int GetAll(void) { return static_cast<int>(m_pBlocks.size()); }
	static CBlock* GetBlock(const int nIdx) { return m_pBlocks[nIdx]; }
	static CBlock* CreateManager(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, const char* pModelName);

private:
	static std::vector<CBlock*>m_pBlocks; // 配置するブロックの動的配列
};
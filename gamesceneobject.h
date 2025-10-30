//===============================================
//
// ゲームのオブジェクト管理処理 [ gameobject.h ]
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
#include "score.h"
#include "object.h"
#include <memory>

//*************************
// 前方宣言
//*************************
class CBlockManager;

//************************************************
// ゲームシーンで使うオブジェクト管理クラスを定義
//************************************************
class CGameSceneObject
{
public:

	CGameSceneObject();
	~CGameSceneObject();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	static CScore* GetScore(void) { return m_pScore; } 
	CBlockManager* GetBlockManager(void) { return m_pBlocks.get(); }

private:

	std::unique_ptr<CBlockManager>m_pBlocks; // ブロックマネージャークラスのポインタ
	static CScore* m_pScore; // スコアクラスのポインタ
};
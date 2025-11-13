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
#include <memory>

//*************************
// 前方宣言
//*************************
class CBlockManager;
class CSelectPoint;
class CFeedManager;

//************************************************
// ゲームシーンで使うオブジェクト管理クラスを定義
//************************************************
class CGameSceneObject
{
public:

	~CGameSceneObject();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	CBlockManager* GetBlockManager(void) { return m_pBlocks.get(); }
	CSelectPoint* GetPoint(void) { return m_pSelectPoint; }
	CFeedManager* GetFeedManager(void) { return m_pFeed; }

	static CScore* GetScore(void) { return m_pScore; }
	static CGameSceneObject* GetInstance(void);

private:

	static CScore* m_pScore; // スコアクラスのポインタ
	static CGameSceneObject* m_pInstance;	// インスタンス

	std::unique_ptr<CBlockManager>m_pBlocks; // ブロックマネージャークラスのポインタ
	CSelectPoint* m_pSelectPoint;	// 選択ポイントのクラス
	CFeedManager* m_pFeed;			// 餌クラス
	
	CGameSceneObject();
};
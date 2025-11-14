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
class CTime;

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

	CScore* GetScore(void) { return m_pScore; }
	CTime* GetTime(void) { return m_pTimer; }
	CFeedManager* GetFeedManager(void) { return m_pFeed.get(); }
	CSelectPoint* GetPoint(void) { return m_pSelectPoint; }
	CBlockManager* GetBlockManager(void) { return m_pBlocks.get(); }

	static CGameSceneObject* GetInstance(void);

private:

	CGameSceneObject();
	
	static CGameSceneObject* m_pInstance;	// シングルトン変数

	CScore* m_pScore;	// スコアクラスのポインタ
	CTime* m_pTimer;	// タイマークラスのポインタ
	CSelectPoint* m_pSelectPoint;	// 選択ポイントのクラス
	std::unique_ptr<CFeedManager>m_pFeed;			// 餌管理クラスのポインタ
	std::unique_ptr<CBlockManager>m_pBlocks; // ブロックマネージャークラスのポインタ
	
};
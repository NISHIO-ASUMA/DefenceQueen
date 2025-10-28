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

private:
	static CScore* m_pScore; // スコアクラスのポインタ
};
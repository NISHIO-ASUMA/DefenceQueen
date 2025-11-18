//=======================================================
//
// 待機状態の末端ノード処理 [ waitleaf.h ]
// Author: Asuma Nishio
// 
// TODO : ここに待機時間を設定するかどうかは後々決める
//
//=======================================================

//*****************************
// インクルードガード
//*****************************
#pragma once

//*****************************
// インクルードファイル
//*****************************
#include "leafnodebase.h"

//*****************************
// 前方宣言
//*****************************
class CBlackBoard;

//******************************************
// 待機状態の処理をするノードクラスを定義
//******************************************
class CWaitLeaf : public CLeafNodeBase
{

public:

	CWaitLeaf(CBlackBoard* blackboard) : CLeafNodeBase(blackboard) {};
	~CWaitLeaf() = default;

	void Update() override
	{
		// 時間が0以下なら

		return;
	}

	void Exit() override
	{
		// 親クラスの終了処理
		CNodeBase::Exit();

		// 時間のカウントをもとに戻す
	}

private:

};
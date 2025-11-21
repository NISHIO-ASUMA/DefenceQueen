//=======================================================
//
// 敵の待機状態の末端ノード処理 [ enemywaitleaf.h ]
// Author: Asuma Nishio
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

//*****************************************
// 待機状態に切り替わるノードのクラス定義
//*****************************************
class CEnemyWaitLeaf : public CLeafNodeBase
{
public:

	CEnemyWaitLeaf(CBlackBoard* blackboard) : CLeafNodeBase(blackboard)  {};
	~CEnemyWaitLeaf() = default;

	void Update() override;

	NodeInfo::NodeResult get_node_result() const override
	{
		// 成功を返す
		return NodeInfo::NodeResult::Re_SUCCESS;
	};
};


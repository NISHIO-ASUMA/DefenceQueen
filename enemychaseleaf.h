//=======================================================
//
// 敵が対象物を追従する処理 [ enemychaseleaf.h ]
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

//*************************************************
// 敵が対象物を追従する末端ノードクラスを定義する
//*************************************************
class CEnemyChaseLeaf : public CLeafNodeBase
{
public:

	CEnemyChaseLeaf(CBlackBoard* blackboard) : CLeafNodeBase(blackboard) {};
	~CEnemyChaseLeaf() = default;

	void Update() override;

	NodeInfo::NodeResult get_node_result() const override
	{
		// 成功を返す
		return NodeInfo::NodeResult::Re_SUCCESS;
	};

private:

};
//===================================================================
//
// トップアリを追従する末端ノード処理 [ followtopleaf.h ]
// Author: Asuma Nishio
//
//===================================================================

//*******************************************************************
// インクルードガード
//*******************************************************************
#pragma once

//*******************************************************************
// インクルードファイル
//*******************************************************************
#include "leafnodebase.h"

//*******************************************************************
// トップアリを追従する末端ノードクラスを定義
//*******************************************************************
class CFolllowTopLeaf : public CLeafNodeBase
{
public:

	CFolllowTopLeaf(CBlackBoard* blackboard) : CLeafNodeBase(blackboard) {};
	~CFolllowTopLeaf() = default;

	void Update(void) override;

	NodeInfo::NodeResult get_node_result() const override
	{
		return NodeInfo::NodeResult::Re_SUCCESS;
	};

private:
};
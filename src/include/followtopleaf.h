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
class CFollowTopLeaf : public CLeafNodeBase
{
public:

	CFollowTopLeaf(CBlackBoard* blackboard) : CLeafNodeBase(blackboard), m_Result(NodeInfo::NodeResult::Re_RUNING){};
	~CFollowTopLeaf() = default;

	void Update(void) override;

	NodeInfo::NodeResult get_node_result() const override
	{
		return m_Result;
	};

private:

	NodeInfo::NodeResult m_Result;
};
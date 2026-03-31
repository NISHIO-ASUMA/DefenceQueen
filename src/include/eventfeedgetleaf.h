//===================================================================
//
// イベント餌取得に関する判別末端ノード処理 [ eventfeedgetleaf.h ]
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
// イベント餌取得判別末端ノード処理クラスを定義
//*******************************************************************
class CEventFeedGetLeaf : public CLeafNodeBase
{
public:

	CEventFeedGetLeaf(CBlackBoard* blackboard) : CLeafNodeBase(blackboard), m_Result(NodeInfo::NodeResult::Re_RUNING) {};
	~CEventFeedGetLeaf() = default;

	void Update(void);

	NodeInfo::NodeResult get_node_result() const override
	{
		// 判別結果を返す
		return 	m_Result;
	};

private:
	NodeInfo::NodeResult m_Result; // ノード判別フラグ
};
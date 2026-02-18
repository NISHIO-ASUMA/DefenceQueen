//===================================================================
//
// 順番にタスクをこなすシーケンスノードクラス [ sequence.h ]
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
#include "compositenodebase.h"

//*******************************************************************
// 前方宣言
//*******************************************************************
class CBlackBoard;

//*******************************************************************
// シーケンスクラスを定義
//*******************************************************************
class CSequence : public CCompositeNodeBase
{
public:

	CSequence(CBlackBoard* blackboard) : CCompositeNodeBase(blackboard) {};
	~CSequence() override = default; 

	void Update() override
	{
		m_ChildeNode[m_RanningIndex]->Update();
		auto result = m_ChildeNode[m_RanningIndex]->get_node_result();

		if (result == NodeInfo::NodeResult::Re_FAIL)
		{
			m_NodeResult = NodeInfo::NodeResult::Re_FAIL;
			Exit();
			return;
		}

		if (result == NodeInfo::NodeResult::Re_SUCCESS)
		{
			NodeIncrement();

			if (m_RanningIndex >= m_ChildeNode.size())
			{
				m_NodeResult = NodeInfo::NodeResult::Re_SUCCESS;
				Exit();
			}
			else
			{
				m_NodeResult = NodeInfo::NodeResult::Re_RUNING;
			}
			return;
		}

		m_NodeResult = NodeInfo::NodeResult::Re_RUNING;
	}

private:
	
	// 次のノードのインデックス番号取得関数
	const int GetNextIdx() const override
	{
		return m_RanningIndex + 1;
	};
};
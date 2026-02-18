//=========================================================
//
// 行動を選択するノードのクラス [ selector.h ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードガード
//*********************************************************
#pragma once

//*********************************************************
// インクルードファイル
//*********************************************************
#include "compositenodebase.h"

//*********************************************************
// 前方宣言
//*********************************************************
class CBlackBoard;

//*********************************************************
// 選択ノードクラスを定義
//*********************************************************
class CSelector : public CCompositeNodeBase
{
public:

	CSelector(CBlackBoard* blackboard) : CCompositeNodeBase(blackboard) {};
	~CSelector() override = default;

	void Update() override
	{
		// 現在ノードの更新処理
		m_ChildeNode[m_RanningIndex]->Update();

		// ノードの状態取得
		auto noderesult = m_ChildeNode[m_RanningIndex]->get_node_result();

		// 子が成功したら Selector 成功
		if (noderesult == NodeInfo::NodeResult::Re_SUCCESS)
		{
			m_NodeResult = NodeInfo::NodeResult::Re_SUCCESS;
			Exit();
			return;
		}

		// 子が失敗したら 次へ
		if (noderesult == NodeInfo::NodeResult::Re_FAIL)
		{
			NodeIncrement();

			// まだ子が残ってるなら RUNNING
			if (m_RanningIndex < m_ChildeNode.size())
			{
				m_NodeResult = NodeInfo::NodeResult::Re_RUNING;
				return;
			}
			else
			{
				// 全部失敗したら Selector 失敗
				m_NodeResult = NodeInfo::NodeResult::Re_FAIL;
				Exit();
				return;
			}
		}

		// RUNNINGはそのまま
		m_NodeResult = NodeInfo::NodeResult::Re_RUNING;
	}

private:

	// 次のノードのインデックス番号取得関数
	const int GetNextIdx() const override
	{
		return m_RanningIndex + 1;
	};
};
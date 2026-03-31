//=============================================================================
//
// トップの命令が終わって基地に帰還する末端ノード処理 [ cleanreturnnestleaf.h ]
// Author: Asuma Nishio
//
//=============================================================================

//*****************************************************************************
// インクルードガード
//*****************************************************************************
#pragma once

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "leafnodebase.h"

//*****************************************************************************
// 餌を取得して元の基地に帰還する行動ノードクラスを定義
//*****************************************************************************
class CCleanReturnNestLeaf : public CLeafNodeBase
{
public:

	CCleanReturnNestLeaf(CBlackBoard* blackboard) : CLeafNodeBase(blackboard), m_Result(NodeInfo::NodeResult::Re_RUNING) {};
	~CCleanReturnNestLeaf() = default;

	void Update(void);

	NodeInfo::NodeResult get_node_result() const override
	{
		return m_Result;
	};

private:
	NodeInfo::NodeResult m_Result; // 判別フラグ
};
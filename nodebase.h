//=======================================================
//
// AIノード基底クラス処理 [ nodebase.h ]
// Author: Asuma Nishio
//
//=======================================================

//**********************
// インクルードガード
//**********************
#pragma once 

//**********************
// インクルードファイル
//**********************
#include "node.h"
#include "blackboard.h"

//**********************
// 使用空間名宣言
//**********************
using namespace NodeInfo;

//*****************************
// ノードベースクラスを定義
//*****************************
class CNodeBase : public CNode
{
public:

	void set_node_id(const int id) override { mNodeId = id; }

private:
	int mNodeId = -1;

protected:

	CNodeBase(CBlackBoard* blackboard)
	{
		m_pBlackBoard = blackboard;
	}

	virtual ~CNodeBase() = default;

	virtual void Init() override { m_NodeResult = NodeInfo::NodeResult::Re_RUNING; }
	virtual void Update() override {};
	virtual void Exit() override {};

	virtual NodeInfo::NodeResult get_node_result() const { return m_NodeResult; }

	virtual int get_running_node_id() const override { return mNodeId; }

	CBlackBoard* m_pBlackBoard = nullptr;								// ブラックボードの変数
	NodeInfo::NodeResult m_NodeResult = NodeInfo::NodeResult::Re_IDLE;	// ノードの状態
};
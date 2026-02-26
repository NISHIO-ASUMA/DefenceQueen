//=========================================================
//
// 枝分かれノードクラス処理 [ branchnodebase.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "branchnodebase.h"

//=========================================================
// 初期化処理
//=========================================================
void CBranchNodeBase::Init()
{
	// 親クラスの初期化
	CNodeBase::Init();

	// 有効なら
	if (IsCondition())
	{
		// インデックス初期化
		m_nTrueIdx = static_cast<int>(BRANCH_NUM::BRANCH_NUM_TRUE);
	}
	else
	{
		m_nTrueIdx = static_cast<int>(BRANCH_NUM::BRANCH_NUM_FALSE);
	}

	// インデックスを使って対象ブランチのノードを初期化
	m_pBranchNode[m_nTrueIdx]->Init();
}
//=========================================================
// 更新処理
//=========================================================
void CBranchNodeBase::Update()
{
	// 判定だけ行う
	bool isResult = IsCondition();

	// true / false のindex決定
	m_nTrueIdx = isResult ? 
		static_cast<int>(BRANCH_NUM::BRANCH_NUM_TRUE) : 
		static_cast<int>(BRANCH_NUM::BRANCH_NUM_FALSE);

	// 選ばれたノードを実行
	if (m_pBranchNode[m_nTrueIdx] != nullptr)
	{
		m_pBranchNode[m_nTrueIdx]->Update();
		m_NodeResult = m_pBranchNode[m_nTrueIdx]->get_node_result();
	}
	else
	{
		m_NodeResult = NodeInfo::NodeResult::Re_FAIL;
	}
}
//=========================================================
// 終了処理
//=========================================================
void CBranchNodeBase::Exit()
{
	// 親クラスの終了処理
	CNodeBase::Exit();

	// 対象ブランチの終了処理
	m_pBranchNode[m_nTrueIdx]->Exit();

	// インデックス番号を変更
	m_nTrueIdx = static_cast<int>(BRANCH_NUM::BRANCH_NUM_FALSE);
}
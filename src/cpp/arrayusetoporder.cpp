//===================================================================
//
// 命令分岐をする判断ノードクラス [ arrayusetoporder.cpp ]
// Author: Asuma Nishio
//
//===================================================================

//*******************************************************************
// クラス定義ヘッダーファイル
//*******************************************************************
#include "arrayusetoporder.h"

//*******************************************************************
// インクルードファイル
//*******************************************************************
#include "array.h"

//===================================================================
// コンストラクタ
//===================================================================
CArrayUseTopOrder::CArrayUseTopOrder(CBlackBoard* blackboard, CNode* TrueNode, CNode* FalseNode) :
	CBranchNodeBase(blackboard, TrueNode, FalseNode)
{

}
//===================================================================
// ノード更新処理
//===================================================================
void CArrayUseTopOrder::Update(void)
{
	// ブラックボードから取得
	CArray::ARRAY_STATE state = m_pBlackBoard->GetValue<CArray::ARRAY_STATE>("CurrentState");

	// 結果に応じて判別ノードを変更
	int nNextIdx = (state != CArray::ARRAY_STATE::NORMAL) ? 0 : 1;

	// もし実行中のノードが切り替わったら、前のノードを終了させて新しい方を初期化する
	if (m_nTrueIdx != nNextIdx)
	{
		if (m_nTrueIdx != -1) m_pBranchNode[m_nTrueIdx]->Exit();
		m_nTrueIdx = nNextIdx;
		m_pBranchNode[m_nTrueIdx]->Init();
	}

	// 選択されたノードを更新
	m_pBranchNode[m_nTrueIdx]->Update();
}
//===================================================================
// 判別結果を返す処理
//===================================================================
const bool CArrayUseTopOrder::IsCondition()
{
	// 命令を受けているか判別する
	return m_pBlackBoard->GetValue<bool>("GetTopOrder");
}
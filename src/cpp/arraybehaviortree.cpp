//===================================================================
//
// 仲間アリのAIツリーを管理するクラス [ arraybehaviortree.cpp ]
// Author: Asuma Nishio
//
//===================================================================

//*******************************************************************
// クラス定義ヘッダーファイル
//*******************************************************************
#include "arraybehaviortree.h"

//*******************************************************************
// インクルードファイル
//*******************************************************************
#include "node.h"
#include "blackboard.h"
#include "inverter.h"
#include "sepuence.h"
#include "alwayssuccess.h"
#include "alwaysfail.h"
#include "selector.h"
#include "followtopleaf.h"
#include "waitorderleaf.h"
#include "attackenemyleaf.h"
#include "feedgetleaf.h"
#include "returnnestleaf.h"
#include "movetofeedleaf.h"
#include "arrayusetoporder.h"
#include "topordertomoveleaf.h"
#include "eventfeedgetleaf.h"
#include "cleanreturnnestleaf.h"

//===================================================================
// 仲間を動かすツリーノードを設定する処理
//===================================================================
CNode* ArrayTree::CArrayBehaviorTree::SetArrayTreeNode(CBlackBoard* blackboard)
{
	// シーケンスノードを作成する
	auto TopRootNode = new CSequence(blackboard);

	//==================================================
	// Topからの命令が true の時
	//==================================================
	auto ChainTopAntSequence = new CSequence(blackboard);
	{
		// 追従処理
		ChainTopAntSequence->AddNode(new CFollowTopLeaf(blackboard));

		// 切り離されて餌に向かう処理
		ChainTopAntSequence->AddNode(new CTopOrderToMoveLeaf(blackboard));

		// 餌獲得を判別する処理
		ChainTopAntSequence->AddNode(new CEventFeedGetLeaf(blackboard));

		// 自身が出てきた基地に帰還するノード処理
		ChainTopAntSequence->AddNode(new CCleanReturnNestLeaf(blackboard));
	}

	//==================================================
	// Topからの命令がfalseの時
	//==================================================
	auto ChainAntSequence = new CSequence(blackboard);
	{
		// 餌獲得ループのシーケンスノード
		auto FoodSequence = new CSequence(blackboard);

		// 餌に向かって行く末端ノード
		FoodSequence->AddNode(new CMoveToFeedLeaf(blackboard));

		// 餌獲得を判別する末端ノード
		FoodSequence->AddNode(new CFeedGetLeaf(blackboard));

		// 基地に帰ってくる末端ノード
		FoodSequence->AddNode(new CReturnNestLeaf(blackboard));

		// falseノードに餌獲得ノードを追加
		ChainAntSequence->AddNode(FoodSequence);
	}

	//=================================
	// 全体命令の判別ノードを作成する
	//=================================
	auto BranchTopsFlag = new CArrayUseTopOrder(blackboard, ChainTopAntSequence, ChainAntSequence);

	// ツリーの一番上のシーケンスノードに追加
	TopRootNode->AddNode(BranchTopsFlag);

	// 生成されたツリーノードのポインタを返す
	return TopRootNode;
}
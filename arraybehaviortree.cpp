//===================================================================
//
// 仲間アリのAIツリーを管理するクラス [ arraybehaviortree.cpp ]
// Author: Asuma Nishio
//
//===================================================================

//*******************************************************************
// インクルードファイル
//*******************************************************************
#include "arraybehaviortree.h"
#include "node.h"
#include "blackboard.h"
#include "inverter.h"
#include "sepuence.h"
#include "alwayssuccess.h"
#include "alwaysfail.h"
#include "selector.h"
#include "hastoporderleaf.h"
#include "folllowtopleaf.h"
#include "waitorderleaf.h"
#include "attackenemyleaf.h"
#include "feedgetleaf.h"
#include "returnnestleaf.h"
#include "movetofeedleaf.h"

//*******************************************************************
// 仲間を動かすツリーノードを設定する処理
//*******************************************************************
CNode* ArrayTree::CArrayBehaviorTree::SetArrayTreeNode(CBlackBoard* blackboard)
{
#if 0
	// トップルートのシーケンスノードを作成する
	auto TopRootNode = new CSequence(blackboard);

	// トップアリからの命令を受けたか判別するSelectorノードを作成し挙動を分岐させる
	auto IsGettingTopOrder = new CSelector(blackboard);

	//-----------------------------
	// Topの命令がtrueの時に走るノード
	//-----------------------------
	auto TopSequence = new CSequence(blackboard);	// Trueノードのシーケンスノードを作成する
	{
		// 判別用のフラグノードを作成する
		auto HasOrder = new CHasTopOrderLeaf(blackboard);

		// トップアリを追従するノードを作成する
		auto FollowTop = new CFolllowTopLeaf(blackboard);
		
		// 停止命令を待つノードを作成する
		auto WaitOrder = new CWaitOrderLeaf(blackboard);
		
		// 敵と戦うノードを作成する
		auto AttackLeaf = new CAttackEnemyLeaf(blackboard);

		// 末端ノードをシーケンスに追加する
		TopSequence->AddNode(HasOrder);
		TopSequence->AddNode(FollowTop);
		TopSequence->AddNode(WaitOrder);
		TopSequence->AddNode(AttackLeaf);
	}

	//-----------------------------
	// Topの命令がfalseの時に走るノード
	//-----------------------------
	auto ChainAntSequence = new CSequence(blackboard); 	// falseノードのシーケンスノードを作成する
	{
		// 結果を反転させるノードに設定
		ChainAntSequence->AddNode(new CInverter(blackboard, new CHasTopOrderLeaf(blackboard)));

		// 餌を取るシーケンスノードを作成
		auto FoodSequence = new CSequence(blackboard);

		// 餌に向かって進むノードを生成
		auto MoveToFeedNode = new CMoveToFeedLeaf(blackboard);
		
		// 餌にヒットしたかどうかの判別フラグノードを生成
		auto GetFeedLeafNode = new CFeedGetLeaf(blackboard);

		// 基地に帰るノードを生成
		auto ReturnNode = new CReturnNestLeaf(blackboard);

		// 餌をとるシーケンスに子ノードを追加する
		FoodSequence->AddNode(MoveToFeedNode);
		FoodSequence->AddNode(GetFeedLeafNode);
		FoodSequence->AddNode(ReturnNode);

		// メインのシーケンスに追加する
		ChainAntSequence->AddNode(FoodSequence);	
	}

	//------------------------------------
	// セレクターに分岐先を追加
	//------------------------------------
	{
		IsGettingTopOrder->AddNode(TopSequence);
		IsGettingTopOrder->AddNode(ChainAntSequence);
	}

	//------------------------------------
	// 生成されたセレクターノードを組み合わせる
	//------------------------------------
	{
		TopRootNode->AddNode(IsGettingTopOrder);
	}

	// 組み合わされたノードを返す
	return TopRootNode;
#else
	// トップをセレクターノードにする
	auto TopRootNode = new CSelector(blackboard);

	//-----------------------------
	// Topの命令がtrueの時
	//-----------------------------
	auto TopSequence = new CSequence(blackboard);
	{
		TopSequence->AddNode(new CHasTopOrderLeaf(blackboard));
		TopSequence->AddNode(new CFolllowTopLeaf(blackboard));
		TopSequence->AddNode(new CWaitOrderLeaf(blackboard));
		TopSequence->AddNode(new CAttackEnemyLeaf(blackboard));
	}

	//-----------------------------
	// Topの命令がfalseの時
	//-----------------------------
	auto ChainAntSequence = new CSequence(blackboard);
	{
		ChainAntSequence->AddNode(new CInverter(blackboard, new CHasTopOrderLeaf(blackboard)));

		auto FoodSequence = new CSequence(blackboard);
		FoodSequence->AddNode(new CMoveToFeedLeaf(blackboard));
		FoodSequence->AddNode(new CFeedGetLeaf(blackboard));
		FoodSequence->AddNode(new CReturnNestLeaf(blackboard));

		ChainAntSequence->AddNode(FoodSequence);
	}

	//------------------------------------
	// ルートノードに追加する
	//------------------------------------
	TopRootNode->AddNode(TopSequence);
	TopRootNode->AddNode(ChainAntSequence);

	return TopRootNode;
#endif
}
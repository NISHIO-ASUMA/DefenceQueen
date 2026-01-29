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
		TopSequence->AddNode(new CHasTopOrderLeaf(blackboard));	// 命令を受けたか判別する末端ノード
		TopSequence->AddNode(new CFolllowTopLeaf(blackboard));	// トップを追従する末端ノード
		TopSequence->AddNode(new CWaitOrderLeaf(blackboard));	// 命令を待つ末端ノード
		TopSequence->AddNode(new CAttackEnemyLeaf(blackboard));	// 敵を攻撃する末端ノード
	}

	//-----------------------------
	// Topの命令がfalseの時
	//-----------------------------
	auto ChainAntSequence = new CSequence(blackboard);
	{
		// インバーターに判別ノードを設定
		ChainAntSequence->AddNode(new CInverter(blackboard, new CHasTopOrderLeaf(blackboard)));

		auto FoodSequence = new CSequence(blackboard); // 餌獲得ループのシーケンスノードを作成

		FoodSequence->AddNode(new CMoveToFeedLeaf(blackboard)); // 餌に向かって行く末端ノード
		FoodSequence->AddNode(new CFeedGetLeaf(blackboard));	// 餌獲得を判別する末端ノード
		FoodSequence->AddNode(new CReturnNestLeaf(blackboard));	// 基地に帰ってくる末端ノード

		// falseノードに餌獲得ノードを追加
		ChainAntSequence->AddNode(FoodSequence);
	}

	//------------------------------------
	// ツリーの一番上のルートノードに追加する
	//------------------------------------
	TopRootNode->AddNode(TopSequence);
	TopRootNode->AddNode(ChainAntSequence);

	// 生成されたツリーノードのポインタを返す
	return TopRootNode;
#endif
}
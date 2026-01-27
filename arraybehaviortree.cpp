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

//*******************************************************************
// 実際の仲間を動かすツリーノードを設定する
//*******************************************************************
CNode* ArrayTree::CArrayBehaviorTree::SetArrayTreeNode(CBlackBoard* blackboard)
{
	// TOPのシーケンスノードを作成する
	auto TopRootNode = new CSequence(blackboard);

	// トップアリからの命令を受けたか判別するSelectorノードを作成し挙動を分岐させる
	auto IsGettingTopOrder = new CSelector(blackboard);

	//-----------------------------
	// Topの命令がtrueの時に走るノード
	//-----------------------------
	auto TopSequence = new CSequence(blackboard); // Trueノードのシーケンスノードを作成する
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

		// ブランチに追加する
		//FoodSequence->AddNode(new CMoveToFoodLeaf(blackboard)); // 餌に向かう
		//FoodSequence->AddNode(new CGetFoodLeaf(blackboard));    // 餌に当たって取得
		//FoodSequence->AddNode(new CReturnNestLeaf(blackboard)); // 基地に帰る

		// メインのシーケンスに追加する
		ChainAntSequence->AddNode(FoodSequence);	
	}

	//-----------------------------
	// 生成されたノードを組み合わせる
	//-----------------------------
	{
		TopRootNode->AddNode(TopSequence); // trueノード
		TopRootNode->AddNode(ChainAntSequence); // falseノード
	}

	// 組み合わされたノードを返す
	return TopRootNode;
}

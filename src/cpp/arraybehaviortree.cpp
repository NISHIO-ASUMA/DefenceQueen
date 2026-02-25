//===================================================================
//
// 仲間アリのAIツリーを管理するクラス [ arraybehaviortree.cpp ]
// Author: Asuma Nishio
//
//===================================================================

//*******************************************************************
// TODO : ここに一個ブランチノードベースを継承したノードを一個入れると解決するはず
// 
//*******************************************************************

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
	// トップをセレクターノードにする
	auto TopRootNode = new CSelector(blackboard);

	// Topからの命令が true の時
	auto ChainTopAntSequence = new CSequence(blackboard);
	{
		// フラグ判定
		ChainTopAntSequence->AddNode(new CHasTopOrderLeaf(blackboard));

		// Top命令時の行動
		ChainTopAntSequence->AddNode(new CFolllowTopLeaf(blackboard));
	}

	// Topからの命令がfalseの時
	auto ChainAntSequence = new CSequence(blackboard);
	{
		// インバーターに判別ノードを設定
		ChainAntSequence->AddNode
		(
			new CInverter(blackboard, 
			new CHasTopOrderLeaf(blackboard))
		);

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

	// Selector に追加
	TopRootNode->AddNode(ChainTopAntSequence);	// トップのノード
	TopRootNode->AddNode(ChainAntSequence);		// 餌獲得ループのノード

	// 生成されたツリーノードのポインタを返す
	return TopRootNode;
}
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
	// トップをセレクターノードにする
	auto TopRootNode = new CSelector(blackboard);

	//-----------------------------
	// Topの命令がfalseの時
	//-----------------------------
	auto ChainAntSequence = new CSequence(blackboard);
	{
		// インバーターに判別ノードを設定
		ChainAntSequence->AddNode(new CInverter(blackboard, new CHasTopOrderLeaf(blackboard)));

		auto FoodSequence = new CSequence(blackboard);			// 餌獲得ループのシーケンスノードを作成

		FoodSequence->AddNode(new CMoveToFeedLeaf(blackboard)); // 餌に向かって行く末端ノード
		FoodSequence->AddNode(new CFeedGetLeaf(blackboard));	// 餌獲得を判別する末端ノード
		FoodSequence->AddNode(new CReturnNestLeaf(blackboard));	// 基地に帰ってくる末端ノード

		// falseノードに餌獲得ノードを追加
		ChainAntSequence->AddNode(FoodSequence);
	}

	//------------------------------------
	// ツリーの一番上のルートノードに追加する
	//------------------------------------
	TopRootNode->AddNode(ChainAntSequence);

	// 生成されたツリーノードのポインタを返す
	return TopRootNode;
}
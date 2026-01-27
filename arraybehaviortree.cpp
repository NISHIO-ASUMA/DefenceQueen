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

//*******************************************************************
// 実際の仲間を動かすツリーノードを設定する
//*******************************************************************
CNode* ArrayTree::CArrayBehaviorTree::SetArrayTreeNode(CBlackBoard* blackboard)
{
	// TOPのシーケンスノードを作成する (ツリー構造の一番トップ)
	auto TopRootNode = new CSequence(blackboard);

	// トップアリからの命令を受けたか判別するSelectorノードを作成し挙動を分岐させる
	auto IsGettingTopOrder = new CSelector(blackboard);

	//-----------------------------
	// Topの命令がtrueの時に走るノード
	//-----------------------------
	{
		// Trueノードのシーケンスノードを作成する
		auto TopSequence = new CSequence(blackboard);
		
		// 判別用のフラグノードを作成する
		auto HasOrder = new CHasTopOrderLeaf(blackboard);

		// トップアリを追従するノードを作成する
		//auto FollowTop = new 
		
		// 停止命令を待つノードを作成する
		// auto WaitorderTop = new
		
		// 命令後、自身で起こすアクションノードを作成する
		// auto ActionSetNode = new 
	}

	//-----------------------------
	// Topの命令がfalseの時に走るノード
	//-----------------------------
	{
		// falseノードのシーケンスノードを作成する
		auto ChainAntSequence = new CSequence(blackboard);

		// 追従して歩くノードを作成する
		// auto TagetFollow = new 
	}
#if 0
	// 
	Sequence->AddNode(new CArrayCheckNear(blackboard, new CAlwaysSuccessLeaf(blackboard), chaseinverter, 100.0f));

	// 追従をするノードをシーケンスノードに追加
	Sequence->AddNode(new CEnemyChaseLeaf(blackboard));

	// 敵を攻撃するノードを生成
	auto attackLoop = new CArrayAttackLeaf(blackboard);

	// 餌を取得するノードを生成
	auto getFood = new CArrayGetFeedLeaf(blackboard);
	auto returnToNest = new CArrayReturnLeaf(blackboard);

	// 食料取得後は巣へ戻るためのSequenceノードを作成
	auto foodSequence = new CSequence(blackboard);
	foodSequence->AddNode(getFood);
	foodSequence->AddNode(returnToNest);

	// 攻撃するか餌を持ち帰るかのセレクター用のノードを生成する
	auto Selector = new CSelector(blackboard);

	Selector->AddNode(attackLoop);		// 成功したらずっと攻撃し続ける
	Selector->AddNode(foodSequence);	//  失敗したら餌を持って帰る

	// セレクターノードを根幹のシーケンスに追加する
	Sequence->AddNode(Selector);

	// 待機時用のノードをシーケンスノードに追加
	Sequence->AddNode(new CEnemyWaitLeaf(blackboard));

	// 作成されたシーケンスノードを返す
	return Sequence;
#endif
	return TopRootNode;
}

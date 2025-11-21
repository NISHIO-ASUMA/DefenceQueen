//=========================================================
//
// 敵のAIツリーを管理するクラス [ enemybehaviortree.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//***********************************
// インクルードファイル
//***********************************
#include "enemybehaviortree.h"
#include "node.h"
#include "inverter.h"
#include "sepuence.h"
#include "alwayssuccess.h"
#include "enemychaseleaf.h"
#include "enemychecknear.h"
#include "enemywaitleaf.h"
#include "selector.h"

//===================================
// 実際のツリーを生成する
//===================================
CNode* EnemyTree::CEnemyBehaviorTree::SetEnemyTreeNode(CBlackBoard* blackboard)
{
#if 1
	// ルートセレクターを作成する
	auto chase_inverter = new CInverter(blackboard, new CEnemyChaseLeaf(blackboard));

	// Sequenceノードを作成する
	auto Sequence = new CSequence(blackboard);

	// 近いかどうかのノード作成
	Sequence->AddNode(new CEnemyCheckNear(blackboard, new CAlwaysSuccessLeaf(blackboard), chase_inverter, 100.0f));

	// 追従ノードをセレクターノードに追加
	Sequence->AddNode(new CEnemyChaseLeaf(blackboard));

	// 待機時ノードセレクターノードに追加
	Sequence->AddNode(new CEnemyWaitLeaf(blackboard));

	// 作成されたルートセレクターノードを返す
	return Sequence;
#else
	// Inverterノードを作成する
	auto chase_inverter = new CInverter(blackboard, new CChaseDestinationLeaf(blackboard));

	// Sequenceノードを作成する
	auto Sequence = new CSequence(blackboard);

	// 近いかどうかのノード作成
	Sequence->AddNode(new CCheckNearDestination(blackboard, new CAlwaysSuccessLeaf(blackboard), chase_inverter, 100.0f));

	// 追従ノードを作成
	Sequence->AddNode(new CChaseDestinationLeaf(blackboard));

	// 待機時のノード作成
	Sequence->AddNode(new CWaitLeaf(blackboard));

	// 作成されたSequenceを返す
	return Sequence;
#endif
}
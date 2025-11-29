//=========================================================
//
// 敵のAIツリーを管理するクラス [ enemybehaviortree.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "enemybehaviortree.h"
#include "node.h"
#include "inverter.h"
#include "sepuence.h"
#include "alwayssuccess.h"
#include "enemychaseleaf.h"
#include "enemychecknear.h"
#include "enemywaitleaf.h"
#include "selector.h"

//=========================================================
// 実際のツリーを生成する
//=========================================================
CNode* EnemyTree::CEnemyBehaviorTree::SetEnemyTreeNode(CBlackBoard* blackboard)
{
	// インバーターを作成する
	auto chase_inverter = new CInverter(blackboard, new CEnemyChaseLeaf(blackboard));

	// シーケンスノードを作成する
	auto Sequence = new CSequence(blackboard);

	// 近いかどうかチェックするノード作成
	Sequence->AddNode(new CEnemyCheckNear(blackboard, new CAlwaysSuccessLeaf(blackboard), chase_inverter, 100.0f));

	// 追従をするノードをシーケンスノードに追加
	Sequence->AddNode(new CEnemyChaseLeaf(blackboard));

	// 待機時用のノードをシーケンスノードに追加
	Sequence->AddNode(new CEnemyWaitLeaf(blackboard));

	// 作成されたシーケンスノードを返す
	return Sequence;
}
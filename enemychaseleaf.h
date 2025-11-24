//=========================================================
//
// 敵が対象物を追従する処理 [ enemychaseleaf.h ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードガード
//*********************************************************
#pragma once

//*********************************************************
// インクルードファイル
//*********************************************************
#include "leafnodebase.h"

//*********************************************************
// 前方宣言
//*********************************************************
class CBlackBoard;

//*********************************************************
// 敵が対象物を追従する末端ノードクラスを定義する
//*********************************************************
class CEnemyChaseLeaf : public CLeafNodeBase
{
public:

	CEnemyChaseLeaf(CBlackBoard* blackboard) : CLeafNodeBase(blackboard) {};
	~CEnemyChaseLeaf() = default;

	void Update() override;

	NodeInfo::NodeResult get_node_result() const override
	{
		// 成功を返す
		return NodeInfo::NodeResult::Re_SUCCESS;
	};

private:

	//**************************
	// 定数格納構造体
	//**************************
	struct ChaseInfo
	{
		static constexpr float DISTANCE = 100.0f; // 最大追従距離
		static constexpr float SPEED = 4.0f;	  // 移動速度
	};
};
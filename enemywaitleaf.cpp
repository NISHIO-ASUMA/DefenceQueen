//=======================================================
//
// 敵の待機状態の末端ノード処理 [ enemywaitleaf.cpp ]
// Author: Asuma Nishio
//
//=======================================================

//*****************************
// インクルードファイル
//*****************************
#include "enemywaitleaf.h"
#include "enemy.h"

//=============================
// ノード更新処理
//=============================
void CEnemyWaitLeaf::Update()
{
	// 敵のポインタ
	auto* Enemy = m_pBlackBoard->GetValue<CEnemy*>("Enemy");

	// 移動量を0にする
	Enemy->SetMove(VECTOR3_NULL);

	// モーションセット
	Enemy->GetMotion()->SetMotion(CEnemy::MOTION_NEUTRAL,true,10);
}

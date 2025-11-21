//=======================================================
//
// 敵が対象物を追従する処理 [ enemychaseleaf.cpp ]
// Author: Asuma Nishio
//
//=======================================================

//*****************************
// インクルードファイル
//*****************************
#include "enemychaseleaf.h"
#include "enemy.h"
#include "selectpoint.h"
#include "template.h"

//=============================
// ノード更新処理
//=============================
void CEnemyChaseLeaf::Update()
{
	// 対象物の目的の座標を取得する
	auto ChaseToDest = m_pBlackBoard->GetValue<CSelectPoint*>("Selector");
	auto DestPos = m_pBlackBoard->GetValue<D3DXVECTOR3>("SelectorPos");

	// 追従する自分を取得する
	auto* DestObject = m_pBlackBoard->GetValue<CEnemy*>("Enemy");

	// 追従するためのベクトルを引く
	auto VecToDestObj = DestPos - DestObject->GetPos();
	float dist = D3DXVec3Length(&VecToDestObj);

	float stopDist = 100.0f; // 停止

	// 停止距離外なら
	if (dist > stopDist)
	{
		// 正規化
		D3DXVec3Normalize(&VecToDestObj, &VecToDestObj);

		// 移動速度
		float speed = 8.0f;

		// 速度を乗算する
		VecToDestObj *= speed;

		// 計算角度
		float angleY = atan2(-VecToDestObj.x, -VecToDestObj.z);
		D3DXVECTOR3 rotDest = DestObject->GetRotDest();
		rotDest.y = angleY;
		rotDest.y = NormalAngle(rotDest.y);

		// 目的角を更新
		DestObject->SetRotDest(rotDest);

		// 移動量をセット
		DestObject->SetMove(VecToDestObj);

		// モーションセット
		DestObject->GetMotion()->SetMotion(CEnemy::MOTION_MOVE);
	}
	else
	{
		// 一定の距離なら動かない
		DestObject->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		// モーションセット
		DestObject->GetMotion()->SetMotion(CEnemy::MOTION_NEUTRAL, true, 10);
	}
}
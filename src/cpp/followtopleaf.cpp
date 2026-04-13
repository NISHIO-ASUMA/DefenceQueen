//===================================================================
//
// トップアリを追従する末端ノード処理 [ followtopleaf.cpp ]
// Author: Asuma Nishio
//
//===================================================================

//*******************************************************************
// クラス定義ヘッダーファイル
//*******************************************************************
#include "followtopleaf.h"

//*******************************************************************
// インクルードファイル
//*******************************************************************
#include "array.h"

//===================================================================
// トップを追従する末端ノードの更新処理
//===================================================================
void CFollowTopLeaf::Update(void)
{
	// アリを取得
	const auto& Array = m_pBlackBoard->GetValue<CArray*>("Array");

	// ステートが [ASSAULT] になっていたら次のステップに移行する
	if (Array->GetState() == CArray::ARRAY_STATE::ASSAULT)
	{
		m_Result = NodeInfo::NodeResult::Re_SUCCESS;
		return;
	}

	// 目的地の決定
	D3DXVECTOR3 targetPos;

	// 自身に「前のアリ」が設定されているか確認
	CArray* pTargetAnt = Array->GetPrevAnt();

	if (pTargetAnt != nullptr)
	{
		// 前のアリの現在座標を目的地にする
		targetPos = pTargetAnt->GetPos();

		// 前のアリとの距離に応じて移動・停止を制御
		// FollowTopを流用するか、仲間用のArrayFollowを呼ぶ
		Array->FollowTop(targetPos);
	}
	else
	{
		// Blackboardにある黄色アリの座標を追う
		targetPos = m_pBlackBoard->GetValue<D3DXVECTOR3>("TopPos");
		Array->FollowTop(targetPos);
	}

	// 実行状態に設定
	m_Result = NodeInfo::NodeResult::Re_RUNING;
}
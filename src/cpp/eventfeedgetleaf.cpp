//===================================================================
//
// イベント餌取得に関する判別末端ノード処理 [ eventfeedgetleaf.cpp ]
// Author: Asuma Nishio
//
//===================================================================

//*******************************************************************
// クラス定義ヘッダーファイル
//*******************************************************************
#include "eventfeedgetleaf.h"

//*******************************************************************
// インクルードファイル
//*******************************************************************
#include "array.h"

//===================================================================
// イベントの餌を確保するノードの更新処理
//===================================================================
void CEventFeedGetLeaf::Update(void)
{
	// キャラクター取得
	const auto& Ant = m_pBlackBoard->GetValue<CArray*>("Array");

	// イベントの餌とのコリジョン関数
	Ant->CollisionEventFeed();

	// フラグ格納変数
	bool IsReturn = false;

	// キー情報が見つかったら判別フラグを取得
	if (m_pBlackBoard->HasKeyData("ReturnSpawn"))
		IsReturn = m_pBlackBoard->GetValue<bool>("ReturnSpawn");

	// 餌獲得で終了
	if (IsReturn)
	{
		// タイマーリセット
		m_pBlackBoard->SetValue("WaitTimer", 0);
		m_Result = NodeInfo::NodeResult::Re_SUCCESS;
	}
	else
	{
		m_Result = NodeInfo::NodeResult::Re_RUNING;
	}
}
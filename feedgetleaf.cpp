//===================================================================
//
// 餌取得に関する判別末端ノード処理 [ feedgetleaf.cpp ]
// Author: Asuma Nishio
//
//===================================================================

//*******************************************************************
// インクルードファイル
//*******************************************************************
#include "feedgetleaf.h"
#include "array.h"

//===================================================================
// 更新処理
//===================================================================
void CFeedGetLeaf::Update(void)
{
	// フラグ格納変数
	bool IsReturn = false;

	// キー情報が見つかったら
	if (m_pBlackBoard->HasKeyData("ReturnSpawn"))
	{
		// 判別フラグを取得
		IsReturn = m_pBlackBoard->GetValue<bool>("ReturnSpawn");
	}

	// ノード結果を設定する
	if (IsReturn)
		m_Result = NodeInfo::NodeResult::Re_SUCCESS;
	else
		m_Result = NodeInfo::NodeResult::Re_RUNING;
}
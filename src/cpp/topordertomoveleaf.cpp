//===================================================================
//
// トップからの命令を受け餌を取る末端ノード [ topordertomoveleaf.cpp ]
// Author: Asuma Nishio
//
//===================================================================

//*******************************************************************
// クラス定義ヘッダーファイル
//*******************************************************************
#include "topordertomoveleaf.h"

//*******************************************************************
// インクルードファイル
//*******************************************************************
#include "array.h"
#include "arraymanager.h"

//===================================================================
// トップからの命令を受けて餌に向かうノードの更新処理
//===================================================================
void CTopOrderToMoveLeaf::Update(void)
{

	// アリを取得
	const auto& Array = m_pBlackBoard->GetValue<CArray*>("Array");
	if (!Array) m_Result = NodeInfo::NodeResult::Re_FAIL;

	// [ASSAULT]ステートの間だけ移動を実行
	if (Array->GetState() == CArray::ARRAY_STATE::ASSAULT)
	{
		// 目的の餌に向かう処理
		Array->MoveDest();
	}

	// 目的地に着いたら [SUCCESS] に変更
	bool IsNear = m_pBlackBoard->GetValue<bool>("CheckNearFeed");
	if (IsNear)
	{
		// 次のノードへ
		m_Result = NodeInfo::NodeResult::Re_SUCCESS;
	}
	else
	{
		// 現在ノードを継続
		m_Result = NodeInfo::NodeResult::Re_RUNING;
	}
}
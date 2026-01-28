//===================================================================
//
// トップアリを追従する末端ノード処理 [ followtopleaf.cpp ]
// Author: Asuma Nishio
//
//===================================================================

//*******************************************************************
// インクルードファイル
//*******************************************************************
#include "folllowtopleaf.h"
#include "array.h"
#include "topant.h"

//===================================================================
// 更新処理
//===================================================================
void CFolllowTopLeaf::Update(void)
{
	// アリを取得
	const auto& Array = m_pBlackBoard->GetValue<CArray*>("Array");
	const auto& Top = m_pBlackBoard->GetValue<CTopAnt*>("TopAnt");

	// 追従する関数を実行する
	Array->FollowDestination(Top->GetPos());
}
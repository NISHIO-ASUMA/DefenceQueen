//=============================================================================
//
// トップの命令が終わって基地に帰還する末端ノード処理 [ cleanreturnnestleaf.cop ]
// Author: Asuma Nishio
//
//=============================================================================

//*****************************************************************************
// クラス定義ヘッダーファイル
//*****************************************************************************
#include "cleanreturnnestleaf.h"

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "array.h"

//=============================================================================
// 更新処理
//=============================================================================
void CCleanReturnNestLeaf::Update(void)
{
	// アリを取得
	const auto& Array = m_pBlackBoard->GetValue<CArray*>("Array");
	if (!Array) m_Result = NodeInfo::NodeResult::Re_FAIL;

	// [RETURN]ステートなら帰還処理を実行
	if (Array->GetState() == CArray::ARRAY_STATE::RETURN)
	{
		// 基地に帰る
		Array->SpawnReturn();
	}

	// 基地に着いて [NORMAL] に戻っていたら SUCCESS
	if (Array->GetState() == CArray::ARRAY_STATE::NORMAL)
	{
		// 保存していた座標に向かうように変更する
		Array->SetDestPos(Array->GetSavePos());

		// 成功結果を返す
		m_Result = NodeInfo::NodeResult::Re_SUCCESS;
		return;
	}
	else
	{
		m_Result = NodeInfo::NodeResult::Re_RUNING;
	}
}
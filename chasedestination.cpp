//===================================================================
//
// 目的の任意の場所に移動するノードの処理 [ chasedestination.h ]
// Author: Asuma Nishio
//
//===================================================================

//*************************************************
// インクルードファイル
//*************************************************
#include "chasedestination.h"
#include "selectpoint.h"
#include "enemy.h"

//=================================================
// コンストラクタ
//=================================================
CChaseDestinationLeaf::CChaseDestinationLeaf(CBlackBoard* blackboard)
	: CLeafNodeBase(blackboard)
{

}
//=================================================
// 更新関数
//=================================================
void CChaseDestinationLeaf::Update()
{
	// 対象物の目的の座標を取得する
	auto DestPos = m_pBlackBoard->GetValue<D3DXVECTOR3>("SelectorPos");

	// 追従する自分を取得する ( 今回は敵 )
	auto* DestObject = m_pBlackBoard->GetValue<CEnemy*>("Enemy");

	// 追従するためのベクトルを引く
	auto VecToDestObj = DestPos - DestObject->GetPos();

	// 移動量を加算する
	DestObject->SetMove(VecToDestObj);
}

//=====================================================
//
// ニュートラル状態管理処理 [ playerstateneutral.cpp ]
// Author: Asuma Nishio
//
//=====================================================

//**********************
// インクルードファイル
//**********************
#include "playerstateneutral.h"

//==============================
// コンストラクタ
//==============================
CPlayerStateNeutral::CPlayerStateNeutral()
{
	// IDセット
	SetID(ID_NEUTRAL);
}
//==============================
// デストラクタ
//==============================
CPlayerStateNeutral::~CPlayerStateNeutral()
{

}
//===============================
// 開始関数
//===============================
void CPlayerStateNeutral::OnStart()
{
	// モーションセット
	m_pPlayer->GetMotion()->SetMotion(CPlayer::MOTION_NEUTRAL, true, 10);
}
//===============================
// 更新関数
//===============================
void CPlayerStateNeutral::OnUpdate()
{

}
//===============================
// 終了関数
//===============================
void CPlayerStateNeutral::OnExit()
{

}
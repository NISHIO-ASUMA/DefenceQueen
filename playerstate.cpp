//=============================================
//
// プレイヤー状態管理処理 [ playerstate.cpp ]
// Author: Asuma Nishio
//
//=============================================

//**************************
// インクルードファイル宣言
//**************************
#include "playerstate.h"
#include "state.h"
#include "manager.h"
#include "gamemanager.h"
#include "pausemanager.h"
#include "input.h"

//==================================
// プレイヤー状態コンストラクタ
//==================================
CPlayerStateBase::CPlayerStateBase()
{
	// 値のクリア
	m_pPlayer = nullptr;
	m_ID = ID_NEUTRAL;
}
//==================================
// プレイヤー状態デストラクタ
//==================================
CPlayerStateBase::~CPlayerStateBase()
{
	// 無し
}


//==================================
// 待機状態時コンストラクタ
//==================================
CPlayerStateNeutral::CPlayerStateNeutral()
{
	// セット
	SetID(ID_NEUTRAL);
}
//==================================
// 待機状態時デストラクタ
//==================================
CPlayerStateNeutral::~CPlayerStateNeutral()
{
	// 無し
}
//==================================
// 待機状態開始関数
//==================================
void CPlayerStateNeutral::OnStart()
{
#if 0
	// 直前が着地なら
	if (m_pPlayer->GetMotion()->GetMotionType() == CPlayer::MOTION_LANDING)
	{
		// ニュートラルモーションに設定
		m_pPlayer->GetMotion()->SetMotion(CPlayer::MOTION_NEUTRAL, false, 0, false);
	}
	else
	{
		// ニュートラルモーションに設定
		m_pPlayer->GetMotion()->SetMotion(CPlayer::MOTION_NEUTRAL, true, 5, false);
	}
#endif
}
//==================================
// 待機状態更新関数
//==================================
void CPlayerStateNeutral::OnUpdate()
{
#if 0
	// キー入力情報の取得
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad* pPad = CManager::GetJoyPad();

	// Damage中は一切入力を受け付けない
	if (m_pPlayer->GetStateMachine()->GetNowStateID() == ID_DAMAGE) return;

	// 移動入力があれば移動状態へ
	if ((m_pPlayer->isMoveInputKey(pInput) || m_pPlayer->isMovePadButton(pPad) || pPad->GetLeftStick()) &&
		m_pPlayer->GetNowMotion() != CPlayer::MOTION_DAMAGE)
	{
		// 状態変更
		m_pPlayer->ChangeState(new CPlayerStateMove, ID_MOVE);

		// ここで処理を返す
		return;
	}
#endif
}
//==================================
// 待機状態時終了関数
//==================================
void CPlayerStateNeutral::OnExit()
{
	// 無し
}


//==================================
// コンストラクタ
//==================================
CPlayerStateAction::CPlayerStateAction()
{
	// セット
	SetID(ID_ACTION);
}
//==================================
// デストラクタ
//==================================
CPlayerStateAction::~CPlayerStateAction()
{
	// 無し
}
//==================================
// 攻撃状態開始関数
//==================================
void CPlayerStateAction::OnStart()
{
}
//==================================
// 攻撃状態更新関数
//==================================
void CPlayerStateAction::OnUpdate()
{

	// 入力情報の取得
	CInputKeyboard* pInput = CManager::GetInstance()->GetInputKeyboard();
	CJoyPad * pPad = CManager::GetInstance()->GetJoyPad();
}
//==================================
// 攻撃状態終了関数
//==================================
void CPlayerStateAction::OnExit()
{
	// 無し
}


//==================================
// 移動状態コンストラクタ
//==================================
CPlayerStateMove::CPlayerStateMove()
{
	// セット
	SetID(ID_MOVE);
}
//==================================
// 移動状態デストラクタ
//==================================
CPlayerStateMove::~CPlayerStateMove()
{
	// 無し
}
//==================================
// 移動状態開始関数
//==================================
void CPlayerStateMove::OnStart()
{
	// 無し
}
//==================================
// 移動状態更新関数
//==================================
void CPlayerStateMove::OnUpdate()
{
#if 0
	// キー入力を取得	
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad* pPad = CManager::GetJoyPad();

	// 移動処理実行
	// m_pPlayer->UpdateMove(MeshPos, pInput, pPad);

	// キー入力が無い
	if (!m_pPlayer->isMoveInputKey(pInput) && !m_pPlayer->isMovePadButton(pPad)
		&& m_pPlayer->GetNowMotion() != CPlayer::MOTION_DAMAGE)
	{
		// ニュートラルに遷移
		m_pPlayer->ChangeState(new CPlayerStateNeutral, ID_NEUTRAL);

		// ここで処理を返す
		return;
	}

	// ジャンプキー入力時にステート変更
	if ((pInput->GetPress(DIK_SPACE) || pPad->GetPress(CJoyPad::JOYKEY_A)) &&
		m_pPlayer->GetNowMotion() != CPlayer::MOTION_DAMAGE		   &&
		!m_pPlayer->IsJumping())
	{
		// ジャンプに遷移
		m_pPlayer->ChangeState(new CPlayerStateJump, ID_JUMP);

		// ここで処理を返す
		return;
	}
#endif
}
//==================================
// 移動状態終了関数
//==================================
void CPlayerStateMove::OnExit()
{
	// 無し
}
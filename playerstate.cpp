//=============================================
//
// �v���C���[��ԊǗ����� [ playerstate.cpp ]
// Author: Asuma Nishio
//
//=============================================

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "playerstate.h"
#include "state.h"
#include "manager.h"
#include "gamemanager.h"
#include "pausemanager.h"
#include "input.h"

//==================================
// �v���C���[��ԃR���X�g���N�^
//==================================
CPlayerStateBase::CPlayerStateBase()
{
	// �l�̃N���A
	m_pPlayer = nullptr;
	m_ID = ID_NEUTRAL;
}
//==================================
// �v���C���[��ԃf�X�g���N�^
//==================================
CPlayerStateBase::~CPlayerStateBase()
{
	// ����
}


//==================================
// �ҋ@��Ԏ��R���X�g���N�^
//==================================
CPlayerStateNeutral::CPlayerStateNeutral()
{
	// �Z�b�g
	SetID(ID_NEUTRAL);
}
//==================================
// �ҋ@��Ԏ��f�X�g���N�^
//==================================
CPlayerStateNeutral::~CPlayerStateNeutral()
{
	// ����
}
//==================================
// �ҋ@��ԊJ�n�֐�
//==================================
void CPlayerStateNeutral::OnStart()
{
#if 0
	// ���O�����n�Ȃ�
	if (m_pPlayer->GetMotion()->GetMotionType() == CPlayer::MOTION_LANDING)
	{
		// �j���[�g�������[�V�����ɐݒ�
		m_pPlayer->GetMotion()->SetMotion(CPlayer::MOTION_NEUTRAL, false, 0, false);
	}
	else
	{
		// �j���[�g�������[�V�����ɐݒ�
		m_pPlayer->GetMotion()->SetMotion(CPlayer::MOTION_NEUTRAL, true, 5, false);
	}
#endif
}
//==================================
// �ҋ@��ԍX�V�֐�
//==================================
void CPlayerStateNeutral::OnUpdate()
{
#if 0
	// �L�[���͏��̎擾
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad* pPad = CManager::GetJoyPad();

	// Damage���͈�ؓ��͂��󂯕t���Ȃ�
	if (m_pPlayer->GetStateMachine()->GetNowStateID() == ID_DAMAGE) return;

	// �ړ����͂�����Έړ���Ԃ�
	if ((m_pPlayer->isMoveInputKey(pInput) || m_pPlayer->isMovePadButton(pPad) || pPad->GetLeftStick()) &&
		m_pPlayer->GetNowMotion() != CPlayer::MOTION_DAMAGE)
	{
		// ��ԕύX
		m_pPlayer->ChangeState(new CPlayerStateMove, ID_MOVE);

		// �����ŏ�����Ԃ�
		return;
	}
#endif
}
//==================================
// �ҋ@��Ԏ��I���֐�
//==================================
void CPlayerStateNeutral::OnExit()
{
	// ����
}


//==================================
// �R���X�g���N�^
//==================================
CPlayerStateAction::CPlayerStateAction()
{
	// �Z�b�g
	SetID(ID_ACTION);
}
//==================================
// �f�X�g���N�^
//==================================
CPlayerStateAction::~CPlayerStateAction()
{
	// ����
}
//==================================
// �U����ԊJ�n�֐�
//==================================
void CPlayerStateAction::OnStart()
{
}
//==================================
// �U����ԍX�V�֐�
//==================================
void CPlayerStateAction::OnUpdate()
{

	// ���͏��̎擾
	CInputKeyboard* pInput = CManager::GetInstance()->GetInputKeyboard();
	CJoyPad * pPad = CManager::GetInstance()->GetJoyPad();
}
//==================================
// �U����ԏI���֐�
//==================================
void CPlayerStateAction::OnExit()
{
	// ����
}


//==================================
// �ړ���ԃR���X�g���N�^
//==================================
CPlayerStateMove::CPlayerStateMove()
{
	// �Z�b�g
	SetID(ID_MOVE);
}
//==================================
// �ړ���ԃf�X�g���N�^
//==================================
CPlayerStateMove::~CPlayerStateMove()
{
	// ����
}
//==================================
// �ړ���ԊJ�n�֐�
//==================================
void CPlayerStateMove::OnStart()
{
	// ����
}
//==================================
// �ړ���ԍX�V�֐�
//==================================
void CPlayerStateMove::OnUpdate()
{
#if 0
	// �L�[���͂��擾	
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad* pPad = CManager::GetJoyPad();

	// �ړ��������s
	// m_pPlayer->UpdateMove(MeshPos, pInput, pPad);

	// �L�[���͂�����
	if (!m_pPlayer->isMoveInputKey(pInput) && !m_pPlayer->isMovePadButton(pPad)
		&& m_pPlayer->GetNowMotion() != CPlayer::MOTION_DAMAGE)
	{
		// �j���[�g�����ɑJ��
		m_pPlayer->ChangeState(new CPlayerStateNeutral, ID_NEUTRAL);

		// �����ŏ�����Ԃ�
		return;
	}

	// �W�����v�L�[���͎��ɃX�e�[�g�ύX
	if ((pInput->GetPress(DIK_SPACE) || pPad->GetPress(CJoyPad::JOYKEY_A)) &&
		m_pPlayer->GetNowMotion() != CPlayer::MOTION_DAMAGE		   &&
		!m_pPlayer->IsJumping())
	{
		// �W�����v�ɑJ��
		m_pPlayer->ChangeState(new CPlayerStateJump, ID_JUMP);

		// �����ŏ�����Ԃ�
		return;
	}
#endif
}
//==================================
// �ړ���ԏI���֐�
//==================================
void CPlayerStateMove::OnExit()
{
	// ����
}
//=====================================================
//
// �j���[�g������ԊǗ����� [ playerstateneutral.cpp ]
// Author: Asuma Nishio
//
//=====================================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "playerstateneutral.h"
#include "manager.h"
#include "input.h"
#include "playerstatemove.h"

//==============================
// �R���X�g���N�^
//==============================
CPlayerStateNeutral::CPlayerStateNeutral()
{
	// ID�Z�b�g
	SetID(ID_NEUTRAL);
}
//==============================
// �f�X�g���N�^
//==============================
CPlayerStateNeutral::~CPlayerStateNeutral()
{

}
//===============================
// �J�n�֐�
//===============================
void CPlayerStateNeutral::OnStart()
{
	// ���[�V�����Z�b�g
	m_pPlayer->GetMotion()->SetMotion(CPlayer::MOTION_NEUTRAL, true, 10);
}
//===============================
// �X�V�֐�
//===============================
void CPlayerStateNeutral::OnUpdate()
{
	// �L�[���͏����擾
	auto pKey = CManager::GetInstance()->GetInputKeyboard();
	auto pPad = CManager::GetInstance()->GetJoyPad();

	// �L�[���͂��������Ȃ�
	if (m_pPlayer->isMoveInputKey(pKey) || m_pPlayer->isMovePadButton(pPad))
	{
		// �ړ���ԂɕύX
		m_pPlayer->ChangeState(new CPlayerStateMove(), ID_MOVE);
		return;
	}
}
//===============================
// �I���֐�
//===============================
void CPlayerStateNeutral::OnExit()
{

}
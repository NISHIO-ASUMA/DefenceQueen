//=============================================
//
// �ړ���ԊǗ����� [ playerstatemove.cpp ]
// Author: Asuma Nishio
//
//=============================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "playerstatemove.h"
#include "manager.h"
#include "input.h"

//===============================
// �R���X�g���N�^
//===============================
CPlayerStateMove::CPlayerStateMove()
{
	// ID�Z�b�g
	SetID(ID_MOVE);
}
//===============================
// �f�X�g���N�^
//===============================
CPlayerStateMove::~CPlayerStateMove()
{

}
//===============================
// �J�n�֐�
//===============================
void CPlayerStateMove::OnStart()
{
	// ���[�V�����Z�b�g
	m_pPlayer->GetMotion()->SetMotion(CPlayer::MOTION_MOVE, true, 5);
}
//===============================
// �X�V�֐�
//===============================
void CPlayerStateMove::OnUpdate()
{
	// �L�[���͏����擾
	auto pKey = CManager::GetInstance()->GetInputKeyboard();
	auto pPad = CManager::GetInstance()->GetJoyPad();

	// �ړ��X�V�֐�
	m_pPlayer->MoveKey(pKey, pPad);
}
//===============================
// �I���֐�
//===============================
void CPlayerStateMove::OnExit()
{

}
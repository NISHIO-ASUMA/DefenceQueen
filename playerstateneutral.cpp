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

}
//===============================
// �I���֐�
//===============================
void CPlayerStateNeutral::OnExit()
{

}
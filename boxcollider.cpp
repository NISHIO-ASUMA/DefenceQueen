//===============================================
//
// ��`�̃R���C�_�[���� [ boxcollider.cpp ]
// Author: Asuma Nishio
//
//===============================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "boxcollider.h"

//==============================
// �R���X�g���N�^
//==============================
CBoxCollider::CBoxCollider() : m_BoxInfo{}
{

}
//==============================
// �f�X�g���N�^
//==============================
CBoxCollider::~CBoxCollider()
{
	// ����
}
//==============================
// ��`��������
//==============================
CBoxCollider* CBoxCollider::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 posold, const D3DXVECTOR3 size)
{
	// �C���X�^���X����
	CBoxCollider* pCollider = new CBoxCollider;
	if (pCollider == nullptr) return nullptr;

	// �l���Z�b�g
	pCollider->SetPos(pos);
	pCollider->m_BoxInfo.posOld = posold;
	pCollider->m_BoxInfo.Size = size;

	// �������ꂽ�|�C���^��Ԃ�
	return pCollider;
}
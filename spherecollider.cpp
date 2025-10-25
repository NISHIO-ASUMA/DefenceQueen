//===============================================
//
// ���`�R���C�_�[���� [ spherecollider.cpp ]
// Author: Asuma Nishio
//
//===============================================

//**********************
// �C���N���[�t�@�C��
//**********************
#include "spherecollider.h"

//===========================
// �R���X�g���N�^
//===========================
CSphereCollider::CSphereCollider() : m_fRadius(NULL)
{
	// �l�̃N���A
}
//===========================
// �f�X�g���N�^
//===========================
CSphereCollider::~CSphereCollider()
{

}
//===========================
// ���`�R���C�_�[��������
//===========================
CSphereCollider* CSphereCollider::Create(D3DXVECTOR3 pos, float fRadius)
{
	// �C���X�^���X����
	CSphereCollider* pSphere = new CSphereCollider;
	if (pSphere == nullptr) return nullptr;

	// �l���Z�b�g
	pSphere->SetPos(pos);
	pSphere->m_fRadius = fRadius;

	// �������ꂽ�|�C���^
	return pSphere;
}
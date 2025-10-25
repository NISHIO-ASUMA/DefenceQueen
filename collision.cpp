//=============================================
//
// �����蔻���ꏈ���N���X [ collision.cpp ]
// Author: Asuma Nishio
// 
//==============================================

//*****************************
// �C���N���[�h�t�@�C��
//*****************************
#include "collision.h"

//==============================================
// �R���X�g���N�^
//==============================================
CCollision::CCollision(TYPE type) : m_Type(type),m_pos(VECTOR3_NULL)
{
	// �l�̃N���A
}
//==============================================
// �f�X�g���N�^
//==============================================
CCollision::~CCollision()
{
	// ����
}
//==============================================
// �R���W������������
//==============================================
CCollision* CCollision::Create(D3DXVECTOR3 pos, TYPE Type)
{
	// �C���X�^���X����
	CCollision* pCollision = new CCollision(Type);
	if (pCollision == nullptr) return nullptr;

	// �l���Z�b�g
	pCollision->SetPos(pos);
	pCollision->SetType(Type);

	// �������ꂽ�|�C���^
	return pCollision;
}

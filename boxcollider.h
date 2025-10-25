//===============================================
//
// ��`�̃R���C�_�[���� [ boxcollider.h ]
// Author: Asuma Nishio
//
//===============================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "collider.h"

//***************************
// ��`�̃R���C�_�[�ݒ菈��
//***************************
class CBoxCollider : public CCollider
{
public:

	//*********************************
	// �R���C�_�[�Ŏg�p����ϐ��\����
	//*********************************
	struct BoxColliderInfo
	{
		D3DXVECTOR3 posOld;// �O��̍��W
		D3DXVECTOR3 Size;  // �R���C�_�[�̑傫��
	};
	
	CBoxCollider();
	~CBoxCollider();

	BoxColliderInfo GetInfo(void) const { return m_BoxInfo; }

	static CBoxCollider* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 posold, const D3DXVECTOR3 size);

private:
	BoxColliderInfo m_BoxInfo; // �\���̕ϐ�
};


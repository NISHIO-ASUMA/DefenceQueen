//===============================================
//
// �R���C�_�[��ꏈ�� [ collider.h ]
// Author: Asuma Nishio
//
//===============================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//******************************
// �R���C�_�[�N���X���`
//******************************
class CCollider
{
public:
	CCollider();
	virtual ~CCollider();

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPos(void) const { return m_pos; }

protected:
	D3DXVECTOR3 m_pos; // �R���C�_�[�ݒ�p���W( �S�N���X�ŋ��L�����̕ϐ� )
};
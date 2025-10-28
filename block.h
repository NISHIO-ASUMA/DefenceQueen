//=====================================
//
// �u���b�N���� [ block.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "objectX.h"

//**********************
// �O���錾
//**********************
class CBoxCollider;

//**********************************
// �u���b�N�I�u�W�F�N�g�N���X���`
//**********************************
class CBlock : public CObjectX
{
public:
	CBlock(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CBlock();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(CBoxCollider * pOther,D3DXVECTOR3 * OutPos);

	static CBlock* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 scale, const char* pModelName);

private:
	CBoxCollider* m_pCollider;	// ����������`�̃R���C�_�[
};


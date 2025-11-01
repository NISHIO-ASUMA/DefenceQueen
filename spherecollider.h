//===============================================
//
// ���`�R���C�_�[���� [ spherecollider.h ]
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

//********************************
// ���`�R���C�_�[�N���X���`
//********************************
class CSphereCollider : public CCollider
{
public:

	CSphereCollider();
	~CSphereCollider();

	void SetRadius(float fRadius) { m_fRadius = fRadius; }
	float GetRadius(void) { return m_fRadius; }

	static CSphereCollider* Create(D3DXVECTOR3 pos, float fRadius);

private:

	float m_fRadius; // �����锼�a
};


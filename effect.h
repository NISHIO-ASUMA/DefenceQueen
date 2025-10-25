//====================================
//
// �G�t�F�N�g���� [ effect.h ]
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
#include "billboard.h"

//*************************************************
// �G�t�F�N�g�N���X���`
//*************************************************
class CEffect : public CBillboard
{
public:
	CEffect(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CEffect();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetLife(int nLife) { m_nLife = nLife; }

	int GetLife(void) { return m_nLife; }

	static CEffect* Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius);

private:
	int m_nLife;		// ����
	float m_fRadius;	// ���a
	D3DXVECTOR3 m_move;	// �ړ���
};
